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
    printf("STORE MANAGER\n");
    printf("CHOOSE YOUR ROLE\n");
    printf("=========================\n");
    printf("1. Admin\n");
    printf("2. User\n");
    printf("0. EXIT PROGRAM\n");
    printf("=========================\n");
}
//Menu Danh Muc
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
        char id[10];
        char name[10];
        int count=0;
        printf("|==============|================|\n");
        printf("|%-14s|%-16s|\n","ID","NAME");
        printf("|==============|================|\n");
        for(int i=0; i<size; i++)
        {
            fread(id,sizeof(char),11,file);strtok(id,"\n");
            printf("|%-14s|",id);
            fread(name,sizeof(char),11,file);strtok(name,"\n");
            printf("%-16s|\n",name);
            printf("|--------------|----------------|\n");
            count++;
            if(count==size)
            {
                break;
            }
        }
    }
}
//Chuc nang 2. Them danh muc
void addNewCategory(int *size, FILE *file)
{
    char id[11];
    char name[11];
    printf("Nhap ID danh muc: ");
    fgets(id,11,stdin);
    strtok(id, "\n");
    clearInput();
    fwrite(id,sizeof(char),10,file);

    fwrite("\n",sizeof(char),1,file);

    printf("Nhap Ten danh muc: ");
    fgets(name,11,stdin);
    strtok(name, "\n");
    fwrite(name,sizeof(char),10,file);
    
    fwrite("\n",sizeof(char),1,file);

    printf("Nhap thanh cong\n");
    (*size)++;
}
//Chuc nang 3. Sua danh muc
void changeCategory(int size, FILE *file)
{
    //Luu lai du lieu cu
    char id[size][11];
    char name[size][11];
    for(int i=0; i<size; i++)
    {
        fread(id[i],sizeof(char),11,file);strtok(id[i],"\n");
        fread(name[i],sizeof(char),11,file);strtok(name[i],"\n");
    }
    printf("%s",name[0]);

    //Chuc nang sua danh muc
    char tempId[11];//10 ki tu + 1 ki tu NULL
    printf("Nhap Id cua danh muc muon chinh sua: ");
    fgets(tempId,11,stdin);
    strtok(tempId, "\n");
    
    int flag=0;
    for(int i=0; i<size; i++)
    {
        if(strcmp(tempId,id[i]) == 0)
        {   
            flag=1;
            printf("Id co ton tai\n");
            char tempName[10];
            printf("Nhap ten danh muc moi: ");
            clearInput();
            scanf("%[^\n]",tempName);

            printf("%s",tempName);
            
            strcpy(name[i],tempName);
            break;
        }
    }
    printf("%s",name[0]);
    if(flag==0)
    {
        printf("[ERROR]Khong tim thay Id\n");
    }else
    {
        //ghhi lai ra file
        freopen("C:\\ProjectC\\data\\Category.bin", "wb", file);
        for (int i = 0; i < size; i++)
        {
            fwrite(id[i], sizeof(char), 11, file);
            fwrite(name[i], sizeof(char), 11, file);
        }
        fclose(file);
    }
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