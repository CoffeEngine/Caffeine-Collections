# Nano Lib
Pequena biblioteca com algorítimos comumente utilizados para C. <br>

O objetivo desta biblioteca não é criar um ambiente de execução grande, complexo e repleto de features,<br> e sim fornecer algumas funções e estruturas úteis durante o desenvolvimento de aplicações.<br> É da responsabilidade do desenvolvedor gerenciar o uso de memória e verificar os dados passados para as funções.

## Data Structure

Era de interesse o suporte a estruturas de dados genéricas mas que ao mesmo tempo não atrapalhasse a checagem estática de tipos feita pelo compilador, assim foi decidido basear-se na utilização de macros para criar as estruturas e funções específicas para um tipo de dado somente quando necessário, esta abordagem trouxe alguns pontos negativos como a necessidade de implementar a api para todos os tipos de interesse e a necessidade de definir um novo tipo para trabalhar com ponteiros ex: p_int ao inves de int* (o simbolo de * não é aceito na definição de indentificadores).

As chamadas de função seguem o seguinte padrão:

estrutura de dados _ função (tipo) (parametros)

A exemplo a criação de um array de inteiros:
```C
array(int) my_arr;
array_create(int)(&my_arr,16);
```
Internamente a macro array_create(int) será resolvida para a função nano_array_int_create, que pode ser utilizada diretamente se o desenvolvedor desejar, e a macro array(int) resolverá para a estrutura array_int_t que também pode ser utilizada de forma direta.

### Configuração

Para a utilização da API é necessário primeiro implementá-la para o tipo desejado, isso pode ser feito através das macros nano_declare_for e nano_implement_for, a primeira macro é responsável por declarar os tipos de dados necessários e as assinaturas das funções e a segunda é responsável pela implementação de fato.

Para uma configuração mais fácil de manter e utilizar, é recomendado a criação de um arquivo .h para as declarações e outro .c para as implementações, como no exemplo a seguir.

<ins>ds_declare.h</ins>

```C
#include "data_structure/cnano.h"

typedef char *string;

nano_declare_vector_for(string,int);
nano_declare_array_for(string,int);
```
<ins>ds_implement.c</ins>
```C
#include "struct_def.h"

nano_implement_core_for(string,int);
nano_implement_vector_for(string,int);
nano_implement_array_for(string,int);
```

É recomendado seguir este padrão pois assim as declarações de tipos e funções podem ser reutilizadas no código sem precisar ficar chamando nano_declare toda vez que for ser utilizada alguma estrutura, é importante lembrar que nano_implement deve ser chamada apenas uma vez para cada tipo, utilizar a macro mais de uma vez para o mesmo tipo como em:

```C
nano_implement_vector_for(string,string);
```
Vai causar duas implementações para as mesmas funções e como consequência a compilação irá falhar, o mesmo vale para a utilização desta macro em um .h e reutilizá-lo em várias partes do código.

Outro ponto a ser observado é que para cada implementação para vector há uma implementação para core ( nano_implement_core_for ), isso é necessário porque algumas estruturas de dados possuem rotinas que são iguais assim por questão de otimização e manutenibilidade foi decidido implementá-las à parte e reutilizar quando necessário, abaixo seguem as estruturas que necessitam de core:

* array
* vector

A macro nano_implement_core também deve ser chamada uma única vez para cada tipo e não necessita ser declarada ( nano_declare_core ).

### Exemplos

É possível encontrar [exemplos](examples) de utilização da biblioteca dentro da pasta examples, para executa-los de maneira rápida e direta é necessário a instalação da ferramente de build [Premake](https://premake.github.io/), posteriormente utilizar o script "run" mais apropriado para sua plataforma.


### Documentação

* [array](doc/nano_array.md)
* [vector](doc/nano_vector.md)
* [hash_map](doc/nano_hash.md)
* [linked_list](doc/nano_linked_list.md)
* [queue](doc/nano_queue.md)
* [stack](doc/nano_stack.md)

### Roadmap
<br>
<p> x | implementado </p>
<p> - | não será implementado </p>
<p> T | em teste </p>
<p> E | erro ao testar </p>


|          | Array  | HashMap  | Linked List  | Vector | Stack | Queue |
| :------- | :----: | :------: | :----------: | :----: | :---: | :---: |
| create   |   x    |     x    |      x       |   x    |   x   |   x   |        
| insert   |   x    |     -    |      x       |   x    |   -   |   -   | 
| set      |   x    |     -    |      x       |   x    |   -   |   -   | 
| get      |   x    |     x    |      x       |   x    |   -   |   -   | 
| push     |   -    |     -    |      -       |   -    |   x   |   -   |
| pop      |   -    |     -    |      -       |   -    |   x   |   -   |
| top      |   -    |     -    |      -       |   -    |   x   |   -   |
| enqueue  |   -    |     -    |      -       |   -    |   -   |   x   |
| dequeue  |   -    |     -    |      -       |   -    |   -   |   x   |
| first    |   x    |     -    |      x       |   x    |   -   |   x   | 
| last     |   x    |     -    |      x       |   x    |   -   |   x   | 
| remove   |   x    |     x    |      x       |   x    |   -   |   -   | 
| lenght   |   x    |     x    |      x       |   x    |   x   |   x   | 
| copy     |   x    |     -    |      x       |   x    |   x   |   x   | 
| clone    |   x    |     x    |      x       |   x    |   x   |   x   | 
| equal    |   x    |     x    |      x       |   x    |   x   |   x   | 
| fill     |   x    |     -    |      x       |   x    |   x   |   x   | 
| find     |   x    |     -    |      x       |   x    |   x   |   x   | 
| find_cmp |   x    |     -    |      x       |   x    |   x   |   x   | 
| resize   |   x    |     -    |      -       |   x    |   x   |   x   | 
| count    |   x    |     x    |      x       |   x    |   x   |   x   | 
| count_cmp|   x    |     x    |      x       |   x    |   x   |   x   | 
| all      |   x    |     x    |      x       |   x    |   x   |   x   | 
| all_cmp  |   x    |     x    |      x       |   x    |   x   |   x   | 
| any      |   x    |     x    |      x       |   x    |   x   |   x   | 
| any_cmp  |   x    |     x    |      x       |   x    |   x   |   x   | 
| join     |   x    |     -    |      x       |   x    |   x   |   x   | 
| reverse  |   x    |     -    |      x       |   x    |   x   |   x   | 
| clear    |   -    |     x    |      -       |   x    |   x   |   x   | 
| free     |   x    |     x    |      x       |   x    |   x   |   x   | 
| map      |   x    |     -    |      x       |   x    |   x   |   x   | 
| filter   |   x    |     -    |      x       |   x    |   x   |   x   |