#ifndef PRODUCT_LIST_DB_H
#define PRODUCT_LIST_DB_H

#include "productList.h"

 void createProductListDB(int capacity);

 void releaseProductLists(void);

 int isProductListDBFull(void);

 int insertProductList(ProductList list);

int removeProductListByName(const char* name);

ProductList getProductListByName(ProductList* lists, const char* name);

int listNameExists(ProductList* lists, int listCount, const char* name);

int searchProductLists(ProductList* lists, const char* searchString, int* foundIndices);

int selectProductListFromResults(ProductList* lists, int* foundIndices, int count);

int printAllProductLists(ProductList* lists, int listCount);

#endif
