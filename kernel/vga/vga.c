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
        cprint(' ', 0x0f);
}

void horizontaltab_print(void)
{
    for (int i = 0; i < 4; i++)
        cprint(' ', 0x0f);
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
void cprint(char c, char color)
{
    unsigned short *buf = (unsigned short *) VGAMEM;

    while(1)
    {
        if (*buf != 0)
            *buf++;

        else
        {
            if (e_check(c) == 0)
                *buf = ((color) << 8) | c;
            else
                break;

            cursor_x++;

            if (cursor_x > (int)CURSOR_X_MAX)
            {
                cursor_x = 1;
                cursor_y++;
            }

            if (cursor_y > (int)CURSOR_Y_MAX)
            {
                vga_scroll();
                cursor_x = 1;
                cursor_y = (int)CURSOR_Y_MAX;
            }

            break;
        }
    }
}

void sprint(char *msg, char color)
{
    for (int i = 0; msg[i] != '\0'; i++)
        cprint(msg[i], color);
}

char num_to_char(int d)
{
    if (d == 0 ||
        d == 1 ||
        d == 2 ||
        d == 3 ||
        d == 4 ||
        d == 5 ||
        d == 6 ||
        d == 7 ||
        d == 8 ||
        d == 9)
        return '0' + d;
}

void iprint(int i, char color)
{
    if (i == 0)
    {
        sprint("0", color);
        return;
    }

    if (i < 0)
    {
        sprint("-", color);
        i *= -1;
    }

    int digits;
    int j = i;
    int k = 1;

    // 桁数の計算
    for (digits = 0; j != 0; digits++)
        j /= 10;

    char str[digits];

    for (digits -= 1; digits >= 0; digits--)
    {
        str[digits] = num_to_char((i / k) % 10);
        k *= 10;
    }

    sprint(str, color);
}