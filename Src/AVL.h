#ifndef AVL_H
#define AVL_H

#include "stdbool.h"
#include "item.h"

#define max(a,b) ((a>b) ? a : b)
#define ERRO -1

typedef struct avl AVL;

AVL *AVL_criar(void); // Cria uma árvore.
AVL *AVL_copiar(AVL *arvore); // Cria uma cópia de uma árvore.
void AVL_apagar(AVL **arvore); // Apaga uma árvore.

bool AVL_inserir(AVL *avl, ITEM *item); // Insere um elemento em uma árvore.
bool AVL_remover(AVL *arvore, ITEM *item); // Remove um elemento de uma árvore.

ITEM * AVL_busca(AVL *arvore, ITEM *item); // Busca um elemento em uma árvore.

void AVL_pre_ordem(AVL *arvore);
void AVL_em_ordem(AVL *arvore);

AVL *AVL_uniao(AVL *arvore_A, AVL *arvore_B); // Cria uma árvore contendo a união dos elementos de duas árvores.
AVL *AVL_interseccao(AVL *arvore_A, AVL *arvore_B); // Cria uma árvore contendo a intersecção dos elementos de duas árvores.
bool AVL_pertence(AVL *arvoce_A, ITEM *item); // Retorna caso um elemento buscado pertence ou não à árvore

#endif