#define size_t unsigned int

void *ft_memset(void *s, int c, size_t n)
{
    unsigned int i;
    unsigned char *sc;

    sc = (unsigned char *)s;
    i = 0;
    while (i < n)
    {
        *sc = c;
        sc++;
        i++;
    }
    return (s);
}