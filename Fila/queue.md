# Fila (Queue)

A fila é uma estrutura de dados de tipo FIFO (first in, first out), ou seja, o primeiro elemento que entra é o primeiro que sai. Aqui não tem segredo, é exatamente a mesma analogia das filas reais

Mesmo assim, vamos dar um exemplo visual:

Vamos enfileirar os seguintes valores, seguindo a ordem que aparecem:

2, 8, 7, 4, 1, 3, 9, 5, 6

```
Inserções

 Início     vazio
   1º       2
   2º       2   8
   3º       2   8   7
   4º       2   8   7   4
   5º       2   8   7   4   1
   6º       2   8   7   4   1   3
   7º       2   8   7   4   1   3   9
   8º       2   8   7   4   1   3   9   5
   9º       2   8   7   4   1   3   9   5   6

            1º  2º  3º  4º  5º  6º  7º  8º  9º  Posição
```

O primeiro item a sair da fila é sempre o primeiro. Depois do 2, sai o 8, e depois o 7, e assim vai. Conforme adicionamos itens, o último item muda constantemente, porém o primeor é o mesmo.

## Como implementar uma fila?

Para implementar uma fila, presicamos de:

### 1. Uma estrutura para um único item

```c
typedef struct Item
{
    tipo_qualquer valor;
    struct Item *proximo;
} Item;
```

As `structs` são uma ótima forma de criar uma estrutura que representa um único item da fila. A ideia é que o item armazene o seu próprio valor (definido pelo desenvolvedor ou usuário), e uma referência do próximo item por meio de um ponteiro. É como se cada item apontasse para o item atrás dele, ficando dessa forma utilizando o nosso exemplo:

**2 &rarr; 8 &rarr; 7 &rarr; 4 &rarr; 1 &rarr; 3 &rarr; 9 &rarr; 5 &rarr; 6**

### 2. Uma referência para o primeiro item

```c
typedef struct Fila
{
    Item *primeiro
} Fila;
```

Para não perder o endereço da fila completa, devemos ter um ponteiro que sempre aponte para o primeiro item, uma vez que **só podemos regredir** na fila.

### 3. Funções da fila

Agora que já temos tudo para formar uma fila, devemos criar as funções que darão o comportamento de uma fila à nossa estrutura, que são:

- Adicionar um item sempre no final da fila
- Remover sempre o primeiro item, e definir o novo primeiro item após a remoção

#### Considerações iniciais

```c
int main()
{
    Fila *fila = (Fila*)malloc(sizeof(Fila));

    //A função maloc retorna NULL se falhar em alocar a memória
    if(fila == NULL)
    {
        printf("Não foi possível alocar memória para a fila\n");

        //Interrompendo o programa
        return 1;
    }

    fila->primeiro = NULL;
}
```

Preciamos, antes de utilizar a nossa fila, ter sua memória alocada e fazer com que o ponteiro que aponta para o primeiro item aponte para um valor **nulo**. Anular o ponteiro é muito importante para o nosso algoritmo, pois ele nos ajudará a identificar se a fila está vazia, ou se chegamos no último item.

#### Adicionando itens

Para adiciona um item, precisamos de duas regras:

1. O último item da fila deve ser o novo item
2. O antigo último item deve apontar para o novo item

```c
int adicionarItem(tipo_item valor, Fila *fila)
{
    //Alocando memória para o novo item
    Item *novoItem = (Item *)malloc(sizeof(Item));

    //Se a alocação falhar, interrompemos a função
    if (novoItem == NULL)
        return 0;

    //Definindo os valores iniciais para o novo item
    novoItem->valor = valor;
    novoItem->proximo = NULL;

    //Ponteiro auxiliar que aponta, inicialmente, para o primeiro item
    Item *item = fila->primeiro;

    //Se o primeiro item já for NULL, ou seja, se a fila estiver vazia, o primeiro item da fila é o novo item
    if (item == NULL)
    {
        fila->primeiro = novoItem;
        return 1;
    }

    //Caso contrário, fazemos um laço de repetição até achar o último item
    while (item->proximo != NULL)
    {
        item = item->proximo;
    }

    //Uma vez encontrado, o antigo último item aponta agora para o novo item, que tomou o cargo de último da fila
    item->proximo = novoItem;

    return 1;
}
```

Com essa função, o último da fila sempre será o item novo. Note que o novo último da fila sempre aponta para nulo. Isso nos ajuda a identificar o último item.

#### Removendo itens

Para remover um item, precisamos de uma regra

1. O primeiro da fila deve ser o antigo segundo da fila

```c
tipo_item removerItem(Fila *fila)
{
    Item *primeiro = fila->primeiro;

    //Se o primeiro for nulo, a fila já está vazia
    if (primeiro == NULL)
        return -1;

    //O primeiro item agora é o antigo segundo item
    fila->primeiro = primeiro->proximo;

    //Guardando o valor do item removido
    tipo_item valorAntigoPrimeiro = primeiro->valor;

    //Liberando a memória do antigo primeiro
    free(primeiro);

    return valorAntigoPrimeiro;
}
```

Com essa função, pegamos o item em segundo lugar e colocamos em primeiro, retirando o antigo primeiro item da fila, liberando a memória reservada para ele, já que não terá mais utilidade, e retornando o seu valor. Adicionamos um nível de segurança ao verificar se a fila já está vazia antes de manipular.

#### EXTRA: imprimindo a fila 

Para ver a fila funcionando, podemos imprimir por completo para ver onde os novos itens estão entrando, e qual item está saindo.

```c
void imprimirFila(Fila *fila)
{
    //Variável auxiliar para não perder a referência do primeiro item da fila
    Item *item = fila->primeiro;

    //Posição do item
    int i = 0;

    //Se o último item imprimido foi o último da fila, o próximo item será nulo e o laço se encerra
    while (item != NULL)
    {
        //Imprimindo a posição e o valor do item
        printf("%d. %d\n", ++i, item->valor);

        //Após impresso o item, vamos para o item de trás
        item = item->proximo;
    }
}
```

Agora, podemos ver na prática como uma fila se comporta.

### Utilidades da fila

- Gerenciamento de processos em sistemas operacionais: Em sistemas operacionais, as filas são usadas para ordernar a execução dos processos.

- Transmissão de dados: Em redes de computadores, as filas são usadas para gerenciar pacotes de dados para assegurar a ordem correta de envio, recebimento e processamento deles.

- Algoritmos de busca em grafos: O algoritmo de busca BFS (Breadth-First Search) utiliza uma fila para explorar os vértices de um grafo. Veja mais sobre grafos [aqui](../Grafo/graph.md). 