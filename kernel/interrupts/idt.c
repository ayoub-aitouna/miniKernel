#include "idt.h"
void memset();
struct idt_entry_struct idt_entries[256];
struct idt_ptr_struct idt_ptr;

extern void idt_flush(uint32_t);

void initIdt()
{
    idt_ptr.limit = sizeof(struct idt_entry_struct) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(struct idt_entry_struct) * 256);
    
    // PIC remap
    // 0x20 commands and x021 data
    // 0xA0 commands and 0xA1 data

}

void set_id_gate(int n, uint32_t base, uint16_t sel, uint8_t flags)
{
}