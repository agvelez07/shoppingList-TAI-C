#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

#define MAX_SEARCH_RESULTS 1000

// Hidden struct definition
struct product {
    char *name;
    char *type;
    float minPrice;
    char *minPriceStore;
};

// Create a new product with name and type
Product createProduct(const char *name, const char *type) {
    Product product = (Product) malloc(sizeof(struct product));
    if (!product) {
        printf("Erro ao alocar memória para produto!\n");
        return NULL;
    }

    product->name = strdup(name);
    product->type = strdup(type);
    product->minPrice = -1;
    product->minPriceStore = NULL;

    return product;
}

// Free all memory allocated for a product
void destroyProduct(Product product) {
    if (product) {
        free(product->name);
        free(product->type);
        if (product->minPriceStore) free(product->minPriceStore);
        free(product);
    }
}

// Getters
const char* getProductName(Product product) {
    return product ? product->name : NULL;
}

const char* getProductType(Product product) {
    return product ? product->type : NULL;
}

float getProductMinPrice(Product product) {
    return product ? product->minPrice : -1;
}

const char* getProductMinPriceStore(Product product) {
    return product ? product->minPriceStore : NULL;
}

// Update the product name
void setProductName(Product product, const char* newName) {
    if (product) {
        free(product->name);
        product->name = strdup(newName);
    }
}

// Update the product price and store (if price is lower)
void updateProductPrice(Product product, float newPrice, const char* store) {
    if (!product) return;

    if (product->minPrice < 0 || newPrice < product->minPrice) {
        product->minPrice = newPrice;
        if (product->minPriceStore) free(product->minPriceStore);
        product->minPriceStore = strdup(store);
    }
}

// Print a product's information
void printProduct(Product product) {
    if (!product) return;

    printf("Nome: %s\n", product->name);
    printf("Tipo: %s\n", product->type);
    if (product->minPrice >= 0 && product->minPriceStore != NULL) {
        printf("Preço mínimo: %.2f € (%s)\n", product->minPrice, product->minPriceStore);
    } else {
        printf("Preço mínimo: (não definido)\n");
    }
    printf("----------------------------\n");
}

// Print all products from an array
void printAllProducts(Product* product, int listCount){
    for(int i = 0; i < listCount; i++){
        if (!product[i]) continue;
        printProduct(product[i]);
    }
}

// Search for products by name (partial match), return indices
int searchProducts(Product* product, int size, const char* searchString, int* foundIndices) {
    int foundCount = 0;

    for (int i = 0; i < size && foundCount < MAX_SEARCH_RESULTS; i++) {
        const char *name = getProductName(product[i]);
        if (strstr(name, searchString)) {
            foundIndices[foundCount++] = i;
        }
    }

    return foundCount;
}

// Print all products that match a type (partial match)
void printProductsByType(Product* product, int size, const char* searchString, int* foundIndices) {
    int foundCount = 0;

    for (int i = 0; i < size && foundCount < MAX_SEARCH_RESULTS; i++) {
        const char *productType = getProductType(product[i]);
        if (strstr(productType, searchString)) {
            foundIndices[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        printf("No products found with type \"%s\".\n", searchString);
    } else {
        printf("Products found with type \"%s\":\n", searchString);
        for (int j = 0; j < foundCount; j++) {
            printProduct(product[foundIndices[j]]);
        }
    }
}
