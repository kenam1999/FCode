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
	int inputted;
	*pNum = 0;
	
	do{		
		gotoxy(0, 14);
		printf("%80.0s");
		printfGreen("MAIN MENU\n\n");
		printf("%80.0s");
		if (position == 1) printfH("Members club menu\n"); 
		else printf("Members club menu\n");
		printf("%80.0s");
		if (position == 2) printfH("Event menu\n"); 
		else printf("Event menu\n");
		printf("%80.0s");
		if (position == 3) printfH("Fund menu\n");
		else printf("Fund menu\n");
		printf("%80.0s");
		if (position == 4) printfH("F-Code's announcement\n");
		else printf("F-Code's announcement\n");
		printf("%80.0s");
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
		} while(letter != 27 && inputted == 0);
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
		printf("%80.0s");
		printfGreen("EVENT MENU\n\n");
		printf("%80.0s");
		if (position == 1) printfH("Print Event list\n"); 
		else printf("Print Event list\n");
		printf("%80.0s");
		if (position == 2) printfH("Register for future events\n"); 
		else printf("Register for future events\n");
		printf("%80.0s");
		if (position == 3) printfH("Show resigntered & attendant check table\n");
		else printf("Show resigntered & attendant check table\n");
		printf("%80.0s");
		if (position == 4) printfH("Check attendant (administrator)\n");
		else printf("Check attendant (administrator)\n");
		printf("%80.0s");
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
		printf("%80.0s");
		printfGreen("EVENT MENU\n\n");
		printf("%80.0s");
		if (position == 1) printfH("Print Event list\n"); 
		else printf("Print Event list\n");
		printf("%80.0s");
		if (position == 2) printfH("Register for future events\n"); 
		else printf("Register for future events\n");
		printf("%80.0s");
		if (position == 3) printfH("Show resigntered & attendant check table\n");
		else printf("Show resigntered & attendant check table\n");
		printf("%80.0s");
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
		printf("%80.0s");
		printfGreen("FUND MENU\n\n");
		printf("%80.0s");
		if (position == 1) printfH("Print fund's expend & income list\n"); 
		else printf("Print fund's expend & income list\n");
		printf("%80.0s");
		if (position == 2) printfH("Print monthly fund\n"); 
		else printf("Print monthly fund\n");
		printf("%80.0s");
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
		printf("%80.0s");
		printfGreen("ANNOUNCEMENT\n\n");
		printf("%80.0s");
		if (position == 1) printfH("Printf announcement\n"); 
		else printf("Printf announcement\n");
		printf("%80.0s");
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
		printf("%80.0s");
		printfGreen("ANNOUNCEMENT\n\n");
		printf("%80.0s");
		if (position == 1) printfH("Printf announcement\n"); 
		else printf("Printf announcement\n");
		printf("%80.0s");
		if (position == 2) printfH("Add new announcement\n"); 
		else printf("Add new announcement\n");
		printf("%80.0s");
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

int printMemberMenuA(int* pNum){

	int position = 1;
	char letter;
	int inputted = 1;
	*pNum = 0;
	do{		
		gotoxy(0, 14);
		printf("%80.0s");
		printfGreen("MEMBER MENU\n\n");
		printf("%80.0s");
		if (position == 1) printfH("Print list of members\n"); 
		else printf("Print list of members\n");
		printf("%80.0s");
		if (position == 2) printfH("Search for members\n");
		else printf("Search for members\n");
		printf("%80.0s");
		if (position == 3) printfH("Add members\n");
		else printf("Add members\n");
		printf("%80.0s");
		if (position == 4) printfH("Delete members\n");
		else printf("Delete members\n");
		printf("%80.0s");
		if (position == 5) printfH("Edit information\n");
		else printf("Edit information\n");
		printf("%80.0s");
		if (position == 6) printfH("Your account\n");
		else printf("Your account\n");
		printf("%80.0s");
		if (position == 7) printfH("Exit\n");
		else printf("Exit\n");

		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
				if (letter == - 32){
					letter = getch();
					if((letter == 80) && position < 7 ) {
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

int printMemberMenuM(int* pNum){

	int position = 1;
	char letter;
	int inputted = 1;
	*pNum = 0;
	do{		
		gotoxy(0, 14);
		printf("%80.0s");
		printfGreen("MEMBER MENU\n\n");
		printf("%80.0s");
		if (position == 1) printfH("Print list of members\n"); 
		else printf("Print list of members\n");
		printf("%80.0s");
		if (position == 2) printfH("Search for members\n");
		else printf("Search for members\n");		
		printf("%80.0s");
		if (position == 3) printfH("Your account\n");
		else printf("Your account\n");
		printf("%80.0s");
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
	system("cls");
}

int printAccSettingMenu(int* pNum){

	int position = 1;
	char letter;
	int inputted = 1;
	*pNum = 0;
	do{		
		gotoxy(0, 14);
		printf("%80.0s");
		printfGreen("ACCOUNT SETTING MENU\n\n");
		printf("%80.0s");
		if (position == 1) printfH("Edit your information\n"); 
		else printf("Edit your information\n");
		printf("%80.0s");
		if (position == 2) printfH("change your password\n");
		else printf("change your password\n");		
		printf("%80.0s");
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
