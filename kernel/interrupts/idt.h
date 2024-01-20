#include <stdint.h>

struct idt_entry_struct
{
    uint16_t base_lo;
    uint16_t sel;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t base_hi;
} __attribute((packed));

struct idt_ptr_struct
{
    uint16_t limit;
    uint32_t base;
} __attribute((packed));

void initIdt();
void set_id_gate(int n, uint32_t base, uint16_t sel, uint8_t flags);