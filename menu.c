#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char array[50][50];
FILE *in, *out;
int numberOfLines, i;

int makeArray() {
    numberOfLines=0;
    in=fopen("password.csv", "rt");
    if(in) 
    {
        for(i=0; !feof(in) && i<50; i++) 
	{
            char temp[50];
            fgets(temp, 50, in);
            temp[strlen(temp)-1] = '\0';
            strcpy(array[i], temp);
            numberOfLines=numberOfLines+1;
        }
        fclose(in);
        decrypt(array);
    }
}


int add(char *username, char *password, char *type) 
{
    
    makeArray();

    for(i = 0; i < numberOfLines; i++) 
    {
        char tempName[50];
        strcpy(tempName, username);
        strcat(tempName, ",");
        if(strncmp(array[i], tempName, strlen(tempName)) == 0) return EXIT_FAILURE;
    }

    strcpy(array[numberOfLines], username); //we add username to the array
    strcat(array[numberOfLines], ", "); //we remove the ',' between each string
    strcat(array[numberOfLines], password);
    strcat(array[numberOfLines], ", ");
    strcat(array[numberOfLines], type);
    
    encrypt(array);
    out=fopen("password.csv", "wt");
    for (i=0; i<numberOfLines; i++) 
    {
        fprintf(out, "%s\n", array[i]);
    }
    fclose(out);
    return EXIT_SUCCESS;
}

int delete(char *username)
{
    int k=0, line, exists=0;
    
    makeArray();

    for (i=0; i<numberOfLines; i++) 
    {
        char tempName[50];
        strcpy(tempName, username);
        strcat(tempName, ",");
        
        if (strncmp(array[i], tempName, strlen(tempName)) == 0) 
	{
            line=i;
            exists=1;
        }
        
    }
    
    if (exists == 1) 
    {
        encrypt(array);
        out=fopen("password.csv", "wt");
        for(k=0; k<line; k++) 
	{
            fprintf(out, "%s\n", array[k]);
        }
        for(k=line+1; k<numberOfLines; k++) 
	{
            fprintf(out, "%s\n", array[k]);
        }
        fclose(out);
        return EXIT_SUCCESS;
    } 
    else return EXIT_FAILURE;
}

int edit(char *username, char *password, char *type, char *usernameEdit, char *passwordEdit, char *typeEdit) 
{

    int exists = 0;
    char toBeReplaced[200];
    char toReplaceWith[200];

    strcpy(toBeReplaced, username);
    strcat(toBeReplaced, ", ");
    strcat(toBeReplaced, password);
    strcat(toBeReplaced, ", ");
    strcat(toBeReplaced, type);
 
    strcpy(toReplaceWith, usernameEdit);
    strcat(toReplaceWith, ", ");
    strcat(toReplaceWith, passwordEdit);
    strcat(toReplaceWith, ", ");
    strcat(toReplaceWith, typeEdit);

    for (i = 0; i < numberOfLines; i++) 
    {
        if (strncmp(array[i], toBeReplaced, strlen(toBeReplaced)) == 0) 
	{
            strcpy(array[i], toReplaceWith);
            exists=1;
        }
    }
    if (exists==1) 
    {
        encrypt(array);
        out=fopen("members.csv", "wt");
        for (i = 0; i < numberOfLines; i++) fprintf(out, "%s\n", array[i]);
        fclose(out);

        return EXIT_SUCCESS;
    } 
    else return EXIT_FAILURE;
}

int verify(char *username, char *password) 
{
    makeArray();
    
    char compare[200];
    strcpy(compare, username);
    strcat(compare, ", ");
    strcat(compare, password);
    strcat(compare, ", ");

    for (i=0; i<numberOfLines; i++) 
    {
        if (strncmp(array[i], compare, strlen(compare)) == 0) return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;    
}



int menu(void) 
{

    int option, optionSuccess, exit=0;
    char username[50], password[50], type[50], usernameEdit[50], passwordEdit[50], typeEdit[50];
    
    while (exit!=1) 
	{
        printf("Welcome To The Passweb Menu \n Choose an option \n1- Add a new User\n2- Delete an existing User \n3- Edit an existing User \n4- Verify Presence of User\n5- Quit\nOption: ");
        scanf("%d", &option);
        //printf("\n");
        
        switch (option) {
            case 1:
                printf("Creating a new user...\n");
                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);
                printf("Enter Type: ");
                scanf("%s", type);
                optionSuccess = add(username, password, type);
                if (optionSuccess == EXIT_SUCCESS) {
                    printf("User added\n");
                } else {
                    printf("User could not be added\n");
                }
		sleep(1);
                break;
                
            case 2:
                printf("Deleting an existing user...\n");
                printf("Enter Username: ");
                scanf("%s", username);
                optionSuccess=delete(username);
                if (optionSuccess==EXIT_SUCCESS) {
                    printf("User deleted. It's that easy!\n");
                } else {
                    printf("User could not be deleted. Record Not found.\n");
                }
		sleep(1);
                break;
                
            case 3:
                printf("Editing an existing user...\n");
                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);
                printf("Enter Type: ");
                scanf("%s", type);
                printf("Enter new Username: ");
                scanf("%s", usernameEdit);
                printf("Enter new Password: ");
                scanf("%s", passwordEdit);
                printf("Enter new Type: ");
                scanf("%s", typeEdit);
                optionSuccess=edit(username, password, type, usernameEdit, passwordEdit, typeEdit);
                if(optionSuccess==EXIT_SUCCESS) {
                    printf("User was modified.\n");
                } else {
                    printf("User could not be modified.\n");
                }
		sleep(1);
                break;

                
            case 4:
                printf("Verifying presence of user...\n");
                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);
                optionSuccess=verify(username, password);
                if (optionSuccess==EXIT_SUCCESS) {
                    printf("User exists.\n");
                }
                else {
                    printf("User does not exist.\n");
                }
		sleep(1);
                break;
                
            case 5:
                exit = 1;
		sleep(1);
                break;
                
            default:
                printf("Please choose an integer number between 1 and 5...\n");
                sleep(1);
        }
    }
    
    return EXIT_SUCCESS;
    
}
