#include <stdio.h>
#include <stdlib.h>

#define tipo_item int

typedef struct Item
{
    tipo_item valor;
    struct Item *antes;
    struct Item *depois;
} Item;

typedef struct ListaEncadeada
{
    Item *primeiro;
} ListaEncadeada;

void prompt()
{
    printf("1. Adicionar um item na primeira posição\n");
    printf("2. Adicionar um item na última posição\n");
    printf("3. Adicionar um item em uma posição válida qualquer");
    printf("4. Remover o primeiro item\n");
    printf("5. Remover o último item\n");
    printf("6. Remover o item em uma posição válida qualquer\n");
    printf("7. Obter o item de uma posição válida qualquer\n");
    printf("8. Imprimir lista\n");
    printf("9. Ajuda\n");
    printf("0. Sair\n");
}

int inserirPrimeiro(tipo_item valor, ListaEncadeada *lista)
{
}

int inserirUltimo(tipo_item valor, ListaEncadeada *lista)
{
}

int inserirNa(int posicao, tipo_item valor, ListaEncadeada *lista)
{
}

int removerPrimeiro(ListaEncadeada *lista)
{
}

int removerUltimo(ListaEncadeada *lista)
{
}

int removerNa(int posicao, ListaEncadeada *lista)
{
}

int obterItemNa(int posicao, ListaEncadeada *lista)
{
}

int imprimirLista(ListaEncadeada *lista)
{
}

int main()
{
    ListaEncadeada *lista = (ListaEncadeada *)malloc(sizeof(ListaEncadeada));

    if (lista == NULL)
    {
        printf("Não foi possível alocar memória para a lista");
        return 1;
    }

    lista->primeiro = NULL;

    int comando;

    prompt();

    do
    {
        scanf("%d", &comando);

        int valor, posicao;

        switch (comando)
        {
        case 1:
            printf("Valor: ");
            scanf("%d", &valor);
            if (!inserirPrimeiro(valor, lista))
                printf("Não foi possível inserir o item na primeira posição\n");
            break;
        case 2:
            printf("Valor: ");
            scanf("%d", &valor);
            if (!inserirUltimo(valor, lista))
                printf("Não foi possível inserir o item na última posição\n");
            break;
        case 3:
            printf("Selecionar posição: ");
            scanf("%d", &posicao);
            printf("Valor: ");
            scanf("%d", &valor);
            if (!inserirNa(posicao, valor, lista))
                printf("Não foi possível inserir o item na posição %d\n", posicao);
            break;
        case 0:
            break;
        default:
            printf("Insira uma entrada válida\n");
            prompt();
        }
    } while (comando != 0);

    return 0;
}