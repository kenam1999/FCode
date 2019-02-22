#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>
#include "string.h"
#include"print_menu.h"
#include"print_logo.h"
#include"gotoxy.h"
#include"decentralize.h"

char inputAddress[100] = "D:\\study\\train c\\classProject\\Nam\\member_Event_Attendant_Check\\";
int numStu;
char studentCurrentCode[9];
char decentralization[20];
//creat struct
struct students 
	{
		char studentCode[9];
		char pass[20];
		int course;
		char sex[4];
		char name[50];
	} student[100];
	
struct Event{
	char idEvent[4];
	char name[70];
	char time[20];
	char place[100];
	char contents[255];	
} event[100];

struct FundBudget {
	char idFund[4];
	char time[20];
	char contents[100];
	int64_t amount;
} fundBudget[100];

struct MonthlyFund{
	char time[20];
	int64_t amount;
}monthlyFund[100];

struct EventAttendance {
	int isRegistered;
	int isAttended;
	char MSSV[9];
}eventAttendance[100];

struct FundAtendance {	
	char MSSV[8];
	int isDone;
}FundAtendance[100];


//print function

void printTable(int numStu)
{
	system("cls");
	int startPosi = 0;
	char letter;
	int inputted = 1;
	int page = 1;
	do
	{		
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("|  Ord  |                      Name                        |    Sex     |Student Code| Course|\n");
		printf("|-------:--------------------------------------------------:------------:------------:-------|\n");
		int i = 0;
		while(i <= 19 && (i + startPosi) <= numStu - 1)
		{
			printf("|  %d\t", i + startPosi + 1);
			printInfo(i + startPosi);
			i++;
		}
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("                                            <%d>\n", page);
		printf("press [esc] to exit!");
		
		
		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
		
			if(letter == -32 || letter == 77 || letter == 75)
			{
			if((letter == 77) && startPosi < numStu - 21) 
			{
				startPosi += 20;
				inputted = 1;
				page++;
				//	system("cls");
			}else if((letter == 75) && startPosi >= 20) 
			{

				startPosi -= 20;
				inputted = 1;
				page--;
				//	system("cls");
			}
		}
			fflush(stdin);
		} while(letter != 27 && !inputted);
		system("cls");
	} while(letter != 27);
}

void deleteOddSpace(char str[])
{	
	while (str[0] == ' ') strcpy(&str[0], &str[1]);
	
	for (int i = 0; i <= strlen(str) - 1; i++)
	{
		if(str[i] == ' ' && str[i + 1] ==' ')
		{
			strcpy(&str[i], &str[i + 1]);
			i--;
		}
	}
	
	while(str[strlen(str) - 1] == ' ') strcpy(&str[strlen(str) - 1], &str[strlen(str)]);
}
	
void printInfo(int orderNum)
{
		char name[50];
		strcpy(name, student[orderNum].name);
		while (strlen(name) < 49)
		{
			strcat(name, " ");
		}
		printf("| %s|", name);
		printf("    %s\t|", student[orderNum].sex);
		printf("%10s  |",student[orderNum].studentCode);
		printf("  K%d  |", student[orderNum].course);
	
		printf("\n");
}
void getInfo(FILE* pAcc, int* pNumStu)
{
	*pNumStu = 0;
	while (!feof(pAcc))
	{
		fscanf(pAcc, "%s", &student[*pNumStu].studentCode);
		fflush(stdin);
		
		fscanf(pAcc, "%s", &student[*pNumStu].pass);
		
		fscanf(pAcc, "%d", &student[*pNumStu].course);
		
		fscanf(pAcc, "%s", &student[*pNumStu].sex);

		fgets(student[*pNumStu].name, 50, pAcc);			
		deleteOddSpace(student[*pNumStu].name);
		
		printf("\n");
		(*pNumStu)++;
	}
		for(int i = 0; i <= *pNumStu - 1; i++)
		{
			if(i != (*pNumStu) - 1)
			{
				student[i].name[strlen(student[i].name) - 1] = '\0';			
			}else student[i].name[strlen(student[i].name)] = '\0';
		}
}

//function check account
int checkAcc(int numStu, char username[], char password[], int* pNumAcc)
{
	for (int i = 0; i <= numStu - 1; i++)
	{
		if (strcmp(username, student[i].studentCode) == 0)
		{		
			if (strcmp(password, student[i].pass) == 0)
			{
				*pNumAcc = i;//to get position of user	
				return 1;
			}else return 0;
		}
	}
	return 0;
}

//get number
void announcementA(){
	char str[255] = "";
	int chooseNum;
	do{
		system("cls");
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
		printf("Hello, %s, your No. is %d\n", studentCurrentCode, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
		printf("Decentralization: [%s]", decentralization);
		gotoxy(0, 3);
		printLogo();
		
		printAnnouncementMenuA(&chooseNum);
		
		switch  (chooseNum) {
			case 1:{
				FILE *pFileAnn;
				pFileAnn = fopen("announcement.txt", "r");	
				
				//print header
				SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
				printf("Hello, %s, your No. is %d\n", studentCurrentCode, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
				printf("Decentralization: [%s]", decentralization);
				gotoxy(0, 3);
				printLogo();
				
				gotoxy(30, 12);
				printfGreen("Announcment from Administator\n\n");
				
				while (!feof(pFileAnn)) {
					fflush(stdin);
					fgets(str, 255, pFileAnn);
					if (str[strlen(str) - 1] == 10) 
						str[strlen(str) - 1] = 0;
					printf("%30.0s");
					printfGreen("|   ");
					puts(str);
				}
				fclose(pFileAnn);
				system("pause");
				break;
			}
			
			case 2:{
				FILE *pFileAnn;
				pFileAnn = fopen("announcement.txt", "w");
				
				//print header
				SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
				printf("Hello, %s, your No. is %d\n", studentCurrentCode, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
				printf("Decentralization: [%s]", decentralization);
				gotoxy(0, 3);
				printLogo();
				
				gotoxy(30, 12);
				printfGreen("Input announcement contents: \n");
				fflush(stdin);
				
				//Input text
				int letter;
				int prevousLine = 14;
				do {
					gotoxy(0, prevousLine);
					printf("%30.0s");
					printfGreen("|   ");
					gets(str);
					fputs(str, pFileAnn);
//					fputs("\n", pFileAnn);
					prevousLine++;
					
					gotoxy(0, 24);
					printfGreen("Press [enter] to comtinue\n[Esc] to finish Process\n");
					letter = getch();
					if (letter == 13) fputs("\n", pFileAnn);
				} while (letter != 27);
				
				fclose(pFileAnn);
				break;
			}
			
			case 3:{
				break;
			}
		}
	}while (chooseNum !=3);
}

void announcementM(){
	char str[255] = "";
	int chooseNum;
	
	do{
		system("cls");
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
		printf("Hello, %s, your No. is %d\n", studentCurrentCode, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
		printf("Decentralization: [%s]", decentralization);
		gotoxy(0, 3);
		printLogo();
		
		printAnnouncementMenuM(&chooseNum);
		
		switch  (chooseNum) {
			case 1:{
				FILE *pFileAnn;
				pFileAnn = fopen("announcement.txt", "r");	
				
				//print header
				SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
				printf("Hello, %s, your No. is %d\n", studentCurrentCode, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
				printf("Decentralization: [%s]", decentralization);
				gotoxy(0, 3);
				printLogo();
				
				gotoxy(30, 12);
				printfGreen("Announcment from Administator\n\n");
				
				while (!feof(pFileAnn)) {
					fflush(stdin);
					fgets(str, 255, pFileAnn);
					if (str[strlen(str) - 1] == 10) 
						str[strlen(str) - 1] = 0;
					printf("%30.0s");
					printfGreen("|   ");
					puts(str);
				}
				
				fclose(pFileAnn);
				getch();
				fflush(stdin);
				break;
			}
			case 2:{
				break;
			}
		
		}
	}while (chooseNum !=2);
}

int getnum(){
	int num;
	fflush(stdin);
	scanf("%d", &num);
	return(num);
	}

//Format value function
int64_t valueOfStrNum(char str[]){
	int i, offset;
	int64_t result = 0;
	
	if (str[0] == '+' || str[0] == '-')
		offset = 1;
	else offset = 0;
	
	for (i = offset; i < strlen(str); i++ ){
		result = result * 10 + str[i] - '0';
	}
	
	if (str[0] == '-') {
		result = - result;
	}
	return(result);
}

int noStuCoSearch(char studentCurrentCode[]){
	int i = 0;
	int flag = 1;
	while (i<= numStu - 1 && flag == 1) {
		if (strcmp(studentCurrentCode, student[i].studentCode) == 0){
			flag = 0;
		}
		i++;
	}
	if (flag == 1) return(-1);
	else return(i - 1);
}

// 2.1
void printRegisteredList(int *pNumEvent){
	system("cls");
	int startPosi = 0;
	char letter;
	int inputted;
	int page = 1;
	do
	{	
		gotoxy(0, 5);
		printf("%60.0s");
		printfGreen("Registered & attendant list\n");
		printf("%24.0s:-------:---------------------------------------------:-----------------:------------:------------:\n");
		printf("%24.0s|  Ord  |                   Name                      |       MSSV      | Registered |  Attended  |\n");
		printf("%24.0s|-------:---------------------------------------------:-----------------:------------:------------|\n");
		int i = 0;
		while(i <= 19 && (i + startPosi) <= numStu - 1)
		{
			printf("%24.0s");
			printf("|  %d\t", i + startPosi + 1);
			printRegisteredInfo(i + startPosi);
			i++;
		}
		printf("%24.0s:-------:---------------------------------------------:-----------------:------------:------------:\n");
		printf("%24.0s");
		printf("                                        <%d>\n", page);
		gotoxy(0, 32);
		printfGreen("Press [esc] to exit!");
		
		
		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
		
			if(letter == -32 || letter == 77 || letter == 75)
			{
			if((letter == 77) && startPosi < numStu - 21) 
			{
				startPosi += 20;
				inputted = 1;
				page++;
				//	system("cls");
			}else if((letter == 75) && startPosi >= 20) 
			{

				startPosi -= 20;
				inputted = 1;
				page--;
				//	system("cls");
			}
		}
			fflush(stdin);
		} while(letter != 27 && !inputted);
		system("cls");
	} while(letter != 27);
}

void printRegisteredInfo(int orderNum)
{
		char name[50];
		strcpy(name, student[orderNum].name);
		while (strlen(name) < 43)
		{
			strcat(name, " ");
		}
		printf("|  %s", name);
		printf("|     %s    |", eventAttendance[orderNum].MSSV);
		if (eventAttendance[orderNum].isRegistered == 0) 
			printf("            |");
		else printf("     X      |");
		if (eventAttendance[orderNum].isAttended == 0) 
			printf("            |");
		else printf("     X      |");	
//		printf("     %d      |", eventAttendance[orderNum].isRegistered);
//		printf("     %d      |",eventAttendance[orderNum].isAttended);	
		printf("\n");
}

void printEventList(int* pNumEvent){
//	system("cls");
	int numEvent = *pNumEvent;
	int startPosi = 0;
	char letter;
	int inputted;
	int page = 1;
	do
	{	
		system("cls");
		gotoxy(0, 5);
		printf("%75.0s");
		printfGreen(" Event list\n");
		printf(":-------:--------------------------------------------:--------------:----------------------:--------------------------------------------------------------------------------------------------:\n");
		printf("|   Id  |                     Name                   |     Time     |       Place          |                                                 Contents                                         |\n");
		printf(":-------:--------------------------------------------:--------------:----------------------:--------------------------------------------------------------------------------------------------:\n");
		int i = 1;
		while(i <= 7 && (i + startPosi) <= numEvent)
		{
//			printf("|  %d\t", i + startPosi);
			printEventInfo(i + startPosi - 1);
			i++;
		}
//		printf(":-------:--------------------------------------------:--------------:----------------------:--------------------------------------------------------------------------------------------------:\n");
		printf("                                                                                <%d>\n", page);
		gotoxy(0,40);
		printfGreen("Press [esc] to exit!");
		
		
		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
		
			if(letter == -32 || letter == 77 || letter == 75)
			{
			if((letter == 77) && startPosi + 7 < numEvent) 
			{
				startPosi += 7;
				inputted = 1;
				page++;
				//	system("cls");
			}else if((letter == 75) && startPosi >= 7) 
			{

				startPosi -= 7;
				inputted = 1;
				page--;
				//	system("cls");
			}
		}
			fflush(stdin);
		} while(letter != 27 && !inputted);
//		system("cls");
	} while(letter != 27);
}

void printEventInfo(int orderNum){
		int i = orderNum;
		printf("|  %s  ", event[i].idEvent);
		printf("| %s" ,event[i].name);
		for(int j = 1;(j <= 43 - strlen(event[i].name)); j++) {
			printf(" ");
		}
		printf("|  %s  ",event[i].time);
		printf("| %s",event[i].place);
		for(int j = 1;(j <= 21 - strlen(event[i].place)); j++) {
			printf(" ");
		}
		if (strlen(event[i].contents) <= 93)
		    printf("|    %s |\n", event[i].contents);
		else{
//			printf(": %0.93s... :\n", event[i].contents);
			char str[255];
			strcpy(str, event[i].contents);
			printf("|    %0.93s |\n", str);
			printf("|       |                                            |              |                      | ");
			int j = 93;
			while (j <= strlen(str)){
				if (j % 96 == 93 && j > 96){
				printf(" |\n");
				printf("|       |                                            |              |                      | ");
				}
				printf("%c", str[j]);
				j++;
			}
			
			int spaceAdd = (96 - (strlen(str) - 92) % 96);
			for (j = 0; j<= spaceAdd; j++ ) printf(" ");
			printf("|\n");
		}
		printf(":-------:--------------------------------------------:--------------:----------------------:--------------------------------------------------------------------------------------------------:\n");
}

int isExist(char str[]){
	FILE * pFile;
	if((pFile = fopen(str,"r"))!=NULL) {
        fclose(pFile);
        return(1);
    }
    else{
	   	return(0);
        }
}


//main's function

//Get input file
void getMonthFundInfo(FILE* pFileMonthlyFund, int* pNumMonthly){
	int i = 0;
	while (!feof(pFileMonthlyFund)){
		
		fgets(monthlyFund[i].time, 255, pFileMonthlyFund);
		monthlyFund[i].time[strlen(monthlyFund[i].time)-1] = 0;
//		printf("time: %s\t", monthlyFund[i].time);
		
		char tmp[255];
		fgets(tmp, 255, pFileMonthlyFund);
		if (tmp[strlen(tmp)-1] == 10)
			tmp[strlen(tmp)-1] = 0;
		monthlyFund[i].amount = valueOfStrNum(tmp);
//		printf("amount: %I64d\n", monthlyFund[i].amount);
		i++;
	}
		*pNumMonthly = i - 1;
}
void getFundBudgetInfo(FILE* pFileStatistic, int* pNumStatistic){
	int i = 0;
	while (!feof(pFileStatistic)){
		
		fgets(fundBudget[i].idFund, 255, pFileStatistic);
		fundBudget[i].idFund[strlen(fundBudget[i].idFund)-1] = 0;
		
		fgets(fundBudget[i].time, 255, pFileStatistic);
		fundBudget[i].time[strlen(fundBudget[i].time)-1] = 0;
		
		fgets(fundBudget[i].contents, 255, pFileStatistic);
		fundBudget[i].contents[strlen(fundBudget[i].contents)-1] = 0;
		
		char tmp[255];
		fgets(tmp, 255, pFileStatistic);
		if (tmp[strlen(tmp)-1] == 10)
			tmp[strlen(tmp)-1] = 0;
		fundBudget[i].amount = valueOfStrNum(tmp);	
		
		i++;
	}
		*pNumStatistic = i - 1;
}

void printFundStatisticList(int* pNumEvent){
//	system("cls");
	int numEvent = *pNumEvent;
	int startPosi = 0;
	char letter;
	int inputted;
	int page = 1;
	do
	{	
		system("cls");
		gotoxy(70, 5);
		printfGreen("Fund budget List list\n\n");
		printf("%20.0s:-------:--------------:------------------------------------------------------------------------------:-------------------:\n");
		printf("%20.0s|   Id  |     Time     |                                                 Contents                     |        Amount     |\n");
		printf("%20.0s:-------:--------------:------------------------------------------------------------------------------:-------------------:\n");
		int i = 1;
		while(i <= 10 && (i + startPosi) <= numEvent + 1)
		{
//			printf("|  %d\t", i + startPosi);
			printf("%20.0s");
			printFundStatisticInfo(i + startPosi - 1);
			i++;
		}
		printf("%20.0s:-------:--------------:------------------------------------------------------------------------------:-------------------:\n");
		printf("%20.0s");
		printf("                                                         <%d>\n", page);
		gotoxy(0,25);
		printfGreen("Press [esc] to exit!");
		
		
		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
		
			if(letter == -32 || letter == 77 || letter == 75)
			{
			if((letter == 77) && startPosi + 10 < numEvent) 
			{
				startPosi += 10;
				inputted = 1;
				page++;
				//	system("cls");
			}else if((letter == 75) && startPosi >= 10) 
			{

				startPosi -= 10;
				inputted = 1;
				page--;
				//	system("cls");
			}
		}
			fflush(stdin);
		} while(letter != 27 && !inputted);
//		system("cls");
	} while(letter != 27);
}

//
void printFundStatisticInfo(int orderNum){
	int i = orderNum;
	printf("|  %s  ", fundBudget[i].idFund);
	printf("|  %s  ",fundBudget[i].time);
	printf("| %s",fundBudget[i].contents);
	for(int j = 1;(j <= 77 - strlen(fundBudget[i].contents)); j++) {
		printf(" ");
	}
	printf("|");
	
	int position = 0;
	int64_t tmp = fundBudget[i].amount;
	if (fundBudget[i].amount < 0 ) position = position + 1;
	while (tmp / 10 != 0){
		tmp = tmp / 10;
		position++;
	}
	
	gotoxy(140 - position, 10 + i);
//	printf ("%d", position);
	printf("%I64d", fundBudget[i].amount);
	gotoxy(142, 10 + i);
	printf("|\n");
}
		    
//fund menu
void fundMenuM(int* pNumMonthly, int* pNumStatistic){

	//Print to screen
	int chooseFundMenu;
	FILE *pFileMonthlyFund;
	pFileMonthlyFund = fopen("monthly_statistic.txt", "r");
				
	FILE *pFileStatistic;
	pFileStatistic = fopen("fund_statistic.txt", "r");
	do{
		system("cls");
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
		printf("Hello, %s, your No. is %d\n", studentCurrentCode, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
		printf("Decentralization: [%s]", decentralization);
		gotoxy(0, 3);
		printLogo();
		
		printFundMenuM(&chooseFundMenu);
		
		//following num
		switch (chooseFundMenu){
			case 1:{
				if (*pNumStatistic == 0) getFundBudgetInfo(pFileStatistic, pNumStatistic);
				printFundStatisticList(pNumStatistic);
//				system("pause");
				break;
			}
			case 2:{
				if (*pNumMonthly == 0) getMonthFundInfo(pFileMonthlyFund, pNumMonthly);
				system("cls");
				gotoxy(60, 5);
				printfGreen("Monthly fund's available balances\n\n");
				for (int i = 0; i <= *pNumMonthly; i++){
					printf("%40.0s");
					printf("Time: %s\t", monthlyFund[i].time);
					printf("amount: %I64d\n\n", monthlyFund[i].amount);
				}
				system("pause");
				break;
			}
			case 3:{
				
				//exit
				fclose(pFileMonthlyFund);
				fclose(pFileStatistic);
				break;
			}
		}
	}while (chooseFundMenu != 3);
}

//
void getEventList(FILE* pFileEvent, int* pNumEvent) {
int i = 0;
		while (!feof(pFileEvent)){
			
			fgets(event[i].idEvent, 255, pFileEvent);
			event[i].idEvent[strlen(event[i].idEvent)-1] = 0;
			fflush(stdin);

			fgets(event[i].name, 255, pFileEvent);
			event[i].name[strlen(event[i].name)-1] = 0;
			fflush(stdin);
			
			fgets(event[i].time, 255, pFileEvent);
			event[i].time[strlen(event[i].time)-1] = 0;
			fflush(stdin);

			fgets(event[i].place, 255, pFileEvent);
			event[i].place[strlen(event[i].place)-1] = 0;
			fflush(stdin);
			
			fgets(event[i].contents, 255, pFileEvent);
			if (event[i].contents[strlen(event[i].contents) - 1] == 10)
				event[i].contents[strlen(event[i].contents) - 1] = 0;
			fflush(stdin);
			
			i++;
		}
		*pNumEvent = i;
//		system("pause");
}

//event menu
void eventMenuAdmin(FILE* pFileEvent, int* pNumEvent){
	
	//Get input file
	getEventList(pFileEvent, pNumEvent);
	//Print to screen
	int chooseEventMenu;
	do{
		system("cls");
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
		printf("Hello, %s, your No. is %d\n", studentCurrentCode, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
		printf("Decentralization: [%s]", decentralization);
		gotoxy(0, 3);
		printLogo();
	
		chooseEventMenuA(&chooseEventMenu);
		
		//following num
		switch (chooseEventMenu){
			case 1:{
				// print event list
				printEventList(pNumEvent);
				break;
			}
			case 2:{
				
				//creat files's address
				char address[100];
//				printEventList(pNumEvent);
				creatRegisterAddress(address);
				printf("Confirm address: \"%s\"\n", address);
				
				//creat table if it hasn't existed
				if (isExist(address) == 0) {
					FILE* pFileCreat;
					pFileCreat = fopen(address, "w");		
					creatRegisterForm(pFileCreat);
					fclose(pFileCreat);
					printf("File has not existed\nCreating new list...\n");
				}
		
				//get information from file
				FILE* pFileRead;
				pFileRead = fopen(address, "r");
								
				getRegistered(pFileRead);
				fclose(pFileRead);
				
				//edit information from file
				int num;
				num = noStuCoSearch(studentCurrentCode);
				eventAttendance[num].isRegistered = 1;	
			
			
				printf(":---------------------------------------------:-----------------:------------:------------:\n");
				printf("|                   Name                      |       MSSV      | Registered |  Attended  |\n");
				printf(":---------------------------------------------:-----------------:------------:------------|\n");
				printRegisteredInfo(num);
				printf("'---------------------------------------------'-----------------'------------'------------'\n");
				
				//Write in file
				FILE* pFileWrite;
				pFileWrite = fopen(address, "w");
				writeEAL(pFileWrite);
				fclose(pFileWrite);
				
				printfGreen("Register success!\n");
				system("pause");
				
				break;
			}
			case 3:{			
				//reat files's address
				char address[100];
//				printEventList(pNumEvent);
				creatRegisterAddress(address);
				
				//creat table if it hasn't existed
				if (isExist(address) == 0) {
					FILE* pFileCreat;
					pFileCreat = fopen(address, "w");		
					creatRegisterForm(pFileCreat);
					fclose(pFileCreat);
					printf("File has not existed\nCreating new list...\n");
				}
		
				//get information from file
				FILE* pFileRead;
				pFileRead = fopen(address, "r");
								
				getRegistered(pFileRead);
				fclose(pFileRead);
				
				printRegisteredList(&numStu);
				break;
			}
			
			case 4:{
				//creat files's address
				char address[100];
				creatRegisterAddress(address);
				printf("Confirm address: \"%s\"\n", address);
				
				//creat table if it hasn't existed
				if (isExist(address) == 0) {
					FILE* pFileCreat;
					pFileCreat = fopen(address, "w");		
					creatRegisterForm(pFileCreat);
					fclose(pFileCreat);
					printf("File has not existed\nCreating new list...\n");
				}
		
				//get information from file
				FILE* pFileRead;
				pFileRead = fopen(address, "r");
								
				getRegistered(pFileRead);
				fclose(pFileRead);
				
				//edit information from file
				int num;
				char studentCode[9];
				do {
					printf("Input student Code:");
					fflush(stdin);
					scanf("%s", studentCode);
				}while (noStuCoSearch(studentCode) == -1) ;
				
				num = noStuCoSearch(studentCode);
				eventAttendance[num].isAttended = 1;	
			
				printf(":---------------------------------------------:-----------------:------------:------------:\n");
				printf("|                   Name                      |       MSSV      | Registered |  Attended  |\n");
				printf(":---------------------------------------------:-----------------:------------:------------|\n");
				printRegisteredInfo(num);
				printf("'---------------------------------------------'-----------------'------------'------------'\n");
				
				//Write in file
				FILE* pFileWrite;
				pFileWrite = fopen(address, "w");
				writeEAL(pFileWrite);
				fclose(pFileWrite);
				
				printfGreen("Check attendant success!\n");
				system("pause");
				break;
			}
			case 5:{
			}
		
		}
	}while (chooseEventMenu != 5);
}	

void eventMenuM(FILE* pFileEvent, int* pNumEvent){
	
	//Get input file
	getEventList(pFileEvent, pNumEvent);
	//Print to screen
	int chooseEventMenu;
	do{
		system("cls");
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
		printf("Hello, %s, your No. is %d\n", studentCurrentCode, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
		printf("Decentralization: [%s]", decentralization);
		gotoxy(0, 3);
		printLogo();
		
		chooseEventMenuM(&chooseEventMenu);
		
		//following num
		switch (chooseEventMenu){
			case 1:{
				// print event list
				printEventList(pNumEvent);
				break;
			}
			case 2:{
				
				//creat files's address
				char address[100];
//				printEventList(pNumEvent);
				creatRegisterAddress(address);
				printf("Confirm address: \"%s\"\n", address);
				
				//creat table if it hasn't existed
				if (isExist(address) == 0) {
					FILE* pFileCreat;
					pFileCreat = fopen(address, "w");		
					creatRegisterForm(pFileCreat);
					fclose(pFileCreat);
					printf("File has not existed\nCreating new list...\n");
				}
		
				//get information from file
				FILE* pFileRead;
				pFileRead = fopen(address, "r");
								
				getRegistered(pFileRead);
				fclose(pFileRead);
				
				//edit information from file
				int num;
				num = noStuCoSearch(studentCurrentCode);
				eventAttendance[num].isRegistered = 1;	
			
				printf(":---------------------------------------------:-----------------:------------:------------:\n");
				printf("|                   Name                      |       MSSV      | Registered |  Attended  |\n");
				printf(":---------------------------------------------:-----------------:------------:------------|\n");
				printRegisteredInfo(num);
				printf("'---------------------------------------------'-----------------'------------'------------'\n");
				
				//Write in file
				FILE* pFileWrite;
				pFileWrite = fopen(address, "w");
				writeEAL(pFileWrite);
				fclose(pFileWrite);
				
				printfGreen("Register success!\n");
				system("pause");
				
				break;
			}
			case 3:{			
				//reat files's address
				char address[100];
//				printEventList(pNumEvent);
				creatRegisterAddress(address);
				
				//creat table if it hasn't existed
				if (isExist(address) == 0) {
					FILE* pFileCreat;
					pFileCreat = fopen(address, "w");		
					creatRegisterForm(pFileCreat);
					fclose(pFileCreat);
					printf("File has not existed\nCreating new list...\n");
				}
		
				//get information from file
				FILE* pFileRead;
				pFileRead = fopen(address, "r");
								
				getRegistered(pFileRead);
				fclose(pFileRead);
				
				printRegisteredList(&numStu);
				break;
			}
			
			case 4:{
				
			}
		}
	}while (chooseEventMenu != 4);
}	


void creatRegisterAddress(char address[]) {
	strcpy(address, "");
	//declare file address
	char idEvent[4];
	printf("\n%40.0s");
	printfGreen("Input event's id: ");
	fflush(stdin);
	scanf("%s", idEvent);
	strcat(address, inputAddress);
	strcat(address, idEvent);
	strcat(address, ".txt");
//	printf("\nFile located: \"%s\" \n", address);
}

void creatRegisterForm(FILE* pFile) {
		//creatEAL(pFileCreat);		
		char tmp[100] ="";
		printf("number of student: %d\n", numStu);
		
		for (int i = 0; i <= numStu -1; i++) {
			strcpy(tmp,"");
			strcat(tmp,"0 0 ");
			strcat(tmp,student[i].studentCode);
			if (i < numStu -1)
				strcat(tmp,"\n");
			fprintf(pFile, tmp);
		}
}

void getRegistered(FILE* pFile){
	//get infermation from file
	int i = 0;
	char tmp[100];	
	while (!feof(pFile)){
		fflush(stdin);
		fscanf(pFile, "%d", &eventAttendance[i].isRegistered);		
		fscanf(pFile, "%d", &eventAttendance[i].isAttended);		
		fscanf(pFile, "%s", eventAttendance[i].MSSV);			
		i++;
	}	
}

void writeEAL(FILE* pFile){
	int i = 0;
	char tmp[8];
	for (i ; i<= numStu - 2; i++){
		fflush(stdin);
		fprintf(pFile, "%d %d %s\n", eventAttendance[i].isRegistered, eventAttendance[i].isAttended, eventAttendance[i].MSSV);
	}
	fprintf(pFile, "%d %d %s", eventAttendance[numStu - 1].isRegistered, eventAttendance[numStu - 1].isAttended, eventAttendance[numStu - 1].MSSV);
}

//main code
 int main(int argc, char *argv[]) {
	
	gotoxy(0,8);
	printFCode();
	int chooseNumber;
	
//admin acc
	strcat(studentCurrentCode, "SE130122");
//member acc
//	strcat(studentCurrentCode, "SE140831");

	FILE* pFileStu;
	pFileStu = fopen("account.txt", "r");
	getInfo(pFileStu, &numStu);
	
	if (decentralizeStu(studentCurrentCode) == 1) {
		strcpy(decentralization, "Administator");
	} else if (decentralizeStu(studentCurrentCode) == 2) {
		strcpy(decentralization, "Fund Manager");
	} else strcpy(decentralization, "Club member");
	
	do{
		
		system("cls");
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
		printf("Hello, %s, your No. is %d\n", studentCurrentCode, noStuCoSearch(studentCurrentCode) + 1); 
		//noStuCoSearch(studentCurrentCode) is No. in DB
		printf("Decentralization: [%s]", decentralization);
		
		gotoxy(0, 3);
		printLogo();
		
		printMainMenu(&chooseNumber);
		switch (chooseNumber){
			
			case 1:{
				printTable(numStu);
				break;
			}
			
			case 2:{
				// event menu
				FILE *pFileEvent;
				pFileEvent = fopen("event.txt", "r");
				int numEvent;
				
				if(decentralizeStu(studentCurrentCode) == 1) 
					eventMenuAdmin(pFileEvent, &numEvent);
				else
					eventMenuM(pFileEvent, &numEvent);
				fclose(pFileEvent);
				break;
			}
			
			case 3:{
				
				//fund menu
				
				int numMonthly = 0;
				int numStatistic = 0;
				fundMenuM(&numMonthly, &numStatistic);
				break;
			}
			case 4:{
				
				//announcement
				
				if(decentralizeStu(studentCurrentCode) == 1) 
					announcementA();
				else
					announcementM();
									
				break;
			}
			case 5:{
				//exit
				break;
			}	
		}
	 		
	}while (chooseNumber != 5);
}
