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
  // TODO: check every possible character offset and print the correct one
  //  HINT: to prevent the hardware cache-line prefetcher from interferring 
  //  use a permutated index instead of a linearly increasing one
  }
  
  return 0;
}
