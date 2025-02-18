#include<stdio.h>
#include<stdlib.h>
#include"datatype.h"
#include"funcion.c"

int main()
{
    int isAdmin = loginManege();
    if (isAdmin)
    {
        printf("Admin logged in.\n");
    } else
    {
        printf("User logged in.\n");
    }
    pressAnyKeyToContinue();
    // FILE *file = fopen ("C:\\ProjectCFinal\\data\\AdminAccount.bin","ab");
    // fwrite("admin001\n12345",sizeof(char),14,file);
    int choice;
    while(1)
    {
        mainMenu();
        choice = inputChoice(0,3);
        fflush(stdin);
        switch (choice)
        {
            case 1:
                categoryManege(isAdmin);
                break;
            case 2:
                productManege(isAdmin);
                break;
            case 3:
                if(!isAdmin)
                {
                    printf("[ERROR]You are not an admin\n");
                    break;
                }
                orderManege();
                break;
        }
        if(choice == 0)
        {
            printf("[EXIT]THANK YOU - SEE YOU SOON");
            break;
        }
        pressAnyKeyToContinue();
        fflush(stdin);
    }
}
