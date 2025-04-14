#ifndef PRODUCT_DB_H
#define PRODUCT_DB_H

#include "product.h"

Product* getAllProducts();
void createProductDB(int capacity);
void releaseProducts(void);
int isProductDBFull(void);
int insertProduct(Product p);
int removeProductByName(const char* name);
int getProductsByName(const char* searchString, int* foundIndices, int maxResults);
int printProductsByType(const char* searchType, int* foundIndices, int maxResults);
Product getProduct(const char* name);
int printAllProducts();

#endif
