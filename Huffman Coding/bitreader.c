#include "bitreader.h"

#include <stdio.h>
#include <stdlib.h>

struct BitReader {
  FILE *underlying_stream;
  uint8_t byte;
  uint8_t bit_position;
};

BitReader *bit_read_open(const char *filename) {
  BitReader *reader = calloc(1, sizeof(BitReader));
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    free(reader);
    return NULL;
  }
  reader->underlying_stream = f;
  reader->byte = 0;
  reader->bit_position = 8;
  return reader;
}

void bit_read_close(BitReader **pbuf) {
  if (*pbuf != NULL) {
    fclose((*pbuf)->underlying_stream);
    free(*pbuf);
    *pbuf = NULL;
  }
}

uint32_t bit_read_uint32(BitReader *buf) {
  uint32_t data = 0x00000000;
  for (int i = 0; i < 32; i++) {
    uint32_t b = bit_read_bit(buf);
    data |= (b << i);
  }
  return data;
}

uint16_t bit_read_uint16(BitReader *buf) {
  uint16_t data = 0x000;
  for (int i = 0; i < 16; i++) {
    uint16_t b = bit_read_bit(buf);
    data |= (b << i);
  }
  return data;
}

uint8_t bit_read_uint8(BitReader *buf) {
  uint8_t byte = 0x00;
  for (int i = 0; i < 8; i++) {
    uint8_t b = bit_read_bit(buf);
    byte |= (b << i);
  }
  return byte;
}

uint8_t bit_read_bit(BitReader *buf) {
  if (buf->bit_position > 7) {
    int next = fgetc(buf->underlying_stream);
    if (next == EOF) {
      return 1;
    }
    buf->byte = (unsigned char)next;
    buf->bit_position = 0;
  }
  uint8_t next = (buf->byte >> buf->bit_position) & 1;
  buf->bit_position += 1;
  return next;
}
