#include "idt.h"

struct idt_entry_struct idt_entries[256];
struct idt_ptr_struct idt_ptr;

extern void idt_flush(uint32_t);

void initIdt()
{

    idt_ptr.limit = sizeof(struct idt_entry_struct) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    // Initialize all entries in the Interrupt Descriptor Table (IDT) to 0
    ft_memset(&idt_entries, 0, sizeof(struct idt_entry_struct) * 256);

    // Start of Programmable Interrupt Controller (PIC) initialization
    // The PICs are being remapped from their defaults
    //(0x08-0x0F and 0x70-0x77) to new vectors (0x20-0x27 and 0x28-0x2F)

    // PIC remap
    // 0x20 commands and x021 data
    // 0xA0 commands and 0xA1 data

    // Send initialization command to both PICs
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);

    // Set the offset for the PICs (0x20 for the Master PIC, 0x28 for the Slave PIC)
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    // Tell Master PIC there is a slave PIC at IRQ2 (0000 0100)
    // Tell Slave PIC its cascade identity (0000 0010)
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    // Set PICs to 8086/88 (MCS-80/85) mode
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);

    // Clear data registers
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);
    // End of PIC initialization

    // Set the first entry in the IDT to the address of the first ISR (isr0)
    // The selector (0x08) points to the kernel code segment
    // The flags (0x8E) indicate that this is an interrupt gate and it is present
    // P DPL Zero  GateType
    // 1 00  0     1110  =  0x8E
    // Code segment offset =  0x08
    set_id_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    set_id_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    set_id_gate(2, (uint32_t)isr2, 0x08, 0x8E);
    set_id_gate(3, (uint32_t)isr3, 0x08, 0x8E);
    set_id_gate(4, (uint32_t)isr4, 0x08, 0x8E);
    set_id_gate(5, (uint32_t)isr5, 0x08, 0x8E);
    set_id_gate(6, (uint32_t)isr6, 0x08, 0x8E);
    set_id_gate(7, (uint32_t)isr7, 0x08, 0x8E);
    set_id_gate(8, (uint32_t)isr8, 0x08, 0x8E);
    set_id_gate(9, (uint32_t)isr9, 0x08, 0x8E);
    set_id_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    set_id_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    set_id_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    set_id_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    set_id_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    set_id_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    set_id_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    set_id_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    set_id_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    set_id_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    set_id_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    set_id_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    set_id_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    set_id_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    set_id_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    set_id_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    set_id_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    set_id_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    set_id_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    set_id_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    set_id_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    set_id_gate(31, (uint32_t)isr31, 0x08, 0x8E);

    set_id_gate(31, (uint32_t)isr128, 0x08, 0x8E);
    set_id_gate(31, (uint32_t)isr177, 0x08, 0x8E);

    // IRQ
    set_id_gate(32, (uint32_t)irq0, 0x08, 0x8E);
    set_id_gate(33, (uint32_t)irq1, 0x08, 0x8E);
    set_id_gate(34, (uint32_t)irq2, 0x08, 0x8E);
    set_id_gate(35, (uint32_t)irq3, 0x08, 0x8E);
    set_id_gate(36, (uint32_t)irq4, 0x08, 0x8E);
    set_id_gate(37, (uint32_t)irq5, 0x08, 0x8E);
    set_id_gate(38, (uint32_t)irq6, 0x08, 0x8E);
    set_id_gate(39, (uint32_t)irq7, 0x08, 0x8E);
    set_id_gate(40, (uint32_t)irq8, 0x08, 0x8E);
    set_id_gate(41, (uint32_t)irq9, 0x08, 0x8E);
    set_id_gate(42, (uint32_t)irq10, 0x08, 0x8E);
    set_id_gate(43, (uint32_t)irq11, 0x08, 0x8E);
    set_id_gate(44, (uint32_t)irq12, 0x08, 0x8E);
    set_id_gate(45, (uint32_t)irq13, 0x08, 0x8E);
    set_id_gate(46, (uint32_t)irq14, 0x08, 0x8E);
    set_id_gate(47, (uint32_t)irq15, 0x08, 0x8E);

    idt_flush((uint32_t)&idt_ptr);
}

void set_id_gate(int n, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[n].base_lo = base & 0xFFFF;
    idt_entries[n].base_hi = (base >> 16) & 0xFFFF;
    idt_entries[n].sel = sel;
    idt_entries[n].zero = 0;
    // set DPL to 11 (0x60) to make it accessible from user mode
    // 0x60 =  0110 0000
    idt_entries[n].type_attr = flags | 0x60;
}

void isr_handler(struct InterruptRegisters *r)
{
    if (r->int_no < 32)
    {
        printf("Received interrupt: %d\n"
               "Exeption System Haulted\n",
               r->int_no);
        while (1)
            ;
    }
}

void *irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0};

void irq_install_handler(int irq, void (*handler)(struct InterruptRegisters *r))
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

void irq_handler(struct InterruptRegisters *r)
{
    void (*handler)(struct InterruptRegisters *r);
    handler = irq_routines[r->int_no - 32];
    if (handler)
        handler(r);
    if (r->int_no >= 40)
        port_byte_out(0xA0, 0x20);
    port_byte_out(0x20, 0x20);
}