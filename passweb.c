#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "menu.c" //functions are included in menu.c
#include "cipher.c"

char array[50][50];

int main (int argc,  char *argv[])
{
	int optionSuccess, i;

	for(i=1; i<argc; i++)
	{
		if (strcmp(argv[i], "-menu")==0) menu();	
	}


	if (strcmp(argv[1], "-add")==0) 
	{
		for(i=1; i<argc; i++)
		{
			if(strcmp(argv[i], "-add") && strcmp(argv[i], "-delete") && strcmp(argv[i], "-verify") && strcmp(argv[i], "-edit")) //making sure that no other option was added
                	{
                		optionSuccess = add(argv[i], argv[i+1], argv[i+2]);
				//Assigning user, password and type to their respective values
            			if (optionSuccess == EXIT_FAILURE) 
				{
                			printf("User could not be added.\n");
            			}
            			return optionSuccess;
        		}  
		}  
    	}

	else if (strcmp(argv[1], "-del") == 0) 
	{
		for(i=1; i<argc; i++)
		{
			if(strcmp(argv[i], "-add") && strcmp(argv[i], "-delete") && strcmp(argv[i], "-verify") && strcmp(argv[i], "-edit")) //making sure that no other option was added
                	{
                		optionSuccess=delete(argv[i]);
            			if (optionSuccess == EXIT_FAILURE) 
				{
                			printf("User could not be deleted.\n");
            			}
            			return optionSuccess;
        		} 
		}  
	}

	else if (strcmp(argv[1], "-edit") == 0) 
	{
		for(i=1; i<argc; i++)
		{
			if(strcmp(argv[i], "-add") && strcmp(argv[i], "-delete") && strcmp(argv[i], "-verify") && strcmp(argv[i], "-edit")) //making sure that no other option was added
                	{
                		optionSuccess=edit(argv[i], argv[i+1], argv[i+2], argv[i+3], argv[i+4], argv[i+5]);
            			if (optionSuccess == EXIT_FAILURE) 
				{
                			printf("User could not be edited.\n");
            			}
            			return optionSuccess;
        		}   
		}
	}

	else if (strcmp(argv[1], "-verify") == 0) 
	{
		for(i=1; i<argc; i++)
		{
			if(strcmp(argv[i], "-add") && strcmp(argv[i], "-delete") && strcmp(argv[i], "-verify") && strcmp(argv[i], "-edit")) //making sure that no other option was added
                	{
                		optionSuccess = verify(argv[i], argv[i+1]);
				if (optionSuccess == EXIT_SUCCESS) 
				{
					printf("VALID\n");
            				return optionSuccess;
				} 
				else 
				{
                			printf("INVALID\n");
            				return optionSuccess;
            			}
        		}   
		}
	}

	else 
	{
        	printf("Wrong syntax. Proper syntax: \n$passweb -menu -add -del -edit -verify username password type user_2 pass _2 type_2\n");
        	return EXIT_FAILURE;
    	}
}
