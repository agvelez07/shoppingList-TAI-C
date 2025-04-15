#include "productListDB.h"
#include "productList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEARCH_RESULTS 100

ProductList* productLists;

// Capacidade total da base de dados
int productListCapacity;

// Número atual de listas inseridas
int productListCount;

// Cria a base de dados de listas com capacidade definida
void createProductListDB(int capacity) {
    int i;

    // Aloca memória para o array de listas
    productLists = (ProductList*)malloc(sizeof(ProductList) * capacity);

    // Começa por colocar todas as posições a NULL
    for (i = 0; i < capacity; i++) {
        productLists[i] = NULL;
    }

    // Guarda a capacidade e inicia contador
    productListCapacity = capacity;
    productListCount = 0;
}

// Liberta toda a memória associada às listas de compras
void releaseProductLists() {
    for (int i = 0; i < productListCapacity; i++) {
        if (productLists[i] != NULL) {
            destroyProductList(productLists[i]);
        }
    }

    // Liberta o array de ponteiros
    free(productLists);
}

// Verifica se a base de dados está cheia
int isProductListDBFull() {
    int result = 0;
    if (productListCount >= productListCapacity) {
        result = 1;
    }
    return result;
}

// Insere uma nova lista na base de dados
int insertProductList(ProductList productList) {
    int result = 0;

    // Procura a primeira posição livre
    for (int i = 0; i < productListCapacity; i++) {
        if (productLists[i] == NULL) {
            productLists[i] = productList;
            productListCount++;
            result = 1; // Sucesso
            break;
        }
    }

    return result;
}

// Remove uma lista pelo nome
int removeProductListByName(const char* name) {
    int result = 0;

    for (int i = 0; i < productListCapacity; i++) {
        if (productLists[i] != NULL &&
            strcmp(getProductListName(productLists[i]), name) == 0) {

            // Liberta a lista e marca a posição como livre
            destroyProductList(productLists[i]);
            productLists[i] = NULL;
            productListCount--;
            result = 1; // Sucesso
            break;
        }
    }

    return result;
}

// Devolve a lista pelo índice
ProductList getProductList(int index) {
    ProductList result = NULL;

    // Verifica se o índice é válido e a posição não está vazia
    if (index >= 0 && index < productListCapacity && productLists[index] != NULL) {
        result = productLists[index];
    }

    return result;
}

// Procura uma lista pelo nome exato
ProductList getProductListByName(const char* name) {
    ProductList result = NULL;

    if (productLists && name) {
        for (int i = 0; i < productListCount; i++) {
            if (productLists[i] != NULL &&
                strcmp(getProductListName(productLists[i]), name) == 0) {

                result = productLists[i];
                break;
            }
        }
    }

    return result;
}

// Pesquisa listas por nome (parcial) e guarda os índices encontrados
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

// Permite ao utilizador escolher uma lista dos resultados encontrados
int selectProductListFromResults(int* foundIndices, int count) {
    int result = 0;

    if (count == 1) {
        // Apenas uma lista encontrada, devolve o índice direto
        result = foundIndices[0];
    } else if (count > 1) {
        // Mostra as opções ao utilizador
        for (int i = 0; i < count; i++) {
            int index = foundIndices[i];
            printf("%d - %s\n", i + 1, getProductListName(productLists[index]));
        }

        // Devolver 1 apenas como indicação deque existem multiplos resultados
        result = 1;
    }

    return result;
}

// Imprime todas as listas da base de dados
int printAllProductLists() {
    int result = 0;

    for (int i = 0; i < productListCount; i++) {
        if (productLists[i] != NULL) {
            printProductList(productLists[i]);
            result = 1; // Pelo menos uma lista foi impressa
        }
    }

    return result;
}
