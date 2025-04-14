#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "product.h"
#include "productDB.h"
#include "productList.h"
#include "productListDB.h"

#define MAX_SEARCH_RESULTS 1000

char buffer[2048];

 void readLine(char* buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}


int mainMenu() {
    int opcao;
    printf("\n====== MENU PRINCIPAL ======\n");
    printf("1 - Gerir produtos\n");
    printf("2 - Gerir listas de compras\n");
    printf("0 - Sair\n");
    printf("Escolha uma opçao: ");
    scanf("%d", &opcao);
    return opcao;
}

void handleAddProductToList()
{   char listName[100], productName[100];
    printf("======== Adicionar Produto a Lista =======");
    printf("\nNome da Lista: ");
    readLine(listName, sizeof(listName));

    ProductList l = getProductListByName(listName);
    if (!l) {
        printf("Lista nao encontrada na base de dados!\n");
    }
    else {


        printf("\nNome do produto a adicionar: ");
        readLine(productName, sizeof(productName));

        Product p = getProduct(buffer);
        if (!p) {
            printf("Produto nao encontrado na base de dados!\n");
        } else {
            int quantity;
            printf("Quantidade a adicionar: ");
            scanf("%d", &quantity);

            if (addProductToList(l, p, quantity, 0)) {
                printf("Produto adicionado com sucesso!\n");
            } else {
                printf("Erro ao adicionar o produto.\n");
            }
        }
    }
    printf("Pressione Qualquer Tecla para continuar...");
    getchar(); getchar();
};

void handleRemoveProductFromList() {
    char listName[100], productName[100];

    printf("======== Remover Produto da Lista =======\n");

    printf("Nome da Lista: ");
    readLine(listName, sizeof(listName));

    ProductList l = getProductListByName(listName);
    if (!l) {
        printf("Lista nao encontrada na base de dados!\n");
    } else {
        printf("Nome do produto a remover da lista: ");
        readLine(productName, sizeof(productName));

        if (removeProductItemFromList(l, productName)) {
            printf("Produto removido com sucesso!\n");
        } else {
            printf("Produto nao encontrado na lista.\n");
        }
    }

    printf("Pressione Qualquer Tecla para continuar...");
    getchar(); getchar();
}


void handleMarkProductAsPurchased() {
    char listName[100], productName[100], store[100];
    float price;

    printf("======== Marcar Produto como Comprado =======\n");

    printf("Nome da Lista: ");
    getchar();
    readLine(listName, sizeof(listName));

    ProductList l = getProductListByName(listName);
    if (!l) {
        printf("Lista nao encontrada na base de dados!\n");
    } else {
        printf("Nome do produto a marcar como comprado: ");
        readLine(productName, sizeof(productName));

        printf("Preço pago: ");
        scanf("%f", &price);
        getchar();

        printf("Loja: ");
        readLine(store, sizeof(store));

        if (markProductAsPurchased(l, productName, price, store)) {
            printf("Produto marcado como comprado.\n");
        } else {
            printf("Produto nao encontrado na lista.\n");
        }
    }

    printf("Pressione Qualquer Tecla para continuar...");
    getchar(); getchar();
}

void handleUnmarkAllProducts() {
    char listName[100];

    printf("======== Desmarcar Todos os Produtos da Lista =======\n");
    printf("Nome da Lista: ");
    getchar();
    readLine(listName, sizeof(listName));

    ProductList l = getProductListByName(listName);
    if (!l) {
        printf("Lista nao encontrada na base de dados!\n");
    } else {
        unmarkAllProductsAsPurchased(l);
        printf("Todos os produtos foram desmarcados como comprados.\n");
    }

    printf("Pressione Qualquer Tecla para continuar...");
    getchar(); getchar();
}

void handlePrintProductList() {
    char listName[100];

    printf("======== Mostrar Lista de Produtos =======\n");
    printf("Nome da Lista: ");
    getchar();
    readLine(listName, sizeof(listName));

    ProductList l = getProductListByName(listName);
    if (!l) {
        printf("Lista nao encontrada na base de dados!\n");
    } else {
        printProductList(l);
    }

    printf("Pressione Qualquer Tecla para continuar...");
    getchar(); getchar();
}

void handleRemoveProductObjectFromList() {
    char listName[100], productName[100];

    printf("=== Remover Produto da Lista (por Objeto) ===\n");

    printf("Nome da Lista: ");
    getchar();
    readLine(listName, sizeof(listName));
    ProductList list = getProductListByName(listName);

    if (!list) {
        printf("Lista nao encontrada.\n");
        return;
    }

    printf("Nome do Produto: ");
    readLine(productName, sizeof(productName));
    Product product = getProduct(productName);

    if (!product) {
        printf("Produto nao encontrado.\n");
        return;
    }

    if (removeProductFromList(list, product)) {
        printf("Produto removido da lista com sucesso!\n");
    } else {
        printf("Erro ao remover o produto da lista.\n");
    }

    printf("Pressione ENTER para continuar...");
    getchar();
}

void handleRemoveProductByNameFromList() {
    char listName[100], productName[100];

    printf("=== Remover Produto da Lista (por Nome) ===\n");

    printf("Nome da Lista: ");
    getchar();
    readLine(listName, sizeof(listName));
    ProductList list = getProductListByName(listName);

    if (!list) {
        printf("Lista nao encontrada.\n");
        return;
    }

    printf("Nome do Produto: ");
    readLine(productName, sizeof(productName));

    if (removeProductFromListByName(list, productName)) {
        printf("Produto removido da lista com sucesso!\n");
    } else {
        printf("Erro ao remover o produto da lista.\n");
    }

    printf("Pressione ENTER para continuar...");
    getchar();
}

void handleUnmarkSingleProduct() {
    char listName[100], productName[100];

    printf("=== Desmarcar Produto como Comprado ===\n");

    printf("Nome da Lista: ");
    getchar();
    readLine(listName, sizeof(listName));
    ProductList list = getProductListByName(listName);

    if (!list) {
        printf("Lista nao encontrada.\n");
        return;
    }

    printf("Nome do Produto: ");
    readLine(productName, sizeof(productName));

    if (unmarkProductAsPurchased(list, productName)) {
        printf("Produto foi desmarcado como comprado com sucesso.\n");
    } else {
        printf("Erro ao desmarcar o produto.\n");
    }

    printf("Pressione ENTER para continuar...");
    getchar();
}

void manageListProducts() {
    char listName[100];

    printf("\nQual o nome da lista que deseja gerir? ");
    getchar();
    readLine(listName, sizeof(listName));

    ProductList list = getProductListByName(listName);

    if (!list) {
        printf("\nLista nao encontrada!\n");
        printf("Pressione ENTER para continuar...");
        getchar();
        return;
    }

    int option;
    do {
        system("cls");
        printf("\n===== Gestao de Produtos da Lista: %s ======\n", getProductListName(list));
        printf("1 - Adicionar produto à lista\n");
        printf("2 - Remover produto da lista (por nome)\n");
        printf("3 - Marcar produto como comprado\n");
        printf("4 - Desmarcar todos os produtos\n");
        printf("5 - Listar produtos da lista\n");
        printf("6 - Remover produto da lista (por objeto)\n");
        printf("7 - Remover produto da lista (por nome direto)\n");
        printf("8 - Desmarcar um produto como comprado\n");
        printf("0 - Voltar\n");
        printf("\nEscolha uma opçao: ");
        scanf("%d", &option);

        switch (option) {
            case 0:
                break;
            case 1:
                handleAddProductToList();
                break;
            case 2:
                handleRemoveProductFromList();
                break;
            case 3:
                handleMarkProductAsPurchased();
                break;
            case 4:
                handleUnmarkAllProducts();
                break;
            case 5:
                handlePrintProductList();
                break;
            case 6:
                handleRemoveProductObjectFromList();
                break;
            case 7:
                handleRemoveProductByNameFromList();
                break;
            case 8:
                handleUnmarkSingleProduct();
                break;
            default:
                printf("Opçao inválida!\n");
                getchar(); getchar();
        }

    } while (option != 0);
}

void addList() {
    char listName[100];
    ProductList l = NULL;
    int capacity;

    if (!isProductListDBFull()) {
        printf("\nIndique o nome da lista: ");
        getchar();
        readLine(listName, sizeof(listName));

        printf("Indique a capacidade da lista: ");
        scanf("%d", &capacity);

        l = createProductList(listName, capacity);
        insertProductList(l);
    } else {
        printf("Memória de Listas cheia!\n");
    }

    printf("Pressione ENTER para continuar...");
    getchar(); getchar();
}

void removeProductList() {
    char listName[100];
    printf("\nQual o nome da lista que quer apagar? ");
    getchar();
    readLine(listName, sizeof(listName));

    if (removeProductListByName(listName) == 1) {
        printf("\nLista removida com sucesso!");
    } else {
        printf("\nErro ao eliminar lista! Verifique o nome.");
    }

    printf("Pressione ENTER para continuar...");
    getchar();
}

void changeProductListName() {
    char oldName[100], newName[100];

    printf("\nQual o nome da lista que quer alterar? ");
    getchar();
    readLine(oldName, sizeof(oldName));

    ProductList list = getProductListByName(oldName);

    if (list) {
        printf("Novo nome: ");
        readLine(newName, sizeof(newName));

        setProductListName(list, newName);
        printf("\nNome da lista alterado com sucesso!\n");
    } else {
        printf("\nLista nao encontrada!\n");
    }

    printf("\nPressione Qualquer Tecla para continuar...");
    getchar();
}

void displayProductList() {
    char listName[100];
    printf("\nPor favor, indique o nome da lista: ");
    getchar();
    readLine(listName, sizeof(listName));

    ProductList list = getProductListByName(listName);

    if (list) {
        printProductList(list);
    } else {
        printf("\nLista nao encontrada!\n");
    }

    printf("Pressione ENTER para continuar...");
    getchar();
}

void handleSearchProductListByName() {
    char search[100];
    printf("\n=== Pesquisar Listas por Nome ===\n");

    printf("Nome (parcial): ");
    getchar();
    readLine(search, sizeof(search));

    int foundIndices[MAX_SEARCH_RESULTS];
    int found = searchProductLists(search, foundIndices);

    if (found == 0) {
        printf("Nenhuma lista encontrada.\n");
    } else {
        int index = selectProductListFromResults(foundIndices, found);
        if (index >= 0) {
            ProductList selectedList = getProductList(index);
            printf("\nLista selecionada:\n");
            printProductList(selectedList);
        } else {
            printf("Seleçao inválida.\n");
        }
    }

    printf("Pressione Qualquer Tecla para continuar...");
    getchar();
}
void handlePrintAllLists()
{
    printf("\n=== Lista de Todos os Produtos ===\n");
    printAllProductLists();
    printf("\nPressione Qualquer Tecla para continuar");
    getchar(); getchar();
}


void listMenu() {
    int option;

    do {
        system("cls");
        printf("\n===== Gestao de Listas de Compras =====\n");
        printf("1 - Criar nova lista\n");
        printf("2 - Apagar lista\n");
        printf("3 - Alterar nome da lista\n");
        printf("4 - Mostrar Lista \n");
        printf("5 - Mostrar todas as listas\n");
        printf("6 - Gerir produtos de uma lista\n");
        printf("7 - Pesquisar lista por nome (parcial)\n");
        printf("0 - Voltar\n");
        printf("\nEscolha uma opçao: ");


        scanf("%d", &option);
        switch (option) {
            case 0:
                break;
            case 1:
                addList();
                break;
            case 2:
                removeProductList();
                break;
            case 3:
                changeProductListName();
                break;
            case 4:
                displayProductList();
                break;
            case 5:
                handlePrintAllLists();
                break;
            case 6:
                manageListProducts();
                break;
            case 7:
                handleSearchProductListByName();
                break;
            default:
                printf("\nOpcao errada\n");
        }

    }while(option != 0);

    printf("Pressione Qualquer Tecla para continuar...");
    getchar();getchar();
}

void handleAddProduct() {
    char name[100], type[100];

    printf("\n=== Adicionar Produto ===\n");

    printf("Nome do produto: ");
    getchar();
    readLine(name, sizeof(name));

    printf("\n%s", name);
    printf("Tipo do produto: ");
    readLine(type, sizeof(type));

    if (isProductDBFull()) {
        printf("Erro: memória de produtos cheia!\n");
    } else {
        Product product = createProduct(name, type);
        if (insertProduct(product)) {
            printf("Produto inserido com sucesso!\n");
        } else {
            printf("Erro ao inserir produto.\n");
        }
    }

    printf("Pressione qualquer tecla para continuar...");
    getchar();
}

void handleRemoveProduct() {
    char name[100];

    printf("\n=== Remover Produto ===\n");
    printf("Nome do produto a remover: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    if (removeProductByName(name)) {
        printf("Produto removido com sucesso!\n");
    } else {
        printf("Produto nao encontrado!\n");
    }

    printf("Pressione ENTER para continuar...");
    getchar();
}

void handleRenameProduct() {
    char currentName[100], newName[100];

    printf("\n=== Alterar Nome do Produto ===\n");

    printf("Nome atual do produto: ");
    getchar();
    fgets(currentName, sizeof(currentName), stdin);
    currentName[strcspn(currentName, "\n")] = '\0';

    Product product = getProduct(currentName);
    if (product) {
        printf("Novo nome: ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = '\0';

        setProductName(product, newName);
        printf("Nome alterado com sucesso!\n");
    } else {
        printf("Produto nao encontrado!\n");
    }

    printf("Pressione ENTER para continuar...");
    getchar();
}

void displayProduct()
{
    printf("Por favor, indique o nome do Produto: ");
    getchar();
    readLine(buffer, sizeof(buffer));

    Product p = getProduct(buffer);

    if (p) {
        printProduct(p);
    } else {
        printf("\nProduto nao encontrado!\n");
    }

    printf("\nPressione Qualquer Tecla para continuar");
    getchar();
}

void handlePrintAllProducts()
{
    printf("\n=== Lista de Todos os Produtos ===\n");
    printAllProducts();
    printf("\nPressione Qualquer Tecla para continuar");
    getchar(); getchar();
}

void handleSearchProductsByType() {
    char type[100];
    int foundIndices[MAX_SEARCH_RESULTS];

    printf("\n=== Pesquisar Produtos por Tipo ===\n");
    printf("Tipo: ");
    getchar();
    readLine(type, sizeof(type));

    printProductsByType(type, foundIndices, MAX_SEARCH_RESULTS);

    printf("\nPressione Qualquer Tecla para continuar");
    getchar();
}

void handleSearchProductByName() {
    int foundIndices[MAX_SEARCH_RESULTS];

    printf("\n=== Pesquisar Produto por Nome ===\n");
    printf("Nome (parcial): ");
    getchar();
    readLine(buffer, sizeof(buffer));
    printf("\n");

    Product* allProducts = getAllProducts();
    int count = getProductsByName(buffer, foundIndices, MAX_SEARCH_RESULTS);

    if (count == 0) {
        printf("Nenhum produto encontrado.\n");
    } else {
        for (int i = 0; i < count; i++) {
            printProduct(allProducts[foundIndices[i]]);
        }
    }

    printf("\nPressione Qualquer Tecla para continuar");
    getchar();
}

void productMenu() {
    int option;

    do {
        system("cls");
        printf("\n===== Gestao de Produtos =====\n");
        printf("1 - Adicionar novo produto\n");
        printf("2 - Remover produto\n");
        printf("3 - Alterar nome do produto\n");
        printf("4 - Mostrar um produto\n");
        printf("5 - Mostrar todos os produtos\n");
        printf("6 - Pesquisar produtos por nome (parcial)\n");
        printf("7 - Pesquisar produtos por tipo (parcial)\n");
        printf("0 - Voltar\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                handleAddProduct();
                break;
            case 2:
                handleRemoveProduct();
                break;
            case 3:
                handleRenameProduct();
                break;
            case 4:
                displayProduct();
                break;
            case 5:
                handlePrintAllProducts();
                break;
            case 6:
                handleSearchProductByName();
                break;
            case 7:
                handleSearchProductsByType();
                break;
            case 0:
                break;
            default:
                printf("Opçao inválida!\n");
                getchar(); getchar();
        }
    } while (option != 0);
}

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    int option, nProductLists, nProducts, i;


    printf("Indique o numero de Listas: ");
    scanf("%i", &nProductLists);

    printf("\nIndique o numero de Produtos: ");
    scanf("%i", &nProducts);

    createProductListDB(nProductLists);
    createProductDB(nProducts);

    do {
        system("cls");
        option = mainMenu();
        switch (option) {
            case 0:
                printf("Obrigado por utilizar este programa!");
                printf("Pressione Qualquer Tecla para continuar...");
                getchar();
                break;
            case 1:
                productMenu();
                break;
            case 2:
                listMenu();
                break;
            default:
                printf("\nOpcao errada\n");
        }
    } while (option != 0);


    releaseProductLists();
    releaseProducts();
    return(0);
}
