#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

// Definição escondida da struct Product
struct product {
    char* name;
    char* type;
    float minPrice;
    char* minPriceStore;
};

// Cria um novo produto
Product createProduct(const char* name, const char* type) {
    Product result = 0;

    // Verifica se os parâmetros são válidos (não nulos e não vazios)
    int validInput = (name != 0 && type != 0 && strlen(name) > 0 && strlen(type) > 0);
    int memoryOK = 1;

    if (validInput) {
        // Aloca memória para o novo produto
        result = (Product)malloc(sizeof(struct product));
        if (result != 0) {
            // Copia o nome e tipo
            result->name = strdup(name);
            result->type = strdup(type);

            //Inicia preço mínimo como indefinido (-1)
            result->minPrice = -1;
            result->minPriceStore = 0;

            // Verifica se as cópias de strings foram bem-sucedidas
            if (result->name == 0 || result->type == 0) {
                memoryOK = 0;
            }
        } else {
            memoryOK = 0;
        }
    }

    // Se algo falhou, liberta a memória já alocada
    if (!validInput || !memoryOK) {
        if (result != 0) {
            free(result->name);
            free(result->type);
            free(result);
            result = 0;
        }
    }

    return result;
}

// Liberta a memória associada ao produto
void destroyProduct(Product product) {
    if (product) {
        // Liberta o nome, tipo e loja
        free(product->name);
        free(product->type);
        if (product->minPriceStore) {
            free(product->minPriceStore);
        }

        // Liberta o próprio produto
        free(product);
    }
}

// Devolve o nome do produto
const char* getProductName(Product product) {
    const char* result = NULL;
    if (product) {
        result = product->name;
    }
    return result;
}

// Devolve o tipo do produto
const char* getProductType(Product product) {
    const char* result = NULL;
    if (product) {
        result = product->type;
    }
    return result;
}

// Devolve o preço mínimo conhecido do produto
float getProductMinPrice(Product product) {
    float result = -1;
    if (product) {
        result = product->minPrice;
    }
    return result;
}

// Devolve o nome da loja onde foi encontrado o preço mínimo
const char* getProductMinPriceStore(Product product) {
    const char* result = NULL;
    if (product) {
        result = product->minPriceStore;
    }
    return result;
}

// Altera o nome do produto
void setProductName(Product product, const char* newName) {
    if (product) {
        // Liberta o nome atual
        free(product->name);

        // Guarda a nova cópia
        product->name = strdup(newName);
    }
}

// Atualiza o preço mínimo do produto, se o novo for mais baixo
void updateProductPrice(Product product, float newPrice, const char* store) {
    if (product) {
        // Se ainda não existe preço ou o novo é menor
        if (product->minPrice < 0 || newPrice < product->minPrice) {
            // Atualiza o preço
            product->minPrice = newPrice;

            // Liberta loja anterior, se existir
            if (product->minPriceStore) {
                free(product->minPriceStore);
            }

            // Guarda nova loja
            product->minPriceStore = strdup(store);
        }
    }
}

// Mostra os dados do produto no ecrã
void printProduct(Product product) {
    if (product) {
        printf("Nome: %s\n", product->name);
        printf("Tipo: %s\n", product->type);

        // Verifica se há preço e loja definidos
        if (product->minPrice >= 0 && product->minPriceStore != NULL) {
            printf("Preco minimo: %.2f € (%s)\n", product->minPrice, product->minPriceStore);
        } else {
            printf("Preco minimo: (nao definido)\n");
        }

        printf("----------------------------\n");
    }
}

// Pesquisa produtos cujo nome contenha uma string
int searchProducts(Product* products, int size, const char* searchString, int* foundIndices, int maxResults) {
    int foundCount = 0;

    // Percorre todos os produtos
    for (int i = 0; i < size && foundCount < maxResults; i++) {
        const char* name = getProductName(products[i]);

        // Se o nome contém a string de pesquisa
        if (name && strstr(name, searchString)) {
            foundIndices[foundCount++] = i;
        }
    }

    return foundCount;
}

/*
// (Função comentada) Pesquisa e mostra produtos por tipo
int printProductsByType(Product* products, int size, const char* searchString, int* foundIndices) {
    int foundCount = 0;
    int result = 0;

    // Percorre todos os produtos
    for (int i = 0; i < size && foundCount < MAX_SEARCH_RESULTS; i++) {
        const char* type = getProductType(products[i]);
        if (type && strstr(type, searchString)) {
            foundIndices[foundCount++] = i;
        }
    }

    // Mostra os resultados
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
*/
