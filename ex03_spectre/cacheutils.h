#ifndef _CACHEUTILS_H_
#define _CACHEUTILS_H_

#include <stdint.h>

#define PAGESIZE 4096

uint64_t rdtsc() {
  uint64_t a, d = 0;

  asm volatile("mfence");
  asm volatile("rdtsc" : "=a"(a), "=d"(d));
  asm volatile("mfence");

  a = (d << 32) | a;
  return a;
}


void flush(void *p) {
  asm volatile("clflush 0(%0)\n" : : "c"(p) : "rax");
}

void fence() {
  asm volatile("mfence\n" : : : "memory");
}

void maccess(void *p) {
  asm volatile("movq (%0), %%rax\n" : : "c"(p) : "rax");
}

size_t flush_reload(void* addr) {
  uint64_t start = 0, end = 0;
  start = rdtsc();
  maccess(addr);
  end = rdtsc();

  flush(addr);

  return end - start;
}

size_t reload(void* addr) {
  uint64_t start = 0, end = 0;
  start = rdtsc();
  maccess(addr);
  end = rdtsc();
  return end - start;
}


size_t calibrate_flush_reload() {
  size_t reload_time = 0, flush_reload_time = 0, i, count = 1000000;
  size_t dummy[16];
  size_t *ptr = dummy + 8;

  maccess(ptr);
  for (i = 0; i < count; i++) {
    reload_time += reload(ptr);
  }
  for (i = 0; i < count; i++) {
    flush_reload_time += flush_reload(ptr);
  }
  reload_time /= count;
  flush_reload_time /= count;

  return (flush_reload_time + reload_time * 2) / 3;
}


#endif
