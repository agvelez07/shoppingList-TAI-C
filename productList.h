#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "product.h"

typedef struct productItem* ProductItem;
typedef struct productList* ProductList;

ProductList createProductList(const char *name, int capacity);
#endif
