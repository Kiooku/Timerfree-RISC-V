// receiver.c
// Compile:
// riscv64-unknown-elf-gcc -O2 -march=rv64gc -pthread -o receiver receiver.c

#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(void) {
    printf("[receiver] Creating/opening shared memory '%s'...\n", SHM_NAME);

    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd < 0) { perror("shm_open"); return 1; }

    if (ftruncate(fd, sizeof(struct shared_area)) < 0) {
        perror("ftruncate"); close(fd); return 1;
    }

    void *map = mmap(NULL, sizeof(struct shared_area),
                     PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap"); close(fd); return 1;
    }
    struct shared_area *sh = (struct shared_area*)map;
while (1)
{
        // initialize control fields (use atomic stores)
    __atomic_store_n(&sh->ready, 1, __ATOMIC_SEQ_CST);
    __atomic_store_n(&sh->turn, 0, __ATOMIC_SEQ_CST);
    __atomic_store_n(&sh->bit_value, 0, __ATOMIC_SEQ_CST);
    __atomic_store_n(&sh->msg_len, 0, __ATOMIC_SEQ_CST);
    __atomic_store_n(&sh->done, 0, __ATOMIC_SEQ_CST);

    // init cache line content
    memset(sh->target_line, 0xAA, CACHELINE);
    fence_all();

    printf("[receiver] Shared memory ready. Calibrating...\n");

    // calibration: gather cached and evicted samples
    const int trials = 80;
    uint64_t sum_cached = 0, sum_evicted = 0;

    // Ensure cached samples
    for (int i = 0; i < 5; i++) {
        volatile uint8_t tmp = sh->target_line[0]; (void)tmp;
    }
    fence_all();
    for (int i = 0; i < trials; i++) sum_cached += measure_access_cycles(sh->target_line);

    // Evicted samples
    for (int i = 0; i < 5; i++) { cbo_flush_ptr(sh->target_line); fence_all(); }
    for (int i = 0; i < trials; i++) {
        sum_evicted += measure_access_cycles(sh->target_line);
        cbo_flush_ptr(sh->target_line);
        fence_all();
    }

    uint64_t avg_c = sum_cached / trials;
    uint64_t avg_e = sum_evicted / trials;
    uint64_t threshold = (avg_c + avg_e) / 2;
    if (threshold <= avg_c) threshold = avg_c + 1;

    printf("[receiver] Calibration done: avg_cached=%llu avg_evicted=%llu threshold=%llu\n",
           (unsigned long long)avg_c, (unsigned long long)avg_e, (unsigned long long)threshold);

    // Wait for sender to set msg_len > 0
    printf("[receiver] Waiting for sender to provide message (msg_len > 0)...\n");
    int msg_len = 0;
    while (1) {
        msg_len = __atomic_load_n(&sh->msg_len, __ATOMIC_SEQ_CST);
        if (msg_len != 0) break;
        // also check if sender already set done (edge case)
        int done = __atomic_load_n(&sh->done, __ATOMIC_SEQ_CST);
        if (done) { fprintf(stderr, "[receiver] detected done with no msg_len\n"); break; }
        usleep(1000);
    }

    if (msg_len <= 0 || msg_len > MESSAGE_MAX_LEN) {
        fprintf(stderr, "[receiver] invalid msg_len=%d\n", msg_len);
        munmap(map, sizeof(struct shared_area));
        close(fd);
        return 1;
    }

    printf("[receiver] Starting to receive %d bytes (%d bits)...\n", msg_len, msg_len*8);

    int total_bits = msg_len * 8;
    int *bits = calloc(total_bits, sizeof(int));
    if (!bits) { perror("calloc"); munmap(map, sizeof(struct shared_area)); close(fd); return 1; }

    for (int i = 0; i < total_bits; i++) {
        // wait for sender to signal (turn == 1)
        while (__atomic_load_n(&sh->turn, __ATOMIC_SEQ_CST) != 1) {
            // check if sender died
            int done = __atomic_load_n(&sh->done, __ATOMIC_SEQ_CST);
            if (done) break;
            // small sleep to avoid burning cycles
            usleep(100);
        }

        fence_all();
        uint64_t access = measure_access_cycles(sh->target_line);
        int bit = (access < threshold) ? 1 : 0;
        bits[i] = bit;

        // optional debug store
        __atomic_store_n(&sh->bit_value, bit, __ATOMIC_SEQ_CST);

        printf("[receiver] bit %3d: measured=%3llu => %d\n", i+1, (unsigned long long)access, bit);

        // give control back to sender
        __atomic_store_n(&sh->turn, 0, __ATOMIC_SEQ_CST);
    }

    // reconstruct message LSB-first per byte
    char *out = calloc(msg_len + 1, 1);
    if (!out) { perror("calloc2"); free(bits); munmap(map, sizeof(struct shared_area)); close(fd); return 1; }

    for (int b = 0; b < msg_len; b++) {
        unsigned char v = 0;
        for (int k = 0; k < 8; k++) {
            int bit = bits[b*8 + k];
            v |= (bit & 1) << k;
        }
        out[b] = (char)v;
    }
    out[msg_len] = '\0';

    printf("[receiver] Recovered message: \"%s\"\n", out);

    // mark done
    __atomic_store_n(&sh->done, 1, __ATOMIC_SEQ_CST);

    free(bits);
    free(out);
    }
    
    // keep SHM for reuse; optionally call shm_unlink(SHM_NAME) if you want to remove it
    munmap(map, sizeof(struct shared_area));
    close(fd);

    printf("[receiver] Finished.\n");

    return 0;
}
