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

    str_print("Welcome to Almas OS!\n", 0x0f);
    str_print("VERSION:0.1ALPHA\n", 0x0f);
    str_print("\nint main(void) {\n\tprintf(\"Hello World!\");\n\treturn 0;\n}", 0x0f);

    return;
}