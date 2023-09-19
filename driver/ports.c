unsigned char port_byte_in(unsigned short port)
{
    unsigned char result;
    // =a(result)   means : put value in regester al in result variable when finished exucting instraction
    // "d"(port)    means : load dx regester with value from variable port
    __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
}

void port_byte_out(unsigned short port, unsigned char data)
{
    __asm__("out %%al, %%dx" : : "a"(data), "d"(port));
}

unsigned char port_word_in(unsigned short port)
{
    unsigned char result;
    __asm__("in %%dx, %%ax" : "=a"(result) : "d"(port));
}

void port_word_out(unsigned short port, unsigned char data)
{
    __asm__("out %%ax, %%dx" : : "a"(data), "d"(port));
}