#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include "string.h"
#include"print_menu.h"
#include"print_logo.h"
#include"gotoxy.h"

#include"decentralize.h"
#include "choice.h"
#include "getAcc.h"
#include "menu.h"

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


//Hoa's function

void upperCase(char str[])
{

	str[0] = toupper(str[0]);
	if (strlen(str) != 1)
	{
		for (int i = 1; i <= strlen(str) - 2; i++)
		{
			if (str[i] == ' ') str[i + 1] = toupper(str[i + 1]);
		}
	}
}

//Function get course
int getCourse(char studentCode[])
{
	char course[3];
	int j = 0;
	for (int i = 2; i <= 3; i++)
	{
		course[j] = studentCode[i];
		j++;
	}
	return atoi(course);
}

//funtion write updated information on file
void writeFile(FILE* pAcc, int numStu)
{
	pAcc = fopen("account.txt", "w");
	for (int i = 0; i <= numStu - 1; i++)
	{
		fprintf(pAcc, "%s " , student[i].studentCode);
		fprintf(pAcc, "%s ", student[i].pass);
		fprintf(pAcc, "%d ", student[i].course);
		fprintf(pAcc, "%s ", student[i].sex);
		fputs(student[i].name, pAcc);
		if(i != numStu - 1)
		{
			fprintf(pAcc, "\n");
		}
	}
	fclose(pAcc);
}

void swap(int firstPosi, int secondPosi)
{
	//swap student code
	char tmpStuCode[9];
	strcpy(tmpStuCode, student[firstPosi].studentCode);
	strcpy(student[firstPosi].studentCode, student[secondPosi].studentCode);
	strcpy(student[secondPosi].studentCode, tmpStuCode);
	
	//swap password
	char tmpPass[4];
	strcpy(tmpPass, student[firstPosi].pass);
	strcpy(student[firstPosi].pass, student[secondPosi].pass);
	strcpy(student[secondPosi].pass, tmpPass);
	
	//swap sex
	char tmpSex[4];	
	strcpy(tmpSex, student[firstPosi].sex);
	strcpy(student[firstPosi].sex, student[secondPosi].sex);
	strcpy(student[secondPosi].sex, tmpSex);
	
	//swap name
	char tmpName[50];
	strcpy(tmpName, student[firstPosi].name);
	strcpy(student[firstPosi].name, student[secondPosi].name);
	strcpy(student[secondPosi].name, tmpName);
	
	//swap course
	int tmpCourse = student[firstPosi].course;
	student[firstPosi].course = student[secondPosi].course;
	student[secondPosi].course = tmpCourse;
	
}

//function cut string to get single word
void cutWord(char substring[], char sourceString[])
{
	char spa[2] = " ";
	if (strstr(sourceString, spa) == '\0')
	{
		strcpy(substring, sourceString);
	}else 
		{
			for (int i = strlen(sourceString) - 1; i >= 0; i--)
			{
				if(sourceString[i] == ' ')
				{		
					int j = 0;
					for (int k = i + 1; k <= strlen(sourceString); k++)
					{
						substring[j] = sourceString[k];
						j++;						
					}
					sourceString[i] = '\0';
					break;
				}
			}
		}

}	

//Function compare name
int compareString(char name1[], char name2[])
{
	char substring1[8];
	char substring2[8];
	if (strcmp(name1, name2) == 0) return 0;
	while (name1 != '\0' && name2 != '\0')
	{
		cutWord(substring1, name1);
		cutWord(substring2, name2);
		if (strcmp(substring1, substring2) > 0) return 1;
		else if(strcmp(substring1, substring2) < 0) return (- 1);
	}
	return 0;	
}


//Sort student list
void sortStuList(int numStu)
{
	char tmpName1[50];
	char tmpName2[50];
	for (int i = 0; i <= numStu - 1; i++)
	{
		for (int j = 0; j <= numStu - 2 - i; j++)
		{
			if (student[j].course > student[j + 1].course)
			{
				swap(j, j + 1);
			} else if (student[j].course == student[j + 1].course)
					{
						strcpy(tmpName1, student[j].name);
						strcpy(tmpName2, student[j + 1].name);
						if (compareString(tmpName1, tmpName2) > 0)
						{
							swap(j, j + 1);
						}
					}
		}
	}
}

void deleMem(FILE* pAcc, int* pNumStu, int posi)
{
	for(int i = posi; i <= *pNumStu - 2; i++)
	{
		strcpy(student[i].name, student[i + 1].name);
		strcpy(student[i].pass, student[i + 1].pass);
		strcpy(student[i].sex, student[i + 1].sex);
		strcpy(student[i].studentCode, student[i + 1].studentCode);
		student[i].course = student[i + 1].course;
	}
	(*pNumStu)--;
	 writeFile(pAcc, *pNumStu);
}


//funtion delete member in table directly
void deleteInTable(int numStu, FILE* pAcc)
{
	int number;
	int startPosi = 0;
	char tmp[5];
	char letter;
	int inputted = 0 ;
	int page = 1;
	for(int i = 0; i <= 3; i++)
	{
		tmp[i] = '\0';
	}
	int i = 0;
	
	do
	{	
		if(letter == 13)
		{
			if(strlen(tmp) >= 1)
			{
				int length = strlen(tmp);
				for (int k = 0; k <= length - 1; k++)
				{
					tmp[k] = '\0';
				}
			}
			i = 0;
		}
		
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("|  Ord  |                      Name                        |    Sex     |Student Code| Course|\n");
		printf("|-------:--------------------------------------------------:------------:------------:-------|\n");
		int j = 0;
		while(j <= 19 && (j + startPosi) <= numStu - 1)
		{
			printf("|  %d\t", j + startPosi + 1);
			printInfo(j + startPosi);
			j++;
		}
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("                                            <%d>\n", page);
		printf("press [esc] to exit!\n");
		printf("\n");
		
		printf("Enter oder number you want to delete: ");
		do
		{
			if(inputted)
			{
				printf("%s", tmp);
			}
			inputted = 0;
			
			fflush(stdin);
			letter = getch();
			if(letter >= 48 && letter <= 57)
			{
				printf("%c", letter);
				tmp[i] = letter;
				i++;				
			}else if(letter == - 32 || letter == 77 || letter == 75 || letter == 13 || letter == 8)
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
				if (letter == 13 && strlen(tmp) >= 1)
				{
					number =  atoi(tmp);	
					if(number <= numStu && number >= 1)
					{
							
						char temp;
						int yes = 1;
						tmp[i] = '\0';
						system("cls");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("                           ___________________________________________________________________________\n");
						printf("                           |                                                                         |\n");
						printf("                           |                  You really want to delete this member?                 |\n");
						printf("                           |                _______                                                  |\n");
						printf("                           |________________|_Yes_|_________________________No_______________________|\n");
						do
						{
						
							temp = getch();
							if(temp == - 32 || temp == 77 || temp == 75)
							{
								if(temp == 77)
								{
									yes = 0;
									system("cls");
									printf("\n");
									printf("\n");
									printf("\n");
									printf("                           ___________________________________________________________________________\n");
									printf("                           |                                                                         |\n");
									printf("                           |                  You really want to delete this member?                 |\n");
									printf("                           |                                             ______                      |\n");
									printf("                           |_________________Yes_________________________|_No_|______________________|\n");
								}
								if(temp == 75)
								{
									yes = 1;
									system("cls");
									printf("\n");
									printf("\n");
									printf("\n");
									printf("                           ___________________________________________________________________________\n");
									printf("                           |                                                                         |\n");
									printf("                           |                  You really want to delete this member?                 |\n");
									printf("                           |                _______                                                  |\n");
									printf("                           |________________|_Yes_|_________________________No_______________________|\n");
								}
							}
						}while(temp != 13);
						if(yes)
						{
							deleMem(pAcc, &numStu, number - 1);
						}
					}
				}
				if (letter == 8 && i > 0)
				{
					tmp[i - 1] = '\0';
					i--;
					inputted = 1;
				}		
			}
	
			
			fflush(stdin);
		} while(letter != 27 && !inputted && letter != 13);

		
		system("cls");
	} while(letter != 27);
}

int checkID(char str[], int numStu, int numAcc)
{
	if(strlen(str) == 8)
	{
		if((str[0] == 'I' && str[1] == 'A') || (str[0] == 'S' && str[1] == 'E'))
		{
			for(int i = 2; i < 8; i++)
			{
				if(str[i] < '0' || str[i] > '9') return 0;
			}
		}else return 0;
	}else return 0;
	
	for (int i = 0; i <= numStu - 1; i++)
	{
		if (i != numAcc)
		{
			if (strcmp(str, student[i].studentCode) == 0)
			{
				return 2;
			}	
		}
	}
	return 1;
}

//function edit single member information
void editMem(int numStu, int number, FILE* pAcc)
{
		char temp;
		char tmp[50];
		char tmpCode[9];
		strcpy(tmpCode, student[number - 1].studentCode);
		
	do
	{
					if(number <= numStu && number >= 1)
					{
						char tmpName[50];
						strcpy(tmpName, student[number - 1].name);
						
						printf("_");
						char tmpSex[4];
						strcpy(tmpSex, student[number - 1].sex);
								
						int posi  = 1;
						do
						{
							int inputted = 0;
							switch (posi)
							{
								case 1:
									system("cls");
									strcpy(tmp, tmpName);
									while (strlen(tmp) < 48)
									{
										strcat(tmp, " ");
									}
									printf("\n%35.0s");
									printfGreen("EDIT YOUR ACCOUT");
									printf("\n");
									printf(":--------------------------------------------------:------------:------------:\n");
									printf("|                      Name                        |    Sex     |Student Code|\n");
									printf(":--------------------------------------------------:------------:------------:\n");
									printf(": ");
									printfH(tmp);
									printf(" : ");
								//	deleteOddSpace(tmpName);
									//printf("_");
									printf(" %s", tmpSex);
									gotoxy(59, 5);
									printf(" ^|v ");
									printf(": ");
									printf("%s", tmpCode);
									gotoxy(77, 5);
									printf(":\n");
									printf(":--------------------------------------------------:------------:------------:\n");
									break;
								case 2:
									system("cls");
									strcpy(tmp, tmpName);
									while (strlen(tmp) < 48)
									{
										strcat(tmp, " ");
									}
									printf("\n%35.0s");
									printfGreen("EDIT YOUR ACCOUT");
									printf("\n");
									printf(":--------------------------------------------------:------------:------------:\n");
									printf("|                      Name                        |    Sex     |Student Code|\n");
									printf(":--------------------------------------------------:------------:------------:\n");
									printf(": ");
									printf(tmp);
									printf(" : ");
								//	deleteOddSpace(tmpName);
									//printf("_");
									printf(" %s", tmpSex);
									gotoxy(59, 5);
									printfH(" ^|v ");
									printf(": ");
									printf("%s", tmpCode);
									gotoxy(77, 5);
									printf(":\n");
									printf(":--------------------------------------------------:------------:------------:\n");
									break;
								case 3:
									system("cls");
									strcpy(tmp, tmpName);
									while (strlen(tmp) < 48)
									{
										strcat(tmp, " ");
									}
									printf("\n%35.0s");
									printfGreen("EDIT YOUR ACCOUT");
									printf("\n");
									printf(":--------------------------------------------------:------------:------------:\n");
									printf("|                      Name                        |    Sex     |Student Code|\n");
									printf(":--------------------------------------------------:------------:------------:\n");
									printf(": ");
									printf(tmp);
									printf(" : ");
								//	deleteOddSpace(tmpName);
									//printf("_");
									printf(" %s", tmpSex);
									gotoxy(59, 5);
									printf(" ^|v ");
									printf(": ");
									printfH(tmpCode);
									gotoxy(77, 5);
									printf(":\n");
									printf(":--------------------------------------------------:------------:------------:\n");
									break;
								
							}
							temp = getch();
							
							if( temp == - 32)
							{
								temp = getch();
								if (temp == 77 && posi < 3)
								{
									posi++;
								}
								
								if (temp == 75 && posi >=2)
								{
									posi --;
								
								}
								
								if (temp == 80)
								{
									if (posi == 2)
									{
										if(strcmp(tmpSex, "Nam") == 0)
										{
											strcpy(tmpSex, "Nu");
										} else strcpy(tmpSex, "Nam");
									}
								}
								
								if(temp == 72)
								{
									if (posi == 2)
									{
										if(strcmp(tmpSex, "Nam") == 0)
										{
											strcpy(tmpSex, "Nu");
										} else strcpy(tmpSex, "Nam");
									}
									
								}
							}else if(temp != - 32 )
										{
											if(temp == 32 || (temp >= 48 && temp <= 57) || (temp >= 65 && temp <= 90) || (temp >= 97 && temp <= 122))
											{
												if(posi == 1)
												{											
													tmpName[strlen(tmpName) + 1] = '\0';
													tmpName[strlen(tmpName)] = temp;	
												}
												if(posi == 3)
												{
													tmpCode[strlen(tmpCode) + 1] = '\0';
													tmpCode[strlen(tmpCode)] = temp;	
												}
											}	
										}
								
							
							if (temp == 8)
							{
								if (posi == 1)
								{
									tmpName[strlen(tmpName) - 1] = '\0';
								}
								if (posi == 3)
								{
									tmpCode[strlen(tmpCode) - 1] = '\0';
								}
							}
							
						}while(temp != 13 && temp != 27);
						
						if(temp == 13)
						{
							if(checkID(tmpCode, numStu, number - 1) == 2)
							{
								system("cls");
								printf("\n\n\n\n\n\n");
								printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
								printf("\t\t\t\t\t!  The student code has been existed!  !\n");
								printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
								getchar();
							}else if(checkID(tmpCode, numStu, numStu) == 0)
								{
									system("cls");
									printf("\n\n\n\n\n\n");
									printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
									printf("\t\t\t\t\tThe student code is invalid!\n");
									printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
									getchar();
								} else
									{
										
										strcpy(student[number - 1].name, tmpName);
										strcpy(student[number - 1].sex, tmpSex);
										strcpy(student[number - 1].studentCode, tmpCode);
										student[number - 1].course = getCourse((student[number - 1].studentCode));
										sortStuList(numStu);
										writeFile(pAcc, numStu);
										break;
							}
						}
							
					}
					if (temp == 27) break;
	}while(1);
	system("cls");
}


//function edit information in table
void editInTable(int numStu, FILE* pAcc)
{
	int number;
	int startPosi = 0;
	char tmp[5];
	char letter;
	int inputted = 0 ;
	int page = 1;
	for(int i = 0; i <= 3; i++)
	{
		tmp[i] = '\0';
	}
	int i = 0;
	
	do
	{	
		if(letter == 13)
		{
			if(strlen(tmp) >= 1)
			{
				int length = strlen(tmp);
				for (int k = 0; k <= length - 1; k++)
				{
					tmp[k] = '\0';
				}
			}
			i = 0;
		}
	//	printf("i = %d", i);
		
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("|  Ord  |                      Name                        |    Sex     |Student Code| Course|\n");
		printf("|-------:--------------------------------------------------:------------:------------:-------|\n");
		int j = 0;
		while(j <= 19 && (j + startPosi) <= numStu - 1)
		{
			printf("|  %d\t", j + startPosi + 1);
			printInfo(j + startPosi);
			j++;
		}
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("                                            <%d>\n", page);
		printf("press [esc] to exit!\n");
		printf("\n");
		
		printf("Enter oder number you want to edit: ");
		do
		{
			if(inputted)
			{
				printf("%s", tmp);
			}
			inputted = 0;
			
			fflush(stdin);
			letter = getch();
			if(letter >= 48 && letter <= 57)
			{
				printf("%c", letter);
				tmp[i] = letter;
				i++;				
			}else if(letter == - 32 || letter == 77 || letter == 75 || letter == 13 || letter == 8)
			{
				if((letter == 77) && startPosi < numStu - 21) 
				{
					startPosi += 20;
					inputted = 1;
					page++;
				}else if((letter == 75) && startPosi >= 20) 
						{
							startPosi -= 20;
							inputted = 1;
							page--;
						}
						
				number = atoi(tmp);		
				if (letter == 13 && strlen(tmp) >= 1)
				{
					editMem(numStu, number, pAcc);					
				}
				if (letter == 8 && i > 0)
				{
					tmp[i - 1] = '\0';
					i--;
					inputted = 1;
				}		
			}
	
			
			fflush(stdin);
		} while(letter != 27 && !inputted && letter != 13);

		
		system("cls");
	} while(letter != 27);
}	


//function check number
int checkNum(char str[])
{
	for(int i = 0; i <= strlen(str) - 1; i++)
	{
		if(str[i] < 48 || str[i] > 57)
		{
			return 0;
		}
	}
	return 1;
}

//function search student
void searchStudent(int numStu)
{
	char tmp;
	char element[50];
	while(1)
	{
	for (int i = 0; i <= 49; i++)
	{
		element[i] = '\0';
	}
	int i = 0;
	do
	{
		system("cls");
			//printf("\n\n\n\n\n\n\n");
		printf("_______________________________________________________\n");
		printf("| Enter elements you want to find:  %s\n", element);
		printf("_______________________________________________________\n");
		if(strlen(element) > 0)
		{
			for (int j = 0; j <= numStu - 1; j ++)
			{
				if (strstr(student[j].name, element) != '\0')
				{
					char name[50];
					strcpy(name, student[j].name);
					while (strlen(name) < 40)
					{
						strcat(name, " ");
					}
					printf("-------------------------------------------\n");
					printf("| %s|\n", name);
					printf("-------------------------------------------\n");
					//printf("%s\n", student[j].name);
				}else if(strstr(student[j].studentCode, element) != '\0')
					{
						//printf("%s\n", student[j].studentCode);
						char code[9];
						strcpy(code, student[j].studentCode);
						while (strlen(code) < 9)
						{
							strcat(code, " ");
						}
						printf("------------\n");
						printf("| %s|\n", code);
						printf("------------\n");	
									
					}else if(strstr(student[j].sex, element) != '\0')
						{
						
							printf("%s\n", student[j].sex);
							break;
						}else if(checkNum(element))
						{
								if(atoi(element) == student[j].course)
								{
									printf("%d", student[j].course);
									break;	
								}
						}
			}
		}
	
		tmp = getch();
		if(tmp == 32 || (tmp >= 48 && tmp <= 57) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
		{
			element[i] = tmp;
			i++;
			upperCase(element);	
		}
		if (tmp == 8 && i >= 1) 
		{
			i--;
			element[i] = '\0';
		}
		
			
	}while(tmp != 13 && tmp != 27);
	if(tmp == 13 && strlen(element) > 0)
	{
		int found = 0;
		int k = 0;
		system("cls");
		deleteOddSpace(element);
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("|  Ord  |                      Name                        |    Sex     |Student Code| Course|\n");
		printf("|-------:--------------------------------------------------:------------:------------:-------|\n");
		for (int j = 0; j <= numStu - 1; j ++)
		{
			if (checkNum(element))
			{
				if(atoi(element) == student[j].course)
				{
					k++;
					printf("|  %d\t", k);
					printInfo(j);
					found = 1;
					
				}
			
			}else if(strstr(student[j].studentCode, element) != '\0')
				{
						k++;
						printf("|  %d\t", k);
						printInfo(j);
						found = 1;				
				}else if(strstr(student[j].sex, element) != '\0')
					{		
							k++;
							printf("|  %d\t", k);			
							printInfo(j);
							found = 1;
					}else if(strstr(student[j].name, element) != '\0')
						{	
							if(strstr(student[j].name, element) != '\0')
							{
								k++;
								printf("|  %d\t", k);
								printInfo(j);
								found = 1;
							}
						}
		}
		if(!found)
		{
			system("cls");
			printf("\n\n\n\n\n\n");
			printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			printf("\t\t\t\t\t!      Can't find out information!     !\n");
			printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			getchar();		
		}else
		{
			printf(":-------:--------------------------------------------------:------------:------------:-------:\n");				
			tmp = getch();
		}
	}
	if(tmp == 27) break;
	}
	system("cls");
}


//Function insert members
void InsertMem(FILE* pAcc, int* pNumStu)
{
	char tmp;
	char tmpName[50];
	char tmpCode[10];
	char tmpSex[4];
	do
	{
		int i = 0;
		for(int j = 0; j <= 49; j++)
		{
			tmpName[j] = '\0';
		}
		for(int j = 0; j <= 9; j++)
		{
			tmpCode[j] = '\0';
		}
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Enter name: ");
			printf("%s\n", tmpName);
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Enter student code:\n");
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Student's sex:  Nu ^|v\n");
			printf("\t\t\t\t\t______________________________________\n");
			tmp = getch();
			if ((tmp == 32) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
			{
				tmpName[i] = tmp;
				i++;
			}
			if(tmp == 8 && i >= 1)
			{
				i--;
				tmpName[i] = '\0';
			}
		} while (tmp != 13 && tmp != 27);
		if(tmp == 27) break;
		deleteOddSpace(tmpName);
		upperCase(tmpName);
		
			i = 0;
			int again = 0;
			do
			{
				do
				{ 
					system("cls");
					printf("\n\n\n\n\n\n\n");
					printf("\t\t\t\t\t______________________________________\n");	
					printf("\t\t\t\t\t| Enter name: %s\n", tmpName);
					printf("\t\t\t\t\t______________________________________\n");
					if(again)
					{
						if(checkID(tmpCode, *pNumStu, *pNumStu) == 0)
						{
							printf("\n\t\t\t\t\tThe student code is not valid!");
							printf("\n\t\t\t\t\t| Enter student code: \n");
							printf("\t\t\t\t\t______________________________________\n");

						}else
						{
							printf("\n\t\t\t\t\tThis student code have been in club already!");
							printf("\n\t\t\t\t\t| Enter student code: \n");
							printf("\t\t\t\t\t______________________________________\n");
						}
						
						for(int j = 0; j <= i - 1; j++)
						{
							tmpCode[j] = '\0';	
						}
						i = 0;
						again = 0;
					}else
						{
							printf("\t\t\t\t\t| Enter student Code: %s\n", tmpCode);
							printf("\t\t\t\t\t______________________________________\n");
						}
					
				//	printf("%s\n", tmpCode);
					printf("\t\t\t\t\t| Student's sex:  Nu ^|v\n");
					printf("\t\t\t\t\t______________________________________\n");
					
					tmp = getch();
					if ((tmp >= 65 && tmp <= 90) || (tmp >= 48 && tmp <= 57))
					{
						tmpCode[i] = tmp;
						i++;
					}
					if(tmp == 8 && i >= 1)
					{
						i--;
						tmpCode[i] = '\0';
					}
				} while (tmp != 13 && tmp != 27);
				
			if(tmp == 27) break;
			again = 0;
			if((checkID(tmpCode, *pNumStu, *pNumStu) == 0) || (checkID(tmpCode, *pNumStu, *pNumStu) == 2) == 1)
			{
				again = 1;		
			}
					
		} while ((checkID(tmpCode, *pNumStu, *pNumStu) == 0) || (checkID(tmpCode, *pNumStu, *pNumStu) == 2));
		if(tmp == 27) break;

		strcpy(tmpSex, "Nu");
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Enter name: ");
			printf("%s\n", tmpName);
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Enter student code: %s\n", tmpCode);
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Student's sex:  %s ^|v\n", tmpSex);
			printf("\t\t\t\t\t______________________________________\n");
			tmp = getch();
			
			if(tmp == - 32 || tmp == 80 || tmp == 72)
			{
				if(tmp == 80 || tmp == 72)
				if (strcmp(tmpSex, "Nu") == 0)
				{
					strcpy(tmpSex, "Nam");
				}else strcpy(tmpSex, "Nu");
			}
		} while(tmp != 13 && tmp != 27);
		
	
	}while (tmp != 27 && tmp != 13);
	//them cai dk neus maf enter thif moiws copy voiws viet vo tep
	
	if(tmp == 13)
	{
		strcpy(student[*pNumStu].name, tmpName);
		strcpy(student[*pNumStu].studentCode, tmpCode);
		strcpy(student[*pNumStu].sex, tmpSex);
		
	student[*pNumStu].course = getCourse(student[*pNumStu].studentCode);
	
		int j = 0;
		for (int i = 5; i <= strlen(student[*pNumStu].studentCode) - 1; i++)
		{
			student[*pNumStu].pass[j] = student[*pNumStu].studentCode[i];
			j++;
		}
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t****************************************\n");
		printf("\t\t\t\t\t*      Add a member successfully!      *\n");
		printf("\t\t\t\t\t****************************************\n");
		getchar();
	(*pNumStu)++;
	sortStuList(*pNumStu);
	
	writeFile(pAcc, *pNumStu);
	}
	system("cls");
		
}

//function change password
void changePass(int numAcc)
{
	int change = 0;
	char starOld[10];
	char starFirstPass[10];
	char starSecondPass[10];
	char oldPass[10];
	char firstPass[10];
	char secondPass[10];

	char tmp;
	do
		{
		for(int i = 0; i<= 9; i++)
		{
			starOld[i] = '\0';
			starFirstPass[i] = '\0';
			starSecondPass[i] = '\0';
			oldPass[i] = '\0';
			firstPass[i] = '\0';
			secondPass[i] = '\0';
		}
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n");
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter your old password: %s\n", starOld);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password: %s\n", starFirstPass);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password again: %s\n", starSecondPass);
				printf("\t\t\t\t\t______________________________________________\n");
			int i = 0;
			do
			{
				system("cls");
				printf("\n\n\n\n\n\n");
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter your old password: %s\n", starOld);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password: %s\n", starFirstPass);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password again: %s\n", starSecondPass);
				printf("\t\t\t\t\t______________________________________________\n");
				tmp = getch();
				if((tmp >= 48 && tmp <= 57) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
				{
					starOld[i] = '*';
					oldPass[i] = tmp;
					i++;
				}
			
				if(tmp == 8)
				{
					i--;
					starOld[i] = '\0';
					oldPass[i] = '\0';
				}
					
			}while (tmp != 27 && tmp != 13);
	
			if (tmp == 27) break;
		
			i = 0;
			do
			{
				system("cls");
				printf("\n\n\n\n\n\n");
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter your old password: %s\n", starOld);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password: %s\n", starFirstPass);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password again: %s\n", starSecondPass);
				printf("\t\t\t\t\t______________________________________________\n");
				tmp = getch();
				if((tmp >= 48 && tmp <= 57) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
				{
					starFirstPass[i] = '*';
					firstPass[i] = tmp;
					i++;
				}
			
				if(tmp == 8 && i >= 1)
				{
					i--;
					starFirstPass[i] = '\0';
					firstPass[i] = '\0';
				}
					
			}while (tmp != 27 && tmp != 13);
	
			if (tmp == 27) break;	
		
			i = 0;
			do
			{
				system("cls");
				printf("\n\n\n\n\n\n");
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter your old password: %s\n", starOld);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password: %s\n", starFirstPass);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password again: %s\n", starSecondPass);
				printf("\t\t\t\t\t______________________________________________\n");
				
				tmp = getch();
				if((tmp >= 48 && tmp <= 57) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
				{
					starSecondPass[i] = '*';
					secondPass[i] = tmp;
					i++;
				}
			
				if(tmp == 8 && i >= 1)
				{
					i--;
					starSecondPass[i] = '\0';
					secondPass[i] = '\0';
				}
			
			
			}while (tmp != 27 && tmp != 13);
	
			if (tmp == 27) break;
			
		}while (tmp != 13);
	
		if(tmp == 13)
		{
			if(strcmp(oldPass, student[numAcc].pass) == 0)
			{
				if(strcmp(firstPass, secondPass) == 0)
				{
					strcpy(student[numAcc].pass, firstPass);
					system("cls");
					printf("\n\n\n\n\n\n\n");
					printf("\t\t\t\t\t\t****************************************\n");
					printf("\t\t\t\t\t\t*  Change your password successfully!  *\n");
					printf("\t\t\t\t\t\t****************************************\n");
					getchar();
					system("cls");
					change = 1;	
				}else
				{
					system("cls");
					printf("\n\n\n\n\n\n\n\n");
					printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
					printf("\t\t\t\t\t!   Enter your new password again!   !\n");
					printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
					getchar();
				}
			}else 
			{
				system("cls");
				printf("\n\n\n\n\n\n\n");
				printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				printf("\t\t\t\t\t!  Your password is not correct!  !\n");
				printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				getchar();
			}
		
		}
		
		if(tmp == 27) 
		{
			system("cls");
			break;
		}
	}while(!change);
	printInfo(numAcc);
}


//function cotrol account
void controlAcc(int numAcc, FILE* pAcc, int numStu)
{
	printInfo(numAcc);
	int choice;
	char password[20];
	do
	{
		system("cls");
		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
		printf("Hello, %s, your No. is %d\n", student[numAcc].name, noStuCoSearch(studentCurrentCode) + 1); 
		//noStuCoSearch(studentCurrentCode) is No. in DB
		printf("Decentralization: [%s]", decentralization);
		
		gotoxy(0, 3);
		printLogo();
		printAccSettingMenu(&choice);
		system("cls");
	//	printInfo(numAcc);
		switch (choice)
		{
			case 1:
			//	editInfo(numAcc, pAcc, numStu);
				editMem(numStu, numAcc + 1, pAcc);
				printInfo(numAcc);
				break;
			case 2:
				changePass(numAcc);
				break;
		}
	}while (choice != 3);
	system("cls");
}

void member(int* pNumStu, char username[], FILE* pAcc, int numAcc)
{
	system("cls");
	int posi;// position is deleted;
	
	int choice;
	if(decentralizeStu(username) == 1)
	{
		do
		{
//			printSpeMenu();	
			system("cls");
			SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
			printf("Hello, %s, your No. is %d\n", student[numAcc].name, noStuCoSearch(studentCurrentCode) + 1); 
			//noStuCoSearch(studentCurrentCode) is No. in DB
			printf("Decentralization: [%s]", decentralization);
			
			gotoxy(0, 3);
			printLogo();
			printMemberMenuA(&choice);
			system("cls");
			switch (choice)
			{
				case 1: 
					printTable(*pNumStu);
					break;
				case 2:
					searchStudent(*pNumStu);
					break;
				case 3:
					InsertMem(pAcc, pNumStu);
					break;
				case 4:
					deleteInTable(*pNumStu, pAcc);
					break;
				case 5:
					editInTable(*pNumStu, pAcc);
					break;
				case 6:
					controlAcc(numAcc, pAcc, *pNumStu);
					break;
				case 7:
					break;									
			}
	
		} while(choice != 7);
						
	}else
		{
			system("cls");
			do
				{
//					printNorMenu();
					system("cls");
					SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
					printf("Hello, %s, your No. is %d\n", student[numAcc].name, noStuCoSearch(studentCurrentCode) + 1); 
					//noStuCoSearch(studentCurrentCode) is No. in DB
					printf("Decentralization: [%s]", decentralization);
					
					gotoxy(0, 3);
					printLogo();
					printMemberMenuM(&choice);
					system("cls");
					switch (choice)
					{
						case 1: 
							printTable(*pNumStu);
							break;
						case 2:
							searchStudent(*pNumStu);
							break;
						case 3:
							controlAcc(numAcc, pAcc, *pNumStu);	
							break;
					}
				} while(choice != 4);
		}
}


//function print information by the table

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
		printf("Hello, %s, your No. is %d\n", student[noStuCoSearch(studentCurrentCode)].name, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
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
				printf("Hello, %s, your No. is %d\n", student[noStuCoSearch(studentCurrentCode)].name, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
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
		printf("Hello, %s, your No. is %d\n", student[noStuCoSearch(studentCurrentCode)].name, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
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
				printf("Hello, %s, your No. is %d\n", student[noStuCoSearch(studentCurrentCode)].name, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
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

int isFileExist(char str[]){
	FILE * pFile;
	if((pFile = fopen(str,"r"))!=NULL) {
        fclose(pFile);
        return(1);
    }
    else{
	   	return(0);
        }
}

int isEventExist(char str[], int* pNumEvent){
	int flag = 0;
	for (int i = 0; i <= *pNumEvent - 1; i++){
		if(strcmp(event[i].idEvent, str) == 0) {
	        flag = 1;
	    }
	}
	if (flag == 1 ) return(1);
	else return(0);
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
		printf("Hello, %s, your No. is %d\n", student[noStuCoSearch(studentCurrentCode)].name, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
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
		printf("Hello, %s, your No. is %d\n", student[noStuCoSearch(studentCurrentCode)].name, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
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
			    char idEvent[4];
				printfGreen("Input event's id: ");
				fflush(stdin);
				scanf("%s", idEvent);
				if (isEventExist(idEvent, pNumEvent) == 1) {
					creatEventAddress(address, idEvent);
//					printf("Confirm address: \"%s\"\n", address);
					
					//creat table if it hasn't existed
					if (isFileExist(address) == 0) {
						FILE* pFileCreat;
						pFileCreat = fopen(address, "w");		
						creatRegisterForm(pFileCreat);
						fclose(pFileCreat);
//						printf("File has not existed\nCreating new list...\n");
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
				}
				else {
					printfGreen("Wrong id event!\n");
					system("pause");
				}
				break;
			}
			case 3:{			
				//reat files's address
				char address[100];
//				printEventList(pNumEvent);
				char idEvent[4];
				printfGreen("Input event's id: ");
				fflush(stdin);
				scanf("%s", idEvent);
				if (isEventExist(idEvent, pNumEvent) == 1) {
					creatEventAddress(address, idEvent);
					//creat table if it hasn't existed
					if (isFileExist(address) == 0) {
						FILE* pFileCreat;
						pFileCreat = fopen(address, "w");		
						creatRegisterForm(pFileCreat);
						fclose(pFileCreat);
//						printf("File has not existed\nCreating new list...\n");
					}
			
					//get information from file
					FILE* pFileRead;
					pFileRead = fopen(address, "r");
									
					getRegistered(pFileRead);
					fclose(pFileRead);
					
					printRegisteredList(&numStu);
					
				}
				else {
					printfGreen("Wrong id event!\n");
					system("pause");
				}
				break;
			}
			
			case 4:{
				//creat files's address
				char address[100];
				char idEvent[4];
				printfGreen("Input event's id: ");
				fflush(stdin);
				scanf("%s", idEvent);
				if (isEventExist(idEvent, pNumEvent) == 1) {
					creatEventAddress(address, idEvent);
//					printf("Confirm address: \"%s\"\n", address);
					
					//creat table if it hasn't existed
					if (isFileExist(address) == 0) {
						FILE* pFileCreat;
						pFileCreat = fopen(address, "w");		
						creatRegisterForm(pFileCreat);
						fclose(pFileCreat);
//						printf("File has not existed\nCreating new list...\n");
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
						printfGreen("Input student's id':");
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
				} else {
					printfGreen("Wrong id event!\n");
					system("pause");
				}
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
		printf("Hello, %s, your No. is %d\n", student[noStuCoSearch(studentCurrentCode)].name, noStuCoSearch(studentCurrentCode) + 1); //noStuCoSearch(studentCurrentCode) is No. in DB
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
				char idEvent[4];
				printfGreen("Input event's id: ");
				fflush(stdin);
				scanf("%s", idEvent);
				if (isEventExist(idEvent, pNumEvent) == 1) {
					creatEventAddress(address, idEvent);
//					printf("Confirm address: \"%s\"\n", address);
					
					//creat table if it hasn't existed
					if (isFileExist(address) == 0) {
						FILE* pFileCreat;
						pFileCreat = fopen(address, "w");		
						creatRegisterForm(pFileCreat);
						fclose(pFileCreat);
//						printf("File has not existed\nCreating new list...\n");
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
				} else {
					printfGreen("Wrong id event!\n");
					system("pause");
				}
				break;
			}
			case 3:{			
				//reat files's address
				char address[100];
//				printEventList(pNumEvent);
				char idEvent[4];
				printfGreen("Input event's id: ");
				fflush(stdin);
				scanf("%s", idEvent);
				if (isEventExist(idEvent, pNumEvent) == 1) {
					creatEventAddress(address, idEvent);
					
					//creat table if it hasn't existed
					if (isFileExist(address) == 0) {
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
				} else {
					printfGreen("Wrong id event!\n");
					system("pause");
				}
				
				break;
			}
			
			case 4:{
				
			}
		}
	}while (chooseEventMenu != 4);
}	


void creatEventAddress(char address[], char idEvent[]) {
	strcpy(address, "");
	//declare file address
	
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
	
	char username[9];
	char password[20];
	char letter;
	int chooseNumber;
	int numAcc;
	
	hidecursor();
	
	do{		
		fflush(stdin);
		getUsername(username);
		getPassword(password, username);
			
		FILE* pFileStu;
		pFileStu = fopen("account.txt", "r");
		getInfo(pFileStu, &numStu);
		
		if(checkAcc(numStu, username, password, &numAcc)){
			
			strcat(studentCurrentCode, username);
						
			if (decentralizeStu(studentCurrentCode) == 1) {
				strcpy(decentralization, "Administator");
			} else if (decentralizeStu(studentCurrentCode) == 2) {
				strcpy(decentralization, "Fund Manager");
			} else strcpy(decentralization, "Club member");
			
			do{
				
				system("cls");
				SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
				printf("Hello, %s, your No. is %d\n", student[noStuCoSearch(studentCurrentCode)].name, noStuCoSearch(studentCurrentCode) + 1); 
				//noStuCoSearch(studentCurrentCode) is No. in DB
				printf("Decentralization: [%s]", decentralization);
				
				gotoxy(0, 3);
				printLogo();
				
				printMainMenu(&chooseNumber);
				switch (chooseNumber){
					
					case 1:{
//						printTable(numStu);
						member(&numStu, username, pFileStu,numAcc);
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
		}else {printf("Account does not exist!\n");		
		}
	}while (!checkAcc(numStu, username, password, &numAcc));
	return(0);
}
