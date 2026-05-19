#ifndef CACHEUTILS_H
#define CACHEUTILS_H

#define MAX(X,Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X,Y) (((X) < (Y)) ? (X) : (Y))

unsigned long probe_timing(char *adrs) {
    volatile unsigned long time;

    asm __volatile__(
        "    mfence             \n"
        "    lfence             \n"
        "    rdtsc              \n"
        "    lfence             \n"
        "    movl %%eax, %%esi  \n"
        "    movl (%1), %%eax   \n"
        "    lfence             \n"
        "    rdtsc              \n"
        "    subl %%esi, %%eax  \n"
        "    clflush 0(%1)      \n"
        : "=a" (time)
        : "c" (adrs)
        : "%esi", "%edx"
    );
    return time;
}

unsigned long long rdcycle() {
	size_t val;
	asm volatile ("mfence" ::: "memory");
	asm volatile ("rdcycle %0" : "=r"(val));
	asm volatile ("mfence" ::: "memory");
	return val;
}

void maccess(void* pointer)
{
  volatile uint32_t value;
    asm volatile ("lw %0, 0(%1)\n\t"
        : "=r" (value)
        : "r" (pointer)
        );
}

void flush(void* addr) {
    asm volatile("xor a7, a7, a7\n"
               "add a7, a7, %0\n"
               ".long 0x278800b"          // DCACHE.CIVA a7
               : : "r"(addr) : "a7", "memory");
}

#endif


