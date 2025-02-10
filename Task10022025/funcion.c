#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datatype.h"
//Ham xoa bo nho dem
void clearInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//Menu bat dau
void startMenu()
{
    printf("CHOOSE YOUR ROLE\n");
    printf("=========================\n");
    printf("1. Admin\n");
    printf("2. \n");
    printf("3. \n");
    printf("0. EXIT PROGRAM\n");
    printf("=========================\n");
}
//Menu Chinh
void mainMenu()
{
    printf("==============MENU================\n");
    printf("|%-32s|\n","1. Hien thi danh sach danh muc");
    printf("|%-32s|\n","2. Them danh muc");
    printf("|%-32s|\n","3. Sua danh muc");
    printf("|%-32s|\n","4. Xoa danh muc");
    printf("|%-32s|\n","5. Tim kiem danh muc");
    printf("|%-32s|\n","6. Sap xep danh muc");
    printf("|%-32s|\n","0. THOAT CHUONG TRINH");
    printf("==================================\n");
}
//Chuc nang 1. Hien thi ds
void showListCategory(int size, FILE *file)
{
    if(size==0)
    {
        printf("[ERROR]Mang Rong\n");
    }else
    {
        for(int i=0; i<size; i++)
        {
            char temp[1000];
            fgets(temp,sizeof(temp),file);
            printf("%s",temp);
        }
    }
}
//Chuc nang 2. Them danh muc
void addNewCategory(int *size, struct Category *list, FILE *file)
{
    printf("Nhap ID danh muc: ");
    fgets(list[*size].categoryId,11,stdin);
    clearInput();
    fputs(list[*size].categoryId,file);

    printf("Nhap Ten danh muc: ");
    fgets(list[*size].categoryName,11,stdin);strtok(list[*size].categoryName,"\n");
    fputs(list[*size].categoryName,file);

    fputs("\n",file);
    (*size)++;
}
//Ham nhap chuc nang
int inputChoice(int start, int end)
{
	int choice;
    while(1)
    {
        printf(">> Moi ban chon chuc nang (tu %d den %d) :", start, end);scanf("%d", &choice);
        if(choice >= start && choice <= end)
        {
            break;
        }
		printf("[ERROR]Chuc nang khong hop le, vui long nhap lai\n");
    }
	return choice;
}