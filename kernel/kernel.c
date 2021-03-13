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

    for (int i = 0; i < 1340; i++)
    {
        str_print("Hello", 0x02);
        str_print("World", 0x03);
        str_print("World", 0x04);
    }

    return;
}