//decentralize student
int decentralizeStu(char username[])
{
	if(strcmp(username, "SE130122") == 0 || strcmp(username, "SE130129") == 0 || strcmp(username, "SE130124") == 0)
	{
		return 1;
	}else if(strcmp(username, "SE120113") == 0)
		{
			return 2;	
		}else return 0;
	
}
