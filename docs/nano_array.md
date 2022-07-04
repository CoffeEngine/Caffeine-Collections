# nano_array

A estrutura mais proxima de um array puro, a única diferença é que esta estrutura contém um campo para armazenar o seu tamanho.

```C
typedef struct
{   
    type* buffer;
    size_t lenght;
} array(type);
```

## <ins>array_create</ins>

```C
void array_create(type)(array(type)* arr, size_t lenght);
```

Recebe um ponteiro para um array e o inicializa, é alocado um bloco de memória dinâmicamente cujo o endereço fica armazenado no campo buffer, o tamanho do bloco é definido por sizeof(type)*lenght.

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um array |
|lenght | tamanho do vetor       |

### Exemplo

```C
array(int) my_array;
array_create(int)(&my_array,10);
printf("array lenght: %d\n", my_array.lenght); //my_array.lenght = 10
```

## <ins>array_set</ins>

```C
void array_set(type)(array(type)* arr, type value, size_t index);
```

Define o valor em uma determinada posição do array.

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um array |
|value  | valor a ser definido   |
|index  | posição onde o valor será alterado|

### Exemplo

```C
array(int) my_array;
array_set(int)(&my_array, -3, 1); //o segundo valor do array passa a ser -3
```

## <ins>array_insert<ins>

```C
void array_insert(type)(array(type)* arr, type value, size_t index);
```
Insere um valor na posição indicada deslocando o valor atual e os subsequentes para a direita, o último valor do array é perdido.

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um array |
|value  | valor a ser definido   |
|index  | posição onde o valor será inserido|

### Exemplo

```C
array(int) my_array; // my_array = [0,1,2,3,4]
array_insert(int)(&my_array, -3, 1); // passa a conter [0,-3,1,2,3]
```

## <ins>array_lenght<ins>

Retornar o tamanho do array.

```C
size_t array_insert(type)(array(type)* arr);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um array |
|return | tamanho do array       |

### Exemplo

```C
array(int) my_array; // my_array = [0,1,2,3,4]
size_t len = array_lenght(int)(&my_array); // len = 5 
```

## <ins>array_remove<ins>

Remove um valor na posição indicada, os valores à direita do valor removido são deslocados para a esquerda, o último valor é duplicado.

```C
void array_remove(type)(array(type)* arr, size_t index);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um array |
|index  | posição onde o valor será removido|

### Exemplo

```C
array(int) my_array; // my_array = [0,1,2,3,4]
array_remove(int)(&my_array, 1); // passa a conter [0,2,3,4,4]
```
## <ins>array_get<ins>

Retorna o valor na posição indicada.

```C
type array_get(type)(array(type)* arr, size_t index);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um array |
|index  | posição onde do valor a ser retornado|
|returns| valor na posição indicada|

### Exemplo

```C
array(int) my_array; // my_array = [0,1,3,5,7]
int v = array_get(int)(&my_array, 2); // v = 3
````
## <ins>array_first<ins>

Retorna o valor na posição 0.

```C
type array_first(type)(array(type)* arr);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um array |
|returns| valor na posição 0|

### Exemplo

```C
array(int) my_array; // my_array = [0,1,3,5,7]
int v = array_first(int)(&my_array); // v = 0
````

## <ins>array_copy<ins>

Copia um trecho do array para outro bloco de memória, este bloco de memória precisa estar préviamente alocado.

```C
void array_copy(type)(array(type)* arr,type * *out, size_t start, size_t end);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um array |
|out| endereço para o bloco de memória destino|
|start| posição de início da cópia|
|end| posição de fim da cópia|

### Exemplo

```C
array(int) my_array; // my_array = [0,1,3,5,7]
int* my_buffer = malloc(sizeof(int)*3);
array_copy(&my_array,&my_buffer,1,3); // my_buffer = [0,1,3,5,7]
````

## <ins>array_clone<ins>

Copia array para outro bloco de memória, este bloco de memória precisa estar préviamente alocado.

```C
void array_clone(type)(array(type)* arr,type * *out);
```

### Parâmetros
|nome   | descrição              |
|:----- |:---------------------- |
|arr    | ponteiro para um array |
|out| endereço para o bloco de memória destino|

### Exemplo

```C
array(int) my_array; // my_array = [0,1,3,5,7]
int* my_buffer = malloc(sizeof(int)*3);
array_clone(&my_array,&my_buffer); // my_buffer = [0,1,3,5,7]
````

## <ins>array_equal<ins>

Checa se dois arrays contém os mesmos valores.

```C
bool array_equal(type)(array(type)* a,array(type)* b);
```

### Parâmetros
|nome | descrição              |
|:-   |:---------------------- |
|a    | ponteiro para um array |
|b    | ponteiro para um array |
|returns| true caso os valores sejam iguals, false caso não |
### Exemplo

```C
array(int) my_array;    // my_array = [0,1,3,5,7]
array(int) other_array; // other_array = [0,1,3,5,7]

bool eq = array_equal(&my_array,&other_array); // eq = true
````

## <ins>array_fill<ins>

Iguala todas as casa do vetor para um valor especificado.

```C
void array_fill(type)(array(type)* arr,type value);
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um array |
|value | valor a ser utilizado  |

### Exemplo

```C
array(int) my_array;    // my_array = [0,1,3,5,7]
array_fill(&my_array,0); // my_array = [0,0,0,0,0]
````

## <ins>array_find<ins>

Busca por um valor no array e retorna a posição da primeira ocorrência, caso não seja encontrado é retornado -1.

```C
int array_find(type)(array(type)* arr,type value);
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um array |
|value | valor a ser encontrado |
|return| posição do valor encontrado ou -1 caso não exista|

### Exemplo

```C
array(int) my_array;    // my_array = [0,1,3,5,7]
int f3 = array_find(&my_array,3); // f3 = 2
int f2 = array_find(&my_array,2); // f2 = -1
````

## <ins>array_find_cmp<ins>

Busca por um valor no array usando uma função customizada para comparação e retorna a posição da primeira ocorrência, caso não seja encontrado é retornado -1.

```C
int array_find_cmp(type)(array(type)* arr,type value,bool (*cmp)(type a, type b));
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um array |
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

array(point) my_array;    // my_array = [{0,1},{1,3},{5,7}]
// ...

point fi = (point){x = 3, y = 1};
point fo = (point){x = 3, y = 7};

int i = array_find_cmp(&my_array,fi,cmp_point); // i = 1
int o = array_find_cmp(&my_array,fo,cmp_point); // o = -1
````

## <ins>array_resize<ins>

Muda o tamanho de um array, note que esta função realoca o bloco de memória podendo assim mudar o seu endereço, tenha isto em mente caso exista alguma referência para um elemento deste array.

Quando o array aumenta de tamanho os novos espaços não terão seus valores definidos por nenhum valor padrão assumindo assim o valor já presente na memória(lixo).

```C
void array_resize(type)(array(type)* arr,size_t lenght);
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um array |
|lenght | novo tamanho do array |


### Exemplo

```C
array(int) my_array;
array_create(int)(&my_array,3); // my_array = [0,1,2]
array_resize(int)(&my_array,5); // my_array = [0,1,2,**,**]
printf("array lenght: %d\n", my_array.lenght); //my_array.lenght = 5
````

## <ins>array_count<ins>

Conta quantas ocorrências de um valor há no array.

```C
int array_count(type)(array(type)* arr,type value);
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um array |
|value | valor a ser encontrado |
|return| quantidade de vezes que o valor foi encontrado|

### Exemplo

```C
array(int) my_array; // my_array = [0,1,0,1,0]
int n = array_count(int)(&my_array,0); // n = 3
```

## <ins>array_count_cmp<ins>

Conta quantas ocorrências de um valor há no array usando uma função customizada para realizar a comparação.

```C
int array_count_cmp(type)(array(type)* arr,type value,bool (*cmp)(type a, type b));
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um array |
|value | valor a ser encontrado |
|cmp   | ponteiro para função de comparação a ser utilizada|
|return| quantidade de vezes que o valor foi encontrado|

### Exemplo

```C
bool is_even(int a, int b){
    return a%2==1;
}
array(int) my_array;    // my_array = [0,1,2,3,4,5,6,7]
int i = array_find_cmp(int)(&my_array,0,is_even); // i = 4
```

## <ins>array_all<ins>

Verifica se todos os valores do array são iguais ao valor informado.

```C
int array_all(type)(array(type)* arr,type value);
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um array |
|value | valor a ser comparado  |
|return| true caso todos os valores sejam iguais a value|

### Exemplo

```C
array(int) my_array;    // my_array = [0,0,0,0,0]
bool i = array_all(int)(&my_array,1); // i = false
bool a = array_all(int)(&my_array,0); // a = true
```

## <ins>array_all_cmp<ins>

Verifica se todos os valores do array são iguais ao valor informado utilizando uma função customizada para realizar a comparação.

```C
int array_all_cmp(type)(array(type)* arr,type value, bool (*cmp)(type a, type b));
```

### Parâmetros
|nome  | descrição              |
|:-    |:---------------------- |
|arr   | ponteiro para um array |
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

array(int) my_array;    // my_array = [1,-3,5,7,9]
bool i = array_all_cmp(int)(&my_array,0,is_even); // i = true
bool a = array_all_cmp(int)(&my_array,0,is_positive); // a = false
```

## <ins>array_join<ins>

Unifica os valores de dois arrays em um array, ao final do processo o array **a** conterá os valores do array **b** começando a partir do último elemento do array **a** original, o array **b** continuará intacto.

Note que esta função realoca o bloco de memória do array **a** podendo assim mudar o seu endereço, tenha isto em mente caso exista alguma referência para um elemento deste array.

```C
void array_join(type)(array(type)* a,array(type)* b);
```

### Parâmetros
|nome  | descrição              |
|:---  |:---------------------- |
|a     | ponteiro para um array |
|b     | ponteiro para um array |


### Exemplo
```C

array(int) my_array; // my_array = [0,1,2]
array(int) other_array; // other_array = [3,4]

array_join(int)(&my_array,&other_array);

// my_array = [0,1,2,3,4]
// other_array = [3,4]
```

## <ins>array_reverse<ins>

Inverte a ordem do valores do array.

```C
void array_reverse(type)(array(type)* arr);
```

### Parâmetros
|nome  | descrição              |
|:---  |:---------------------- |
|a     | ponteiro para um array |

### Exemplo

```C
array(int) my_array; // my_array = [0,1,2]
array_reverse(int)(&my_array) // my_array = [2,1,0]
```

## <ins>array_free<ins>

Libera o bloco de memória alocado pelo array.

```C
void array_free(type)(array(type)* arr);
```

### Parâmetros
|nome  | descrição              |
|:---  |:---------------------- |
|a     | ponteiro para um array |

```C
array(int) my_array; // my_array = [0,1,2]
array_free(int)(&my_array) // my_array = []
```