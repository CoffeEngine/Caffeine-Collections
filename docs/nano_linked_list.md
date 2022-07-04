# nano_linked_list

Lista duplamente encadeada.

```C
typedef struct         
{
    linked_list_node(type) * pnext;
    type value
} linked_list_node(type);        

typedef struct
{
    linked_list_node(type) * first;
    linked_list_node(type) * last;
    size_t count;
} linked_list(type);
```
## <ins>linked_list_create</ins>

```C
void linked_list_create(type)(linked_list(type) * arr);
```

Recebe um ponteiro para uma lista e a inicializa.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |


### Exemplo

```C
linked_list(int) my_list;

linked_list_create(int)(&my_list);
```
## <ins>linked_list_add</ins>

```C
void linked_list_insert(type)(linked_list(type) * arr,type value);
```

Insere um valor do fim da lista.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| value    | valor a ser inserido na lista |


### Exemplo

```C
linked_list(int) my_list;

linked_list_create(int)(&my_list);

linked_list_add(int)(&my_list,-1); // my_list = [-1]
linked_list_add(int)(&my_list, 3); // my_list = [-1 3]

```

## <ins>linked_list_set</ins>

```C
void linked_list_set(type)(linked_list(type) * arr,type value, size_t index);
```

Altera um valor da lista na posição indicada, a posição deve ser menor que o tamanho da lista.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| value    | novo valor |
| index    | posição em que o valor será alterado |


### Exemplo

```C
linked_list(int) my_list;

linked_list_create(int)(&my_list);

linked_list_add(int)(&my_list,-1); // my_list = [-1]
linked_list_set(int)(&my_list,4,0); // my_list = [4]
```

## <ins>linked_list_insert</ins>

```C
void linked_list_insert(type)(linked_list(type) * arr,type value, size_t index);
```

Insere um valor na lista na posição indicada, a posição deve ser menor ou igual o tamanho da lista.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| value    | valor a ser inserido na lista |
| index    | posição em que o valor será inserido |


### Exemplo

```C
linked_list(int) my_list;

linked_list_create(int)(&my_list);

linked_list_add(int)(&my_list,-1); // my_list = [-1]
linked_list_insert(int)(&my_list,4,0); // my_list = [4 -1]
```

## <ins>linked_list_remove</ins>

```C
void linked_list_remove(type)(linked_list(type) * arr, size_t index);
```

Remove um valor da lista na posição indicada, a posição deve ser menor que o tamanho da lista.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| index    | posição em que o valor será removido |


### Exemplo

```C
linked_list(int) my_list;

linked_list_create(int)(&my_list);

linked_list_add(int)(&my_list,-1); // my_list = [-1]
linked_list_remove(int)(&my_list,0); // my_list = [ ]
```

## <ins>linked_list_get</ins>

```C
type linked_list_get(type)(linked_list(type) * arr, size_t index);
```

Retorna um valor da lista na posição indicada, a posição deve ser menor que o tamanho da lista.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| index    | posição em que o valor será buscado |
| return   | valor na posição indicada |

### Exemplo

```C
linked_list(int) my_list;

linked_list_create(int)(&my_list);

linked_list_add(int)(&my_list,-1); // my_list = [-1]
int v = linked_list_get(int)(&my_list,0); // v = -1
```

## <ins>linked_list_first</ins>

```C
type linked_list_first(type)(linked_list(type) * arr);
```

Retorna o primeiro valor da lista.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| return   | primeiro item da lista   |

### Exemplo

```C
linked_list(int) my_list;

linked_list_create(int)(&my_list);

linked_list_add(int)(&my_list,-1); // my_list = [-1]
linked_list_add(int)(&my_list,-2); // my_list = [-1 -2]

int v = linked_list_first(int)(&my_list); // v = -1
```

## <ins>linked_list_copy</ins>

```C
void linked_list_copy(type)(linked_list(type) * arr,linked_list(type) * *out, size_t start, size_t end);
```

Copia uma parte de uma lista em outra lista

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista de origem |
| out      | ponteiro de ponteiro para a lista destino |
| start    | posição de início da cópia |
| end      | posição de fim da cópia |


### Exemplo

```C
linked_list(int) my_list; // my_lista = [0 1 2 3 4 5 6]
linked_list(int)* other_list; // other_list = [ ]

linked_list_copy(int)(&my_list,&other_list,2,5); // other_list = [2 3 4 5]
```

## <ins>linked_list_clone</ins>

```C
void linked_list_clone(type)(linked_list(type) * arr,linked_list(type) * *out);
```

Copia uma lista inteira em outra lista

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista de origem |
| out      | ponteiro de ponteiro para a lista destino |



### Exemplo

```C
linked_list(int) my_list; // my_lista = [0 1 2 3 4 5 6]
linked_list(int)* other_list; // other_list = [ ]

linked_list_clone(int)(&my_list,&other_list); // other_list = [0 1 2 3 4 5 6]
```

## <ins>linked_list_equal</ins>

```C
bool linked_list_equal(type)(linked_list(type) * a,linked_list(type) *b);
```

Verifica se duas listas tem os mesmos valores

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| a      | ponteiro para a primeira lista |
| b      | ponteiro para a segunda lista |
| return | true caso os valores sejam iguais, false caso não |



### Exemplo

```C
linked_list(int) my_list; // my_lista = [0 1 2 3 4 5 6]
linked_list(int) other_list; // other_list = [0 1 2 3 4 5 6]

bool eq = linked_list_equal(int)(&my_list,&other_list); // eq = true
```

## <ins>linked_list_fill</ins>

```C
void linked_list_fill(type)(linked_list(type) * arr, type value);
```

Subistitui todos os valores da lista pelo valor indicado

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| value    | novo valor a ser substituido |


### Exemplo

```C
linked_list(int) my_list; // my_list = [-1 -2 -3 -4 -5]

linked_list_fill(int)(&my_list,0); // my_list = [0 0 0 0 0]
```

## <ins>linked_list_find</ins>

```C
type linked_list_find(type)(linked_list(type) * arr, type value);
```

Retorna a posição do primeiro elemento igual a value. Caso não seja encontrado retorna -1.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| value    | valor a ser encontrado   |
| return   | posição do valor encontrado, caso não haja retorna -1 |


### Exemplo

```C
linked_list(int) my_list; // my_list = [-1 -2 -3 -4 -5]

int f = linked_list_find(int)(&my_list,-3); // f = 2
    f = linked_list_find(int)(&my_list, 2); // f = -1
```

## <ins>linked_list_find_cmp</ins>

```C
int linked_list_find_cmp(type)(linked_list(type) * arr, type value,bool (*cmp)(type a, type b));
```

Retorna a posição do primeiro elemento igual a value usando a função apontada por cmp para realizar a comparação. Caso não seja encontrado retorna -1.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| value    | valor a ser encontrado   |
| cmp      | ponteiro para função a ser utilizada na comparação |
| return   | posição do valor encontrado, caso não haja retorna -1 |


### Exemplo

```C

bool cmp_fn(int a, int b){
    return a == b;
}

linked_list(int) my_list; // my_list = [-1 -2 -3 -4 -5]

int f = linked_list_find_cmp(int)(&my_list,-3, cmp_fn); // f = 2
    f = linked_list_find_cmp(int)(&my_list, 2, cmp_fn); // f = -1
```

## <ins>linked_list_all</ins>

```C
bool linked_list_all(type)(linked_list(type) * arr, type value);
```

Verifica se todos os elementos do array são iguais ao valor fornecido.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| value    | valor a ser verificado   |
| return   | **true** caso todos os valores sejam iguais, **false** caso contrário |


### Exemplo

```C
linked_list(int) my_list; // my_list = [0 0 0 0 0]

bool f = linked_list_all(int)(&my_list, 0); // f = true
     f = linked_list_all(int)(&my_list, 2); // f = false
```

## <ins>linked_list_all_cmp</ins>

```C
bool linked_list_all_cmp(type)(linked_list(type) * arr, type value,bool (*cmp)(type a, type b));
```

Verifica se todos os elementos do array são iguais ao valor fornecido usando a função apontada por cmp para realizar a comparação.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| value    | valor a ser verificado   |
| cmp      | ponteiro para função a ser utilizada na comparação |
| return   | **true** caso todos os valores sejam iguais, **false** caso contrário |


### Exemplo

```C
bool cmp_fn(int a, int b){
    return a == b;
}

linked_list(int) my_list; // my_list = [0 0 0 0 0]

bool f = linked_list_all_cmp(int)(&my_list, 0, cmp_fn); // f = true
     f = linked_list_all_cmp(int)(&my_list, 2, cmp_fn); // f = false
```

## <ins>linked_list_join</ins>

```C
void linked_list_join(type)(linked_list(type) * a,linked_list(type) * b);
```

Une as duas listas fornecidas em uma, o primeiro elemento da lista **b** será linkado ao último elemento da lista **a**. É importante saber que os elementos da lista **b** serão transferidos para a lista **a** assim após o termino da função **b** não conterá nenhum elemento. 

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| a        | ponteiro para a primeira lista    |
| b        | ponteiro para a segunda  lista    |

### Exemplo
```C

linked_list(int) my_list; // my_list = [1 2 3]
linked_list(int) other_list; // my_list = [4 5]

linked_list_join(int)(&my_list,&other_list); // my_list = [1 2 3 4 5]
                                             // other_list = []

```

## <ins>linked_list_reverse</ins>

```C
void linked_list_reverse(type)(linked_list(type) * arr);
```

Inverte a ordem dos elementos da lista.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |

### Exemplo

```C
linked_list(int) my_list; // my_list = [1 2 3]
linked_list_reverse(int)(&my_list); // my_list = [3 2 1]
```

## <ins>linked_list_free</ins>

```C
void linked_list_free(type)(linked_list(type) * arr);
```

Libera os blocos de memória alocados pela lista.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |

### Exemplo

```C
linked_list(int) my_list; // my_list = [1 2 3]
linked_list_free(int)(&my_list); // my_list = []
```

## <ins>linked_list_lenght</ins>

```C
size_t linked_list_lenght(type)(linked_list(type) * arr);
```
Retorna a quantidade de elementos presentes na lista.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| arr      | ponteiro para a lista    |
| returns  | némuero de elementos da lista |
### Exemplo

```C
linked_list(int) my_list; // my_list = [1 2 3]
size_t len = linked_list_lenght(int)(&my_list); // len = 3
```

