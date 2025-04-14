#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "product.h"

typedef struct productItem* ProductItem;
typedef struct productList* ProductList;

ProductList createProductList(const char* name, int capacity);

// Liberta toda a memória associada à lista
void destroyProductList(ProductList productList);

/* === Acesso e modificação ao nome da lista === */

// Devolve o nome da lista de compras
const char* getProductListName(ProductList productList);

// Altera o nome da lista de compras
void setProductListName(ProductList productList, const char* newName);

/* === Gestão de produtos na lista === */

// Adiciona um produto à lista
int addProductToList(ProductList productList, Product product, int quantity, int purchased);

// Remove um produto da lista (por ponteiro)
int removeProductFromList(ProductList productList, Product product);

// Remove um produto da lista (por nome)
int removeProductItemFromList(ProductList productList, const char* productName);
int removeProductFromListByName(ProductList productList, const char* productName);

/* === Estado de compra dos produtos === */

// Marca um produto como comprado, atualizando o preço e loja
int markProductAsPurchased(ProductList productList, const char* productName, float price, const char* store);

// Desmarca todos os produtos da lista como comprados
int unmarkAllProductsAsPurchased(ProductList productList);

// Desmarca um produto específico como comprado
int unmarkProductAsPurchased(ProductList productList, const char* productName);

// Conta o número de produtos por comprar na lista
int countPendingProducts(ProductList productList);

/* === Pesquisa de produtos === */

// Pesquisa produtos pelo nome na lista
int searchProductsInList(ProductList productList, const char* searchTerm, int* foundIndices);

/* === Impressão === */

// Imprime todos os detalhes de uma lista de compras
int printProductList(ProductList productList);

#endif
