#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "rlibsc.h"
#include <time.h>

#define REP5(x) x x x x x
#define REP10(x) REP5(x) REP5(x)

static __attribute__((always_inline)) inline
uint64_t timespec_to_ns(const struct timespec *ts)
{
    return (uint64_t)ts->tv_sec * UINT64_C(1000000000)
         + (uint64_t)ts->tv_nsec;
}

static __attribute__((always_inline)) inline uint64_t read_ns(void)
{
    struct timespec ts;
    asm volatile("fence rw, rw" ::: "memory");
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts); // thread cpu time id or process cpu time id
    asm volatile("fence rw, rw" ::: "memory");
    return timespec_to_ns(&ts);
}

char __attribute__((aligned(4096))) buffer[4096 * 32];
static inline void evict(void *addr) {
  int i = 1;
  REP10(maccess(buffer + i++ * 4096);)
}

char __attribute__((aligned(4096))) target[4096];

int main() {
  memset(target, 1, sizeof(target));
  memset(buffer, 2, sizeof(buffer));
  for (int i = 0; i < 2; i++) {
    if (i == 0)
      printf("[ No Walk ]\n");
    else
      printf("[ Walk ]\n");
    size_t sum = 0, min = -1;
    int64_t sum_clock_fixed = 0, min_clock_fixed = -1;
    for (int avg = 0; avg < 10; avg++) {
      if (i == 0)
        maccess(target + 256);
      else
        evict(target);
      uint64_t start_clock_fixed = read_ns();
      size_t before = rdinstret();
      maccess(target);
      size_t after = rdinstret();
      uint64_t end_clock_fixed = read_ns();
      size_t delta = after - before;
      sum += delta;
      if (delta < min)
        min = delta;
      delta = end_clock_fixed - start_clock_fixed;
      sum_clock_fixed += delta;
      if (delta < min_clock_fixed)
	min_clock_fixed = delta;      
    }
    printf("Retired: %zd (avg: %zd) | Time (clock_fixed): %zd (avg: %zd)\n", min, sum / 10,
	   min_clock_fixed, sum_clock_fixed / 10);
  }
}
