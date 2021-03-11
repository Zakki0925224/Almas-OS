#include <vga.h>

int cursor_x;
int cursor_y;

void cls(void)
{
    unsigned short *buf = (unsigned short *) VGAMEM;

    for (int i = 0; i <= (int)CURSOR_X_MAX * (int)CURSOR_Y_MAX; i++)
        buf[i] = 0;
}

void vga_initialize(void)
{
    cls();
    cursor_x = 1;
    cursor_y = 1;
}

// 画面スクロール（戻れない）
void vga_scroll(void)
{
    
}

// 改行（端までスペース埋め）
void newline(void)
{
    unsigned short *buf = (unsigned short *) VGAMEM;

    for (int i = cursor_x * cursor_y - 1; i < (int)CURSOR_X_MAX * cursor_y; i++)
        buf[i] = (0x0f) << 8 | ' ';

    cursor_x = 1;
    cursor_y++;
}

// 文字と文字色を指定して出力
void char_print(char c, char color)
{
    unsigned short *buf = (unsigned short *) VGAMEM;

    while(1)
    {
        if (*buf != 0)
            *buf++;

        else
        {
            if (cursor_x > (int)CURSOR_X_MAX)
                newline();

            if ((cursor_x > (int)CURSOR_X_MAX) &&
                (cursor_y > (int)CURSOR_Y_MAX))
                vga_scroll();

            *buf = ((color) << 8) | c;
            cursor_x++;
            break;
        }
    }
}

void str_print(char *msg, char color)
{
    unsigned short *buf = (unsigned short *) VGAMEM;

    for (int i = 0; msg[i] != '\0'; i++)
        char_print(msg[i], color);
}