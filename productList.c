#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "productList.h"
#include "product.h"

// Definição da estrutura ProductItem
struct productItem {
    Product *product;
    int quantity;
    int purchased;
};

// Definição da estrutura ProductList
struct productList {
    char *name;
    ProductItem *productItems;
    int size;
    int capacity;
};

// Criação de uma nova lista de compras
ProductList createProductList(const char *name, int capacity) {
    // Aloca memória para a lista
    ProductList productList = (ProductList) malloc(sizeof(struct productList));
    if (!productList) return NULL;

    // Copia o nome, aloca espaço para os items, define capacidade e começa com tamanho 0
    productList->name = strdup(name);
    productList->productItems = malloc(sizeof(ProductItem) * capacity);
    productList->capacity = capacity;
    productList->size = 0;

    return productList;
}

// Liberta a memória de uma lista de compras
void destroyProductList(ProductList productList){
    if (!productList) return;

    // Liberta o nome da lista
    free(productList->name);

    // Liberta cada produto da lista
    for (int i = 0; i < productList->size; i++) {
        free(productList->productItems[i]);
    }

    // Liberta o array de itens e a própria lista
    free(productList->productItems);
    free(productList);
}

// Devolve o nome da lista
const char* getProductListName(ProductList productList) {
    const char* name = NULL;
    if (productList) {
        name = productList->name;
    }
    return name;
}

// Altera o nome da lista
void setProductListName(ProductList productList, const char* newName) {
    if (productList) {
        free(productList->name);
        productList->name = strdup(newName);
    }
}

// Adiciona um produto à lista
int addProductToList(ProductList list, Product product, int quantity) {
    int result = 1;

    // Verifica argumentos válidos
    if (list == NULL || product == NULL || quantity <= 0) {
        result = -1;
    }
    else if (list->size >= list->capacity) {
        result = -2; // lista cheia
    }
    else {
        // Aloca memória para o novo produto na lista
        ProductItem item = malloc(sizeof(struct productItem));
        if (item == NULL) {
            result = -3; // erro de memória
        }
        else {
            // Preenche os dados do produto na lista
            item->product = product;
            item->quantity = quantity;
            item->purchased = 0;

            // Adiciona à lista
            list->productItems[list->size] = item;
            list->size++;
        }
    }

    return result;
}

// Remove um produto da lista
int removeProductFromList(ProductList productList, Product product) {
    int result = 0;

    for (int i = 0; i < productList->size; i++) {
        if (strcmp(getProductName(productList->productItems[i]->product), getProductName(product)) == 0) {
            // Move os itens para preencher a vaga
            for (int j = i; j < productList->size - 1; j++) {
                productList->productItems[j] = productList->productItems[j + 1];
            }

            productList->size--;
            result = 1;
        }
    }
    return result;
}

// Remove um produto da lista pelo nome
int removeProductItemFromList(ProductList productList, const char* productName) {
    int result = 0;

    for (int i = 0; i < productList->size; i++) {
        if (strcmp(getProductName(productList->productItems[i]->product), productName) == 0) {
            // Desloca os itens para preencher a vaga
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

// Marca um produto como comprado
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

// Desmarca um produto como comprado
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

// Desmarca todos os produtos da lista
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

// Conta quantos produtos ainda não foram comprados
int countPendingProducts(ProductList productList){
    int unpurchasedProductsCount = 0;

    for(int i = 0; i < productList->size; i++){
        if(productList->productItems[i]->purchased == 0){
            unpurchasedProductsCount++;
        }
    }

    return unpurchasedProductsCount;
}

// Pesquisa produtos por nome parcial dentro da lista
int searchProductsInList(ProductList productList, const char* searchTerm, int* foundIndices, int maxResults) {
    int foundCount = 0;

    for (int i = 0; i < productList->size && foundCount < maxResults; i++) {
        const char* name = getProductName(productList->productItems[i]->product);
        if (name && strstr(name, searchTerm)) {
            foundIndices[foundCount++] = i;
        }
    }

    return foundCount;
}

// Mostra os produtos da lista no ecrã
int printProductList(ProductList list) {
    int result = 0;

    if (!list) {
        result = 0;
    }
    else {
        printf("\n=========== Lista: %s ===========\n", getProductListName(list));

        for (int i = 0; i < list->size; i++) {
            ProductItem item = list->productItems[i];

            // Mostra os dados de cada produto
            printf("\nProduto %d:", i + 1);
            printf("\n- Nome: %s", getProductName(item->product));
            printf("\n- Tipo: %s", getProductType(item->product));

            float price = getProductMinPrice(item->product);
            const char *store = getProductMinPriceStore(item->product);

            if (price >= 0 && store) {
                printf("\n- Preco minimo: %.2f eur, (%s)", price, store);
            } else {
                printf("\n- Preco minimo: (nao definido)");
            }

            printf("\n- Quantidade: %d", item->quantity);
            printf("\n- Comprado: %s", item->purchased ? "Sim" : "Nao");
            printf("\n--------------------------------");
        }

        // Mostra o número de produtos por comprar
        printf("\nProdutos por comprar: %d", countPendingProducts(list));
        printf("\n====================================\n");

        result = 1;
    }

    return result;
}
