#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 16

unsigned char buffer[BUFFER_SIZE];
unsigned char lineBuffer[BUFFER_SIZE];
ssize_t byteRead = 0;
int byteCount = 0;
int offset = 0;

void Asciirep(int c) {
  for (int i = 0; i < c; ++i) {
    printf("%c",
           (lineBuffer[i] >= 32 && lineBuffer[i] <= 126) ? lineBuffer[i] : '.');
  }
  printf("\n");
}

int main(int argc, char **argv) {
  int fileDescriptor = STDIN_FILENO;
  if (argc > 2)
    return 1;
  if (argc == 2) {
    fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor == -1)
      return 1;
  }

  while ((byteRead = read(fileDescriptor, buffer, BUFFER_SIZE)) > 0) {
    for (int i = 0; i < byteRead; i++) {
      if (byteCount == 0) {
        printf("%08x :", offset);
        offset += BUFFER_SIZE;
      }
      printf("%02x", buffer[i]);
      if (byteCount % 2 == 1)
        printf(" ");
      lineBuffer[byteCount] = buffer[i];
      byteCount = (byteCount + 1) % BUFFER_SIZE;
      if (byteCount == 0) {
        printf(" ");
        Asciirep(BUFFER_SIZE);
      }
    }
  }

  if (byteCount > 0) {
    printf(" ");
    for (int i = byteCount; i < BUFFER_SIZE; i++) {
      printf("  ");
      if (i % 2 == 1) {
        printf(" ");
      }
      Asciirep(BUFFER_SIZE);
    }
  }
  return 0;
}
