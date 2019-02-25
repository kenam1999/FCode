#include <conio.h>
#include"print_logo.h"
#include"print_menu.h"
#include"gotoxy.h"
// Get username
void getUsername(char username[])
{

	char tmp;
	int i = 0;
	for(int i = 0; i <= 8; i++)
	{
		username[i] = '\0';
	}
	do
	{
		system("cls");
		gotoxy(0,8);
		printFCode();
		printf("\n\n\n");
		printf("%60.0s");
		printfGreen(":--------------------------------------------------------:\n");
		printf("%60.0s");
		printfGreen("|   Enter your username: ");
		printf("%s\n", username);
		printf("%60.0s");
		printfGreen("|                                                        |\n");
		printf("%60.0s");
		printfGreen("|   Enter your password: \n");
		printf("%60.0s");
		printfGreen(":--------------------------------------------------------:\n");
	
		gotoxy(117, 24);
		printfGreen("|");
		gotoxy(117, 25);
		printfGreen("|");
		gotoxy(117, 26);
		printfGreen("|");
		
		tmp = getch();
		if(tmp != 13 && tmp != 8)
		{
			username[i] = tmp;
			i++;
		}else if (tmp == 8 && i >= 1)
			{
				i--;
				username[i] = '\0';
						
			}
		
	} while (tmp != 13);
	username[i] = '\0';

}

// Get password
void getPassword(char password[], char username[])
{
	char tmp;
	char star[10];
	for(int i = 0; i <= 9; i++)
	{
		star[i] = '\0';
	}
	int i = 0;
	do
	{
		system("cls");
		gotoxy(0,8);
		printFCode();
		printf("\n\n\n");
		printf("%60.0s");
		printfGreen(":--------------------------------------------------------:\n");
		printf("%60.0s");
		printfGreen("|   Enter your username: ");
		printf("%s\n", username);
		printf("%60.0s");
		printfGreen("|                                                        |\n");
		printf("%60.0s");
		printfGreen("|   Enter your password: ");
		printf("%s\n", star);
		printf("%60.0s");
		printfGreen(":--------------------------------------------------------:\n");
		
		gotoxy(117, 24);
		printfGreen("|");
		gotoxy(117, 25);
		printfGreen("|");
		gotoxy(117, 26);
		printfGreen("|");
		
		tmp = getch();
		if(tmp != 13 && tmp != 8)
		{
			star[i] = '*';
			password[i] = tmp;
			i++;
		}else if (tmp == 8)
			{
				i--;
				password[i] = '\0';
				star[i] = '\0';
						
			}
		
	} while (tmp != 13);
	password[i] = '\0';
	star[i] = '\0';

}
