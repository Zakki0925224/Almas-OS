#include "multiboot.h"
#include "grapgic/output.h"

void cstart(unsigned long magic, unsigned long addr)
{
    cls(1000);
    str_print("Welcome to ", 0x0f);
    str_print("Almas OS ", 0x0e);
    str_print("!", 0x0f);

    return;
}