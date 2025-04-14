#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "productList.h"
#include "product.h"

#define MAX_SEARCH_RESULTS 1000

// Definição de ProductItem
struct productItem {
    Product product;
    int quantity;
    int purchased;
};

// Definição de ProductList
struct productList {
    char *name;
    ProductItem *productItems;
    int size;
    int capacity;
};

// Criação de nova lista (vazia)
ProductList createProductList(const char *name, int capacity) {
    ProductList productList = (ProductList) malloc(sizeof(struct productList));
    if (!productList) {
        return NULL;
    }

    productList->name = strdup(name);
    productList->productItems = malloc(sizeof(ProductItem) * capacity);
    productList->capacity = capacity;
    productList->size = 0;

    return productList;
}

void destroyProductList(ProductList productList){
    if (!productList) return;

    free(productList->name);
    free(productList->productItems);
    free(productList);
}

const char* getProductListName(ProductList  productList) {
    const char* name = NULL;

    if (productList) {
        name = productList->name;
    }

    return name;
}

void setProductListName(ProductList productList, const char* newName) {
    if (productList) {
        free(productList->name);
        productList->name = strdup(newName);
    }
}

int addProductToList(ProductList productList, Product product, int quantity, int purchased) {
    int result = 0;

    if (productList->size >= productList->capacity) {
        int newCapacity = productList->capacity * 2;
        ProductItem* newProductItem = realloc(productList->productItems, newCapacity * sizeof(ProductItem));

        productList->productItems = newProductItem;
        productList->capacity = newCapacity;
        result = 1;

    }

    ProductItem productItem;
    productItem->product = product;
    productItem->quantity = quantity;
    productItem->purchased = purchased;

    // Inserir na posição livre
    productList->productItems[productList->size] = productItem;
    productList->size++;

    return result;
}

int removeProductFromList(ProductList productList, Product product) {
    int result = 0;
    for (int i = 0; i < productList->size; i++) {
        if (strcmp(getProductName(productList->productItems[i]->product), getProductName(product)) == 0) {

            for (int j = i; j < productList->size - 1; j++) {
                productList->productItems[j] = productList->productItems[j + 1];
            }

            productList->size--;
            result = 1;
        }
    }
    return result;
}

int removeProductItemFromList(ProductList productList, const char* productName) {
    int result = 0;
    for (int i = 0; i < productList->size; i++) {
        if (strcmp(getProductName(productList->productItems[i]->product), productName) == 0) {
            for (int j = i; j < productList->size - 1; j++) {
                productList->productItems[j] = productList->productItems[j + 1];
            }
            productList->size--;
            result = 1;
            break;
        }
    }
    return result;
}

int removeProductFromListByName(ProductList productList, const char* productName) {
    int removed = 0;
    int result = 0;
    if (productList && productName) {
        for (int i = 0; i < productList->size; i++) {
            const char* name = getProductName(productList->productItems[i]->product);

            if (name && strcmp(name, productName) == 0) {
                 for (int j = i; j < productList->size - 1; j++) {
                     productList->productItems[j] = productList->productItems[j + 1];
                }
                productList->size--;
                removed = 1;
                result = 1;
                break;
            }
        }
    }

    return result;
}

int markProductAsPurchased(ProductList productList, const char* productName, float price, const char* store) {
    int result = 0;
    for (int i = 0; i < productList->size; i++) {
        if (strcmp(getProductName(productList->productItems[i]->product), productName) == 0) {
            productList->productItems[i]->purchased = 1;
            updateProductPrice(productList->productItems[i]->product, price, store);
            result = 1;
        }
    }
    return result;
}

int unmarkProductAsPurchased(ProductList list, const char* productName) {
    int result = 0;

    if (list && productName) {
        for (int i = 0; i < list->size; i++) {
            if (strcmp(getProductName(list->productItems[i]->product), productName) == 0) {
                list->productItems[i]->purchased = 0;
                result = 1;
                break;
            }
        }
    }

    return result;
}

int unmarkAllProductsAsPurchased(ProductList productList){
    int result = 0;
    for(int i = 0; i < productList->size; i++){
        if(productList->productItems[i]->purchased != 0){
            productList->productItems[i]->purchased = 0;
            result = 1;
        }
    }
    return result;
}

int countPendingProducts(ProductList productList){
    int unpurchasedProductsCount = 0;

    for(int i = 0; i < productList->size; i++){
        if(productList->productItems[i]->purchased == 0){
            unpurchasedProductsCount++;
        }
    }
    return unpurchasedProductsCount;
}

int searchProductsInList(ProductList productList, const char* searchTerm, int* foundIndices) {
    int foundCount = 0;

    for (int i = 0; i < productList->size && foundCount < MAX_SEARCH_RESULTS; i++) {
        const char* name = getProductName(productList->productItems[i]->product);
        if (name && strstr(name, searchTerm)) {
            foundIndices[foundCount++] = i;
        }
    }

    return foundCount;
}

int printProductList(ProductList list) {
    int result = 0;
    if (!list) {
        result = 0;
    }
    else {
        printf("\n=========== Lista: %s ===========\n", getProductListName(list));

        for (int i = 0; i < list->size; i++) {
            ProductItem item = list->productItems[i];

            printf("\nProduto %d:", i + 1);
            printf("\n- Nome: %s", getProductName(item->product));
            printf("\n- Tipo: %s", getProductType(item->product));

            float price = getProductMinPrice(item->product);
            const char *store = getProductMinPriceStore(item->product);

            if (price >= 0 && store) {
                printf("\n- Preço mínimo: %.2f € (%s)", price, store);
            } else {
                printf("\n- Preço mínimo: (não definido)");
            }

            printf("\n- Quantidade: %d", item->quantity);
            printf("\n- Comprado: %s", item->purchased ? "Sim" : "Não");
            printf("\n--------------------------------");
        }

        printf("\nProdutos por comprar: %d", countPendingProducts(list));
        printf("\n================================\n");
        result = 1;
    }
    return result;
}
