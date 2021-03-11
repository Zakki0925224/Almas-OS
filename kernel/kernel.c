#include <multiboot.h>
#include <vga.h>

void kernel_main(unsigned long magic, unsigned long addr, multiboot_info_t *boot_info)
{
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        str_print("Error: Invalid magic number", 0x0f);
        return;
    }

    vga_initialize();
    str_print("hello world!", 0x0f);
    newline();

    for (int i = 0; i < 200; i++)
        str_print("hello world!", 0x0f);

    return;
}