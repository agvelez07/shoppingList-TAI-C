#ifndef PRODUCT_LIST_DB_H
#define PRODUCT_LIST_DB_H

#include "productList.h"

void createProductListDB(int capacity);
void releaseProductLists(void);
int isProductListDBFull(void);
int insertProductList(ProductList list);
int removeProductListByName(const char* name);
ProductList getProductList(int index);
ProductList getProductListByName(const char* name);
int searchProductLists(const char* searchString, int* foundIndices);
int selectProductListFromResults(int* foundIndices, int count);
int printAllProductLists();

#endif
