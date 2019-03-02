#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include"print_logo.h"

// C function showing how to do time delay 
#include <stdio.h> 
// To use time library of C 
#include <time.h> 
  
void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
} 

void printFCode(){
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
	printf("%40.0s           _                      _       \n");
	printf("%40.0s _ _ _ ___| |___ ___ _____ ___   | |_ ___ \n");
	printf("%40.0s| | | | -_| |  _| . |     | -_|  |  _| . |\n");
	printf("%40.0s|_____|___|_|___|___|_|_|_|___|  |_| |___|\n");
	printf("%40.0s__/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\______________________/\\\\\\\\\\\\\\\\\\_______________________/\\\\\\_________________        \n");
	printf("%40.0s _\\/\\\\\\///////////____________________/\\\\\\////////_______________________\\/\\\\\\_________________       \n");
	printf("%40.0s  _\\/\\\\\\_____________________________/\\\\\\/________________________________\\/\\\\\\_________________      \n");
	printf("%40.0s   _\\/\\\\\\\\\\\\\\\\\\\\\\______/\\\\\\\\\\\\\\\\\\\\\\__/\\\\\\_________________/\\\\\\\\\\___________\\/\\\\\\______/\\\\\\\\\\\\\\\\__     \n");
	printf("%40.0s    _\\/\\\\\\///////______\\///////////__\\/\\\\\\_______________/\\\\\\///\\\\\\____/\\\\\\\\\\\\\\\\\\____/\\\\\\/////\\\\\\_    \n");
	printf("%40.0s     _\\/\\\\\\____________________________\\///\\\\\\__________\\//\\\\\\__/\\\\\\__\\/\\\\\\__\\/\\\\\\__\\//\\\\///////___  \n");
	printf("%40.0s      _\\/\\\\\______________________________\\////\\\\\\\\\\\\\\\\\\__\\///\\\\\\\\\\/___\\//\\\\\\\\\\\\\\/\\\\__\\//\\\\\\\\\\\\\\\\\\\\__\n");
	printf("%40.0s       _\\///________________________________\\/////////_____\\/////______\\///////\\//____\\//////////____\n");
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
}
void printLogo(){
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
	printf("%67.0s8888888888        .d8888b.                888          \n");
	printf("%67.0s888              d88P  Y88b               888          \n");
	printf("%67.0s888              888    888               888          \n");
	printf("%67.0s8888888          888         .d88b.   .d88888  .d88b.  \n");
	printf("%67.0s888              888        d88\"\"88b d88\" 888 d8P  Y8b \n");
	printf("%67.0s888      888888  888    888 888  888 888  888 88888888 \n");
	printf("%67.0s888              Y88b  d88P Y88..88P Y88b 888 Y8b.     \n");
	printf("%67.0s888               \"Y8888P\"   \"Y88P\"   \"Y88888  \"Y8888  \n");
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
}
