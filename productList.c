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
        printf("Erro ao alocar memória para a lista de compras.\n");
        return NULL;
    }

    productList->name = strdup(name);
    productList->productItems = malloc(sizeof(ProductItem) * capacity);
    productList->capacity = capacity;
    productList->size = 0;

    return productList;
}

const char* getproductListName(ProductList productList) {
    return productList ? productList->name : NULL;
}

int listNameExists(ProductList* productList, int listCount, char* name){
    for(int i = 0; i < listCount; i++){
        if(strcmp(getproductListName(productList[i]), name) == 0){
            return 1;
        }
    }
    return 0;
}

int addItemToList(ProductList productList, Product product, int quantity, int purchased) {
    if(!getProductMinPriceStore(product) && !getProductMinPrice(product)){
        return -1;
    }
    if (productList->size >= productList->capacity) {
        int newCapacity = productList->capacity * 2;
        ProductItem* newProductItem = realloc(productList->productItems, newCapacity * sizeof(ProductItem));
        if (!newProductItem) {
            printf("Erro ao realocar memória para itens.\n");
            return 0;
        }
        productList->productItems = newProductItem;
        productList->capacity = newCapacity;
    }

    ProductItem productItem;
    productItem->product = product;
    productItem->quantity = quantity;
    productItem->purchased = purchased;

    // Inserir na posição livre
    productList->productItems[productList->size] = productItem;
    productList->size++;

    return 1;
}

void markAsPurchased(ProductList productList, const char* productName, float price, const char* store) {
    for (int i = 0; i < productList->size; i++) {
        if (strcmp(getProductName(productList->productItems[i]->product), productName) == 0) {
            productList->productItems[i]->purchased = 1;
            updateProductPrice(productList->productItems[i]->product, price, store);
            printf("\nMarked '%s' as purchased (%.2f€ at %s).\n", productName, price, store);
        }
    }
}

void printAllLists(ProductList* productList, int listCount){
    for(int i = 0; i < listCount; i++){
        if(!productList[i]){
            break;
        }
        printList(productList[i]);
    }
}

void unmarkAllPurchased(ProductList productList){
    for(int i = 0; i < productList->size; i++){
        if(productList->productItems[i]->purchased != 0){
            productList->productItems[i]->purchased = 0;
        }
    }
}

int countUnpurchasedProducts(ProductList productList){
    int unpurchasedProductsCount = 0;

    for(int i = 0; i < productList->size; i++){
        if(productList->productItems[i]->purchased == 0){
            unpurchasedProductsCount++;
        }
    }
    return unpurchasedProductsCount;
}

void printList(ProductList productList) {
    printf("\n=========== List: %s ===========\n", productList->name);

    for (int i = 0; i < productList->size; i++) {
        ProductItem productItem = productList->productItems[i]; // items[i] is a pointer to ProductItem

        printf("\nProduct %d:", i + 1);
        printf("\n- Name: %s", getProductName(productItem->product));
        printf("\n- Type: %s", getProductType(productItem->product));

        float minPrice = getProductMinPrice(productItem->product);
        const char* store = getProductMinPriceStore(productItem->product);

        if (minPrice >= 0 && store) {
            printf("\n- Lowest price: %.2f € (%s)", minPrice, store);
        } else {
            printf("\n- Lowest price: (not defined)");
        }

        printf("\n- Quantity: %d", productItem->quantity);
        printf("\n- Purchased: %s", productItem->purchased ? "Yes" : "No");
        printf("\n--------------------------------");
    }
    printf("\nItems left to purchase: %d", countUnpurchasedProducts(productList));
    printf("\n================================");

}

void setproductListName(ProductList productList, const char* newName) {
    if (productList) {
        free(productList->name);
        productList->name = strdup(newName);
    }
}

void removeProductFromList(ProductList productList, Product product) {
    if (!productList || !product) return;

    for (int i = 0; i < productList->size; i++) {
        if (strcmp(getProductName(productList->productItems[i]->product), getProductName(product)) == 0) {

            for (int j = i; j < productList->size - 1; j++) {
                productList->productItems[j] = productList->productItems[j + 1];
            }

            productList->size--;
            printf("Product removed from list.\n");
            return;
        }
    }

    printf("Product not found in list.\n");
}

void destroyProductList(ProductList productList){
    if (!productList) return;

    free(productList->name);
    free(productList->productItems);
    free(productList);
}

void removeProductItemFromList(ProductList productList, const char* productName) {
    if (!productList || !productName) return;

    for (int i = 0; i < productList->size; i++) {
        if (strcmp(getProductName(productList->productItems[i]->product), productName) == 0) {
            for (int j = i; j < productList->size - 1; j++) {
                productList->productItems[j] = productList->productItems[j + 1];
            }
            productList->size--; // reduz a contagem de itens
            break;
        }
    }
 }

int searchProductsInList(ProductItem* products, int size, const char* searchString, int* foundIndices) {
    int foundCount = 0;

    for (int i = 0; i < size && foundCount < MAX_SEARCH_RESULTS; i++) {
        const char* name = getProductName(products[i]->product);
        if (strstr(name, searchString)) {
            foundIndices[foundCount++] = i;
        }
    }

    return foundCount;
}

int selectProductFromResults(ProductList list, int* foundIndices, int count) {
    if (count == 0) {
        printf("No matching products found.\n");
        return -1;
    }

    if (count == 1) {
        return foundIndices[0];
    }

    printf("Multiple products found:\n");
    for (int i = 0; i < count; i++) {
        int index = foundIndices[i];
        printf("%d - %s\n", i + 1, getProductName(list->productItems[index]->product));
    }

    int choice = 0;
    do {
        printf("Choose a product (1-%d): ", count);
        scanf("%d", &choice);
    } while (choice < 1 || choice > count);

    return foundIndices[choice - 1];
}


