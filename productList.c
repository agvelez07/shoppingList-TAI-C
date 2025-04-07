#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "productList.h"
#include "product.h"

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
    ProductList list = (ProductList) malloc(sizeof(struct productList));
    if (!list) {
        printf("Erro ao alocar memória para a lista de compras.\n");
        return NULL;
    }

    list->name = strdup(name);
    list->capacity = capacity;
    list->size = 0;

    return list;
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


int listNameExists(ProductList* productList, int listCount, char* name){
    for(int i = 0; i < listCount; i++){
        if(!productList[i]){
            break;
        }
        printList(productList[i]);
    }
}


void markAsPuchased(ProductList productList, char productName){
    for(int i = 0; i < productList->size; i++){
        if(strcmp(getProductName(productList->productItems[i]->product), productName) == 0){
            productList->productItems[i]->purchased = 1;
            printf("\nMarked '%s' as purchased.\n", productName);
        }
    }
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
        printf("\n================================");
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