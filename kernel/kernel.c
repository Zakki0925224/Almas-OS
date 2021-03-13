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

    for (int i = 0; i < 500; i++)
    {
        str_print("#include<stdio.h>\n", 0x0f);
        str_print("\nint main(void) {\n", 0x0f);
        str_print("\tprintf(\"Hello World!\");\n", 0x0f);
        str_print("\treturn 0;\n}\n\n", 0x0f);
    }

    return;
}