#include "multiboot.h"
#include "kernel/io.h"

void cstart(unsigned long magic, unsigned long addr)
{
    str_print("Welcome to Almas OS!", 0x0f, 0xb8000);
    str_print("Hello World!", 0x0f, 0xb802a);

    return;
}