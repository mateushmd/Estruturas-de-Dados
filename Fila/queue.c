#include <stdio.h>
#include <stdlib.h>

#define tipo_item int

typedef struct Item
{
    tipo_item valor;
    struct Item *proximo;
} Item;

typedef struct Fila
{
    Item *primeiro;
} Fila;

void prompt()
{
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Imprimir o primeiro item\n");
    printf("4. Imprimir a fila\n");
    printf("0. Sair\n");
}

int adicionarItem(tipo_item valor, Fila *fila)
{
    Item *novoItem = (Item *)malloc(sizeof(Item));

    if (novoItem == NULL)
        return 0;

    novoItem->valor = valor;
    novoItem->proximo = NULL;

    Item *item = fila->primeiro;

    if (item == NULL)
    {
        fila->primeiro = novoItem;
        return 1;
    }

    while (item->proximo != NULL)
    {
        item = item->proximo;
    }

    item->proximo = novoItem;

    return 1;
}

int removerItem(Fila *fila)
{
    Item *primeiro = fila->primeiro;

    if (primeiro == NULL)
        return 0;

    fila->primeiro = primeiro->proximo;

    free(primeiro);

    return 1;
}

int imprimirPrimeiro(Fila *fila)
{
    Item *primeiro = fila->primeiro;

    if (primeiro == NULL)
        return 0;

    printf("%d\n", primeiro->valor);

    return 1;
}

void imprimirFila(Fila *fila)
{
    Item *item = fila->primeiro;

    int i = 0;

    while (item != NULL)
    {
        printf("%d. %d\n", ++i, item->valor);
        item = item->proximo;
    }
}

int main()
{
    Fila *fila = (Fila *)malloc(sizeof(Fila));

    if (fila == NULL)
    {
        printf("Não foi possível alocar memória para a fila");
        return 0;
    }

    fila->primeiro = NULL;

    int command;

    prompt();

    do
    {
        scanf("%d", &command);

        switch (command)
        {
        case 1:
            printf("Valor: ");
            int val;
            scanf("%d", &val);
            if (!adicionarItem(val, fila))
                printf("Não foi possível adicionar um novo item na fila\n");
            break;
        case 2:
            if (!removerItem(fila))
                printf("A fila já está vazia\n");
            break;
        case 3:
            if (!imprimirPrimeiro(fila))
                printf("A fila está vazia\n");
            break;
        case 4:
            imprimirFila(fila);
            break;
        case 0:
            break;
        default:
            printf("Insira uma entrada válida\n");
            prompt();
        }
    } while (command != 0);

    while (fila->primeiro != NULL)
    {
        removerItem(fila);
    }

    free(fila);

    return 0;
}