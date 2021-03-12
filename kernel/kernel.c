#include <multiboot.h>
#include <vga.h>

void kernel_main(unsigned long magic, unsigned long addr, multiboot_info_t *boot_info)
{
    vga_initialize();

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        str_print("Error: Invalid magic number", 0x0f);
        return;
    }

    for (int i = 0; i < CURSOR_Y_MAX + 5; i++)
        str_print("\t\n", 0x0f);

    return;
}