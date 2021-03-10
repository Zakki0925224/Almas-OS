#ifndef IO_H
#define IO_H

#define VIDEO   0xb8000;

// output.h
void char_print(char c, char color);
void str_print(char *msg, char color);
void cls(int length);

#endif