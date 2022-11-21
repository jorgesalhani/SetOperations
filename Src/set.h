#ifndef SET_H
#define SET_H

#include "AVL.h"
#include "item.h"

typedef struct set SET;

SET *set_criar(void); // Cria um conjunto.
void set_apagar(SET **conjunto); // Apaga um conjunto.

bool set_inserir (SET *conjunto, int elemento); // Insere um elemento em um conjunto.
bool set_remover(SET *conjunto, int elemento); // Remove um elemento de um conjunto.

bool set_pertence(SET *conjunto, int elemento); // Verifica se um elemento pertence a um conjunto.

SET *set_uniao(SET *conjunto_A, SET *conjunto_B); // Cria o conjunto da união de dois conjuntos.
SET *set_interseccao(SET *conjunto_A, SET *conjunto_B); // Cria o conjunto da intersecção de dois conjuntos.

void set_imprimir(SET *conjunto); // Imprime os elementos de um conjunto.

#endif