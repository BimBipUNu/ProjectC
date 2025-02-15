#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datatype.h"

#define MAX 100 

//Ham xoa bo nho dem
void clearInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//Ham nhap chuc nang
int inputChoice(int start, int end)
{
	int choice;
    while(1)
    {
        printf(">>Please Select Function (from %d to %d) :", start, end);scanf("%d", &choice);
        if(choice >= start && choice <= end)
        {
            break;
        }
		printf("[ERROR]Invalid funcion, please select again.\n");
        clearInput();
    }
	return choice;
}
// Kiem tra chuoi ID hop le
int isValidStringOfId(char str[])
{
    //Ktra do dai
    if(strlen(str) != 10)
    {
        printf("[ERROR]Invalid length (10 characters)\n");
        return 0;
    }
    //Ktra trung nhau
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin","rb");
    struct Category tempCategory;
    while(fread(&tempCategory,sizeof(struct Category),1,file) == 1)
    {
        if(strcmp(str,tempCategory.categoryId) == 0)
        {
            printf("[ERROR]ID already existed\n");
            fclose(file);
            clearInput();
            return 0;
        }
    }
    fclose(file);
    return 1;
}
// Kiem tra chuoi Name hop le
int isValidStringOfName(char str[])
{
    //Ktra do dai
    if(strlen(str) == 0 && strlen(str) > 10)
    {
        printf("[ERROR]Invalid length (Up to 10 characters)\n");
        return 0;
    }
    //Ktra trung nhau
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin","rb");
    struct Category tempCategory;
    while(fread(&tempCategory,sizeof(struct Category),1,file) == 1)
    {
        if(strcmp(str,tempCategory.categoryName) == 0)
        {
            printf("[ERROR]Name already existed\n");
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}
//=========================================LOGIN=========================================================
//Menu Dang nhap
void loginMenu()
{
    printf("STORE MANAGER\n");
    printf("CHOOSE YOUR ROLE\n");
    printf("=========================\n");
    printf("1. Admin\n");
    printf("2. User\n");
    printf("0. EXIT PROGRAM\n");
    printf("=========================\n");
}
//Login Admin
int loginAdmin()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\AdminAccount.bin","rb");
    char username[9],password[6];
    fread(&username,sizeof(char),8,file);
    fseek(file,1,SEEK_CUR);
    fread(&password,sizeof(char),6,file);

    printf("Import Admin Account\n");
}
//Login Manage
void loginManege()
{
    int choice;
    while(1)
    {
        loginMenu();
        choice = inputChoice(0,2);
        fflush(stdin);
        clearInput();
        switch(choice)
        {
            case 1:
                loginAdmin();
                break;
            case 2:
                break;
        }
        if(choice==0)
        {
            printf("[EXIT]THANK YOU - SEE YOU SOON");
            break;
        }
    }
}
//=================================CATEGORY============================================================
//Menu Danh Muc
void categoryMenu()
{
    printf("==============MENU================\n");
    printf("|%-32s|\n","1. Show list category");
    printf("|%-32s|\n","2. Add new category");
    printf("|%-32s|\n","3. Change category");
    printf("|%-32s|\n","4. Delete category");
    printf("|%-32s|\n","5. Search category");
    printf("|%-32s|\n","6. Sort category");
    printf("|%-32s|\n","0. EXIT PROGRAM");
    printf("==================================\n");
}
//Chuc nang 1. Hien thi ds
void showListCategory()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin", "rb");
    if (file == NULL) {
        printf("[ERROR]Unable to open file.\n");
        return;
    }
    struct Category tempCategory;
    int index =0;
    printf("|==============|================|\n");
    printf("|%-14s|%-16s|\n","ID","NAME");
    printf("|==============|================|\n");
    while(fread(&tempCategory, sizeof(struct Category), 1, file) == 1)
    {
        index++;
        printf("|%-14s|%-16s|\n",tempCategory.categoryId,tempCategory.categoryName);
        printf("|--------------|----------------|\n");
    }
    if(index == 0)
    {
        printf("[ERROR]List category is empty\n");
    }
    fclose(file);
}
//Chuc nang 2. Them danh muc
void addNewCategory()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin", "ab");
    struct Category newCategory;
    while(1)
    {
        printf("Import ID of category: ");scanf("%s",newCategory.categoryId);
        clearInput();
        if(isValidStringOfId(newCategory.categoryId))
        {
            printf("String valid\n");
            break;
        }else
        {
            printf("Please import again\n");
        }
    }
    while(1)
    {
        printf("Import Name of category: ");scanf("%[^\n]",newCategory.categoryName);
        clearInput();
        if(isValidStringOfName(newCategory.categoryName) && strcmp(newCategory.categoryId,newCategory.categoryName) != 0)
        {
            printf("String valid\n");
            break;
        }else
        {
            if(strcmp(newCategory.categoryId,newCategory.categoryName) == 0)
            {
                printf("[ERROR]Name unable same ID\n");
            }
            printf("Import again\n");
        }
    }
    //Luu vao file
    fwrite(&newCategory, sizeof(struct Category), 1, file);
    printf("Successful import\n");
    fclose(file);
}
//Chuc nang 3. Sua danh muc
void changeCategory()
{
    //Chuc nang sua danh muc
    char tempId[11];//10 ki tu + 1 ki tu NULL
    printf("Import ID of category which you want to change: ");
    fgets(tempId,11,stdin);
    strtok(tempId, "\n");
    
    int flag=0;
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin", "rb");
    struct Category changeCategory[MAX];
    int index=0;
    while(fread(&changeCategory[index], sizeof(struct Category), 1, file))
    {
        if(strcmp(tempId,changeCategory[index].categoryId) == 0)
        {   
            flag=1;
            printf("ID valid\n");
            printf("|==============|================|\n");
            printf("|%-14s|%-16s|\n","ID","NAME");
            printf("|==============|================|\n");
            printf("|%-14s|%-16s|\n",changeCategory[index].categoryId,changeCategory[index].categoryName);
            printf("|==============|================|\n");
            char tempName[10];
            printf("Import new name of category: ");
            clearInput();
            scanf("%[^\n]",tempName);

            strcpy(changeCategory[index].categoryName,tempName);
            break;
        }
        index++;
    }
    fclose(file);
    if(flag==0)
    {
        printf("[ERROR]ID not found\n");
    }else
    {
        //ghi lai ra file
        int size = index + 1;
        FILE *writeFile = freopen("C:\\ProjectCFinal\\data\\Category.bin", "wb", file);
        for (int i = 0; i < size; i++)
        {
            fwrite(&changeCategory[i], sizeof(struct Category), 1, writeFile);
        }
        fclose(file);
    }
}
//Chuc nang 4. Xoa danh muc
void deleteCategory()
{
    char delCategory[11];
    printf("Import ID of category which you want to delete: ");scanf("%s",delCategory);
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file\n");
        return;
    }
    struct Category deleteCategory[MAX];
    int index = 0;
    int found = 0;
    while (fread(&deleteCategory[index], sizeof(struct Category), 1, file))
    {
        if (strcmp(delCategory, deleteCategory[index].categoryId) == 0)
        {
            found = 1;
        }
        index++;
    }
    fclose(file);
    if (!found)
    {
        printf("[ERROR]ID not found\n");
        return;
    }
    int confirm;
    printf("Are you sure you want to delete?\n");
    printf("1.Yes\n");
    printf("0.NO\n");
    confirm = inputChoice(0, 1);
    if (confirm)
    {
        file = fopen("C:\\ProjectCFinal\\data\\Category.bin", "wb");
        if (file == NULL)
        {
            printf("[ERROR]Unable to open file\n");
            return;
        }
        for (int i = 0; i < index; i++)
        {
            if (strcmp(delCategory, deleteCategory[i].categoryId) != 0)
            {
                fwrite(&deleteCategory[i], sizeof(struct Category), 1, file);
            }
        }
        fclose(file);
        printf("Successful delete\n");
    }
}
//Chuc nang 5. tim kiem theo ten
void searchByName()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file\n");
        return;
    }
    struct Category searchCategory;
    char searchName[10];
    int find=0;
    printf("Import name which you searching: ");scanf("%[^\n]",searchName);
    while(fread(&searchCategory, sizeof(struct Category), 1, file))
    {
        if(strstr(searchCategory.categoryName, searchName) != NULL)
        {
            if(find==0)
            {
                printf("|==============|================|\n");
                printf("|%-14s|%-16s|\n","ID","NAME");
                printf("|==============|================|\n");
            }
            find++;
            printf("|%-14s|%-16s|\n",searchCategory.categoryId,searchCategory.categoryName);
            printf("|==============|================|\n");
        }
    }
    if(find == 0)
    {
        printf("[ERROR]Name not found\n");
    }
}
//Chuc nang 6. Sap Xep danh muc
void sortCategory()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file\n");
        return;
    }
    struct Category sortCategory[MAX];
    int index=0;
    while(fread(&sortCategory[index], sizeof(struct Category), 1, file) == 1)
    {
        index++;
    }
    //Sap xep
    int choice;
    printf("Sort by: \n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    choice = inputChoice(1,2);
    if(choice == 1)
    {
        for(int i=0; i<index-1; i++)
        {
            for(int j=i+1; j<index; j++)
            {
                if(strcmp(sortCategory[i].categoryName, sortCategory[j].categoryName)>0)
                {
                    //Swap
                    struct Category temp;
                    memcpy(&temp, &sortCategory[i], sizeof(struct Category));
                    memcpy(&sortCategory[i], &sortCategory[j], sizeof(struct Category));
                    memcpy(&sortCategory[j], &temp, sizeof(struct Category));
                }
            }
        }
    }else
    {
        for(int i=0; i<index-1; i++)
        {
            for(int j=i+1; j<index; j++)
            {
                if(strcmp(sortCategory[i].categoryName, sortCategory[j].categoryName)<0)
                {
                    //Swap
                    struct Category temp;
                    memcpy(&temp, &sortCategory[i], sizeof(struct Category));
                    memcpy(&sortCategory[i], &sortCategory[j], sizeof(struct Category));
                    memcpy(&sortCategory[j], &temp, sizeof(struct Category));
                }
            }
        }
    }
    fclose(file);
    //ghi lai ra file
    file = fopen("C:\\ProjectCFinal\\data\\Category.bin", "wb");
    for (int i = 0; i < index; i++)
    {
        fwrite(&sortCategory[i], sizeof(struct Category), 1, file);
    }
    fclose(file);
    printf("Successful sort\n");
}
//CATEGORY MANEGE
void categoryManege()
{
    int choice;
    while(1)
    {
        categoryMenu();
        choice = inputChoice(0,6);
        fflush(stdin);
        clearInput();
        switch(choice)
        {
            case 1:
                showListCategory();
                break;
            case 2:
                addNewCategory();
                break;
            case 3:
                changeCategory();
                break;
            case 4:
                deleteCategory();
                break;
            case 5:
                searchByName();
                break;
            case 6:
                sortCategory();
                break;
        }
        if(choice==0)
        {
            printf("[EXIT]THANK YOU - SEE YOU SOON");
            break;
        }
    }
}
//=======================================================================================================
//=======================PRODUCT=========================================================================
