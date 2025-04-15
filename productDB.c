#include "productDB.h"
#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 Product* products;

// Capacidade máxima de produtos
int productCapacity;

// Número atual de produtos inseridos
int productCount;

// Devolve todos os produtos
Product* getAllProducts() {
    return products;
}

// Devolve o número de produtos atualmente inseridos
int getProductCapacity() {
    return productCount;
}

// Cria a base de dados de produtos com uma capacidade específica
void createProductDB(int capacity) {
    int i;

    // Aloca memória para o array de produtos
    products = (Product*)malloc(sizeof(Product) * capacity);

    // Começa todos os elementos como NULL
    for (i = 0; i < capacity; i++) {
        products[i] = NULL;
    }

    // Guarda a capacidade
    productCapacity = capacity;
    productCount = 0;
}

// Liberta toda a memória associada aos produtos
void releaseProducts() {
    for (int i = 0; i < productCapacity; i++) {
        // Se o produto existir, destrói-o
        if (products[i] != NULL) {
            destroyProduct(products[i]);
        }
    }

    // Liberta o array de ponteiros
    free(products);
}

// Verifica se a base de dados está cheia
int isProductDBFull() {
    int result = 0;

    if (productCount >= productCapacity) {
        result = 1;
    }

    return result;
}

// Insere um novo produto na base de dados
int insertProduct(Product p) {
    int result = 0;

    // Procura a primeira posição livre (NULL)
    for (int i = 0; i < productCapacity; i++) {
        if (products[i] == NULL) {
            products[i] = p;
            productCount++;
            result = 1; // Sucesso
            break;
        }
    }

    return result;
}

// Remove um produto pelo nome
int removeProductByName(const char* name) {
    int result = 0;

    for (int i = 0; i < productCapacity; i++) {
        if (products[i] != NULL &&
            strcmp(getProductName(products[i]), name) == 0) {
            // Liberta a memória do produto
            destroyProduct(products[i]);

            // Marca a posição como livre
            products[i] = NULL;

            // Atualiza o contador
            productCount--;

            result = 1; // Sucesso
            break;
        }
    }

    return result;
}

// Imprime todos os produtos da base de dados
int printAllProducts() {
    int result = 0;

    for (int i = 0; i < productCapacity; i++) {
        if (products[i] != NULL) {
            printProduct(products[i]);
            result = 1; // Pelo menos um produto impresso
        }
    }

    return result;
}

// Procura produtos por nome. Guarda os índices encontrados
int getProductsByName(const char* searchString, int* foundIndices, int maxResults) {
    int foundCount = 0;

    for (int i = 0; i < productCapacity && foundCount < maxResults; i++) {
        const char* name = getProductName(products[i]);
        if (name && strstr(name, searchString)) {
            foundIndices[foundCount++] = i;
        }
    }

    return foundCount;
}

// Procura produtos por tipo. Print e guarda os índices encontrados
int printProductsByType(const char* searchType, int* foundIndices, int maxResults) {
    int foundCount = 0;
    int result = 0;

    for (int i = 0; i < productCapacity && foundCount < maxResults; i++) {
        const char* type = getProductType(products[i]);
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

// Devolve o ponteiro para o produto com nome igual ao fornecido
Product getProduct(const char* name) {
    Product result = NULL;

    for (int i = 0; i < productCapacity; i++) {
        if (products[i] != NULL &&
            strcmp(getProductName(products[i]), name) == 0) {
            result = products[i];
            break;
        }
    }

    return result;
}
