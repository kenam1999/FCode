/*Problem: */
#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE * pFile;
if((pFile = fopen("D:\\study\\train c\\classProject\\Nam\\member_Event_Attendant_Check\\001.txt","r"))!=NULL)
        {
        	  printf ("It exists\n");
            fclose(pFile);
        }
    else
        {
            	  printf ("It is not exists\n");
        }
	return(0);
}

