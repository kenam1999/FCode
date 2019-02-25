// get choice
#include <stdio.h>
int getChoice(int numChoice)
{
	int choice;
	int numFormat;
	char endChar;
	printf("\n");
	printf("\t\t\t\t\tYour choice is: ");
	do
	{
		numFormat = scanf("%d%c", &choice, &endChar);
		
		if (numFormat != 2 || endChar != '\n' || choice < 1 || choice > numChoice)
		{
			printf("\t\t\t\t\tInput again: ");
			fflush(stdin);
		}else return choice;
	} while(numFormat != 2 || endChar != '\n' || choice < 1 || choice > numChoice);
	return 0;
}
