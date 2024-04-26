# Pilha (Stack)

## O que é uma pilha?

A pilha é uma estrutura de dados de tipo LIFO (last in, first out), ou seja, o último elemento que entra é o primeiro que sai. Uma boa analogia é uma pilha de pratos.

Supondo que você esteja lavando alguns pratos. Conforme você termina de enxaguar, você os deixa empilhados em um canto para secar depois. O último prato que você enxaguar vai ser o a ser secado, por estar no topo da pilha, e o primeiro a ser enxaguado vai ser o último a ser secado, por estar na base da pilha.

Vamos dar um exemplo mais visual:

5, 3, 6, 8, 7, 1, 2, 9, 4

Supondo que você empilhou esses números, começando no 5 e terminando no 4. Como ficaria sua pilha?

| Posição | Item |
|---------|------|
| 9º      | 4 (Topo)|
| 8º      | 9    |
| 7º      | 2    |
| 6º      | 1    |
| 5º      | 7    |
| 4º      | 8    |
| 3º      | 6    |
| 2º      | 3    |
| 1º      | 5 (Base)|

Dessa forma, o primeiro número a sair da pilha é o 4, e o último é o 5.

## Como implementar uma pilha?

Para implementar uma pilha, preciamos de, principalmente, 2 itens.

### 1. Uma estrutura para um único item

```c
typedef struct Item
{
    tipo_qualquer valor;
    struct Item *proximo;
} Item;
```

As `structs` são uma ótima forma de criar uma estrutura que representa um único item da pilha. A ideia é que o item armazene o seu próprio valor (definido pelo desenvolvedor ou usuário), e uma referência do próximo item por meio de um ponteiro. É como se cada item apontasse para o item logo abaixo de sua posição, ficando dessa forma:

**4 &rarr; 9 &rarr; 2 &rarr; 1 &rarr; 7 &rarr; 8 &rarr; 6 &rarr; 3 &rarr; 5**

### 2. Uma referência para o primeiro item

```c
Item *topo;
```
Para não perder o endereço da pilha completa, devemos ter um ponteiro que sempre aponte para o topo, uma vez que **só podemos avançar** na pilha. Para isso, precisamos de um ponteiro que sempre aponte para o topo.

### 3. Funções da pilha

Agora que já temos tudo que precisamos para formar uma pilha, devemos criar as funções que darão os comportamentos de uma pilha à nossa estrutura, que são:

- Adicionar um item sempre no topo
- Remover sempre o item do topo, e definir o novo topo da pilha após a remoção

#### Adidionando itens

Para adicionar um item, precisamos de duas regras:

1. O topo da pilha deve ser o novo item
2. O novo item deve apontar para o antigo topo

```c
void adicionarItem(tipo_qualquer valor, Item *topo)
{
    //Alocando memória para o novo item
    Item *novoItem = (Item *)malloc(sizeof(Item)); 

    //Ponteiro auxiliar para não perder a referência do antigo topo
    Item *antigoTopo = topo;

    //O ponteiro topo agora aponta para o novo item
    topo = novoItem;

    //O item logo abaixo do novo item é o antigo topo
    novoItem->proximo = antigoTopo;
}
```

Com essa função, o topo da pilha sempre será o item novo, e o antigo topo estará logo abaixo dele.

#### Removendo itens

Para remover um item, precisamos agora de apenas uma regra:

1. O topo da pilha deve ser o item logo abaixo do topo (o 2º item da pilha)

```c
tipo_qualquer removerItem(Item *topo)
{
    //Guardando o valor do item a ser removido
    tipo_qualquer valorAntigoTopo = topo->valor;

    //O topo agora é o item logo abaixo do antigo topo, o 2º item
    topo = topo->proximo;

    return valorAntigoTopo;
}
```

Nessa função, atualizamos devidamente o topo após a remoção, e ainda retornamos o valor do item removido. Note que **retornar o valor do item removido não é obrigatório**.

#### Extra: imprimindo a pilha

Para podermos ver a pilha funcionando, podemos imprimi-la por completo para ver onde os novos itens estão entrando, e qual antigo item está saindo.

```c
void imprimirPilha(Item *topo)
{
    //Sempre utilizando um ponteiro auxiliar para não perder a referência do topo
    Item *itemAtual = topo;

    //Variável para mostrar a posição do item na pilha
    int i = 1;

    //Se o último item imprimido foi o item da base, itemAtual vira null e o laço se encerra
    while(itemAtual != NULL)
    {
        //Imprimindo a posiação, e o valor do item na posição
        printf("%d. %d\n", i, itemAtual->valor);

        //Após impresso o item da posição atual, descemos para o próximo item
        itemAtual = itemAtual->proximo;
        
        //Incrementando a posição
        i++;
    }
}
```

Agora, podemos ver na prática como uma pilha se comporta. Esse algoritmo funciona pois sabemos que o primeiro item a ser inserido na pilha (e consequentemente o último), não possui nenhum item abaixo dele para apontar. 