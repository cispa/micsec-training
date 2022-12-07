#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "cacheutils.h"

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

  while (1) {
    printf("Enter character to send: ");
    fflush(stdout);
    int current_char = getchar();
    int newline = getchar();
    printf("Sent '%c'\n", current_char);
    if (current_char == EOF) {
      printf("Stopping sender.\n");
    }
    maccess(mem + current_char * PAGESIZE);
  }

  return 0;
}
