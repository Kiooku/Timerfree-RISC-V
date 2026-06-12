#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

int main(void) {

    char msg_buf[MESSAGE_MAX_LEN + 2];
        // Wait until receiver has created shared memory (ready == 1)
    printf("[sender] Opening shared memory (waiting for receiver)...\n");
    int fd = -1;
    void *map = MAP_FAILED;
    struct shared_area *sh = NULL;

    for (int retry = 0; retry < 10000; retry++) {
        fd = shm_open(SHM_NAME, O_RDWR, 0666);
        if (fd >= 0) {
            map = mmap(NULL, sizeof(struct shared_area),
                       PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            if (map != MAP_FAILED) {
                sh = (struct shared_area*)map;
                break;
            } else {
                close(fd);
                fd = -1;
            }
        }
        usleep(1000); // wait 1ms and retry
    }

    if (!sh) {
        fprintf(stderr, "[sender] failed to open shared memory after retries: %s\n", strerror(errno));
        return 1;
    }

    while (1) { 
    printf("[sender] Type the secret message (max %d chars) and press Enter:\n", MESSAGE_MAX_LEN);
    if (!fgets(msg_buf, sizeof(msg_buf), stdin)) {
        fprintf(stderr, "[sender] no input\n");
        return 1;
    }
    // strip newline
    size_t len = strlen(msg_buf);
    if (len > 0 && msg_buf[len-1] == '\n') { msg_buf[len-1] = '\0'; len--; }

    if (len == 0) {
        fprintf(stderr, "[sender] empty message, aborting\n");
        return 1;
    }
    if (len > MESSAGE_MAX_LEN) {
        fprintf(stderr, "[sender] message too long (max %d)\n", MESSAGE_MAX_LEN);
        return 1;
    }

    // confirm receiver presence
    int ready = 0;
    for (int i = 0; i < 5000; i++) {
        ready = __atomic_load_n(&sh->ready, __ATOMIC_SEQ_CST);
        if (ready == 1) break;
        usleep(1000);
    }
    if (ready != 1) {
        fprintf(stderr, "[sender] receiver not ready (ready=%d)\n", ready);
        munmap(map, sizeof(struct shared_area));
        close(fd);
        return 1;
    }

    printf("[sender] Shared memory opened. Sending message (%zu bytes): \"%s\"\n", len, msg_buf);

    // write msg_len so receiver knows how many bytes to expect
    __atomic_store_n(&sh->msg_len, (int)len, __ATOMIC_SEQ_CST);

    // small stabilization before starting
    fence_all();
    tiny_delay();

    // For each byte, send 8 bits LSB-first.
    for (size_t b = 0; b < len; b++) {
        unsigned char c = (unsigned char)msg_buf[b];
        for (int k = 0; k < 8; k++) {
            int bit = (c >> k) & 1; // LSB-first

            // wait until it's our turn (turn == 0)
            while (__atomic_load_n(&sh->turn, __ATOMIC_SEQ_CST) != 0) {
                // optional: check receiver alive
                usleep(50);
            }

            // store for debug
            __atomic_store_n(&sh->bit_value, bit, __ATOMIC_SEQ_CST);

            if (bit) {
                prefetch_w_ptr(sh->target_line);
                // ensure it's touched
                volatile uint8_t tmp = sh->target_line[0]; (void)tmp;
            } else {
                cbo_flush_ptr(sh->target_line);
                // a second flush to be extra robust
                cbo_flush_ptr(sh->target_line);
            }

            fence_all();
            tiny_delay();

            // signal receiver to measure
            __atomic_store_n(&sh->turn, 1, __ATOMIC_SEQ_CST);
        }
    }
    // mark done
    __atomic_store_n(&sh->done, 1, __ATOMIC_SEQ_CST);

    printf("[sender] Finished sending.\n");

}
    // // mark done
    // __atomic_store_n(&sh->done, 1, __ATOMIC_SEQ_CST);

    printf("[sender] Finished sending. Cleaning up map.\n");

    munmap(map, sizeof(struct shared_area));
    close(fd);

    return 0;
}
