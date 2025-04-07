#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

// Hidden struct definition
struct product {
    char *name;
    char *type;
    float minPrice;
    char *minPriceStore;
};

Product createProduct(const char *name, const char *type) {
    Product product = (Product) malloc(sizeof(struct product));
    if (!product) {
        printf("Erro ao alocar memória para produto!\n");
        return NULL;
    }

    product->name = strdup(name);
    product->type = strdup(type);

    return product;
}

void destroyProduct(Product product) {
    if (product) {
        free(product->name);
        free(product->type);
        if (product->minPriceStore) free(product->minPriceStore);
        free(product);
    }
}

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

void setProductName(Product product, const char* newName) {
    if (product) {
        free(product->name);
        product->name = strdup(newName);
    }
}

void updateProductPrice(Product product, float newPrice, const char* store) {
    if (!product) return;

    if (product->minPrice < 0 || newPrice < product->minPrice) {
        product->minPrice = newPrice;
        if (product->minPriceStore) free(product->minPriceStore);
        product->minPriceStore = strdup(store);
    }
}

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
