#include "multiboot.h"
#include "graphic/io.h"

void cstart(unsigned long magic, unsigned long addr, multiboot_info_t *boot_info)
{
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        str_print("Error: Invalid magic number", 0x0f);
        return;
    }

    cls(1000);
    str_print("Welcome to ", 0x0f);
    str_print("Almas OS ", 0x0e);
    str_print("!", 0x0f);

    return;
}