
#ifndef SHARED_H
#define SHARED_H

#define _GNU_SOURCE
#include <stdint.h>
#define CACHELINE 64
#define SHM_NAME "/prefetch_cbo_shm_v2_fix"

// Maximum ASCII message length (both sides must use same value)
#define MESSAGE_MAX_LEN 128
#define MAX_BITS (MESSAGE_MAX_LEN * 8)

// Shared layout placed in POSIX shared memory.
// Use plain ints in shared memory and access them with __atomic builtins
struct shared_area {
    int ready;      // receiver sets to 1 after creating SHM (use atomic stores)
    int turn;       // 0 = sender may act, 1 = receiver may act
    int bit_value;  // latest bit value (for optional debug)
    int msg_len;    // number of bytes sender will send (0 until sender starts)
    int done;       // sender sets to 1 when finished
    uint8_t target_line[CACHELINE] __attribute__((aligned(CACHELINE)));
};

// full fence (serializing)
static inline void fence_all(void) {
    asm volatile("fence rw, rw" ::: "memory");
}

// tiny delay to stabilize cache state under single-core scheduling
static inline void tiny_delay(void) {
    for (volatile int i = 0; i < 400; i++);
    asm volatile("fence rw, rw" ::: "memory");
}

// rdcycle
static inline uint64_t rdcycle64(void) {
    uint64_t v;
    asm volatile("rdcycle %0" : "=r"(v));
    return v;
}


/* ============================================================
 * PREFETCH (prefetch_w_ptr)
 * ============================================================
 *
 * If C910 → emulate by ld
 * Else    → prefetch.w + t0
 */

#ifdef C910

// C910: emulate with load (triggers HW prefetch)
static inline void prefetch_w_ptr(void *p) {
    asm volatile(
        "ld t0, 0(%0)\n\t"
        : : "r"(p) : "t0", "memory"
    );
    asm volatile("fence rw, rw" ::: "memory");
}

#else

// Normal systems: use real prefetch.w
static inline void prefetch_w_ptr(void *p) {
    asm volatile(
        "mv t0, %0\n\t"
        "prefetch.w 0(t0)\n\t"
        : : "r"(p) : "t0", "memory"
    );
    asm volatile("fence rw, rw" ::: "memory");
}

#endif



/* ============================================================
 * CBO.FLUSH
 * ============================================================
 *
 * If C910 → use T-Head DCACHE.CIVA
 * Else    → use real cbo.flush
 */

#ifdef C910

static inline void cbo_flush_ptr(void *p) {
    asm volatile(
        "xor a7, a7, a7\n"
        "add a7, a7, %0\n"
        ".long 0x278800b\n"   // DCACHE.CIVA a7
        : : "r"(p) : "a7", "memory"
    );
    asm volatile("fence rw, rw" ::: "memory");
}

#else

static inline void cbo_flush_ptr(void *p) {
    asm volatile(
        "mv t0, %0\n\t"
        "cbo.flush 0(t0)\n\t"
        : : "r"(p) : "t0", "memory"
    );
    asm volatile("fence rw, rw" ::: "memory");
}

#endif



/* ============================================================
 * ICACHE flush (iflush)
 * ============================================================
 */

#ifdef C910

static inline void iflush(void *addr) {
    asm volatile(
        "xor a7, a7, a7\n"
        "add a7, a7, %0\n"
        ".long 0x308800b\n"   // ICACHE.IVA a7
        : : "r"(addr) : "a7", "memory"
    );
}

#else

static inline void iflush(void *addr) {
    asm volatile("fence.i" ::: "memory");
}

#endif

// measure one access in cycles (simple)
static inline uint64_t measure_access_cycles(void *p) {
    fence_all();
    uint64_t t0 = rdcycle64();
    volatile uint8_t tmp = *(volatile uint8_t*)p;
    (void)tmp;
    uint64_t t1 = rdcycle64();
    fence_all();
    return t1 - t0;
}

#endif // SHARED_H

