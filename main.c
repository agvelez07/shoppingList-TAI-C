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
    // Lê até "size - 1" caracteres do teclado
    if (fgets(buffer, size, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline
    }
}

int mainMenu() {
    int opcao;
    printf("\n=========== MENU PRINCIPAL ===========\n");
    printf("1 - Gerir produtos\n");
    printf("2 - Gerir listas de compras\n");
    printf("0 - Sair\n");
    printf("Escolha uma ocçao: ");
    scanf("%d", &opcao);
    return opcao;
}

void addItemToList(ProductList l)
{
    char productName[100];
    int result = 0;

     printf("=========== Adicionar Produto a Lista ===========\n");

    // Verifica se a lista existe
    if (!l) {
        printf("Lista nao encontrada na base de dados!\n");
    }
    else {
        // Pede o nome do produto
        printf("Nome do produto a adicionar: ");
        getchar(); // Limpa o ENTER anterior
        readLine(productName, sizeof(productName));

        // Procura o produto na base de dados
        Product p = getProduct(productName);
        if (!p) {
            printf("Produto nao encontrado na base de dados!\n");
        }
        else {
            int quantity;

            // Pede a quantidade
            printf("Quantidade a adicionar: ");
            scanf("%d", &quantity);

            // Tenta adicionar o produto à lista
            result = addProductToList(l, p, quantity);

            // Mostra o resultado da operação
            switch (result) {
                case 1:
                    printf("Produto adicionado com sucesso!\n");
                    break;
                case -1:
                    printf("Erro: argumentos inválidos.\n");
                    break;
                case -2:
                    printf("Erro: a lista já atingiu a sua capacidade máxima.\n");
                    break;
                case -3:
                    printf("Erro: falha na alocação de memória.\n");
                    break;
                default:
                    printf("Erro desconhecido.\n");
            }
        }
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER Tecla para continuar...");
    getchar(); getchar();
}

void removeItemFromList(ProductList l) {
    char productName[100];

     printf("=========== Remover Produto da Lista ===========\n");

    // Verifica se a lista existe
    if (!l) {
        printf("Lista nao encontrada na base de dados!\n");
    } else {
        // Pede o nome do produto a remover
        printf("Nome do produto a remover da lista: ");
        readLine(productName, sizeof(productName));

        // Tenta remover o produto da lista
        if (removeProductItemFromList(l, productName)) {
            printf("Produto removido com sucesso!\n");
        } else {
            printf("Produto nao encontrado na lista.\n");
        }
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER Tecla para continuar...");
    getchar();
    getchar();
}

void markItemAsPurchased(ProductList l) {
    char productName[100], store[100];
    float price;

     printf("=========== Marcar Produto como Comprado ===========\n");

    // Verifica se a lista existe
    if (!l) {
        printf("Lista nao encontrada na base de dados!\n");
    } else {
        // Pede o nome do produto
        printf("Nome do produto a marcar como comprado: ");
        readLine(productName, sizeof(productName));

        // Pede o preço pago pelo produto
        printf("Preco pago: ");
        scanf("%f", &price);
        getchar(); // Limpa o ENTER do scanf

        // Pede o nome da loja onde o produto foi comprado
        printf("Loja: ");
        readLine(store, sizeof(store));

        // Tenta marcar o produto como comprado
        if (markProductAsPurchased(l, productName, price, store)) {
            printf("Produto marcado como comprado.\n");
        } else {
            printf("Produto nao encontrado na lista.\n");
        }
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER Tecla para continuar...");
    getchar();
}

void unmarkAllPurchasesFromList(ProductList l) {
    // Verifica se a lista existe
    if (!l) {
        printf("Lista nao encontrada na base de dados!\n");
    } else {
        // Desmarca todos os produtos como comprados
        unmarkAllProductsAsPurchased(l);
        printf("Todos os produtos foram desmarcados como comprados.\n");
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER Tecla para continuar...");
    getchar();
}

void viewListItems(ProductList l) {
    printf("=========== Mostrar Lista de Produtos ===========\n");

    // Verifica se a lista existe
    if (!l) {
        printf("Lista nao encontrada na base de dados!\n");
    } else {
        // Mostra os produtos da lista
        printProductList(l);
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER Tecla para continuar...");
    getchar();
}

void removeItemByObject(ProductList l) {
    char productName[100];

    printf("=========== Remover Produto da Lista (por Objeto) ===========\n");

    // Verifica se a lista existe
    if (!l) {
        printf("Lista nao encontrada.\n");
        return;
    }

    // Pede o nome do produto
    printf("Nome do Produto: ");
    readLine(productName, sizeof(productName));

    // Procura o produto na base de dados
    Product product = getProduct(productName);

    // Verifica se o produto existe
    if (!product) {
        printf("Produto nao encontrado.\n");
        return;
    }

    // Tenta remover o produto da lista
    if (removeProductFromList(l, product)) {
        printf("Produto removido da lista com sucesso!\n");
    } else {
        printf("Erro ao remover o produto da lista.\n");
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER para continuar...");
    getchar();
}

void unmarkProduct(ProductList l) {
    char productName[100];
    
    printf("=========== Desmarcar Produto como Comprado ===========\n");

    // Verifica se a lista existe
    if (!l) {
        printf("Lista nao encontrada.\n");
        return;
    }

    // Pede o nome do produto
    printf("Nome do Produto: ");
    readLine(productName, sizeof(productName));

    // Tenta desmarcar o produto
    if (unmarkProductAsPurchased(l, productName)) {
        printf("Produto foi desmarcado como comprado com sucesso.\n");
    } else {
        printf("Erro ao desmarcar o produto.\n");
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER para continuar...");
    getchar();
    getchar();
}

void manageListProducts() {
    char listName[100];

    // Pede o nome da lista a gerir
    printf("\nQual o nome da lista que deseja gerir? ");
    getchar(); // Limpa o ENTER anterior
    readLine(listName, sizeof(listName));

    // Procura a lista pelo nome
    ProductList list = getProductListByName(listName);

    // Verifica se a lista foi encontrada
    if (!list) {
        printf("\nLista nao encontrada!\n");
        printf("Pressione ENTER para continuar...");
        getchar();
    }
    else {
        int option;
        do {
            // Limpa o ecrã (no Windows)
            system("cls");

            // Mostra o menu de gestão de produtos
            printf("\n=========== Gestao de Produtos da Lista: %s ===========\n", getProductListName(list));
            printf("1 - Adicionar produto a lista\n");
            printf("2 - Remover produto da lista (por nome)\n");
            printf("3 - Marcar produto como comprado\n");
            printf("4 - Desmarcar todos os produtos\n");
            printf("5 - Desmarcar um produto como comprado\n");
            printf("6 - Remover produto da lista\n");
            printf("8 - Listar produtos da lista\n");
            printf("0 - Voltar\n");

            // Lê a opção do utilizador
            printf("\nEscolha uma opcao: ");
            scanf("%d", &option);

            // Executa a ação correspondente
            switch (option) {
                case 0:
                    break;
                case 1:
                    addItemToList(list);
                    break;
                case 2:
                    removeItemFromList(list);
                    break;
                case 3:
                    markItemAsPurchased(list);
                    break;
                case 4:
                    unmarkAllPurchasesFromList(list);
                    break;
                case 5:
                    unmarkProduct(list);
                    break;
                case 6:
                    removeItemByObject(list);
                    break;
                case 8:
                    viewListItems(list);
                    break;
                default:
                    // Em caso de opções inválidas
                    printf("Opcao inválida!\n");
                    getchar();
                    getchar();
            }
        } while (option != 0);
    }
}

void addNewList() {
    char listName[100];
    ProductList l = NULL;
    int capacity;

    // Verifica se há espaço para mais listas
    if (!isProductListDBFull()) {
        // Pede o nome da nova lista
        printf("\nIndique o nome da lista: ");
        getchar(); // Limpa o ENTER anterior
        readLine(listName, sizeof(listName));

        // Pede a capacidade da lista
        printf("Indique a capacidade da lista: ");
        scanf("%d", &capacity);

        // Cria e insere a nova lista
        l = createProductList(listName, capacity);
        insertProductList(l);
    } else {
        // Informa que não há mais espaço
        printf("Memória de Listas cheia!\n");
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER para continuar...");
    getchar();
    getchar();
}

void deleteList() {
    char listName[100];

    // Pede o nome da lista a apagar
    printf("\nQual o nome da lista que quer apagar? ");
    getchar(); // Limpa o ENTER anterior
    readLine(listName, sizeof(listName));

    // Tenta remover a lista pelo nome
    if (removeProductListByName(listName) == 1) {
        printf("\nLista removida com sucesso!");
    } else {
        printf("\nErro ao eliminar lista! Verifique o nome.");
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER para continuar...");
    getchar();
    //getchar();
}

void renameList() {
    char oldName[100], newName[100];

    // Pede o nome atual da lista
    printf("\nQual o nome da lista que quer alterar? ");
    getchar(); // Limpa o ENTER anterior
    readLine(oldName, sizeof(oldName));

    // Procura a lista pelo nome
    ProductList list = getProductListByName(oldName);

    // Verifica se a lista existe
    if (list) {
        // Pede o novo nome
        printf("Novo nome: ");
        readLine(newName, sizeof(newName));

        // Altera o nome da lista
        setProductListName(list, newName);
        printf("\nNome da lista alterado com sucesso!\n");
    } else {
        // Lista não encontrada
        printf("\nLista nao encontrada!\n");
    }

    // Espera que o utilizador carregue ENTER
    printf("\nPressione ENTER Tecla para continuar...");
    getchar();
    getchar();
}

void displayProductList() {
    char listName[100];

    // Pede o nome da lista a mostrar
    printf("\nPor favor, indique o nome da lista: ");
    getchar(); // Limpa o ENTER anterior
    readLine(listName, sizeof(listName));

    // Procura a lista pelo nome
    ProductList list = getProductListByName(listName);

    // Verifica se a lista existe
    if (list) {
        // Mostra os produtos da lista
        printProductList(list);
    } else {
        // Lista não encontrada
        printf("\nLista nao encontrada!\n");
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER para continuar...");
    getchar();
    getchar();
}

void searchListByName() {
    char search[100];

    
    printf("\n=========== Pesquisar Listas por Nome ===========\n");

    // Pede parte do nome da lista
    printf("Nome (parcial): ");
    getchar(); // Limpa o ENTER anterior
    readLine(search, sizeof(search));

    // Procura listas que contenham o texto inserido
    int foundIndices[MAX_SEARCH_RESULTS];
    int found = searchProductLists(search, foundIndices);

    // Verifica se foram encontradas listas
    if (found == 0) {
        printf("Nenhuma lista encontrada.\n");
    } else {
        // Permite selecionar uma das listas encontradas
        int index = selectProductListFromResults(foundIndices, found);

        if (index >= 0) {
            // Mostra a lista selecionada
            ProductList selectedList = getProductList(index);
            printf("\nLista selecionada:\n");
            printProductList(selectedList);
        } else {
            // Seleção inválida
            printf("Seleçao inválida.\n");
        }
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER Tecla para continuar...");
    getchar();
}

void viewAllLists() {
    
    printf("\n=========== Lista de Todos os Produtos ===========\n");

    // Mostra todas as listas existentes
    printAllProductLists();

    // Espera que o utilizador carregue ENTER
    printf("\nPressione ENTER Tecla para continuar");
    getchar();
    getchar();
}

void listMenu() {
    int option;

    do {
        // Limpa o ecrã (Windows)
        system("cls");

        printf("\n=========== Gestao de Listas de Compras ===========\n");
        printf("1 - Criar nova lista\n");
        printf("2 - Apagar lista\n");
        printf("3 - Alterar nome da lista\n");
        printf("4 - Mostrar Lista\n");
        printf("5 - Mostrar todas as listas\n");
        printf("6 - Gerir produtos de uma lista\n");
        printf("7 - Pesquisar lista por nome (parcial)\n");
        printf("0 - Voltar\n");
        printf("\nEscolha uma opcao: ");

        // Lê a opção do utilizador
        scanf("%d", &option);

        // Executa a ação correspondente
        switch (option) {
            case 0:
                break;
            case 1:
                addNewList();
                break;
            case 2:
                deleteList();
                break;
            case 3:
                renameList();
                break;
            case 4:
                displayProductList();
                break;
            case 5:
                viewAllLists();
                break;
            case 6:
                manageListProducts();
                break;
            case 7:
                searchListByName();
                break;
            default:
                // Opção inválida
                printf("\nOpcao errada\n");
        }

    } while(option != 0);
}

void addNewProduct() {
    char name[100], type[100];
    Product product = 0;
    int insertResult = 0;
    int dbFull = 0;
    int created = 0;

    
    printf("\n=========== Adicionar Produto ===========\n");

    // Pede o nome do produto
    printf("Nome do produto: ");
    getchar(); // Limpa o ENTER anterior
    readLine(name, sizeof(name));

    // Pede o tipo do produto
    printf("Tipo do produto: ");
    readLine(type, sizeof(type));

    // Verifica se a base de dados está cheia
    dbFull = isProductDBFull();
    if (!dbFull) {
        // Cria o produto
        product = createProduct(name, type);
        if (product != 0) {
            created = 1;

            // Insere o produto na base de dados
            insertResult = insertProduct(product);
        }
    }

    // Mostra o resultado da operação
    if (dbFull) {
        printf("Erro: memória de produtos cheia!\n");
    } else if (!created) {
        printf("Erro ao criar o produto. Verifique os dados ou a memória.\n");
    } else if (insertResult) {
        printf("Produto inserido com sucesso!\n");
    } else {
        // Liberta memória se falhar a inserção
        destroyProduct(product);
        printf("Erro ao inserir produto na base de dados.\n");
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione qualquer tecla para continuar...");
    getchar();
}

void deleteProduct() {
    char name[100];

    
    printf("\n=========== Remover Produto ===========\n");

    // Pede o nome do produto a remover
    printf("Nome do produto a remover: ");
    getchar(); // Limpa o ENTER anterior
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove o '\n' do fim

    // Tenta remover o produto da base de dados
    if (removeProductByName(name)) {
        printf("Produto removido com sucesso!\n");
    } else {
        printf("Produto nao encontrado!\n");
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER para continuar...");
    getchar();
    getchar();
}

void renameProduct() {
    char currentName[100], newName[100];

    
    printf("\n=========== Alterar Nome do Produto ===========\n");

    // Pede o nome atual do produto
    printf("Nome atual do produto: ");
    getchar(); // Limpa o ENTER anterior
    fgets(currentName, sizeof(currentName), stdin);
    currentName[strcspn(currentName, "\n")] = '\0'; // Remove o '\n'

    // Procura o produto na base de dados
    Product product = getProduct(currentName);

    // Verifica se o produto existe
    if (product) {
        // Pede o novo nome
        printf("Novo nome: ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = '\0'; // Remove o '\n'

        // Altera o nome do produto
        setProductName(product, newName);
        printf("Nome alterado com sucesso!\n");
    } else {
        printf("Produto nao encontrado!\n");
    }

    // Espera que o utilizador carregue ENTER
    printf("Pressione ENTER para continuar...");
    getchar();
    getchar();
}

void viewProduct() {
    // Pede o nome do produto
    printf("Por favor, indique o nome do Produto: ");
    getchar(); // Limpa o ENTER anterior
    readLine(buffer, sizeof(buffer));

    // Procura o produto na base de dados
    Product p = getProduct(buffer);

    // Verifica se o produto existe
    if (p) {
        // Mostra os dados do produto
        printProduct(p);
    } else {
        printf("\nProduto nao encontrado!\n");
    }

    // Espera que o utilizador carregue ENTER
    printf("\nPressione ENTER Tecla para continuar");
    getchar();
    getchar();
}

void viewAllProducts() {
    
    printf("\n=========== Lista de Todos os Produtos ===========\n");

    // Mostra todos os produtos da base de dados
    printAllProducts();

    // Espera que o utilizador carregue ENTER
    printf("\nPressione ENTER Tecla para continuar");
    getchar();
    getchar();
}

void searchProductByType() {
    char type[100];
    int foundIndices[MAX_SEARCH_RESULTS];

    
    printf("\n=========== Pesquisar Produtos por Tipo ===========\n");

    // Pede o tipo de produto a pesquisar
    printf("Tipo: ");
    getchar(); // Limpa o ENTER anterior
    readLine(type, sizeof(type));

    // Mostra os produtos encontrados com esse tipo
    printProductsByType(type, foundIndices, MAX_SEARCH_RESULTS);

    // Espera que o utilizador carregue ENTER
    printf("\nPressione ENTER Tecla para continuar");
    getchar();
    getchar();
}

void searchProductByName() {
    int foundIndices[MAX_SEARCH_RESULTS];

    
    printf("\n=========== Pesquisar Produto por Nome ===========\n");

    // Pede parte do nome do produto
    printf("Nome (parcial): ");
    getchar(); // Limpa o ENTER anterior
    readLine(buffer, sizeof(buffer));
    printf("\n");

    // Obtém todos os produtos da base de dados
    Product* allProducts = getAllProducts();

    // Procura produtos que contenham o nome indicado
    int count = getProductsByName(buffer, foundIndices, MAX_SEARCH_RESULTS);

    // Mostra os resultados da pesquisa
    if (count == 0) {
        printf("Nenhum produto encontrado.\n");
    } else {
        for (int i = 0; i < count; i++) {
            printProduct(allProducts[foundIndices[i]]);
        }
    }

    // Espera que o utilizador carregue ENTER
    printf("\nPressione ENTER Tecla para continuar");
    getchar();
    getchar();
}

void productMenu() {
    int option;

    do {
        // Limpa o ecrã (Windows)
        system("cls");

        printf("\n=========== Gestao de Produtos ===========\n");
        printf("1 - Adicionar novo produto\n");
        printf("2 - Remover produto\n");
        printf("3 - Alterar nome do produto\n");
        printf("4 - Mostrar um produto\n");
        printf("5 - Mostrar todos os produtos\n");
        printf("6 - Pesquisar produtos por nome (parcial)\n");
        printf("7 - Pesquisar produtos por tipo (parcial)\n");
        printf("0 - Voltar\n");

        // Lê a opção escolhida
        printf("\nEscolha uma opcao: ");
        scanf("%d", &option);

        // Executa a opção correspondente
        switch (option) {
            case 1:
                addNewProduct();
                break;
            case 2:
                deleteProduct();
                break;
            case 3:
                renameProduct();
                break;
            case 4:
                viewProduct();
                break;
            case 5:
                viewAllProducts();
                break;
            case 6:
                searchProductByName();
                break;
            case 7:
                searchProductByType();
                break;
            case 0:
                break;
            default:
                // Opção inválida
                printf("Opcao inválida!\n");
                getchar();
        }
    } while (option != 0);
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    int option, nProductLists, nProducts;

    // Pede o número máximo de listas
    printf("Indique o numero de Listas: ");
    scanf("%i", &nProductLists);

    // Pede o número máximo de produtos
    printf("\nIndique o numero de Produtos: ");
    scanf("%i", &nProducts);

    // Inicializa a base de dados de listas e produtos
    createProductListDB(nProductLists);
    createProductDB(nProducts);

    // Loop principal do programa
    do {
        system("cls");

        // Mostra o menu principal e lê a opção
        option = mainMenu();

        // Executa a opção escolhida
        switch (option) {
            case 0:
                // Sai do programa
                printf("Obrigado por utilizar este programa!");
                printf("\nPressione ENTER Tecla para continuar...");
                getchar(); getchar();
                break;
            case 1:
                // Vai para o menu de produtos
                productMenu();
                break;
            case 2:
                // Vai para o menu de listas
                listMenu();
                break;
            default:
                // Opção inválida
                printf("\nOpcao errada\n");
        }

    } while (option != 0);

    // Liberta a memória das listas e produtos
    releaseProductLists();
    releaseProducts();

    return 0;
}
