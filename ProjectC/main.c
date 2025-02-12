#include<stdio.h>
#include<stdlib.h>
#include"datatype.h"
#include"funcion.c"

#define MAX 100 
struct Category listCategory[MAX];

int main()
{
    int size =0;
    char temp[1000];
    FILE *fCategory = fopen("C:\\ProjectC\\data\\Category.bin","rb");
    if (fCategory == NULL)
    {
        printf("[ERROR] Cannot open file for reading.\n");
        return 1; // Exit the program
    }
    while(fread(temp, sizeof(char), 10, fCategory) ==10)
    {
        size++;
    }
    size /=2;
    fclose(fCategory);
    int choose;
    while(1)
    {
        mainMenu();
        choose = inputChoice(0,6);
        fflush(stdin);
        clearInput();
        switch(choose)
        {
            case 1:
                fCategory = fopen("C:\\ProjectC\\data\\Category.bin", "rb");
                showListCategory(size, fCategory);
                fclose(fCategory);
                break;
            case 2:
                fCategory = fopen("C:\\ProjectC\\data\\Category.bin", "ab");
                addNewCategory(&size, fCategory);
                fclose(fCategory);
                break;
            case 3:
                fCategory = fopen("C:\\ProjectC\\data\\Category.bin", "rb");
                changeCategory(size, fCategory);
                fclose(fCategory);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
        }
        if(choose==0)
        {
            printf("[EXIT]THANK YOU - SEE YOU SOON");
            break;
        }
    }
}