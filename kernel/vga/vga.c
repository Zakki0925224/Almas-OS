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
    cursor_x = 0;
    cursor_y = 0;
}

// 画面スクロール（戻れない）
void vga_scroll(void)
{
    unsigned short *buf = (unsigned short *) VGAMEM;

    for (int i = (int)CURSOR_X_MAX; i < (int)CURSOR_X_MAX * (int)CURSOR_Y_MAX; i++)
        buf[i - (int)CURSOR_X_MAX] = buf[i];

    for (int i = (int)CURSOR_X_MAX * ((int)CURSOR_Y_MAX - 1); i < (int)CURSOR_X_MAX * (int)CURSOR_Y_MAX; i++)
        buf[i] = 0;
}

// 改行（端までスペース埋め）
void newline(void)
{
    int x = cursor_x;
    int y = cursor_y;

    for (int i = ((int)CURSOR_X_MAX * (y - 1) + x - 1); i < (int)CURSOR_X_MAX * y; i++)
        char_print('*', 0x01);
}

void horizontaltab_print(void)
{
    for (int i = 0; i < 4; i++)
        char_print('*', 0x02);

    cursor_x--; // ズレ防止
}

// エスケープチェック
int e_check(char c)
{
    if (c == '\n')
    {
        newline();
        return 1;
    }
    else if (c == '\t')
    {
        horizontaltab_print();
        return 1;
    }
    else
        return 0;
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
            cursor_x++;

            if (cursor_x > (int)CURSOR_X_MAX)
            {
                cursor_x = 0;
                cursor_y++;
            }

            if (cursor_y > (int)CURSOR_Y_MAX)
            {
                vga_scroll();
                cursor_x = 0;
                cursor_y = (int)CURSOR_Y_MAX;
            }

            if (e_check(c) == 0)
                *buf = ((color) << 8) | c;

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