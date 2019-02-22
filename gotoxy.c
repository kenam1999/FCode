#include"gotoxy.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>
void gotoxy(short x, short y)                                                       
{
 COORD pos ={x,y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
