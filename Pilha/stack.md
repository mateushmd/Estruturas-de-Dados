# Pilha (Stack)

## O que é uma pilha?

A pilha é uma estrutura de dados de tipo LIFO (last in, first out), ou seja, o último elemento que entra é o primeiro que sai. Uma boa analogia é uma pilha de pratos.

Supondo que você esteja lavando alguns pratos. Conforme você termina de enxaguar, você os deixa empilhados em um canto para secar depois. O último prato que você enxaguar vai ser o a ser secado, por estar no topo da pilha, e o primeiro a ser enxaguado vai ser o último a ser secado, por estar na base da pilha.

Vamos dar um exemplo mais visual:

5, 3, 6, 8, 7, 1, 2, 9, 4

Supondo que empilhamos esses números, começando no 5 e terminando no 4. Como ficaria a pilha?

```
                                        4
                                    9   9
                                2   2   2
                            1   1   1   1
                        7   7   7   7   7
                    8   8   8   8   8   8
                6   6   6   6   6   6   6
            3   3   3   3   3   3   3   3  
vazia   5   5   5   5   5   5   5   5   5

Inicio  1º  2º  3º  4º  5º  6º  7º  8º  9º <- Inserções
```
Dessa forma, depois da última inserção o primeiro número a sair da pilha é o 4, e o último é o 5. Além disso, conforme vamos adicionando itens, o topo muda constantemente, porém a base é a mesma.

## Como implementar uma pilha?

Para implementar uma pilha, preciamos de:

### 1. Uma estrutura para um único item

```c
typedef struct Item
{
    tipo_qualquer valor;
    struct Item *proximo;
} Item;
```

As `structs` são uma ótima forma de criar uma estrutura que representa um único item da pilha. A ideia é que o item armazene o seu próprio valor (definido pelo desenvolvedor ou usuário), e uma referência do próximo item por meio de um ponteiro. É como se cada item apontasse para o item logo abaixo de sua posição, ficando dessa forma utilizando nosso exemplo:

**4 &rarr; 9 &rarr; 2 &rarr; 1 &rarr; 7 &rarr; 8 &rarr; 6 &rarr; 3 &rarr; 5**

### 2. Uma referência para o item do topo

```c
typedef struct Pilha 
{
    Item *topo;
} Pilha;
```
Para não perder o endereço da pilha completa, devemos ter um ponteiro que sempre aponte para o topo, uma vez que **só podemos avançar** na pilha.

### 3. Funções da pilha

Agora que já temos tudo para formar uma pilha, devemos criar as funções que darão os comportamentos de uma pilha à nossa estrutura, que são:

- Adicionar um item sempre no topo
- Remover sempre o item do topo, e definir o novo topo da pilha após a remoção

#### Considerações iniciais

```c
int main()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));

    //A função malloc retorna NULL se falhar em alocar a memória
    if(pilha == NULL)
    {
        printf("Não foi possível alocar memória para a pilha\n");
        
        //Interrompendo o programa
        return 1;
    }

    pilha->topo = NULL;
}
```

Precisamos, antes de utilizar a nossa pilha, ter sua memória alocada e fazer com que o ponteiro que aponta para o topo aponte para um valor **nulo**. Anular o ponteiro é muito importante para o nosso algoritmo, pois ele nos ajudará a identificar o final da pilha.

#### Adidionando itens

Para adicionar um item, precisamos de duas regras:

1. O topo da pilha deve ser o novo item
2. O novo item deve apontar para o antigo topo

```c
void adicionarItem(tipo_qualquer valor, Pilha *pilha)
{
    //Alocando memória para o novo item
    Item *novoItem = (Item *)malloc(sizeof(Item)); 

    //Definindo o valor do novo item
    novoItem->valor = valor;

    //Ponteiro auxiliar para não perder a referência do antigo topo
    Item *antigoTopo = pilha->topo;

    //O ponteiro topo agora aponta para o novo item
    pilha->topo = novoItem;

    //O item logo abaixo do novo item é o antigo topo
    novoItem->proximo = antigoTopo;
}
```

Com essa função, o topo da pilha sempre será o item novo, e o antigo topo estará logo abaixo dele. Note que, se o item adicionado for o primeiro item da pilha, seu ponteiro para o próximo item será nulo, marcando assim o final da pilha.

#### Removendo itens

Para remover um item, precisamos uma regra:

1. O topo da pilha deve ser o item logo abaixo do topo

```c
tipo_qualquer removerItem(Pilha *pilha)
{
    Item topo = pilha->topo;

    //Se o topo da pilha for nulo, ela já está vazia
    if(topo == NULL)
    {
        printf("A pilha já está vazia\n");
        return NULL;
    }

    //Guardando o valor do item a ser removido
    tipo_qualquer valorAntigoTopo = topo->valor;

    //O topo agora é o item logo abaixo do antigo topo, o 2º item
    pilha->topo = topo->proximo;

    //Liberando a memória do antigo topo
    free(topo);

    return valorAntigoTopo;
}
```

Nessa função, atualizamos devidamente o topo após a remoção, e ainda retornamos o valor do item removido. Note que **retornar o valor do item removido não é obrigatório**. Liberamos a memória alocada para o item removido pois ele não será mais utilizado. Por questões de robustez, verificamos se a pilha já está vazia antes de realizar qualquer operação, e interrompemos a função caso esteja.

#### Extra: imprimindo a pilha

Para ver a pilha funcionando, podemos imprimir por completo para ver onde os novos itens estão entrando, e qual item antigo está saindo.

```c
void imprimirPilha(Item *topo)
{
    //Sempre utilizando um ponteiro auxiliar para não perder a referência do topo
    Item *itemAtual = topo;

    //Variável para mostrar a posição do item na pilha
    int i = 1;

    //Se o último item imprimido foi o item da base, itemAtual fica nulo e o laço se encerra
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

## Utilidades da pilha

- Gerenciar memória: As pilhas são muito utilizadas em linguagens de programação para gerenciar memória. Uma pilha muito importante é a call stack (pilha de chamadas de funções).

- Reversão de vetores ou strings: As pilhas facilitam a reversão de arrays ou strings. Basta empilhar os valores do primeiro ao último, e depois varrer a pilha.

- Desfazer: O `ctrl + z` é uma pilha. Nossas ações são registradas e empilhadas. Ao desfazer, estamos simplesmente voltando uma ação abaixo na pilha.