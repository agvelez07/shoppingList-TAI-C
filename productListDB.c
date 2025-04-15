#include "productListDB.h"
#include "productList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEARCH_RESULTS 100

ProductList* productLists;
int productListCapacity;
int productListCount;

void createProductListDB(int capacity) {
    int i;

    productLists = (ProductList*)malloc(sizeof(ProductList) * capacity);
    for (i = 0; i < capacity; i++) {
        productLists[i] = NULL;
    }

    productListCapacity = capacity;
    productListCount = 0;
}

void releaseProductLists() {
    for (int i = 0; i < productListCapacity; i++) {
        if (productLists[i] != NULL) {
            destroyProductList(productLists[i]);
        }
    }
    free(productLists);
}

int isProductListDBFull() {
    int result = 0;
    if (productListCount >= productListCapacity) {
        result = 1;
    }
    return result;
}

int insertProductList(ProductList productList) {
    int result = 0;

    for (int i = 0; i < productListCapacity; i++) {
        if (productLists[i] == NULL) {
            productLists[i] = productList;
            productListCount++;
            result = 1;
            break;
        }
    }

    return result;
}

int removeProductListByName(const char* name) {
    int result = 0;

    for (int i = 0; i < productListCapacity; i++) {
        if (productLists[i] != NULL && strcmp(getProductListName(productLists[i]), name) == 0) {
            destroyProductList(productLists[i]);
            productLists[i] = NULL;
            productListCount--;
            result = 1;
            break;
        }
    }

    return result;
}

ProductList getProductList(int index) {
    ProductList result = NULL;

    if (index >= 0 && index < productListCapacity && productLists[index] != NULL) {
        result = productLists[index];
    }

    return result;
}

ProductList getProductListByName(const char* name) {
    ProductList result = NULL;

    if (productLists && name) {
        for (int i = 0; i < productListCount; i++) {
            if (productLists[i] != NULL && strcmp(getProductListName(productLists[i]), name) == 0) {
                result = productLists[i];
                break;
            }
        }
    }

    return result;
}

int searchProductLists(const char* searchString, int* foundIndices) {
    int foundCount = 0;

    for (int i = 0; i < productListCount && foundCount < MAX_SEARCH_RESULTS; i++) {
        const char* name = getProductListName(productLists[i]);
        if (name && strstr(name, searchString)) {
            foundIndices[foundCount++] = i;
        }
    }

    return foundCount;
}

int selectProductListFromResults(int* foundIndices, int count) {
    int result = 0;

    if (count == 1) {
        result = foundIndices[0];
    } else if (count > 1) {
        printf("Listas encontradas:\n");
        for (int i = 0; i < count; i++) {
            int index = foundIndices[i];
            printf("%d - %s\n", i + 1, getProductListName(productLists[index]));
            result = 1;
        }
    }
    else{
        printf("Nao forma encontras productListas para esta pesquisa!");
    }
    return result;
}

int printAllProductLists() {
    int result = 0;

    for (int i = 0; i < productListCount; i++) {
        if (productLists[i] != NULL) {
            printProductList(productLists[i]);
            result = 1;
        }
    }

    return result;
}
