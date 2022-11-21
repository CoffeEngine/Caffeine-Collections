# nano_hash
Armazena dados no formato chave-valor, para tal é necessário o fornecimento de uma função que gere um índice a partir do valor fornecido, quanto menor a repetibilidade de índices gerados para valores diferentes melhor a função de hash.

Para lidar com as colisões o hash_map utiliza vetores internamente, assim caso duas chaves gerem o mesmo índice ambas serão adicionadas no vetor associado aquele índice, um vetor só é alocado quando há pelo menos uma chave pertencente aquele índice.

```C
typedef struct                                                             
{                                                                          
    key_type key;                                                         
    value_type value;                                                      
} bucket(key_type, value_type);   

typedef struct                     
{                                  
    type *arr;                     
    size_t lenght;                    
    size_t count;                  
} hash_arr(type);

typedef struct                                                             
{                                                                          
    hash_arr(bucket(key_type, value_type)) *buffer; 
    size_t lenght;                                                            
    size_t count;                                                          
    uintmax_t (*hash_fn)(char *);                                          
    bool (*cmp_key_fn)(key_type a, key_type b);                            
} hash_map(key_type, value_type);
```

## <ins>hash_map_create</ins>

```C
void hash_map_create(hash_map(key_type, value_type) * hash_ptr, size_t lenght, uintmax_t(*hash_fn)(char *), bool (*cmp_key_fn)(key_type a, key_type b));
```

Inicializa um hash_map, para isso é preciso informar o tamanho do buffer a ser alocado, quanto maior o buffer menor a probabilidade de ocorrer uma colisão, outras duas informações requeridas são um ponteiro para a função de hash a ser utilizada e um ponteiro para função de comparação a ser utilizada, a função de comparação será utilizada para checar se duas chaves são iguais.

A chave final gerada para um valor será o resto da divisão entre o valor retornado pela função de hash e o tamanho do hash_map (lenght).

A função de hash sempre recebe um ponteiro para o valor da chave ou invés do próprio valor.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| hash_ptr | ponteiro para o hash_map |
| lenght   | quantidade de índices disponíveis |
| hash_fn  | ponteiro para função de hash que será utilizada |
| cmp_key_fn | ponteiro para função que verifica igualdade entre duas chaves

### Exemplo

```C

uintmax_t hashfn(unsigned char *str)
{
    unsigned long hash = 5381;
   
    for(int i=0;i<sizeof(int);i++)
        hash = ((hash << 5) + hash) + str[i];

    return hash;
}

bool hashcmp(int a, int b)
{
    return a == b;
}

hash_map(int,int) my_hash;

hash_map_create(string, string)(&my_hash, 16, hashfn, hashcmp);

```

## <ins>hash_map_add</ins>

```C
void hash_map_add(hash_map(key_type, value_type) * hash_ptr,key_type key,value_type value);
```

Adiciona um valor ao hash_map, caso a chave seja uma já existente seu valor será atualizado.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| hash_ptr | ponteiro para o hash_map |
| key      | chave a ser utilizada    |
| value    | valor a ser inserido     |

### Exemplo

```C
hash_map(int,int) my_hash;
hash_map_add(&my_hash,0,5);
hash_map_add(&my_hash,1,10);
hash_map_add(&my_hash,2,15);
hash_map_add(&my_hash,0,20); // atualiza o valor da chave 0
```

## <ins>hash_map_remove</ins>

```C
bool hash_map_add(hash_map(key_type, value_type) * hash_ptr,key_type key);
```

Remove um conjunto chave-valor do hash_map, caso a chave fornecida exista retorna **true**, caso contrário retorna **false**.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| hash_ptr | ponteiro para o hash_map |
| key      | chave a ser removida     |
| return   | **true** caso a chave exista, **false** caso não |

### Exemplo

```C
hash_map(int,int) my_hash;
hash_map_add(&my_hash,0,5);
hash_map_remove(&my_hash,0);

bool exist = hash_map_exist(&my_hash,0); //exist = false
```

## <ins>hash_map_get</ins>

```C
bool hash_map_get(hash_map(key_type, value_type) * hash_ptr, key_type key, value_type * value);                                                          
```

Busca o valor associado a uma chave, se encontrado o valor será colocado no endereço de memória apontado por **value** e a função retornará **true**, caso contrário a função retornará **false**.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| hash_ptr | ponteiro para o hash_map |
| key      | chave do valor a ser procurado |
| value    | ponteiro para o endereço onde o valor será copiado caso exista |
| return   | **true** caso a chave exista no hash_map, **false** caso não |

### Exemplo

```C

hash_map(int,int) my_hash;
hash_map_add(&my_hash,0,5);

int my_value = 0;

if(hash_map_get(&my_hash,0,&my_value)){
    printf("%d\n",my_value); // prints 5 to the output
}

if(hash_map_get(&my_hash,1,&my_value)){
    printf("%d\n",my_value); // dont be executed 
}

```

## <ins>hash_map_exist</ins>

```C
bool hash_map_exist(hash_map(key_type, value_type) * hash_ptr,key_type key);
```

Verifica se uma chave está presente no hash_map.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| hash_ptr | ponteiro para o hash_map |
| key      | chave a ser pesquisada   |

### Exemplo

```C
hash_map(int,int) my_hash;
hash_map_add(&my_hash,0,5);

bool exist = hash_map_exist(&my_hash,1); // exist = false
exist = hash_map_exist(&my_hash,0); // exist = true
```

## <ins>hash_map_free</ins>

```C
void hash_map_free(hash_map(key_type, value_type) * hash_ptr);
```

Libera a memória alocada pelo hash_map.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| hash_ptr | ponteiro para o hash_map |

### Exemplo

```C
hash_map(int,int) my_hash;
hash_map_free(&my_hash);
```

## <ins>hash_map_clear</ins>

```C
void hash_map_clear(hash_map(key_type, value_type) * hash_ptr);
```

Remove todos os conjuntos chave-valor do hash_map.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| hash_ptr | ponteiro para o hash_map |

### Exemplo

```C
hash_map(int,int) my_hash;
hash_map_add(&my_hash,0,5);
hash_map_clear(&my_hash);

bool exist = hash_map_exist(&my_hash,0); //exist = false
```

## <ins>hash_map_lenght</ins>

```C
size_t hash_map_lenght(hash_map(key_type, value_type) * hash_ptr);
```

Retorna a quantidade de chaves-valores presentes no hash_map.

### Parametros
|nome      | descrição                |
|:-------- |:------------------------ |
| hash_ptr | ponteiro para o hash_map |
| returns  | quantidade de chaves-valores |

### Exemplo
```C
hash_map(int,int) my_hash;
hash_map_add(&my_hash,0,5);
size_t len = hash_map_lenght(&my_hash); // len = 1
```