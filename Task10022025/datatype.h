#ifndef DATATYPE_H
#define DATATYPE_H
//Date
struct Date
{
    int day, month, year;
};
//Danh muc
struct Category
{
    char categoryId[10];
    char categoryName[10];
};
//San pham
struct Product
{
    char productId[10];
    char categoryId[10];
    char productNam[10];
    int quantity;
    int price;
};
//Don hang
struct Order
{
    char orderId[10];
    char customerId[20];
    struct Date date;
    struct Product product;
};
#endif