#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "vaddr_input.h"

// prints bits with space after each byte (bit * 4)
void print_bits(int count, unsigned int num) {
    int size = sizeof(num) * 8;
    int bits[size];

    printf("num:  %d (0x%x)\n", num, num);
    printf("bits: ");

    // shift bits into bits array (end first)
    for(int i = 0; i < size; i++) {
        bits[size - i - 1] = num & 0x01;
        num = num >> 1;
    }

    for(int i = size - count; i < size; i++) {
        printf("%d", bits[i]);
        if ((i + 1) % 4 == 0) printf(" ");
    }

    printf("\n\n");
}

int calc_pageno(unsigned int vaddr) {
  return vaddr / PAGE_SIZE;
};

unsigned int calc_page_offset(unsigned int vaddr) {
  return vaddr % PAGE_SIZE;
};

unsigned int calc_paddr(unsigned int vaddr) {
  int num_offset_bits = log2(PAGE_SIZE);
  int num_pgframes = PHYS_MEMSIZE / PAGE_SIZE;
  int num_bits_index_pgframes = log2(num_pgframes);
  int num_phys_addr_index_bits = num_bits_index_pgframes + num_offset_bits;

  printf("VADDR: %x \n", vaddr);
  print_bits(16, vaddr);

  int offset = calc_page_offset(vaddr);
  printf("Page Offset: \n");
  print_bits(num_offset_bits, offset);

  int pageno = calc_pageno(vaddr);
  printf("Page Number: %d\n\n", pageno);

  unsigned int frame_entry = VPNENTRY[pageno];
  printf("FRAME_ENTRY: \n");
  print_bits(sizeof(frame_entry)*8, frame_entry);

  unsigned int frame_check = 1 << (sizeof(frame_entry) - 1);
  printf("Frame Check: 0x%d (0x8 is good)\n", frame_check);
  print_bits(4, frame_check);
  
  unsigned int frame_num = frame_entry & 0xF;
  printf("Frame Num: \n");
  print_bits(num_bits_index_pgframes, frame_num);

  printf("Physical Address: \n");
  unsigned int paddr = frame_num << num_offset_bits | offset;
  print_bits(num_phys_addr_index_bits, paddr);

  printf("\n");

  return paddr;

}

void print_stats(){
  int num_offset_bits = log2(PAGE_SIZE);
  int num_pages = VADDR_SIZE / PAGE_SIZE;
  int num_bits_index = log2(num_pages);
  int num_page_frames = PHYS_MEMSIZE / PAGE_SIZE;
  int num_bits_pframes_index = log2(num_page_frames);
  int num_paddr_bits = num_bits_pframes_index + num_offset_bits;

  printf("Num Offset Bits: %d \n", num_offset_bits);
  printf("Num Virtual Pages: %d \n", num_pages);
  printf("Num Index Bits (VPages): %d \n", num_bits_index);
  printf("Num Physical Pages (Page Frames): %d \n", num_page_frames);
  printf("Num Index Bits (PPages): %d \n", num_bits_pframes_index);
  printf("Num Physical Address Bits: %d \n", num_paddr_bits);

  printf("----------------------------------------------------------------\n");
}

int main(int argc, char *argv[]) {

  // Check enough arguments.
  if (argc != 3) {
      puts ("Not enough arguments");
      return 1;
  }
  // Convert to ulong WITH CHECKING!
  int base = strtol(argv[2], NULL, 10);
  unsigned int vaddr = strtoul (argv[1], NULL, base);

  calc_paddr(vaddr);
  return 0;
}
