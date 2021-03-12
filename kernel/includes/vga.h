#ifndef VGA_H
#define VGA_H 1

#define VGAMEM 0xb8000
#define CURSOR_X_MAX 80
#define CURSOR_Y_MAX 25

// kernel/vga/vga.c
void cls(void);
void vga_initialize(void);
void vga_scroll(void);
void char_put(char c, int place, char color);
void newline(void);
void horizontab_print(void);
int e_check(char c);
void char_print(char c, char color);
void str_print(char *msg, char color);

#endif