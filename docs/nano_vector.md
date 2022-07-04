# nano_vector

Sua estrutura e funcionaliade assemelha-se a um array, entretanto seu tamanho é variável, realocando-se automáticamente a medida que não há espaço inutilizado e novos itens são adicionados.

```C
typedef struct
{   
    type* buffer;
    size_t lenght;
    size_t count;
} vector(type);
```

## <ins>vector_create</ins>

```C
void vector_create(type)(vector(type)* arr, size_t lenght);
```

Recebe um ponteiro para um vector e o inicializa, é alocado um bloco de memória dinâmicamente cujo o endereço fica armazenado no campo buffer, o tamanho do bloco é definido por sizeof(type)*lenght.

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|lenght | tamanho do vetor       |

### Exemplo

```C
vector(int) my_vector;
vector_create(int)(&my_vector,10);
printf("vector lenght: %d\n", my_vector.lenght); //my_vector.lenght = 10
```

## <ins>vector_set</ins>

```C
void vector_set(type)(vector(type)* arr, type value, size_t index);
```

Define o valor em uma determinada posição do vector.

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|value  | valor a ser definido   |
|index  | posição onde o valor será alterado|

### Exemplo

```C
vector(int) my_vector;
vector_set(int)(&my_vector, -3, 1); //o segundo valor do vector passa a ser -3
```

## <ins>vector_insert<ins>

```C
void vector_insert(type)(vector(type)* arr, type value, size_t index);
```
Insere um valor na posição indicada deslocando o valor atual e os subsequentes para a direita, o último valor do vector é perdido.

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|value  | valor a ser definido   |
|index  | posição onde o valor será inserido|

### Exemplo

```C
vector(int) my_vector; // my_vector = [0,1,2,3,4]
vector_insert(int)(&my_vector, -3, 1); // passa a conter [0,-3,1,2,3]
```

## <ins>vector_lenght<ins>

Retornar o tamanho do vector.

```C
size_t vector_insert(type)(vector(type)* arr);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|return | tamanho do vector       |

### Exemplo

```C
vector(int) my_vector; // my_vector = [0,1,2,3,4]
size_t len = vector_lenght(int)(&my_vector); // len = 5 
```

## <ins>vector_remove<ins>

Remove um valor na posição indicada, os valores à direita do valor removido são deslocados para a esquerda, o último valor é duplicado.

```C
void vector_remove(type)(vector(type)* arr, size_t index);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|index  | posição onde o valor será removido|

### Exemplo

```C
vector(int) my_vector; // my_vector = [0,1,2,3,4]
vector_remove(int)(&my_vector, 1); // passa a conter [0,2,3,4,4]
```
## <ins>vector_get<ins>

Retorna o valor na posição indicada.

```C
type vector_get(type)(vector(type)* arr, size_t index);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|index  | posição onde do valor a ser retornado|
|returns| valor na posição indicada|

### Exemplo

```C
vector(int) my_vector; // my_vector = [0,1,3,5,7]
int v = vector_get(int)(&my_vector, 2); // v = 3
````
## <ins>vector_first<ins>

Retorna o valor na posição 0.

```C
type vector_first(type)(vector(type)* arr);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|returns| valor na posição 0|

### Exemplo

```C
vector(int) my_vector; // my_vector = [0,1,3,5,7]
int v = vector_first(int)(&my_vector); // v = 0
````

## <ins>vector_last<ins>

Retorna o último elemento do vector.

```C
type vector_last(type)(vector(type)* arr);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|returns| o último valor|

### Exemplo

```C
vector(int) my_vector; // my_vector = [0,1,3,5,7]
int v = vector_last(int)(&my_vector); // v = 7
````

## <ins>vector_push_front<ins>

Insere um item no início do vector

```C
void vector_push_front(type)(vector(type)* arr, type value);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|value  | valor a ser inserido|

### Exemplo
```C
vector(int) my_vector; // my_vector = [0,1,3,5,7]
vector_push_front(int)(&my_vector,-1); // my_vector = [-1,0,1,3,5,7]
```

## <ins>vector_push_back<ins>

Insere um item no fim do vector

```C
void vector_push_back(type)(vector(type)* arr, type value);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|value  | valor a ser inserido|

### Exemplo
```C
vector(int) my_vector; // my_vector = [0,1,3,5,7]
vector_push_back(int)(&my_vector,9); // my_vector = [0,1,3,5,7,9]
```

## <ins>vector_pop_front<ins>

Remove um item do início do vector

```C
void vector_pop_front(type)(vector(type)* arr);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |

### Exemplo
```C
vector(int) my_vector; // my_vector = [0,1,3,5,7]
vector_pop_front(int)(&my_vector); // my_vector = [1,3,5,7]
```

## <ins>vector_pop_back<ins>

Remove um item do fim do vector

```C
void vector_pop_back(type)(vector(type)* arr);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |


### Exemplo
```C
vector(int) my_vector; // my_vector = [0,1,3,5,7]
vector_pop_back(int)(&my_vector); // my_vector = [0,1,3,5]
```

## <ins>vector_copy<ins>

Copia um trecho do vector para outro bloco de memória, este bloco de memória precisa estar préviamente alocado.

```C
void vector_copy(type)(vector(type)* arr,type * *out, size_t start, size_t end);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|out| endereço para o bloco de memória destino|
|start| posição de início da cópia|
|end| posição de fim da cópia|

### Exemplo

```C
vector(int) my_vector; // my_vector = [0,1,3,5,7]
int* my_buffer = malloc(sizeof(int)*3);
vector_copy(&my_vector,&my_buffer,1,3); // my_buffer = [0,1,3,5,7]
````

## <ins>vector_clone<ins>

Copia vector para outro bloco de memória, este bloco de memória precisa estar préviamente alocado.

```C
void vector_clone(type)(vector(type)* arr,type * *out);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um vector |
|out| endereço para o bloco de memória destino|

### Exemplo

```C
vector(int) my_vector; // my_vector = [0,1,3,5,7]
int* my_buffer = malloc(sizeof(int)*3);
vector_clone(&my_vector,&my_buffer); // my_buffer = [0,1,3,5,7]
````

## <ins>vector_equal<ins>

Checa se dois vectors contém os mesmos valores.

```C
bool vector_equal(type)(vector(type)* a,vector(type)* b);
```

### Parâmetros
|nome | descrição              |
|:-   |:---------------------- |
|a    | ponteiro para um vector |
|b    | ponteiro para um vector |
|returns| true caso os valores sejam iguals, false caso não |
### Exemplo

```C
vector(int) my_vector;    // my_vector = [0,1,3,5,7]
vector(int) other_vector; // other_vector = [0,1,3,5,7]

bool eq = vector_equal(&my_vector,&other_vector); // eq = true
````

## <ins>vector_fill<ins>

Iguala todas as casa do vetor para um valor especificado.

```C
void vector_fill(type)(vector(type)* arr,type value);
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um vector |
|value | valor a ser utilizado  |

### Exemplo

```C
vector(int) my_vector;    // my_vector = [0,1,3,5,7]
vector_fill(&my_vector,0); // my_vector = [0,0,0,0,0]
````

## <ins>vector_find<ins>

Busca por um valor no vector e retorna a posição da primeira ocorrência, caso não seja encontrado é retornado -1.

```C
type vector_find(type)(vector(type)* arr,type value);
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um vector |
|value | valor a ser encontrado |
|return| posição do valor encontrado ou -1 caso não exista|

### Exemplo

```C
vector(int) my_vector;    // my_vector = [0,1,3,5,7]
int f3 = vector_find(&my_vector,3); // f3 = 2
int f2 = vector_find(&my_vector,2); // f2 = -1
````

## <ins>vector_find_cmp<ins>

Busca por um valor no vector usando uma função customizada para comparação e retorna a posição da primeira ocorrência, caso não seja encontrado é retornado -1.

```C
type vector_find_cmp(type)(vector(type)* arr,type value,bool (*cmp)(type a, type b));
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um vector |
|value | valor a ser encontrado |
|cmp   | ponteiro para função de comparação a ser utilizada|
|return| posição do valor encontrado ou -1 caso não exista|

### Exemplo

```C

typedef struct { 
    float x;
    float y;
} point;

bool cmp_point(point a, point b){
    return (a.x == b.x && a.y == b.y) || (a.x == b.y && a.y == b.x);
}

vector(point) my_vector;    // my_vector = [{0,1},{1,3},{5,7}]
// ...

point fi = (point){x = 3, y = 1};
point fo = (point){x = 3, y = 7};

int i = vector_find_cmp(&my_vector,fi,cmp_point); // i = 1
int o = vector_find_cmp(&my_vector,fo,cmp_point); // o = -1
````

## <ins>vector_resize<ins>

Muda o tamanho de um vector, note que esta função realoca o bloco de memória podendo assim mudar o seu endereço, tenha isto em mente caso exista alguma referência para um elemento deste vector.

Quando o vector aumenta de tamanho os novos espaços não terão seus valores definidos por nenhum valor padrão assumindo assim o valor já presente na memória(lixo).

```C
void vector_resize(type)(vector(type)* arr,size_t lenght);
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um vector |
|lenght | novo tamanho do vector |


### Exemplo

```C
vector(int) my_vector;
vector_create(int)(&my_vector,3); // my_vector = [0,1,2]
vector_resize(int)(&my_vector,5); // my_vector = [0,1,2,**,**]
printf("vector lenght: %d\n", my_vector.lenght); //my_vector.lenght = 5
````

## <ins>vector_count<ins>

Conta quantas ocorrências de um valor há no vector.

```C
size_t vector_count(type)(vector(type)* arr,type value);
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um vector |
|value | valor a ser encontrado |
|return| quantidade de vezes que o valor foi encontrado|

### Exemplo

```C
vector(int) my_vector; // my_vector = [0,1,0,1,0]
int n = vector_count(int)(&my_vector,0); // n = 3
```

## <ins>vector_count_cmp<ins>

Conta quantas ocorrências de um valor há no vector usando uma função customizada para realizar a comparação.

```C
size_t vector_count_cmp(type)(vector(type)* arr,type value,bool (*cmp)(type a, type b));
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um vector |
|value | valor a ser encontrado |
|cmp   | ponteiro para função de comparação a ser utilizada|
|return| quantidade de vezes que o valor foi encontrado|

### Exemplo

```C
bool is_even(int a, int b){
    return a%2==1;
}
vector(int) my_vector;    // my_vector = [0,1,2,3,4,5,6,7]
int i = vector_find_cmp(int)(&my_vector,0,is_even); // i = 4
```

## <ins>vector_all<ins>

Verifica se todos os valores do vector são iguais ao valor informado.

```C
bool vector_all(type)(vector(type)* arr,type value);
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um vector |
|value | valor a ser comparado  |
|return| true caso todos os valores sejam iguais a value|

### Exemplo

```C
vector(int) my_vector;    // my_vector = [0,0,0,0,0]
bool i = vector_all(int)(&my_vector,1); // i = false
bool a = vector_all(int)(&my_vector,0); // a = true
```

## <ins>vector_all_cmp<ins>

Verifica se todos os valores do vector são iguais ao valor informado utilizando uma função customizada para realizar a comparação.

```C
bool vector_all_cmp(type)(vector(type)* arr,type value, bool (*cmp)(type a, type b));
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um vector |
|value | valor a ser comparado  |
|cmp   | ponteiro para função de comparação a ser utilizada|
|return| true caso todos os valores sejam iguais a value|

### Exemplo

```C

bool is_even(int a, int b){
    return a%2==1;
}

bool is_positive(int a, int b){
    return a>0;
}

vector(int) my_vector;    // my_vector = [1,-3,5,7,9]
bool i = vector_all_cmp(int)(&my_vector,0,is_even); // i = true
bool a = vector_all_cmp(int)(&my_vector,0,is_positive); // a = false
```

## <ins>vector_join<ins>

Unifica os valores de dois vectors em um vector, ao final do processo o vector **a** conterá os valores do vector **b** começando a partir do último elemento do vector **a** original, o vector **b** continuará intacto.

Note que esta função realoca o bloco de memória do vector **a** podendo assim mudar o seu endereço, tenha isto em mente caso exista alguma referência para um elemento deste vector.

```C
void vector_join(type)(vector(type)* a,vector(type)* b);
```

### Parâmetros
|nome  | descrição              |
|:---  |:---------------------- |
|a     | ponteiro para um vector |
|b     | ponteiro para um vector |

### Exemplo
```C

vector(int) my_vector; // my_vector = [0,1,2]
vector(int) other_vector; // other_vector = [3,4]

vector_join(int)(&my_vector,&other_vector,my_vector.lenght,other_vector.lenght);

// my_vector = [0,1,2,3,4]
// other_vector = [3,4]
```

## <ins>vector_reverse<ins>

Inverte a ordem do valores do vector.

```C
void vector_reverse(type)(vector(type)* arr);
```

### Parâmetros
|nome  | descrição              |
|:---  |:---------------------- |
|arr   | ponteiro para um vector |

### Exemplo

```C
vector(int) my_vector; // my_vector = [0,1,2]
vector_reverse(int)(&my_vector) // my_vector = [2,1,0]
```

## <ins>vector_free<ins>

Libera o bloco de memória alocado pelo vector.

```C
void vector_free(type)(vector(type)* arr);
```

### Parâmetros
|nome  | descrição              |
|:---  |:---------------------- |
|arr   | ponteiro para um vector |

```C
vector(int) my_vector; // my_vector = [0,1,2]
vector_free(int)(&my_vector) // my_vector = []
```