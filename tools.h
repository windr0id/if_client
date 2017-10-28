#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string.h>
#include <QDebug>

void IntToByteArray(int n, char* b);
int ByteArrayToInt(char* b);
void ByteArrayToStr(char* b, char* dest, int len);

void setHead(char* buff, int title, int num);
int setData(char* buff, int num, char* (pdata)[], int datalen[]);

int t_parse(char* buff, int* title, int* num, char* (pdata)[], int datalen[]);

#endif // TOOLS_H
