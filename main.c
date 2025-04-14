#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "productList.h"
#include "product.h"

char buffer[2048];

int menu() {
    int opcao;
    printf("\n\n  ** MENU DE GESTÃO DE PRODUTOS **\n");
    printf("1 - Adicionar novo produto\n");
    printf("2 - Remover produto\n");
    printf("3 - Editar stock do produto\n");
    printf("4 - Editar preço do produto\n");
    printf("5 - Listar todos os produtos\n");
    printf("0 - Sair\n");
    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

void addProductList(Product* products, int total) {
    int i;
    int serial, stock;
    float price;

    for (i = 0; i < total; i++) {
        if (products[i] == NULL) {
            printf("\nCódigo do produto: ");
            scanf(" %d", &serial);
            printf("Nome do produto: ");
            scanf(" %s", buffer);
            printf("Stock do produto: ");
            scanf("%d", &stock);
            printf("Preço do produto: ");
            scanf("%f", &price);
            products[i] = addNewProduct(serial, buffer, stock, price);
            printf("Produto adicionado com sucesso!\n");
            return;
        }
    }
    printf("Limite máximo de produtos atingido!\n");
}/*
void removeProduct(Product* products, int total) {
    char nome[100];
    printf("\nDigite o nome do produto que deseja remover: ");
    scanf(" %s", nome);

    for (int i = 0; i < total; i++) {
        if (products[i] != NULL && strcmp(products[i]->name, nome) == 0) {
            removeProduct()t(products[i]);
            products[i] = NULL;
            printf("Produto removido com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado!\n");
}
void editStock(Product* products, int total) {
    char nome[100];
    int novoStock;

    printf("\nDigite o nome do produto cujo stock deseja editar: ");
    scanf(" %s", nome);

    for (int i = 0; i < total; i++) {
        if (products[i] != NULL && strcmp(products[i]->name, nome) == 0) {
            printf("Digite o novo stock: ");
            scanf("%d", &novoStock);
            editStock(products[i], novoStock);
            printf("Stock atualizado com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado!\n");
}
void editPrice(Product* products, int total) {
    char nome[100];
    float novoPreco;

    printf("\nDigite o nome do produto cujo preço deseja editar: ");
    scanf(" %s", nome);

    for (int i = 0; i < total; i++) {
        if (products[i] != NULL && strcmp(products[i]->name, nome) == 0) {
            printf("Digite o novo preço: ");
            scanf("%f", &novoPreco);
            editPrice(products[i], novoPreco);
            printf("Preço atualizado com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado!\n");
}
void listProducts(Product* products, int total) {
    printf("\n\n** Lista de Produtos **\n");
    for (int i = 0; i < total; i++) {
        if (products[i] != NULL) {
            checkProduct(products[i]);
        }
    }
}*/
int main(void) {
    int option, maxListCount, maxProductCount, i;
    printf("Digite o número máximo de Listas: ");
    scanf("%d", &maxListCount);
    printf("Digite o número máximo de Produtos: ");
    scanf("%d", &maxProductCount);

    ProductList* productLists = (Product*)malloc( maxListCount * sizeof(Product));
    Product* products = (Product*)malloc(maxProductCount * sizeof(Product));
    if (productLists == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o array de listas!\n");
        return 1;
    }
    if (products == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o array de produtos!\n");
        return 1;
    }

    for (i = 0; i < maxListCount; i++) {
        productLists[i] = NULL;
    }
    for (i = 0; i < maxProductCount; i++) {
        products[i] = NULL;
    }

    do {
        option = menu();
        switch (option) {
            case 1:
                addProductList(productLists, maxListCount);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                printf("Encerrando o programa. Obrigado!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (option != 0);

    //liberarMemoria(products, total);
    free(productLists);
    free(products);
    return 0;
}
