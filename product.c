#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

#define MAX_SEARCH_RESULTS 1000

// Hidden struct definition
struct product {
    char* name;
    char* type;
    float minPrice;
    char* minPriceStore;
};

Product createProduct(const char* name, const char* type) {
    Product result = (Product)malloc(sizeof(struct product));

    if (result) {
        result->name = strdup(name);
        result->type = strdup(type);
        result->minPrice = -1;
        result->minPriceStore = NULL;
    } else {
        printf("Erro ao alocar memória para produto!\n");
    }

    return result;
}

void destroyProduct(Product product) {
    if (product) {
        free(product->name);
        free(product->type);
        if (product->minPriceStore) {
            free(product->minPriceStore);
        }
        free(product);
    }
}

const char* getProductName(Product product) {
    const char* result = NULL;
    if (product) {
        result = product->name;
    }
    return result;
}

const char* getProductType(Product product) {
    const char* result = NULL;
    if (product) {
        result = product->type;
    }
    return result;
}

float getProductMinPrice(Product product) {
    float result = -1;
    if (product) {
        result = product->minPrice;
    }
    return result;
}

const char* getProductMinPriceStore(Product product) {
    const char* result = NULL;
    if (product) {
        result = product->minPriceStore;
    }
    return result;
}

void setProductName(Product product, const char* newName) {
    if (product) {
        free(product->name);
        product->name = strdup(newName);
    }
}

void updateProductPrice(Product product, float newPrice, const char* store) {
    if (product) {
        if (product->minPrice < 0 || newPrice < product->minPrice) {
            product->minPrice = newPrice;

            if (product->minPriceStore) {
                free(product->minPriceStore);
            }

            product->minPriceStore = strdup(store);
        }
    }
}

void printProduct(Product product) {
    if (product) {
        printf("Nome: %s\n", product->name);
        printf("Tipo: %s\n", product->type);

        if (product->minPrice >= 0 && product->minPriceStore != NULL) {
            printf("Preço mínimo: %.2f € (%s)\n", product->minPrice, product->minPriceStore);
        } else {
            printf("Preço mínimo: (não definido)\n");
        }

        printf("----------------------------\n");
    }
}

int searchProducts(Product* products, int size, const char* searchString, int* foundIndices) {
    int foundCount = 0;

    for (int i = 0; i < size && foundCount < MAX_SEARCH_RESULTS; i++) {
        const char* name = getProductName(products[i]);
        if (name && strstr(name, searchString)) {
            foundIndices[foundCount++] = i;
        }
    }

    return foundCount;
}

int printProductsByType(Product* products, int size, const char* searchString, int* foundIndices) {
    int foundCount = 0;
    int result = 0;

    for (int i = 0; i < size && foundCount < MAX_SEARCH_RESULTS; i++) {
        const char* type = getProductType(products[i]);
        if (type && strstr(type, searchString)) {
            foundIndices[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        printf("No products found with type \"%s\".\n", searchString);
    } else {
        printf("Products found with type \"%s\":\n", searchString);
        for (int j = 0; j < foundCount; j++) {
            printProduct(products[foundIndices[j]]);
        }
        result = 1;
    }

    return result;
}
