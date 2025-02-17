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
    char categoryId[11];//Them 1 ki tu NULL
    char categoryName[11];
};
//San pham
struct Product
{
    char productId[11];
    char categoryId[11];
    char productName[11];
    int quantity;
    int price;
};
//Don hang
struct Order
{
    char orderId[11];
    char customerId[21];
    struct Date date;
    struct Product product;
};
#endif