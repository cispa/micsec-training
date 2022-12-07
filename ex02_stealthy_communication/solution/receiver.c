#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "cacheutils.h"

///
/// Bijective permutation of input and output (useful to prevent prefetching effects)
///
size_t get_permutated_index(size_t original_idx) {
  return ((original_idx * 167u) + 13u) & 255u;
}

int main(int argc, char* argv[]) {

  // open file "./sharedmem" as shared memory region between sender and receiver
  int fd = open("./sharedmem", O_RDONLY);
  if (fd <= 0) {
    fprintf(stderr, "Could not open ./sharedmem. Did you run 'make'?\n");
  }
  char* mem = (char*)mmap(0, PAGESIZE * 256, PROT_READ, MAP_SHARED, fd, 0);
  if (mem == MAP_FAILED) {
    fprintf(stderr, "Could not open ./sharedmem. Did you run 'make'?\n");
  }


  // get cache miss threshold
  uint64_t cache_miss = calibrate_flush_reload();

  while (1) {
    for (size_t i = 0; i < 256; i++) {
      // iterate in pseudorandom order to prevent interference
      // from hardware prefetchers
      size_t idx = get_permutated_index(i);
      uint64_t before = rdtsc();
      maccess(mem + idx * PAGESIZE);
      uint64_t after = rdtsc();
      flush(mem + idx * PAGESIZE);
      if (after - before < cache_miss) {
        printf("Received '%c'\n", idx);
      }
    }
  }
  
  return 0;
}
