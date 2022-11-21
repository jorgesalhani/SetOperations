#include "set.h"
#include <stdio.h>
#include <stdlib.h>

struct set{
    AVL *arvore;
};


SET *set_criar(void){
    SET *conjunto = (SET *) malloc(sizeof(SET));
    if (conjunto != NULL){
        conjunto->arvore = AVL_criar();

        if (conjunto->arvore == NULL){
            free(conjunto);
            conjunto = NULL;
        }
    }

    return conjunto;
}

bool set_inserir(SET *conjunto, int elemento){
    ITEM *item = item_criar(elemento);
    AVL_inserir(conjunto->arvore, item);
}

bool set_remover(SET *conjunto, int elemento){
    ITEM *item = item_criar(elemento);
    AVL_remover(conjunto->arvore, item);
    item_apagar(&item);
}

void set_apagar(SET **conjunto){
    if (*conjunto != NULL){
        AVL_apagar(&((*conjunto)->arvore));
        free(*conjunto);
        *conjunto = NULL;
    }
}

void set_imprimir(SET *conjunto){
    if (conjunto != NULL)
        AVL_em_ordem(conjunto->arvore);
}

SET *set_uniao(SET *conjunto_A, SET *conjunto_B){
    if (conjunto_A != NULL && conjunto_B != NULL){
        SET *uniao = (SET *) malloc(sizeof(SET)); 

        if (uniao != NULL){
            uniao->arvore = AVL_uniao(conjunto_A->arvore, conjunto_B->arvore);

            if (uniao->arvore == NULL){
                free(uniao);
                uniao = NULL;
            }
        }

        return uniao;
    }

    return NULL;
}

SET *set_interseccao(SET *conjunto_A, SET *conjunto_B){
    if (conjunto_A != NULL && conjunto_B != NULL){
        SET *interseccao = (SET *) malloc(sizeof(SET));

        if (interseccao != NULL){
            interseccao->arvore = AVL_interseccao(conjunto_A->arvore, conjunto_B->arvore);

            if (interseccao->arvore == NULL){
                free(interseccao);
                interseccao = NULL;
            } 
        }

        return interseccao;
    }

    return NULL;
}