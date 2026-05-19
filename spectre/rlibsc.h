#ifndef CACHE_UTILS_H
#define CACHE_UTILS_H

#include <stddef.h>
#include <stdint.h>

// ============================================================================
// Common macros – repeat a token many times (for unrolling)
// ============================================================================
#define REP1(x) x
#define REP2(x) x x
#define REP3(x) x x x
#define REP4(x) x x x x
#define REP5(x) x x x x x
#define REP6(x) x x x x x x
#define REP8(x) REP4(x) REP4(x)
#define REP10(x) REP5(x) REP5(x)
#define REP16(x) REP8(x) REP8(x)
#define REP20(x) REP10(x) REP10(x)
#define REP100(x)                                                              \
  REP10(x) REP10(x) REP10(x) REP10(x) REP10(x) REP10(x) REP10(x) REP10(x)      \
  REP10(x) REP10(x)
#define REP1K(x)                                                               \
  REP100(x) REP100(x) REP100(x) REP100(x) REP100(x) REP100(x) REP100(x)        \
  REP100(x) REP100(x) REP100(x)
#define REP64(x) REP8(x) REP8(x) REP8(x) REP8(x) REP8(x) REP8(x) REP8(x) REP8(x)
#define REP512(x)                                                              \
  REP64(x) REP64(x) REP64(x) REP64(x) REP64(x) REP64(x) REP64(x) REP64(x)
#define REP4K(x) REP512(x) REP512(x) REP512(x) REP512(x) REP512(x) REP512(x)   \
                  REP512(x) REP512(x)

// ============================================================================
// Common RISC-V CSR / pseudo-instruction access
// ============================================================================

// Read instructions retired (via pseudo-instruction)
static inline size_t rdinstret(void) {
  size_t val;
  asm volatile("rdinstret %0" : "=r"(val));
  return val;
}

// Read cycle counter (via pseudo-instruction)
static inline size_t rdcycle(void) {
  size_t val;
  asm volatile("rdcycle %0" : "=r"(val));
  return val;
}

// Access a memory location (load into a7, clobber a7 and memory)
static inline void maccess(void *addr) {
  asm volatile("ld a7, (%0)" : : "r"(addr) : "a7", "memory");
}

// Instruction cache fence (fence.i)
static inline void fencei(void) {
  asm volatile("fence.i");
}

// Read time CSR (64-bit)
static inline uint64_t rdtime(void) {
  uint64_t val;
  asm volatile("rdtime %0" : "=r"(val));
  return val;
}

// Read cycle CSR explicitly
static inline uint64_t get_cycle_perf(void) {
  uint64_t val;
  asm volatile("csrr %0, cycle" : "=r"(val));
  return val;
}

// Read time CSR explicitly
static inline uint64_t get_time_perf(void) {
  uint64_t val;
  asm volatile("csrr %0, time" : "=r"(val));
  return val;
}

// Read instret CSR explicitly
static inline uint64_t get_retire_perf(void) {
  uint64_t val;
  asm volatile("csrr %0, instret" : "=r"(val));
  return val;
}

// Simple counter loop (prevents optimization)
static uint64_t count_thread(uint64_t spins) {
  uint64_t val = 0;
  for (uint64_t i = 0; i < spins; i++) {
    val++;
    asm volatile("" ::: "memory"); // prevent loop removal
  }
  return val;
}

// Fence (all memory operations)
static inline void fence(void) {
  asm volatile("fence" ::: "memory");
}

// ============================================================================
// Architecture‑specific cache maintenance
// ============================================================================

// ----------------------------------------------------------------------------
// T‑Head C906 / C910 (custom encodings)
// ----------------------------------------------------------------------------
#if defined(C906) || defined(C910)

// Flush a virtual address from the data cache (DCACHE.CIVA a7)
static inline void flush(void *addr) {
  asm volatile("xor a7, a7, a7\n"
               "add a7, a7, %0\n"
               ".long 0x278800b"          // DCACHE.CIVA a7
               : : "r"(addr) : "a7", "memory");
}

// Flush a virtual address from the instruction cache (ICACHE.IVA a7)
static inline void iflush(void *addr) {
  asm volatile("xor a7, a7, a7\n"
               "add a7, a7, %0\n"
               ".long 0x308800b"          // ICACHE.IVA a7
               : : "r"(addr) : "a7", "memory");
}

// ----------------------------------------------------------------------------
// Generic RISC‑V (using standard extensions if available)
// ----------------------------------------------------------------------------
#else

// If the Zicbom extension is available, use cbo.flush; otherwise do nothing.
// (Define USE_ZICBOM to enable it.)
//#ifdef USE_ZICBOM
//static inline void flush(void *addr) {
  // Some platforms require the address to be cache‑line aligned.
  // Uncomment the alignment if needed:
  // uintptr_t aligned = (uintptr_t)addr & ~(64 - 1);
  //asm volatile("cbo.flush 0(%0)" : : "r"(addr) : "memory");
//}
//#else
//static inline void flush(void *addr) {
//  (void)addr;               // ignore address
//  fence();                  // at least ensure ordering
//}
//#endif // USE_ZICBOM

static inline void flush(void *addr) {
  asm volatile("xor a7, a7, a7\n"
               "add a7, a7, %0\n"
               ".long 0x278800b"          // DCACHE.CIVA a7
               : : "r"(addr) : "a7", "memory");
}

// Instruction cache flush – always use fence.i
static inline void iflush(void *addr) {
  (void)addr;
  fencei();
}

#endif // C906 || C910

#endif // CACHE_UTILS_H
