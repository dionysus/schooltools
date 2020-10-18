#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "multiaddr_input.h"

unsigned int calc_page_offset(unsigned int vaddr) {
  return vaddr % PAGE_SIZE;
};

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

unsigned int get_middle_bits (int front, int mid, int end, unsigned int num) {
    
    num = (num >> end);

    int tn = 0;
    for (int i = 0; i < mid ; i ++){
        int flag = 1 << i;
        int t = num & flag;
        tn = tn | t;
    }

    return tn;
}

int check_byte_fault (unsigned int num){
    if ((num & (1 << (PTEBYTES*8 - 1)))) {
        return 1;
    }
    return 0;
}

unsigned int calc_paddr(unsigned int vaddr) {
    int num_offset_bits = log2(PAGE_SIZE);
    int num_vbits = log2(NUM_PAGES);
    int num_pframes_bits= log2(NUM_PG_FRAMES);
    int num_paddr_bits = num_offset_bits + num_pframes_bits;
    int num_ml_bits = num_offset_bits + num_vbits;

    int num_pdir_bits = 5; // Top 5 used for pdir for multilevel
    int num_ptable_bits = num_vbits - num_pdir_bits;
    // Page Dir bits //  Page Table bits // OFFSET
    
    printf("---------------------------------------------------\n");
    printf("00. VADDR: 0x%x \n", vaddr);
    print_bits(16, vaddr);

    int offset = calc_page_offset(vaddr);
    printf("Offset: \n");
    print_bits(num_offset_bits, offset);

    printf("PBDR (first frame): %d\n\n", PBDR);

// 01. PAGE DIRECTORY
    printf("---------------------------------------------------\n");
    int dir_entry = vaddr >> (num_ml_bits - num_pdir_bits); 
    printf("01. PAGE DIR INDEX:\n");
    print_bits(num_pdir_bits, dir_entry);

    // the frame entry in the first table (including check)
    int frame_entry = FRAMES[PBDR][dir_entry];
    printf("PAGE DIR ENTRY w/ Check @ [%d][%d]:\n", PBDR, dir_entry);
    print_bits(PTEBYTES*8, frame_entry);

    // FAULT CHECK HERE
    if (check_byte_fault(frame_entry) == 0){
        printf("Fault!\n\n");
        return 0;
    }


    // the frame number in the page table
    int frame_no = frame_entry ^ (1 << 7); // TODO is this right?
    printf("PAGE DIR ENTRY: \n");
    print_bits( PTEBYTES*8, frame_no);

// 02. PAGE TABLE BITS
    printf("---------------------------------------------------\n");
    int dir_entry_b = get_middle_bits(num_pdir_bits, num_ptable_bits, num_offset_bits, vaddr);
    printf("02. PAGE TABLE BITS:\n");
    print_bits(num_vbits - num_pdir_bits, dir_entry_b);

    int frame_entry_b = FRAMES[frame_no][dir_entry_b];
    printf("PAGE TABLE ENTRY w/check @ [%d][%d]:\n", frame_no, dir_entry_b);
    print_bits(PTEBYTES*8, frame_entry_b);

    // FAULT CHECK HERE
    if (check_byte_fault(frame_entry_b) == 0){
        printf("Fault!\n\n");
        return 0;
    }

    int frame_no_b = get_middle_bits(1, num_pframes_bits, 0, frame_entry_b);
    printf("PAGE TABLE ENTRY:\n");
    print_bits(num_pframes_bits, frame_no_b);

// 03. PHYSICAL ADDRESS
    printf("---------------------------------------------------\n");
    
    printf("PAGE TABLE ENTRY\n");
    print_bits(num_pframes_bits, frame_no_b);
    printf(" + \n\n");
    printf("Offset: \n");
    print_bits(num_offset_bits, offset);

    printf("---------------------------------------------------\n");

    printf("Physical Address: \n");
    unsigned int paddr = frame_no_b << num_offset_bits | offset;
    print_bits(num_paddr_bits, paddr);

    int val = FRAMES[frame_no_b][offset];
    printf("Value @ PADDR: 0x%x\n", val);

    printf("---------------------------------------------------\n");

    return 0;
}


void print_stats(){
    int num_offset_bits = log2(PAGE_SIZE);
    int num_vbits = log2(NUM_PAGES);
    int num_pframes_bits= log2(NUM_PG_FRAMES);
    int num_paddr_bits = num_offset_bits + num_pframes_bits;

    printf("Num Offset Bits: %d \n", num_offset_bits);
    printf("Num Virtual Pages: %d \n", NUM_PAGES);
    printf("Num VPN Bits: %d bits\n", num_vbits);
    printf("Num Physical Pages (Page Frames): %d \n", NUM_PG_FRAMES);
    printf("Num Physical Bits: %d bits\n", num_pframes_bits);
    printf("Num Physical Address Bits: %d \n", num_paddr_bits);
    printf("----------------------------------------------------------------\n");
}

// args: number, base
int main(int argc, char *argv[]) {

    // Check enough arguments.
    if (argc != 3) {
        puts ("Not enough arguments");
        return 1;
    }
    // Convert to ulong WITH CHECKING!
    int base = strtol(argv[2], NULL, 10);
    unsigned int num = strtoul (argv[1], NULL, base);

    print_stats();
    calc_paddr(num);
    return 0;
}

