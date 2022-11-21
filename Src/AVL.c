#include "AVL.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct no NO;

struct no{
    ITEM *item;
    NO *esquerda;
    NO *direita;
    int altura;
};

struct avl{
    NO *raiz;
    int profundidade;
};

void AVL_copiar_no(AVL *arvore, AVL *copia, NO *raiz);
void AVL_uniao_no(AVL *arvore, NO *raiz);
void AVL_interseccao_no(AVL *interseccao, AVL *arvore_B, NO *raiz);

AVL *AVL_criar(void){
    AVL *arvore = (AVL *) malloc(sizeof(AVL));

    if (arvore != NULL){
        arvore->raiz = NULL;
        arvore->profundidade = -1;
    }

    return arvore;
}

void AVL_apagar_aux(NO ** raiz){
    if(*raiz != NULL){
        AVL_apagar_aux(&((*raiz)->esquerda));
        AVL_apagar_aux(&((*raiz)->direita));
        item_apagar(&(*raiz)->item);
        free(*raiz);
        *raiz = NULL;
    }
}

void AVL_apagar(AVL **arvore){
    if (*arvore != NULL){
        AVL_apagar_aux(&(*arvore)->raiz);
        free(*arvore);
        *arvore = NULL;
    }
}

int no_altura(NO * no){
    if(no == NULL)
        return -1;
    return no->altura;
}

NO *AVL_criar_no(ITEM *item){
    NO *no = (NO *) malloc(sizeof(NO));

    if (no != NULL){
        no->item = item;
        no->esquerda = NULL;
        no->direita = NULL;
        no->altura = 0;
    }

    return no;
}

void avl_apaga_no(NO ** no){
    item_apagar(&(*no)->item);
    free(*no);
    *no = NULL;
}

NO * rodar_direita(NO *a){
    NO * b = a->esquerda;
    a->esquerda = b->direita;
    b->direita = a;

    a->altura = max(no_altura(a->esquerda), no_altura(a->direita)) + 1;
    b->altura = max(no_altura(b->esquerda), a->altura) + 1;

    return b;
}

NO * rodar_esquerda(NO *a){
    NO * b = a->direita;
    a->direita = b->esquerda;
    b->esquerda = a;

    a->altura = max(no_altura(a->esquerda), no_altura(a->direita)) + 1;
    b->altura = max(a->altura, no_altura(b->direita)) + 1;

    return b;
}

NO * rodar_esquerda_direita(NO * a){
    a->esquerda = rodar_esquerda(a->esquerda);
    return rodar_direita(a);
}

NO * rodar_direita_esquerda(NO * a){
    a->direita = rodar_direita(a->direita);
    return rodar_esquerda(a);
}

NO * avl_inserir_no(NO * raiz, ITEM * item){
    if(raiz == NULL)
        raiz = AVL_criar_no(item);
    else if(item_get_chave(item) < item_get_chave(raiz->item))
        raiz->esquerda = avl_inserir_no(raiz->esquerda, item);
    else if(item_get_chave(item) > item_get_chave(raiz->item))
        raiz->direita = avl_inserir_no(raiz->direita, item);
    
    raiz->altura = max(no_altura(raiz->esquerda), no_altura(raiz->direita)) + 1;

    if(no_altura(raiz->esquerda) - no_altura(raiz->direita) == -2)
        if(item_get_chave(item) > item_get_chave(raiz->direita->item))
            raiz = rodar_esquerda(raiz);
        else
            raiz = rodar_direita_esquerda(raiz);
    
    if(no_altura(raiz->esquerda) - no_altura(raiz->direita) == 2)
        if(item_get_chave(item) < item_get_chave(raiz->esquerda->item))
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);

    return raiz;
}

bool AVL_inserir(AVL * avl, ITEM * item){
    return ((avl->raiz = avl_inserir_no(avl->raiz, item)) != NULL);
}

void troca_max_esq(NO * troca, NO * raiz, NO * ant){

    if(troca->direita != NULL){
        troca_max_esq(troca->direita, raiz, troca);
        return;
    }
    if(raiz == ant)
        ant->esquerda = troca->esquerda;
    else
        ant->direita = troca->esquerda;

    item_apagar(&(raiz->item));
    raiz->item = troca->item;
    free(troca);
    troca = NULL;
}

NO * avl_remover_no(NO ** raiz, ITEM * item){
    NO * aux;

    if(*raiz == NULL)
        return NULL;
    else if(item_get_chave(item) == item_get_chave((*raiz)->item)){

        if((*raiz)->esquerda == NULL|| (*raiz)->direita == NULL){
            aux = *raiz;
            if((*raiz)->esquerda == NULL)
                *raiz = (*raiz)->direita;
            else
                *raiz = (*raiz)->esquerda;
            avl_apaga_no(&aux);
        }

        else
            troca_max_esq((*raiz)->esquerda, (*raiz), (*raiz));
    }
    else if(item_get_chave(item) < item_get_chave((*raiz)->item))
        (*raiz)->esquerda = avl_remover_no(&(*raiz)->esquerda, item);
    else if(item_get_chave(item) > item_get_chave((*raiz)->item))
        (*raiz)->direita = avl_remover_no(&(*raiz)->direita, item);

    if(*raiz != NULL){
        (*raiz)->altura = max(no_altura((*raiz)->esquerda),no_altura((*raiz)->direita)) + 1;
        if(no_altura((*raiz)->esquerda) - no_altura((*raiz)->direita) == -2){
            if(no_altura((*raiz)->direita->esquerda) - no_altura((*raiz)->direita->direita) <= 0){
                *raiz = rodar_esquerda(*raiz);
            }
            else{
                *raiz = rodar_direita_esquerda(*raiz);
            }
        }
        if(no_altura((*raiz)->esquerda) - no_altura((*raiz)->direita) == 2){
            if(no_altura((*raiz)->esquerda->direita) - no_altura((*raiz)->esquerda->direita) >= 0){
                *raiz = rodar_direita(*raiz);
            }
            else{
                *raiz = rodar_esquerda_direita(*raiz);
            }
        }
    }

    return *raiz;
}

bool AVL_remover(AVL *arvore, ITEM *item){
    return ((arvore->raiz = avl_remover_no(&arvore->raiz, item)) != NULL);
}

ITEM *AVL_busca_no(NO *raiz, ITEM *item){
    if (raiz == NULL)
        return NULL;
    if (item_get_chave(item) == item_get_chave(raiz->item))
        return raiz->item;

    if (item_get_chave(item) < item_get_chave(raiz->item))
        return AVL_busca_no(raiz->esquerda, item);
    else
        return AVL_busca_no(raiz->direita, item);
}

ITEM *AVL_busca(AVL *arvore, ITEM * item){
    return AVL_busca_no(arvore->raiz, item);
}



void AVL_em_ordem_no(NO * no){
    if(no != NULL){
        AVL_em_ordem_no(no->esquerda);
        printf("%d ", item_get_chave(no->item));
        AVL_em_ordem_no(no->direita);
    }

}

void AVL_em_ordem(AVL *arvore){
    if (arvore != NULL){
        AVL_em_ordem_no(arvore->raiz);
        putchar('\n');
    }
}

void AVL_pre_ordem_no(NO *no){
    if (no != NULL){
        printf("%d(", item_get_chave(no->item));
        AVL_pre_ordem_no(no->esquerda);
        printf(",");
        AVL_pre_ordem_no(no->direita);
        printf(")");
    }
    else
        printf("_");
}

void AVL_pre_ordem(AVL *arvore){
    if (arvore != NULL){
        AVL_pre_ordem_no(arvore->raiz);
        putchar('\n');
    }
}

AVL *AVL_copiar(AVL *arvore){
    AVL *copia = AVL_criar();
    AVL_copiar_no(arvore, copia, arvore->raiz);
    return copia;
}

void AVL_copiar_no(AVL *arvore, AVL *copia, NO *raiz){
    if (raiz != NULL){ // Em-ordem
        AVL_inserir(copia, item_criar(item_get_chave(raiz->item)));
        AVL_copiar_no(arvore, copia, raiz->esquerda);
        AVL_copiar_no(arvore, copia, raiz->direita);
    }
}

AVL *AVL_uniao(AVL *arvore_A, AVL *arvore_B){
    if (arvore_A != NULL && arvore_B != NULL){
        AVL *uniao = AVL_copiar(arvore_A);

        if (uniao != NULL)
            AVL_uniao_no(uniao, arvore_B->raiz);

        if (uniao->raiz != NULL)
            return uniao;
        else{
            AVL_apagar(&uniao);
            uniao = NULL;
        }
            
    }  

    return NULL;
}

void AVL_uniao_no(AVL *uniao, NO *raiz){
    if (raiz != NULL){ // Em-ordem
        if (AVL_busca(uniao, raiz->item) == NULL)
            AVL_inserir(uniao, item_criar(item_get_chave(raiz->item)));
        AVL_uniao_no(uniao, raiz->esquerda);
        AVL_uniao_no(uniao, raiz->direita);
    }
}

AVL *AVL_interseccao(AVL *arvore_A, AVL *arvore_B){
    if (arvore_A != NULL && arvore_B != NULL){
        AVL *interseccao = AVL_criar();

        if (interseccao != NULL)
            AVL_interseccao_no(interseccao, arvore_B, arvore_A->raiz);
        
        if (interseccao->raiz != NULL)
            return interseccao;
        else{
            AVL_apagar(&interseccao);
            interseccao = NULL;
        }
            
    }

    return NULL;
}

void AVL_interseccao_no(AVL *interseccao, AVL *arvore_B, NO *raiz){
    if (raiz != NULL){
        if (AVL_busca(arvore_B, raiz->item) != NULL)
            AVL_inserir(interseccao, item_criar(item_get_chave(raiz->item)));
        AVL_interseccao_no(interseccao, arvore_B, raiz->esquerda);
        AVL_interseccao_no(interseccao, arvore_B, raiz->direita);
    }  
}
