#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "rlibsc.h"
#include <time.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>

#define REP5(x) x x x x x
#define REP10(x) REP5(x) REP5(x)

char __attribute__((aligned(4096))) buffer[4096 * 32];
static inline void evict(void *addr) {
  int i = 1;
  REP10(maccess(buffer + i++ * 4096);)
}

char __attribute__((aligned(4096))) target[4096];

int main() {
  // Setup the perf_event_open timer
  static struct perf_event_attr attr;
  attr.type = PERF_TYPE_HARDWARE;
  attr.config = PERF_COUNT_HW_CPU_CYCLES;
  attr.size = sizeof(attr);
  attr.exclude_kernel = 1;
  attr.exclude_hv = 1;
  attr.exclude_callchain_kernel = 1;

  int perf_timer = syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);

  memset(target, 1, sizeof(target));
  memset(buffer, 2, sizeof(buffer));
  for (int i = 0; i < 2; i++) {
    if (i == 0)
      printf("[ No Walk ]\n");
    else
      printf("[ Walk ]\n");
    size_t sum = 0, min = -1;
    long long sum_perf_event_open = 0, min_perf_event_open = -1;
    for (int avg = 0; avg < 10; avg++) {
      if (i == 0)
        maccess(target + 256);
      else
        evict(target);
      long long start_perf_event_open = 0, end_perf_event_open = 0;
      read(perf_timer, &start_perf_event_open, sizeof(start_perf_event_open));
      size_t before = rdinstret();
      maccess(target);
      size_t after = rdinstret();
      read(perf_timer, &end_perf_event_open, sizeof(end_perf_event_open));
      size_t delta = after - before;
      sum += delta;
      if (delta < min)
        min = delta;
      delta = end_perf_event_open - start_perf_event_open;
      sum_perf_event_open += delta;
      if (delta < min_perf_event_open)
        min_perf_event_open = delta;
    }
    printf("Retired: %zd (avg: %zd) | Time (perf_event_open): %lld (avg: %lld)\n", min, sum / 10,
	   min_perf_event_open, sum_perf_event_open / 10);
  }
}
