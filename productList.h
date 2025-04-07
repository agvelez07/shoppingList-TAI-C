#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "product.h"

typedef struct productItem* ProductItem;
typedef struct productList* ProductList;

ProductList createProductList(const char *name, int capacity);

const char* getproductListName(ProductList productList);
int listNameExists(ProductList* productList, int listCount, char* name);
int addItemToList(ProductList productList, Product product, int quantity, int purchased);
void markAsPurchased(ProductList productList, const char* productName, float price, const char* store);
void printList(ProductList productList);
void printAllLists(ProductList* productList, int listCount);
void unmarkAllPurchased(ProductList list);

#endif
