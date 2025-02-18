#include <stdio.h>
#include <string.h>
#include <conio.h> // Thu vien nhap ki tu ma khong hien thi ra man hinh
#include <stdlib.h>
#include <time.h>
#include "datatype.h"

#define MAX 100

//Ham Xoa system
void pressAnyKeyToContinue()
{
    printf("Press any key to continue...");
    getch();
    system("cls");
}
//Ham xoa bo nho dem
void clearInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//Ham nhap chuc nang
int inputChoice(int start, int end)
{
    fflush(stdin);
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
    fflush(stdin);
	return choice;
}
//Main menu
void mainMenu()
{
    printf("======STORE MANAGER======\n");
    printf("1. Category\n");
    printf("2. Product\n");
    printf("3. Order\n");
    printf("0. EXIT\n");
    printf("=========================\n");
}
//=========================================LOGIN=========================================================
//Menu Dang nhap
void loginMenu()
{
    printf("======STORE MANAGER======\n");
    printf("=====CHOICE YOUR ROLE====\n");
    printf("=========================\n");
    printf("1. Admin\n");
    printf("2. User\n");
    printf("=========================\n");
}
//Ham nhap ko hien mk
void importPassword(char *pass, int maxLen)
{
    int i = 0;
    char c;

    printf("Import password of admin acccount: ");

    while (i < maxLen - 1)
    {
        c = getch(); // Doc ki tu dang ghi
        if (c == 13)
        { // kiemtr Enter
            break;
        }
        if (c == 8)
        { // kiemtra Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else
        {
            pass[i] = c;
            i++;
            printf("*"); //"*"
        }
    }
    pass[i] = '\0'; // Ket chuoi
    printf("\n");
}
//Login Admin
int loginAdmin()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\AdminAccount.bin","rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return 0;
    }
    //Thong tin tai khoan accmin
    char username[9],password[6];
    fread(&username,sizeof(char),8,file);
    fseek(file,1,SEEK_CUR);
    fread(&password,sizeof(char),6,file);

    //Dang nhap
    char tempUsername[20],tempPassword[8];
    printf("Import username of admin account: ");scanf("%s",tempUsername);
    importPassword(tempPassword,8);

    if((strcmp(username,tempUsername)==0) && (strcmp(password,tempPassword)==0))
    {
        printf("Username and password are correct\n");
        return 1;
    }else
    {
        printf("[ERROR]Username or password is incorrect\n");
        return 0;
    }
}
//Login Manage
int loginManege()
{
    int choice;
    int activeAdmin;
    while(1)
    {
        loginMenu();
        choice = inputChoice(1,2);
        fflush(stdin);
        clearInput();
        switch(choice)
        {
            case 1:
                activeAdmin = loginAdmin();
                if(activeAdmin)
                {
                    return activeAdmin;
                }else
                {
                    break;
                }
                break;
            case 2:
                activeAdmin = 0;
                return activeAdmin;
        }
    }
}
//==============================LOGIN====END===========================================================
//=================================CATEGORY============================================================
//Menu Danh Muc
void categoryMenu()
{
    printf("============CATEGORY==============\n");
    printf("|%-32s|\n","1. Show list category");
    printf("|%-32s|\n","2. Add new category");
    printf("|%-32s|\n","3. Change category");
    printf("|%-32s|\n","4. Delete category");
    printf("|%-32s|\n","5. Search category");
    printf("|%-32s|\n","6. Sort category");
    printf("|%-32s|\n","0. EXIT Category Manage");
    printf("==================================\n");
}
// Kiem tra chuoi ID hop le
int isValidStringOfIdForCategory(char str[])
{
    //Ktra do dai
    if(strlen(str) != 10)
    {
        printf("[ERROR]Invalid length (10 characters)\n");
        return 0;
    }
    //Ktra trung nhau
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin","rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return 0;
    }
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
int isValidStringOfNameForCategory(char str[])
{
    //Ktra do dai
    if(strlen(str) == 0 || strlen(str) > 10)
    {
        printf("[ERROR]Invalid length (Up to 10 characters)\n");
        return 0;
    }
    //Ktra trung nhau
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin","rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return 0;
    }
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
//Chuc nang 1. Hien thi ds
void showListCategory()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return ;
    }
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
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return ;
    }
    struct Category newCategory;
    while(1)
    {
        printf("Import ID of category: ");scanf("%[^\n]",newCategory.categoryId);
        clearInput();
        if(isValidStringOfIdForCategory(newCategory.categoryId))
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
        if(isValidStringOfNameForCategory(newCategory.categoryName) && strcmp(newCategory.categoryId,newCategory.categoryName) != 0)
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
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return ;
    }
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
            printf("Successful change\n");

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
        fclose(writeFile);
    }
}
//Chuc nang 4. Xoa danh muc
void deleteCategory()
{
    char delCategory[11];
    printf("Import ID of category which you want to delete: ");scanf("%s",delCategory);
    fflush(stdin);
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return ;
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
    printf("Are you sure you want to delete this category?\n");
    printf("1.Yes\n");
    printf("0.NO\n");
    confirm = inputChoice(0, 1);
    if (confirm)
    {
        FILE *writeFile = fopen("C:\\ProjectCFinal\\data\\Category.bin", "wb");
        if (writeFile == NULL)
        {
            printf("[ERROR]Unable to open file.\n");
            return ;
        }
        for (int i = 0; i < index; i++)
        {
            if (strcmp(delCategory, deleteCategory[i].categoryId) != 0)
            {
                fwrite(&deleteCategory[i], sizeof(struct Category), 1, writeFile);
            }
        }
        fclose(writeFile);
        //Xoa danh muc thi xoa luon san pham
        FILE *fileProduct = fopen("C:\\ProjectCFinal\\data\\Product.bin", "rb");
        if (fileProduct == NULL)
        {
            printf("[ERROR]Unable to open file.\n");
            return ;
        }
        //Lay lai du lieu cu
        struct Product product[MAX];
        int indexProduct = 0;
        while(fread(&product[indexProduct],sizeof(struct Product),1,fileProduct))
        {
            indexProduct++;
        }
        fclose(fileProduct);
        //Xoa san pham co danh muc bi xoa
        fileProduct = fopen("C:\\ProjectCFinal\\data\\Product.bin", "wb");
        if (fileProduct == NULL)
        {
            printf("[ERROR]Unable to open file.\n");
            return ;
        }
        for (int i = 0; i < indexProduct; i++)
        {
            if(strcmp(product[i].categoryId,delCategory) != 0)
            {
                fwrite(&product[i],sizeof(struct Product),1,fileProduct);
            }
        }
        fclose(fileProduct);
        printf("Successful deletion\n");
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
    printf("Enter the name of the category you want to search for: ");scanf("%[^\n]",searchName);
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
            find = 1;
            printf("|%-14s|%-16s|\n",searchCategory.categoryId,searchCategory.categoryName);
            printf("|==============|================|\n");
        }
    }
    if(find == 0)
    {
        printf("[ERROR]Name not found\n");
    }
    fclose(file);
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
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return ;
    }
    for (int i = 0; i < index; i++)
    {
        fwrite(&sortCategory[i], sizeof(struct Category), 1, file);
    }
    fclose(file);
    printf("Successful sort\n");
}
//CATEGORY MANEGE
void categoryManege(int isAdmin)
{
    int choice;
    while(1)
    {
        categoryMenu();
        choice = inputChoice(0,6);
        fflush(stdin);
        clearInput();
        if(isAdmin == 0 && (choice == 2 || choice == 3 || choice == 4))
        {
            printf("[ERROR]You are not admin\n");
            pressAnyKeyToContinue();
            continue;
        }
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
            printf("[EXIT]Category Manage, back to Main menu\n");
            break;
        }
        pressAnyKeyToContinue();
        fflush(stdin);
    }
}
//============================CATEGORY=END====================================================================
//==========================PRODUCT===================================================================
//Product menu
void productMenu()
{
    printf("=============PRODUCT==============\n");
    printf("|%-32s|\n","1. Show list product");
    printf("|%-32s|\n","2. Add new product");
    printf("|%-32s|\n","3. Change product");
    printf("|%-32s|\n","4. Delete product");
    printf("|%-32s|\n","5. Search product");
    printf("|%-32s|\n","6. Sort product");
    printf("|%-32s|\n","7. Filter product");
    printf("|%-32s|\n","0. EXIT Product Manage");
    printf("==================================\n");
}
//Kiem tra chuoi id hop le
int isValidStringOfIdForProduct(char str[])
{
    //Ktra do dai
    if(strlen(str) != 10)
    {
        printf("[ERROR]Invalid length (10 characters)\n");
        return 0;
    }
    //Ktra trung nhau
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Product.bin","rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return 0;
    }
    struct Product tempProduct;
    while(fread(&tempProduct, sizeof(struct Product), 1, file)==1)
    {
        if(strcmp(str, tempProduct.productId) == 0)
        {
            printf("[ERROR]Product ID already exists\n");
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}
//Ktra chuoi ID CATEGORY cua san pham hop le
int isValidStringOfIdCategoryForProduct(char str[])
{
    //Ktra do dai
    if(strlen(str) != 10)
    {
        printf("[ERROR]Invalid length (10 characters)\n");
        return 0;
    }
    //Ktra Id danh muc nhap vao cho san pham phai ton tai roi
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Category.bin","rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return 0;
    }
    struct Category tempCategory;
    while(fread(&tempCategory, sizeof(struct Category), 1, file)==1)
    {
        if(strcmp(str, tempCategory.categoryId) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    printf("Category ID does not exist\n");
    fclose(file);
    return 0;
}
//Kiem tra chuoi name hop le
int isValidStringOfNameForProduct(char str[])
{
    //ktra do dai
    if(strlen(str) > 10 && strlen(str) == 0)
    {
        printf("[ERROR]Invalid length (0-10 characters)\n");
        return 0;
    }
    //Ktra trung nhau
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Product.bin","rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return 0;
    }
    struct Product tempProduct;
    while(fread(&tempProduct, sizeof(struct Product), 1, file)==1)
    {
        if(strcmp(str, tempProduct.productName) == 0)
        {
            printf("[ERROR]Product name already exists\n");
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}
//Chuc nang 1. Hien thi danh sach san pham
void showListProduct()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Product.bin","rb");
    if(file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return;
    }
    struct Product tempProduct;
    printf("|===============|===============|===============|===============|===============|\n");
    printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n","ID","CATEGORY ID","NAME","QUANTITY","PRICE");
    printf("|===============|===============|===============|===============|===============|\n");
    int index=0;
    while(fread(&tempProduct, sizeof(struct Product), 1, file)==1)
    {
        index++;
        printf("|%-15s|%-15s|%-15s|%-15d|%-12dVND|\n",tempProduct.productId,tempProduct.categoryId,tempProduct.productName,tempProduct.quantity,tempProduct.price);
        printf("|---------------|---------------|---------------|---------------|---------------|\n");
    }
}
//Chuc nang 2. Them moi san pham
void addNewProduct()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Product.bin","ab");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return ;
    }
    struct Product newProduct;
    while(1)
    {
        printf("Import ID of product: ");scanf("%[^\n]",newProduct.productId);
        clearInput();
        if(isValidStringOfIdForProduct(newProduct.productId))
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
        printf("Import ID of category: ");scanf("%[^\n]",newProduct.categoryId);
        clearInput();
        if(isValidStringOfIdCategoryForProduct(newProduct.categoryId))
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
        printf("Import Name of product: ");scanf("%[^\n]",newProduct.productName);
        clearInput();
        if(isValidStringOfNameForProduct(newProduct.productName) && strcmp(newProduct.productId, newProduct.productName) != 0)
        {
            printf("String valid\n");
            break;
        }else
        {
            if(strcmp(newProduct.productId, newProduct.productName) == 0)
            {
                printf("[ERROR]Name unable same ID\n");
            }
            printf("Import again\n");
        }
    }
    printf("Import quantity of product: ");scanf("%d",&newProduct.quantity);
    printf("Import price of product: ");scanf("%d",&newProduct.price);
    //Luu vao file
    fwrite(&newProduct,sizeof(struct Product),1,file);
    printf("Successful import product\n");
    fclose(file);
}
//Chuc nang 3. thay doi san pham
void changeProduct()
{
    char tempId[11];
    printf("Import ID of product which you want to change: ");
    fgets(tempId, 11, stdin);
    strtok(tempId, "\n");

    int flag=0;
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Product.bin","rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return ;
    }
    struct Product changeProduct[MAX];
    int index=0;
    while(fread(&changeProduct[index],sizeof(struct Product),1,file) == 1)
    {
        if(strcmp(changeProduct[index].productId,tempId) == 0)
        {
            printf("ID valid\n");
            printf("|===============|===============|===============|===============|===============|\n");
            printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n","ID","CATEGORY ID","NAME","QUANTITY","PRICE");
            printf("|===============|===============|===============|===============|===============|\n");
            printf("|%-15s|%-15s|%-15s|%-15d|%-12dVND|\n",changeProduct[index].productId,changeProduct[index].categoryId,changeProduct[index].productName,changeProduct[index].quantity,changeProduct[index].price);
            printf("|---------------|---------------|---------------|---------------|---------------|\n");
            char tempName[10];
            int tempQuantityOrPrice;
            printf("1. Change Name of product\n");
            printf("2. Change Quantity of product\n");
            printf("3. Change Price of product\n");
            flag = inputChoice(1,3);
            clearInput();
            switch(flag)
            {
                case 1:
                    printf("Import new name of product: ");scanf("%[^\n]",tempName);
                    clearInput();
                    strcpy(changeProduct[index].productName,tempName);
                    break;
                case 2:
                    printf("Import new quantity of product: ");scanf("%d",&tempQuantityOrPrice);
                    changeProduct[index].quantity = tempQuantityOrPrice;
                    break;
                case 3:
                    printf("Import new price of product: ");scanf("%d",&tempQuantityOrPrice);
                    changeProduct[index].price = tempQuantityOrPrice;
                    break;
            }
            flag=1;
        }
        index++;
    }
    fclose(file);
    if(flag == 0)
    {
        printf("[ERROR]ID not found\n");
    }else
    {
        //Ghi lai ra file
        FILE *writeFile = fopen("C:\\ProjectCFinal\\data\\Product.bin","wb");
        if (writeFile == NULL)
        {
            printf("[ERROR]Unable to open file.\n");
            return ;
        }
        for (int i=0; i<index; i++)
        {
            fwrite(&changeProduct[i], sizeof(struct Product),1,writeFile);
        }
        fclose(writeFile);
        printf("Successful change\n");
    }
}
//Chuc nang 4. Xoa San pham
void deleteProduct()
{
    char delProduct[11]; // Tăng kích thước mảng để chứa ký tự NULL
    printf("Import ID of product you want to delete: ");
    scanf("%10s", delProduct); // Giới hạn số ký tự nhập vào
    fflush(stdin);

    FILE *file = fopen("C:\\ProjectCFinal\\data\\Product.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]File not found\n");
        return;
    }

    struct Product deleteProduct[MAX];
    int index = 0;
    int found = 0;

    while (fread(&deleteProduct[index], sizeof(struct Product), 1, file))
    {
        if (strcmp(deleteProduct[index].productId, delProduct) == 0)
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
    printf("Are you sure you want to delete this product?\n");
    printf("1. Yes\n");
    printf("0. No\n");
    confirm = inputChoice(0, 1);

    if (confirm)
    {
        FILE *writeFile = fopen("C:\\ProjectCFinal\\data\\Product.bin", "wb");
        if (writeFile == NULL)
        {
            printf("[ERROR]Unable to open file\n");
            return;
        }
        for (int i = 0; i < index; i++)
        {
            if (strcmp(deleteProduct[i].productId, delProduct) != 0)
            {
                fwrite(&deleteProduct[i], sizeof(struct Product), 1, writeFile);
            }
        }
        fclose(writeFile);
        printf("Successful deletion\n");
    }
}
//Chuc nang 5. Tim kiem theo ten ( tim kiem tuong doi)
void searchProduct()
{
    FILE *file = fopen ("C:\\ProjectCFinal\\data\\Product.bin","rb");
    if(file == NULL)
    {
        printf("[ERROR]Unable to open file\n");
        return;
    }
    struct Product searchProduct;
    char searchNameOfProduct[10];
    int find =0;
    printf("Enter the name of the product you want to search for: ");scanf("%[^\n]",searchNameOfProduct);
    while(fread(&searchProduct,sizeof (struct Product),1,file))
    {
        if(strstr(searchProduct.productName, searchNameOfProduct) != NULL)
        {
            if(find == 0)
            {
                printf("|===============|===============|===============|===============|===============|\n");
                printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n","ID","CATEGORY ID","NAME","QUANTITY","PRICE");
                printf("|===============|===============|===============|===============|===============|\n");
            }
            find =1;
            printf("|%-15s|%-15s|%-15s|%-15d|%-12dVND|\n",searchProduct.productId,searchProduct.categoryId,searchProduct.productName,searchProduct.quantity,searchProduct.price);
            printf("|---------------|---------------|---------------|---------------|---------------|\n");
        }
    }
    if(find == 0)
    {
        printf("[ERROR]Name not found\n");
    }
    fclose(file);
}
//Chuc nang 6. Sap xep theo gia tien
void sortPrice()
{
    FILE *file = fopen ("C:\\ProjectCFinal\\data\\Product.bin","rb");
    if(file == NULL)
    {
        printf("[ERROR]Unable to open file\n");
        return;
    }
    struct Product sortProduct[MAX];
    int index=0;
    while(fread(&sortProduct[index],sizeof (struct Product),1,file))
    {
        index++;
    }
    //Sap xep
    int choice;
    printf("Sort price by: \n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    choice = inputChoice(1,2);
    if(choice == 1)
    {
        for(int i = 0; i < index - 1; i++)
        {
            for(int j=i+1; j< index; j++)
            {
                if(sortProduct[i].price > sortProduct[j].price)
                {
                    //swap
                    struct Product temp;
                    memcpy(&temp, &sortProduct[i],sizeof(struct Product));
                    memcpy(&sortProduct[i], &sortProduct[j],sizeof(struct Product));
                    memcpy(&sortProduct[j], &temp,sizeof(struct Product));
                }

            }

        }
    }else
    {
        for(int i = 0; i < index - 1; i++)
        {
            for(int j=i+1; j< index; j++)
            {
                if(sortProduct[i].price < sortProduct[j].price)
                {
                    //swap
                    struct Product temp;
                    memcpy(&temp, &sortProduct[i],sizeof(struct Product));
                    memcpy(&sortProduct[i], &sortProduct[j],sizeof(struct Product));
                    memcpy(&sortProduct[j], &temp,sizeof(struct Product));
                }

            }

        }
    }
    fclose(file);
    //Luu lai ra file
    FILE *writeFile = fopen ("C:\\ProjectCFinal\\data\\Product.bin","wb");
    if (writeFile == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return ;
    }
    for(int i = 0; i < index; i++)
    {
        fwrite(&sortProduct[i],sizeof(struct Product),1,writeFile);
    }
    fclose(writeFile);
    printf("Successful sort\n");
}
//Chuc nang 7. Loc san pham
void filterProduct()
{
    int choice;
    printf("Filter product\n");
    printf("1. Filter by price\n");
    printf("2. Filter by categoryId\n");
    choice = inputChoice(1,2);
    clearInput();
    if(choice == 1)
    {
        int start,end;
        while(1)
        {
            printf("Enter start price: ");scanf("%d",&start);
            printf("Enter end price: ");scanf("%d",&end);
            if(start > end || start < 0 || end < 0)
            {
                printf("Invalid input\n");
            }else
            {
                break;
            }
        }
        FILE *file = fopen ("C:\\ProjectCFinal\\data\\Product.bin","rb");
        if (file == NULL)
        {
            printf("[ERROR]Unable to open file.\n");
            return ;
        }
        struct Product filterByPrice;
        int index = 0;
        int find = 0;
        while(fread(&filterByPrice,sizeof(struct Product),1,file))
        {
            if(filterByPrice.price >= start && filterByPrice.price <= end)
            {
                if(find == 0)
                {
                    printf("|===============|===============|===============|===============|===============|\n");
                    printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n","ID","CATEGORY ID","NAME","QUANTITY","PRICE");
                    printf("|===============|===============|===============|===============|===============|\n");
                }
                find = 1;
                printf("|%-15s|%-15s|%-15s|%-15d|%-12dVND|\n",filterByPrice.productId,filterByPrice.categoryId,filterByPrice.productName,filterByPrice.quantity,filterByPrice.price);
                printf("|---------------|---------------|---------------|---------------|---------------|\n");
            }
            index++;
        }
        if(!find)
        {
            printf("[ERROR]Product not found\n");
        }
        fclose(file);
    }else
    {
        char tempCategoryId[10];
        while(1)
        {
            printf("Enter category ID: ");scanf("%[^\n]",tempCategoryId);
            clearInput();
            if(isValidStringOfIdCategoryForProduct(tempCategoryId))
            {
                printf("String valid\n");
                break;
            }else
            {
                printf("Please import again\n");
            }
        }
        FILE *file = fopen ("C:\\ProjectCFinal\\data\\Product.bin","rb");
        if (file == NULL)
        {
            printf("[ERROR]Unable to open file.\n");
            return ;
        }
        struct Product filterByCategoryId;
        int index = 0;
        int find = 0;
        while(fread(&filterByCategoryId,sizeof(struct Product),1,file))
        {
            if(strcmp(tempCategoryId,filterByCategoryId.categoryId) == 0)
            {
                if(find == 0)
                {
                    printf("|===============|===============|===============|===============|===============|\n");
                    printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n","ID","CATEGORY ID","NAME","QUANTITY","PRICE");
                    printf("|===============|===============|===============|===============|===============|\n");
                }
                find = 1;
                printf("|%-15s|%-15s|%-15s|%-15d|%-12dVND|\n",filterByCategoryId.productId,filterByCategoryId.categoryId,filterByCategoryId.productName,filterByCategoryId.quantity,filterByCategoryId.price);
                printf("|---------------|---------------|---------------|---------------|---------------|\n");
            }
            index++;
        }
        if(!find)
        {
            printf("[ERROR]This category ID has no products\n");
        }
        fclose(file);
    }
}
//PRODUCT MANGE
void productManege(int isAdmin)
{
    int choice;
    while(1)
    {
        fflush(stdin);
        productMenu();
        choice = inputChoice(0,7);
        fflush(stdin);
        clearInput();
        if(isAdmin == 0 && (choice == 2 || choice == 3 || choice ==4))
        {
            printf("[ERROR]You are not admin\n");
            pressAnyKeyToContinue();
            continue;
        }
        switch(choice)
        {
            case 1:
                showListProduct();
                break;
            case 2:
                addNewProduct();
                break;
            case 3:
                changeProduct();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                searchProduct();
                break;
            case 6:
                sortPrice();
                break;
            case 7:
                filterProduct();
                break;
        }
        if(choice == 0)
        {
            printf("[EXIT]Product Manage, back to Main menu\n");
            break;
        }
        pressAnyKeyToContinue();
    }
}
//=============================PRODUCT====END=============================================================`
//==============================ORDER=====================================================================
// Order Menu
void orderMenu()
{
    printf("==============ORDER===============\n");
    printf("|%-32s|\n","1. Show list order");
    printf("|%-32s|\n","2. Add new order");
    printf("|%-32s|\n","3. Search order");
    printf("|%-32s|\n","4. Sort order");
    printf("|%-32s|\n","0. EXIT Order Manage");
    printf("==================================\n");
}
// Ktra chuoi Id hop le
int isValidStringOfIdForOrder(char str[])
{
    // Ktra do dai
    if (strlen(str) != 10)
    {
        printf("[ERROR]Invalid length (10 characters)\n");
        return 0;
    }

    // Ktra trung nhau
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Order.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return 0;
    }

    struct Order tempOrder;
    while (fread(&tempOrder, sizeof(struct Order), 1, file) == 1)
    {
        if (strcmp(str, tempOrder.orderId) == 0)
        {
            printf("[ERROR]Order ID already exists\n");
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}
//Ktra ID PRODUCT nhap vao pahi ton tai
int isValidStringOfIdProductForOrder(char str[])
{
    // Ktra do dai
    if (strlen(str) != 10)
    {
        printf("[ERROR]Invalid length (10 characters)\n");
        return 0;
    }
    // Ktra ID san pham phai ton tai roi
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Product.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file\n");
        return 0;
    }
    struct Product tempProduct;
    while (fread(&tempProduct, sizeof(struct Product), 1, file) ==1)
    {
        if(strcmp(tempProduct.productId,str)==0)
        {
            printf("String of ID Product is valid\n");
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
//Hien thi danh sach don hang
void showListOrder()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Order.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return;
    }

    struct Order tempOrder;
    int index = 0;
    printf("|==============|==============|==============|==============|==============|==============|\n");
    printf("|==========================================ORDERS=========================================|\n");
    printf("|==============|==============|==============|==============|==============|==============|\n");

    while (fread(&tempOrder, sizeof(struct Order), 1, file) == 1) {
        index++;
        int totalPrice = 0;
        for (int i = 0; i < tempOrder.productCount; i++) {
            totalPrice += tempOrder.products[i].price * tempOrder.products[i].quantity;
        }
        printf("|ID: %s\n|CUSTOMERID: %s\n|%02d/%02d/%04d %02d:%02d:%02d\n|PRODUCTSCOUNT: %d\n|PRICE: %dVND\n",
               tempOrder.orderId, tempOrder.customerId,
               tempOrder.date.day, tempOrder.date.month, tempOrder.date.year,
               tempOrder.time.hour, tempOrder.time.minute, tempOrder.time.second,
               tempOrder.productCount, totalPrice);
        printf("|--------------|--------------|--------------|--------------|\n");

        for (int i = 0; i < tempOrder.productCount; i++) {
            printf("|%-14s|%-14d|%-14d|%-11dVND|\n",
                    tempOrder.products[i].productId, tempOrder.products[i].quantity, tempOrder.products[i].price, tempOrder.products[i].price * tempOrder.products[i].quantity);
            printf("|--------------|--------------|--------------|--------------|\n");
        }
    }

    if (index == 0) {
        printf("[ERROR]List order is empty\n");
    }

    fclose(file);
}
//add new order
void addNewOrder()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Order.bin","ab");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return ;
    }
    struct Order newOrder;
    while(1)
    {
        printf("Import ID of order: ");scanf("%[^\n]", newOrder.orderId);
        clearInput();
        if(isValidStringOfIdForOrder(newOrder.orderId))
        {
            printf("String valid\n");
            break;
        }else
        {
            printf("Import again\n");
        }
    }
    while(1)
    {
        printf("Import customer ID: ");scanf("%[^\n]", newOrder.customerId);
        clearInput();
        if(strlen(newOrder.customerId) != 10)
        {
            printf("[ERROR]Invalid length (10 character)\n");
            continue;
        }else
        {
            break;
        }
    }
    // Thoi gian don hang duoc lay tu thoi gian thuc
    time_t now = time(NULL);
    struct tm*t = localtime(&now);

    newOrder.date.day = t->tm_mday;
    newOrder.date.month = t->tm_mon + 1;
    newOrder.date.year = t->tm_year + 1900;

    newOrder.time.hour = t->tm_hour;
    newOrder.time.minute = t->tm_min;
    newOrder.time.second = t->tm_sec;

    while(1)
    {
        printf("How many products in this order?: ");scanf("%d",&newOrder.productCount);
        clearInput();
        if(newOrder.productCount <=10 && newOrder.productCount > 0)
        {
            break;
        }else
        {
            printf("Import again\n");
        }
    }
    for (int i = 0; i < newOrder.productCount; i++) {
        while (1)
        {
            printf("Import ID of product %d: ", i + 1);scanf("%[^\n]", newOrder.products[i].productId);
            clearInput();
            if (isValidStringOfIdProductForOrder(newOrder.products[i].productId))
            {
                printf("String valid\n");
                break;
            } else
            {
                printf("Import again\n");
            }
        }

        printf("Import quantity of product %d: ", i + 1);scanf("%d", &newOrder.products[i].quantity);
        clearInput();
        //Lay gia tien tu file san pham
        FILE *productFile = fopen("C:\\ProjectCFinal\\data\\Product.bin", "rb");
        if (productFile == NULL)
        {
            printf("[ERROR]Unable to open product file.\n");
            fclose(file);
            return;
        }

        struct Product tempProduct;
        while (fread(&tempProduct, sizeof(struct Product), 1, productFile) == 1)
        {
            if (strcmp(tempProduct.productId, newOrder.products[i].productId) == 0)
            {
                newOrder.products[i].price = tempProduct.price;
                break;
            }
        }
        fclose(productFile);
    }
    fwrite(&newOrder, sizeof(struct Order), 1, file);
    printf("Successful import order\n");
    fclose(file);
}
//Tim kiem don hang dua vao ID
void searchOrderById()
{
    char searchId[11];
    printf("Enter the ID of the order you want to search for: ");
    scanf("%10s", searchId); // Limit input to 10 characters
    clearInput();

    FILE *file = fopen("C:\\ProjectCFinal\\data\\Order.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return;
    }

    struct Order tempOrder;
    int found = 0;
    while (fread(&tempOrder, sizeof(struct Order), 1, file) == 1)
    {
        if (strcmp(tempOrder.orderId, searchId) == 0)
        {
            found = 1;
            int totalPrice = 0;
            for (int i = 0; i < tempOrder.productCount; i++)
            {
                totalPrice += tempOrder.products[i].price * tempOrder.products[i].quantity;
            }
            printf("|==========================================ORDER==========================================|\n");
            printf("|ID: %s\n|CUSTOMERID: %s\n|%02d/%02d/%04d %02d:%02d:%02d\n|PRODUCTSCOUNT: %d\n|PRICE: %dVND\n",
                   tempOrder.orderId, tempOrder.customerId,
                   tempOrder.date.day, tempOrder.date.month, tempOrder.date.year,
                   tempOrder.time.hour, tempOrder.time.minute, tempOrder.time.second,
                   tempOrder.productCount, totalPrice);
            printf("|--------------|--------------|--------------|--------------|\n");

            for (int i = 0; i < tempOrder.productCount; i++)
            {
                printf("|%-14s|%-14d|%-14d|%-11dVND|\n",
                       tempOrder.products[i].productId, tempOrder.products[i].quantity, tempOrder.products[i].price, tempOrder.products[i].price * tempOrder.products[i].quantity);
                printf("|--------------|--------------|--------------|--------------|\n");
            }
            break;
        }
    }

    if (!found)
    {
        printf("[ERROR]Order ID not found\n");
    }

    fclose(file);
}
//Sap xep don hang theo gia tri don hang
void sortOrder()
{
    FILE *file = fopen("C:\\ProjectCFinal\\data\\Order.bin", "rb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file.\n");
        return;
    }

    struct Order orders[MAX];
    int count = 0;

    // Tinh so luong don hang
    while (fread(&orders[count], sizeof(struct Order), 1, file) == 1)
    {
        count++;
    }
    fclose(file);

    // Tinh gia tri don hang cua tung don
    int totalPrices[MAX];
    for (int i = 0; i < count; i++)
    {
        totalPrices[i] = 0;
        for (int j = 0; j < orders[i].productCount; j++)
        {
            totalPrices[i] += orders[i].products[j].price * orders[i].products[j].quantity;
        }
    }

    int choice;
    printf("Sort by price:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    choice = inputChoice(1,2);
    // Sắp xếp tăng dần
    if (choice == 1)
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                if (totalPrices[j] > totalPrices[j + 1])
                {
                    // Đổi chỗ struct đơn hàng
                    struct Order tempOrder = orders[j];
                    orders[j] = orders[j + 1];
                    orders[j + 1] = tempOrder;

                    // Đổi chỗ giá trị đơn hàng theo
                    int tempPrice = totalPrices[j];
                    totalPrices[j] = totalPrices[j + 1];
                    totalPrices[j + 1] = tempPrice;
                }
            }
        }
    }
    // Sắp xếp giảm dần
    else
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                if (totalPrices[j] < totalPrices[j + 1])
                {
                    // Đổi chỗ struct đơn hàng
                    struct Order tempOrder = orders[j];
                    orders[j] = orders[j + 1];
                    orders[j + 1] = tempOrder;

                    // Đổi chỗ giá trị đơn hàng theo
                    int tempPrice = totalPrices[j];
                    totalPrices[j] = totalPrices[j + 1];
                    totalPrices[j + 1] = tempPrice;
                }
            }
        }
    }
    // Ghi vao file
    file = fopen("C:\\ProjectCFinal\\data\\Order.bin", "wb");
    if (file == NULL)
    {
        printf("[ERROR]Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fwrite(&orders[i], sizeof(struct Order), 1, file);
    }
    fclose(file);
    printf("Successful sort\n");
}
//Order manage
void orderManege()
{
    int choice;
    while(1)
    {
        orderMenu();
        choice = inputChoice(0,7);
        clearInput();
        switch(choice)
        {
            case 1:
                showListOrder();
                break;
            case 2:
                addNewOrder();
                break;
            case 3:
                searchOrderById();
                break;
            case 4:
                sortOrder();
                break;
        }
        if(choice == 0)
        {
            printf("[EXIT]Order Manage, back to Main menu\n");
            break;
        }
        pressAnyKeyToContinue();
    }
}
