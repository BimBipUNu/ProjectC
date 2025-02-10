#include<stdio.h>
//Ham xoa bo nho dem
void clearInput();
//Menu Bat dau
void startMenu();
//Menu chinh
void mainMenu();
//Chuc nang 1. Hien thi ds
void showListCategory(int size, FILE *file);
//Chuc nang 2. Them danh muc
void addNewCategory(int *size, struct Category *list, FILE *file);
//Ham nhap chuc nang
int inputChoose(int start, int end);