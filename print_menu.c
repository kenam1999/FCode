#include"print_menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "string.h"
#include <conio.h>
#include"gotoxy.h"

void printfH(char str[255]){
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0xA0);
	printf ("%s", str);
  	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
}

void printfGreen(char str[255]){
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
	printf ("%s", str);
  	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
}

int printMainMenu(int* pNum){

	int position = 1;
	char letter;
	int inputted = 1;
	*pNum = 0;
	do{		
		gotoxy(0, 14);
		printf("%40.0s");
		printfGreen("MAIN MENU\n\n");
		printf("%40.0s");
		if (position == 1) printfH("Members club menu\n"); 
		else printf("Members club menu\n");
		printf("%40.0s");
		if (position == 2) printfH("Event menu\n"); 
		else printf("Event menu\n");
		printf("%40.0s");
		if (position == 3) printfH("Fund menu\n");
		else printf("Fund menu\n");
		printf("%40.0s");
		if (position == 4) printfH("F-Code's announcement\n");
		else printf("F-Code's announcement\n");
		printf("%40.0s");
		if (position == 5) printfH("Exit\n");
		else printf("Exit\n");
//		printfGreen("\nExit: press [esc] to exit!\n");				
		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
				if (letter == - 32){
					letter = getch();
					if((letter == 80) && position < 5 ) {
						position ++;
						inputted = 1;
//						printf("ok, %d\n", position);
					}if((letter == 72) && position > 1) 
					{
						position --;
						inputted = 1;
//						printf("ok, %d\n", position);
					}	
				}
				if (letter == 13) {
						*pNum = position;
						letter = 27;
						inputted = 0;
				}
		} while(letter != 27 && inputted != 1);
//		system("cls");
	} while(letter != 27);
	system("cls");
}

int chooseEventMenuA(int* pNum){

	int position = 1;
	char letter;
	int inputted = 1;
	*pNum = 0;
	do{		
		gotoxy(0, 14);
		printf("%40.0s");
		printfGreen("EVENT MENU\n\n");
		printf("%40.0s");
		if (position == 1) printfH("Print Event list\n"); 
		else printf("Print Event list\n");
		printf("%40.0s");
		if (position == 2) printfH("Register for future events\n"); 
		else printf("Register for future events\n");
		printf("%40.0s");
		if (position == 3) printfH("Show resigntered & attendant check table\n");
		else printf("Show resigntered & attendant check table\n");
		printf("%40.0s");
		if (position == 4) printfH("Check attendant (only available for administrator)\n");
		else printf("Check attendant (only available for administrator)\n");
		printf("%40.0s");
		if (position == 5) printfH("Exit\n");
		else printf("Exit\n");

		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
				if (letter == - 32){
					letter = getch();
					if((letter == 80) && position < 5 ) {
						position ++;
						inputted = 1;
//						printf("ok, %d\n", position);
					}if((letter == 72) && position > 1) 
					{
						position --;
						inputted = 1;
//						printf("ok, %d\n", position);
					}	
				}
				if (letter == 13) {
						*pNum = position;
						letter = 27;
						inputted = 0;
				}
		} while(letter != 27 && inputted != 1);

	} while(letter != 27);
//	system("cls");
}

int chooseEventMenuM(int* pNum){

	int position = 1;
	char letter;
	int inputted = 1;
	*pNum = 0;
	do{		
		gotoxy(0, 14);
		printf("%40.0s");
		printfGreen("EVENT MENU\n\n");
		printf("%40.0s");
		if (position == 1) printfH("Print Event list\n"); 
		else printf("Print Event list\n");
		printf("%40.0s");
		if (position == 2) printfH("Register for future events\n"); 
		else printf("Register for future events\n");
		printf("%40.0s");
		if (position == 3) printfH("Show resigntered & attendant check table\n");
		else printf("Show resigntered & attendant check table\n");
		printf("%40.0s");
		if (position == 4) printfH("Exit\n");
		else printf("Exit\n");

		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
				if (letter == - 32){
					letter = getch();
					if((letter == 80) && position < 4 ) {
						position ++;
						inputted = 1;
//						printf("ok, %d\n", position);
					}if((letter == 72) && position > 1) 
					{
						position --;
						inputted = 1;
//						printf("ok, %d\n", position);
					}	
				}
				if (letter == 13) {
						*pNum = position;
						letter = 27;
						inputted = 0;
				}
		} while(letter != 27 && inputted != 1);

	} while(letter != 27);
//	system("cls");
}

int printFundMenuM(int* pNum){

	int position = 1;
	char letter;
	int inputted = 1;
	*pNum = 0;
	do{		
		gotoxy(0, 14);
		printf("%40.0s");
		printfGreen("FUND MENU\n\n");
		printf("%40.0s");
		if (position == 1) printfH("Print fund's expend & income list\n"); 
		else printf("Print fund's expend & income list\n");
		printf("%40.0s");
		if (position == 2) printfH("Print monthly fund\n"); 
		else printf("Print monthly fund\n");
		printf("%40.0s");
		if (position == 3) printfH("Exit\n");
		else printf("Exit\n");

		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
				if (letter == - 32){
					letter = getch();
					if((letter == 80) && position < 3 ) {
						position ++;
						inputted = 1;
//						printf("ok, %d\n", position);
					}if((letter == 72) && position > 1) 
					{
						position --;
						inputted = 1;
//						printf("ok, %d\n", position);
					}	
				}
				if (letter == 13) {
						*pNum = position;
						letter = 27;
						inputted = 0;
				}
		} while(letter != 27 && inputted != 1);

	} while(letter != 27);
	system("cls");
}

int printAnnouncementMenuM(int* pNum){

	int position = 1;
	char letter;
	int inputted = 1;
	*pNum = 0;
	do{		
		gotoxy(0, 14);
		printf("%40.0s");
		printfGreen("ANNOUNCEMENT\n\n");
		printf("%40.0s");
		if (position == 1) printfH("Printf announcement\n"); 
		else printf("Printf announcement\n");
		printf("%40.0s");
		if (position == 2) printfH("Exit\n");
		else printf("Exit\n");

		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
				if (letter == - 32){
					letter = getch();
					if((letter == 80) && position < 2 ) {
						position ++;
						inputted = 1;
//						printf("ok, %d\n", position);
					}if((letter == 72) && position > 1) 
					{
						position --;
						inputted = 1;
//						printf("ok, %d\n", position);
					}	
				}
				if (letter == 13) {
						*pNum = position;
						letter = 27;
						inputted = 0;
				}
		} while(letter != 27 && inputted != 1);

	} while(letter != 27);
	system("cls");
}

int printAnnouncementMenuA(int* pNum){

	int position = 1;
	char letter;
	int inputted = 1;
	*pNum = 0;
	do{		
		gotoxy(0, 14);
		printf("%40.0s");
		printfGreen("ANNOUNCEMENT\n\n");
		printf("%40.0s");
		if (position == 1) printfH("Printf announcement\n"); 
		else printf("Printf announcement\n");
		printf("%40.0s");
		if (position == 2) printfH("Add new announcement\n"); 
		else printf("Add new announcement\n");
		printf("%40.0s");
		if (position == 3) printfH("Exit\n");
		else printf("Exit\n");

		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
				if (letter == - 32){
					letter = getch();
					if((letter == 80) && position < 3 ) {
						position ++;
						inputted = 1;
//						printf("ok, %d\n", position);
					}if((letter == 72) && position > 1) 
					{
						position --;
						inputted = 1;
//						printf("ok, %d\n", position);
					}	
				}
				if (letter == 13) {
						*pNum = position;
						letter = 27;
						inputted = 0;
				}
		} while(letter != 27 && inputted != 1);

	} while(letter != 27);
	system("cls");
}
