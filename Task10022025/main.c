#include<stdio.h>
#include<stdlib.h>
#include"datatype.h"
#include"funcion.c"

#define MAX 100

int main()
{
    struct Category listCategory[MAX];// Xu ly Mang dong
    int size =0;
    char temp[1000];
    FILE *fCategory = fopen("C:\\ProjectC\\data\\Category.txt","r");
    while(fgets(temp,sizeof(temp),fCategory) != NULL)
    {
        size++;
    }
    fclose(fCategory);
    int choose;
    while(1)
    {
        mainMenu();
        choose = inputChoice(0,6);
        clearInput();
        switch(choose)
        {
            case 1:
                fCategory = fopen("C:\\ProjectC\\data\\Category.txt","r");
                showListCategory(size, fCategory);
                fclose(fCategory);
                break;
            case 2:
                fCategory = fopen("C:\\ProjectC\\data\\Category.txt", "a");
                addNewCategory(&size, listCategory,fCategory);
                fclose(fCategory);
                break;
            case 3:
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