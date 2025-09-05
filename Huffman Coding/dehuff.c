#include "bitreader.h"
#include "node.h"
#include "pq.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 64

void stack_push(Node **stack, int *front, Node *node) {
  if (*front < STACK_SIZE - 1) {
    stack[++(*front)] = node;
  } else {
    fprintf(stderr, "Error: stack push failed\n");
  }
}

Node *stack_pop(Node **stack, int *front) {
  if (*front >= 0) {
    return stack[(*front)--];
  } else {
    fprintf(stderr, "Error: stack pop failed\n");
    return NULL;
  }
}

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
  uint8_t type1 = bit_read_uint8(inbuf);
  uint8_t type2 = bit_read_uint8(inbuf);
  uint32_t filesize = bit_read_uint32(inbuf);
  uint16_t num_leaves = bit_read_uint16(inbuf);
  assert(type1 == 'H');
  assert(type2 == 'C');

  uint16_t num_nodes = 2 * num_leaves - 1;
  Node *stack[STACK_SIZE];
  int front = -1;

  for (uint16_t i = 0; i < num_nodes; ++i) {
    int bit = bit_read_bit(inbuf);
    Node *node;

    if (bit == 1) {
      uint8_t symbol = bit_read_uint8(inbuf);
      node = node_create(symbol, 0);
    } else {
      node = node_create(0, 0);
      node->right = stack_pop(stack, &front);
      node->left = stack_pop(stack, &front);
    }
    stack_push(stack, &front, node);
  }

  if (front < 0) {
    fprintf(stderr, "Error: Empty\n");
    return;
  }

  Node *code_tree = stack_pop(stack, &front);
  for (uint32_t i = 0; i < filesize; ++i) {
    Node *node = code_tree;

    while (1) {
      int bit = bit_read_bit(inbuf);
      if (bit == 0) {
        node = node->left;
      } else {
        node = node->right;
      }
      if (node->left == NULL || node->right == NULL) {
        break;
      }
    }
    fputc(node->symbol, fout);
  }
  node_free(&code_tree);
}

void print_options(void) {
  fprintf(stdout, "Usage: dehuff -i infile -o outfile\n"
                  "       dehuff -v -i infile -o outfile\n"
                  "       dhuff -h\n");
}

int main(int argc, char **argv) {
  int option;
  FILE *outf = NULL;
  const char *inputvar;

  if (argc < 3) {
    fprintf(stderr, "dehuff:  -i option is required\n");
    print_options();
    return 1;
  } else if (argc <= 4) {
    fprintf(stderr, "dehuff:  -o option is required\n");
    print_options();
    return 1;
  }

  while ((option = getopt(argc, argv, "hi:o:")) != -1) {
    switch (option) {
    case 'h':
      print_options();
      return 0;
    case 'i':
      inputvar = optarg;
      break;
    case 'o':
      outf = fopen(optarg, "w");
      if (outf == NULL) {
        fprintf(stderr, "dehuff:  error opening output file\n");
        print_options();
        return 1;
      }
      break;
    default:
      break;
    }
  }

  BitReader *inbuf = bit_read_open(inputvar);
  dehuff_decompress_file(outf, inbuf);
  bit_read_close(&inbuf);
  fclose(outf);
  return 0;
}
