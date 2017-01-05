#include <kernel/descriptors.h>
#include <kernel/gdt.h>

struct gdt_ptr
{
  unsigned short limit;
  unsigned int base;

} __attribute__((packed));

typedef struct gdt_ptr gdt_ptr_t;

struct gdt_entry
{
  unsigned short limit_low;
  unsigned short base_low;
  unsigned char  base_middle;
  unsigned char  access;
  unsigned char  granularity;
  unsigned char  base_high;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry_t;

struct idt_entry
{
  unsigned short offset_high;
  unsigned short selector;
  unsigned char reserved;
  unsigned char flags;
  unsigned short offset_low;
} __attribute__((packed));

typedef struct idt_entry idt_entry_t;


gdt_entry_t gdt_set_gate(unsigned int base,unsigned int limit,unsigned char access,unsigned char granularity)
{
  gdt_entry_t gdt_entry;
  gdt_entry.base_low=(base&0xFFFF);
  gdt_entry.base_middle=(base>>16)&0xFF;
  gdt_entry.base_high=(base>>24)&0xFF;
  gdt_entry.limit_low=(limit&0xFFFF);
  gdt_entry.granularity=(limit>>16)&0x0F;
  gdt_entry.granularity|=granularity&0xF0;
  gdt_entry.access=access;
  return gdt_entry;
}


void setup_gdt()
{
  gdt_entry_t entries[5];
  gdt_ptr_t gdt_ptr;
  gdt_ptr.base = (unsigned int) &entries;
  gdt_ptr.limit = (sizeof(gdt_entry_t)*5) - 1;
  entries[0] = gdt_set_gate(0, 0, 0, 0);
  entries[1] = gdt_set_gate(0, 0xFFFFFFFF, 0x9A, 0xCF); //Readable kernel code
  entries[2] = gdt_set_gate(0, 0xFFFFFFFF, 0x92, 0xCF); //writable kernel data
  entries[3] = gdt_set_gate(0, 0xFFFFFFFF, 0xFA, 0xCF); //Readable user code
  entries[4] = gdt_set_gate(0, 0xFFFFFFFF, 0xF2, 0xCF); //writable user data
  gdt_write((unsigned int)&gdt_ptr);

}
