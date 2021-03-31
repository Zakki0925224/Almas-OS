#include <multiboot.h>
#include <vga.h>

void kernel_main(unsigned long magic, unsigned long addr, multiboot_info_t *boot_info)
{
    vga_initialize();

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        sprint("Error: Invalid magic number", 0x0f);
        return;
    }

    iprint(1920 * 1080, 0x0f);

    return;
}