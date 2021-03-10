// 文字列を色を指定して出力
// *msg -> 文字列
// color -> 背景色と文字色
// addr 出力するアドレス（VRAM 0xb8000以降）
void str_print(char *msg, char color, unsigned short *addr)
{
    // 2byte/1char
    // color 0x0 -> 背景色 f -> 文字色
    char ch;

    // 1文字ずつVRAMに転送
    while (ch = *msg++)
        *addr++ = ((color) << 8) | ch;
}