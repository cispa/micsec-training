#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void maccess(void* address) {
  asm volatile("movq (%0), %%rax\n" : : "r"(address) : "rax");
}

void flush(void* address) {
  asm volatile("clflush 0(%0)\n" : : "r"(address));
}

void mfence() {
  asm volatile("mfence\n");
}

size_t rdtsc() {
  int64_t low, high;
  asm volatile("rdtsc\n" : "=a"(low), "=d"(high));
  return high << 32 | low;
}

int min(int a, int b) {
  return a < b ? a : b;
}

#define ITERATIONS_NO 50000
#define MAX_LINESIZE 500

__attribute__((aligned(4096)))
char* addr[4096];

void measure_cache_hits(FILE* logfile_fd) {
  char* line = malloc(MAX_LINESIZE);

  for (size_t i = 0; i < ITERATIONS_NO; i++) {
    int timing = 0;
    // TODO: measure cache hits
    sprintf(line, "hit;%d\n", timing);
    fwrite(line, min(strlen(line), MAX_LINESIZE), 1, logfile_fd);
  }

  free(line);
}

void measure_cache_misses(FILE* logfile_fd) {
  char* line = malloc(MAX_LINESIZE);

  for (size_t i = 0; i < ITERATIONS_NO; i++) {
    int timing = 0;
    // TODO: measure cache misses
    sprintf(line, "miss;%d\n", timing);
    fwrite(line, min(strlen(line), MAX_LINESIZE), 1, logfile_fd);
  }

  free(line);
}

int main(int argc, char* argv[]) {
  FILE* fd = fopen("cache.log", "w");
  measure_cache_hits(fd);
  measure_cache_misses(fd);
  fclose(fd);
  return 0;
}
