#ifndef PRODUCT_DB_H
#define PRODUCT_DB_H

#include "product.h"

void createProductDB(int capacity);
void releaseProducts(void);
int isProductDBFull(void);
int insertProduct(Product p);
int removeProductByName(const char* name);
int searchProductsByName(const char* searchString, int* foundIndices);
int printProductsByType(const char* searchType, int* foundIndices);
Product findProduct(const char* name);
int printAllProducts(void);

#endif
