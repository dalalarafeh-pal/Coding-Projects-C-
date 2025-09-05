#include"bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <getopt.h>
#include <stdio.h>

typedef struct Code {
  uint64_t code;
  uint8_t code_length;
} Code;

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
  for (int i = 0; i < 256; ++i) {
    histogram[i] = 0;
  }

  ++histogram[0x00];
  ++histogram[0xff];

  uint32_t filesize = 0;
  int byte;

  while ((byte = fgetc(fin)) != EOF) {
    ++histogram[byte];
    ++filesize;
  }

  fseek(fin, 0, SEEK_SET);
  return filesize;
}

Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
  if (histogram == NULL) {
    return NULL;
  }

  PriorityQueue *pq = pq_create();

  for (uint16_t i = 0; i < 256; ++i) {
    if (histogram[i] > 0) {
      Node *n_node = node_create((uint8_t)i, histogram[i]);
      enqueue(pq, n_node);
    }
  }

  while (!pq_size_is_1(pq)) {
    Node *left = dequeue(pq);
    Node *right = dequeue(pq);
    Node *n = node_create(0, left->weight + right->weight);
    n->left = left;
    n->right = right;
    enqueue(pq, n);
    (*num_leaves)++;
  }
  Node *tree = dequeue(pq);
  pq_free(&pq);
  (*num_leaves)++;
  return tree;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code,
                     uint8_t code_length) {
  if (node == NULL) {
    return;
  }

  if (node->left == NULL && node->right == NULL) {
    code_table[node->symbol].code = code;
    code_table[node->symbol].code_length = code_length;
    return;
  }

  fill_code_table(code_table, node->left, code, code_length + 1);
  code |= ((uint64_t)1 << code_length);
  fill_code_table(code_table, node->right, code, code_length + 1);
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
  if (node->left == NULL) {
    bit_write_bit(outbuf, 1);
    bit_write_uint8(outbuf, node->symbol);
  } else {
    huff_write_tree(outbuf, node->left);
    huff_write_tree(outbuf, node->right);
    bit_write_bit(outbuf, 0);
  }
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize,
                        uint16_t num_leaves, Node *code_tree,
                        Code *code_table) {
  bit_write_uint8(outbuf, 'H');
  bit_write_uint8(outbuf, 'C');
  bit_write_uint32(outbuf, filesize);
  bit_write_uint16(outbuf, num_leaves);
  huff_write_tree(outbuf, code_tree);

  fseek(fin, 0, SEEK_SET);

  int file;

  while ((file = fgetc(fin)) != EOF) {
    uint64_t code = code_table[file].code;
    uint8_t code_length = code_table[file].code_length;
    for (int i = 0; i < code_length; ++i) {
      bit_write_bit(outbuf, (code & 1));
      code >>= 1;
    }
  }
}

void print_options(void) {
  fprintf(stdout, "Usage: huff -i infile -o outfile\n"
                  "	huff -v -i infile -o outfile\n"
                  "	huff -h\n");
}

int main(int argc, char **argv) {
  int option;
  FILE *inputf = NULL;
  BitWriter *outputvar;

  if (argc < 3) {
    fprintf(stderr, "huff:  -i option is required\n");
    print_options();
    return 1;
  } else if (argc <= 4) {
    fprintf(stderr, "huff:  -o option is required\n");
    print_options();
    return 1;
  }

  while ((option = getopt(argc, argv, "hi:o:")) != -1) {
    switch (option) {
    case 'h':
      print_options();
      return 0;
    case 'i':
      inputf = fopen(optarg, "r");
      if (inputf == NULL) {
        fprintf(stderr, "huff:  error opening input file\n");
        print_options();
      }
      break;
    case 'o':
      outputvar = bit_write_open(optarg);
      if (outputvar == NULL) {
        fprintf(stderr, "huff:  error opening output file\n");
        bit_write_close(&outputvar);
        return 1;
      }
      break;
    default:
      return 1;
      break;
    }
  }

  uint32_t histogram[256];
  uint32_t filesize = fill_histogram(inputf, histogram);
  uint16_t num_leaves = 0;
  Node *tree = create_tree(histogram, &num_leaves);

  Code *table = malloc(256 * sizeof(Code));
  fill_code_table(table, tree, 0, 0);
  huff_compress_file(outputvar, inputf, filesize, num_leaves, tree, table);
  free(table);
  node_free(&tree);
  fclose(inputf);
  inputf = NULL;
  bit_write_close(&outputvar);
  return 0;
}
