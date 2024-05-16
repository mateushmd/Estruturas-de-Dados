#include <stdio.h>
#include <stdlib.h>

#define tipo_item int

typedef struct Item
{
    tipo_item valor;
    struct Item *anterior;
} Item;

typedef struct Pilha
{
    Item *topo;
} Pilha;

void prompt()
{
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Imprimir a pilha\n");
    printf("0. Sair\n");
}

int adicionarItem(tipo_item val, Pilha *pilha)
{
    Item *item = (Item *)malloc(sizeof(struct Item));

    if (item == NULL)
        return 0;

    item->valor = val;

    Item *topo = pilha->topo;

    item->anterior = topo;

    pilha->topo = item;

    return 1;
}

tipo_item removerItem(Pilha *pilha)
{
    Item *topo = pilha->topo;

    if (topo == NULL)
        return -1;

    pilha->topo = topo->anterior;

    tipo_item valor = topo->valor;

    free(topo);

    return valor;
}

void imprimirPilha(Pilha *pilha)
{
    Item *item = pilha->topo;
    int i = 0;

    while (item != NULL)
    {
        printf("%d. %d\n", ++i, item->valor);
        item = item->anterior;
    }
}

int main()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));

    if (pilha == NULL)
    {
        printf("Não foi possível alocar memória para a pilha\n");
        return 1;
    }

    pilha->topo = NULL;

    int comando;

    prompt();

    do
    {
        scanf("%d", &comando);

        switch (comando)
        {
        case 1:
            printf("Valor: ");
            tipo_item val;
            scanf("%d", &val); // Mudar conforme o tipo do item
            if (!adicionarItem(val, pilha))
                printf("Não foi possível adicionar um novo item à pilha\n");
            break;
        case 2:
            tipo_item valorItemRemovido = removerItem(pilha);
            if (valorItemRemovido == -1)
                printf("A pilha já está vazia\n");
            else
                printf("Valor do item removido: %d\n", valorItemRemovido); // Mudar conforme o tipo do item
            break;
        case 3:
            imprimirPilha(pilha);
            break;
        case 0:
            break;
        default:
            printf("Insira uma entrada válida\n");
            prompt();
        }
    } while (comando != 0);

    while (pilha->topo != NULL)
    {
        removerItem(pilha);
    }

    free(pilha);

    return 0;
}