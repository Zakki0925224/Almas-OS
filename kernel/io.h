#include "arch/i386/vga.h"

// 文字を色を指定して出力
void char_print(char c, char color)
{
    unsigned short *vmem = (unsigned short *)VIDEO;

    while(1)
    {
        if (*vmem != 0)
            *vmem++;

        else
        {
            *vmem = ((color) << 8) | c;
            break;
        }
    }
}

// 文字列を色を指定して出力
// *msg -> 文字列
// color -> 背景色と文字色
void str_print(char *msg, char color)
{
    for (int i = 0; msg[i] != '\0'; i++)
        char_print(msg[i], color);
}

// 0で埋める
void cls(int length)
{
    unsigned short *vmem = (unsigned short *)VIDEO;

    for (int i = 0; i < length; i++)
        vmem[i] = 0;
}