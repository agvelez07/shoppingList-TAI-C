#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "product.h"

typedef struct productItem* ProductItem;
typedef struct productList* ProductList;

ProductList createProductList(const char* name, int capacity);
void destroyProductList(ProductList productList);
const char* getProductListName(ProductList productList);
void setProductListName(ProductList productList, const char* newName);
int addProductToList(ProductList productList, Product product, int quantity, int purchased);
int removeProductFromList(ProductList productList, Product product);
int removeProductItemFromList(ProductList productList, const char* productName);
int removeProductFromListByName(ProductList productList, const char* productName);
int markProductAsPurchased(ProductList productList, const char* productName, float price, const char* store);
int unmarkAllProductsAsPurchased(ProductList productList);
int unmarkProductAsPurchased(ProductList productList, const char* productName);
int countPendingProducts(ProductList productList);
int printProductList(ProductList productList);

#endif