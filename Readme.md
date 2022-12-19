# Atividade 3 - Fila de funções e escalonamento

Neste repositório constam as implementações da fila de função, alarme, temporizador (*Timer*).

## Compilação e gravação

Para compilar e gravar no microcontrolador ATMega328p, basta utilizar os comandos abaixo:

```C++
make clean all
```

O comando ```make clean``` garante que código antigo seja atualizado.


## Projeto

O projeto consistiu em aplicações que demonstram o funcionamento de dois escalonadores de funções: RMS (Rate Monotonic Scheduling) e EDD (Earliest Due Date).

## Lista Encadeada

A lista encadeada facilita bastante a implementação de outras funcionalidades na biblioteca como um todo. Ela é declarada da seguinte forma

```C++
ListaEncadeada<T tipo, bool ORDENADA, bool RELATIVA, T_ORDEM ordem>;
```

Dessa forma, ela é capaz de guardar dados de forma a mantê-los sempre ordenados de acordo um _rank_ especificado no tipo de dados _T_ORDEM_. Isso permite definir logo de início quem poderá ter uma posição mais facilitada de acesso.

### Método "insere"

Declarado da seguinte forma:

```C++
void insere(T _dado, T_ORDEM _rank = 0);
```

Quando um dado é inserido na lista, caso o parâmetro "ORDENADA" seja definido como "true", o dado é inserido na lista de acordo com o seu "_rank". Caso "ORDENADA" seja "false", o dado é anexado ao final da lista. Se "_rank" não for especificado, é assumido o valor padrão 0.

### Método "obtem"

Declarado da seguinte forma:

```C++
T obtem(int posicao);
```

Permite acessar um dado em uma posição específica da lista.

### Método "remove_inicio"

Declarado da seguinte forma:

```C++
T remove_inicio();
```

Remove o primeiro ítem da lista e retorna o mesmo. Com isso, o segundo elemento da lista, passa a ser o primeiro.

### Método "atualiza_rank_inicio"

Declarado da seguinte forma:

```C++
T_ORDEM atualiza_rank_inicio(T_ORDEM valor)
```

Ajusta o atributo _rank_ do primeiro elemento da lista, retorando o novo rank.

### Método "tamanho"

Retorna o tamanho atual da lista.

### Método "insere_primeiro"

É privado e declarado da seguinte forma:

```C++
void insere_primeiro(T _dado, T_ORDEM _rank);
```

É utilizado quando a lista está vazia e o primeiro elemento será inserido.

### Método "insere_ordenada"

É privado e declarado da seguinte forma:

```C++
void insere_ordenada(T _dado, T_ORDEM _rank);
```

É utilizado quando deseja-se manter a lista ordenada ao mesmo tempo que novos dados são inseridos. A ordem do dado repeita o valor definido em "_rank".

### Método "anexa"

É privado e declarado da seguinte forma:

```C++
void anexa(T _dado, T_ORDEM _rank);
```

Utilizado quando o dado a ser inserido ocupa a última posição, ou seja, é anexado ao final da lista.

## Alarme

## Temporizador

## FIFO Circular

## Fila de função