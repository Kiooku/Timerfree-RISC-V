#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "rlibsc.h"
#include <time.h>
#include <pthread.h>

#define REP5(x) x x x x x
#define REP10(x) REP5(x) REP5(x)

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

static inline uint64_t read_counter(void)
{
    uint64_t v;
    asm volatile("fence" ::: "memory");
    v = sw_counter;
    asm volatile("fence" ::: "memory");
    return v;
}

char __attribute__((aligned(4096))) buffer[4096 * 32];
static inline void evict(void *addr) {
  int i = 1;
  REP10(maccess(buffer + i++ * 4096);)
}

char __attribute__((aligned(4096))) target[4096];

int main() {
  /* Start software counter thread BEFORE doing any measurements            */
  pthread_t tid;
  if (pthread_create(&tid, NULL, counter_thread_fn, NULL) != 0) {
      perror("pthread_create");
      return 1;
  }

  /* Allow counter thread to reach steady-state speed                       */
  struct timespec ts = {0, 10000000L};   /* 10 ms                          */
  nanosleep(&ts, NULL);

  memset(target, 1, sizeof(target));
  memset(buffer, 2, sizeof(buffer));
  for (int i = 0; i < 2; i++) {
    if (i == 0)
      printf("[ No Walk ]\n");
    else
      printf("[ Walk ]\n");
    size_t sum = 0, min = -1;
    int64_t sum_thread = 0, min_thread = 0;
    for (int avg = 0; avg < 10; avg++) {
      if (i == 0)
        maccess(target + 256);
      else
        evict(target);
      uint64_t start_thread = read_counter();
      size_t before = rdinstret();
      maccess(target);
      size_t after = rdinstret();
      uint64_t end_thread = read_counter();
      size_t delta = after - before;
      sum += delta;
      if (delta < min)
        min = delta;
      delta = end_thread - start_thread;
      sum_thread += delta;
      if (delta < min_thread)
	min_thread = delta;      
    }
    printf("Retired: %zd (avg: %zd) | Time (thread) %zd (avg: %zd)\n", min, sum / 10,
	   min_thread, sum_thread / 10);
  }
}
