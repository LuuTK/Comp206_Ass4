#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *userType(char *user)
{
	FILE *p=fopen("members.csv", "rt");
	char *tempUser;
	char *tempPass;
	char *tempType;
	int done=1;

	while(!feof(p))
	{
		fscanf(p, "%s %s %s", tempUser, tempPass, tempType);
		if (strcmp(user, tempUser)==1)
		{
			return tempType;
		}
	}
	return NULL;
}


int main()
{
	char username[50];
	char password[50];
	char *toVerify=NULL;
	char *data=getenv("QUERY_STRING");
	int i, j, k;
	for (i=0; i<strlen(data); i++)
	{
		if(data[i]=='x')
			{
				for (j=i+2, k=0; data[j]!='&'; j++, k++) //j=i+2 b/c we want to skip the 'x='
				{
					username[k]=data[j];
				}
				i=j;
			}
		if(data[i]=='y')
			{
				for (j=i+2, k=0; data[j]<strlen(data); j++, k++) //j=i+2 b/c we want to skip the 'y='
				{
					password[k]=data[j];
				}
				i=strlen(data)-1;
			}
	}

    toVerify=("./passweb -verify %s %s", username, password);
    
    if(system(toVerify)==EXIT_SUCCESS) //to check if the user exists
	{
	printf("%s%c%c\n","Content-Type:text/html;charset=8859-1",13,10);
	char *n1 = "menu";
	char *act = "./menu.cgi";
	char *met = "get";
	char *rad = "radio";
	printf("<form name=%s action=%s method=%s", n1, act, met);
		char *type=userType(username);
		char *o1 = "
		if(type=="syso") //we want to be specific for syso only. if anything else is written, it must be user
		{
			printf("<input type=%s name=%s value=%s>Access passweb.c<BR>"
		}
		else
		{
			return 1;
		}
        return 1;
	}
    else
    {
	printf("%s%c%c\n", "Content-Type:text/html;charset=8859-1",13,10);
        printf("<p>ERROR! Wrong Username/Password.</p>");
	char *home="www.cs.mcgill.ca/homepage.htm";
	char *login="www.cs.mcgill.ca/homepage.htm";
        return 0;
    }
}
