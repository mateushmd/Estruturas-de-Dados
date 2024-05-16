#include <stdio.h>
#include <stdlib.h>

#define tipo_item int

#define DISTANCIA 10

typedef struct No
{
    tipo_item valor;
    struct No *esquerda;
    struct No *direita;
} No;

No *novoNo(int valor)
{
    No *no = (No *)malloc(sizeof(No));

    if (no == NULL)
        return NULL;

    no->valor = valor;

    no->esquerda = NULL;
    no->direita = NULL;

    return no;
}

// Remove um nó e todos os seus filhos
int removerRamificacao(No *no)
{
    if (no == NULL)
        return 0;

    removerRamificacao(no->esquerda);
    removerRamificacao(no->direita);

    free(no);
}

No *procurarSuperNo(No *raiz, No *no)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->esquerda == no || raiz->direita == no)
        return raiz;

    No *busca;

    busca = procurarSuperNo(raiz->esquerda, no);

    if (busca != NULL)
        return busca;

    busca = procurarSuperNo(raiz->direita, no);

    if (busca != NULL)
        return busca;

    return NULL;
}

int removerNo(No *no, No *raiz)
{
    if (no == NULL)
        return 0;

    if (no->esquerda == NULL && no->direita == NULL)
    {
        free(no);
        return 1;
    }

    No *subNoPreservado = no->esquerda != NULL ? no->esquerda : no->direita;

    int lado = no->esquerda != NULL ? 0 : 1;

    if (no->esquerda != NULL && no->direita != NULL)
    {
        removerRamificacao(no->direita);
        no->direita = NULL;
    }

    No *superNo = procurarSuperNo(raiz, no);

    return 1;
}

void imprimirArvore(No *raiz, int espaco)
{
    if (raiz == NULL)
        return;

    espaco += DISTANCIA;

    imprimirArvore(raiz->esquerda, espaco);

    printf("\n");

    for (int i = DISTANCIA; i < espaco; i++)
    {
        printf(" ");
    }

    printf("%d\n", raiz->valor);

    imprimirArvore(raiz->direita, espaco);
}

int main()
{
    No *raiz = (No *)malloc(sizeof(No));

    if (raiz == NULL)
    {
        printf("Não foi possível alocar memória para a árvore");
        return 1;
    }

    raiz->valor = 0;

    raiz->esquerda = novoNo(1);
    raiz->direita = novoNo(2);

    raiz->esquerda->esquerda = novoNo(3);
    raiz->esquerda->direita = novoNo(4);

    raiz->direita->esquerda = novoNo(5);
    raiz->direita->direita = novoNo(6);

    imprimirArvore(raiz, 10);
}