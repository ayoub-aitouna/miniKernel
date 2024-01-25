#include <stdint.h>
#include "../../driver/port.h"
#include "../printf/printf.h"
#include "../utils/string.h"

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

struct InterruptRegisters
{
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, csm, eflags, useresp, ss;
};

void initIdt();
void set_id_gate(int n, uint32_t base, uint16_t sel, uint8_t flags);

void isr_handler(struct InterruptRegisters *r);
void irq_handler(struct InterruptRegisters *r);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void isr128();
extern void isr177();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_uninstall_handler(int irq);
void irq_install_handler(int irq, void (*handler)(struct InterruptRegisters *r));