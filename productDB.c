#include "productDB.h"
#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Product* products;
int productCapacity;
int productCount;


Product* getAllProducts() {
    return products;
}

int getProductCapacity() {
    return productCount;
}


void createProductDB(int capacity) {
    int i;

    products = (Product*)malloc(sizeof(Product) * capacity);
    for (i = 0; i < capacity; i++) {
        products[i] = NULL;
    }

    productCapacity = capacity;
    productCount = 0;
}

void releaseProducts() {
    for (int i = 0; i < productCapacity; i++) {
        if (products[i] != NULL) {
            destroyProduct(products[i]);
        }
    }

    free(products);
}

int isProductDBFull() {
    int result = 0;

    if (productCount >= productCapacity) {
        result = 1;
    }

    return result;
}

int insertProduct(Product p) {
    int result = 0;

    for (int i = 0; i < productCapacity; i++) {
        if (products[i] == NULL) {
            products[i] = p;
            productCount++;
            result = 1;
            break;
        }
    }

    return result;
}

int removeProductByName(const char* name) {
    int result = 0;

    for (int i = 0; i < productCapacity; i++) {
        if (products[i] != NULL && strcmp(getProductName(products[i]), name) == 0) {
            destroyProduct(products[i]);
            products[i] = NULL;
            productCount--;
            result = 1;
            break;
        }
    }

    return result;
}

int printAllProducts() {
    int result = 0;

    for (int i = 0; i < productCapacity; i++) {
        if (products[i] != NULL) {
            printProduct(products[i]);
            result = 1;
        }
    }

    return result;
}

int getProductsByName(const char* searchString, int* foundIndices, int maxResults) {
    int foundCount = 0;

    for (int i = 0; i < productCapacity && foundCount < maxResults; i++) {
        const char *name = getProductName(products[i]);
        if (name && strstr(name, searchString)) {
            foundIndices[foundCount++] = i;
        }
    }

    return foundCount;
}

int printProductsByType(const char* searchType, int* foundIndices, int maxResults) {
    int foundCount = 0;
    int result = 0;

    for (int i = 0; i < productCapacity && foundCount < maxResults; i++) {
        const char *type = getProductType(products[i]);
        if (type && strstr(type, searchType)) {
            foundIndices[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        printf("Nenhum produto com tipo \"%s\" encontrado.\n", searchType);
    } else {
        printf("Produtos encontrados com tipo \"%s\":\n", searchType);
        for (int j = 0; j < foundCount; j++) {
            printProduct(products[foundIndices[j]]);
        }
        result = 1;
    }

    return result;
}

Product getProduct(const char* name) {
    Product result = NULL;

    for (int i = 0; i < productCapacity; i++) {
        if (products[i] != NULL && strcmp(getProductName(products[i]), name) == 0) {
            result = products[i];
            break;
        }
    }

    return result;
}
