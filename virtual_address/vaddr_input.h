int VADDR_SIZE = 32 * 1024;
int PHYS_MEMSIZE = 64 * 1024;
int PAGE_SIZE = 4 * 1024;

unsigned int VPNENTRY[8] = {
  0x00000000,
  0x80000004,
  0x8000000c,
  0x8000000a,
  0x8000000b,
  0x80000008,
  0x80000007,
  0x80000000
};