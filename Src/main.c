#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  SET * A, * B;
  int n_a, n_b, x;
  int op;

  A = set_criar();
  B = set_criar();

  n_a = 5;
  n_b = 3;
  int setA[5] = {1, 2, 3, 4, 5};
  int setB[3] = {7, 2, 8};
  
  op = 1;

  // scanf("%d %d", &n_a, &n_b);

  for(int i=0; i<n_a; i++){
    // scanf("%d",&x);
    set_inserir(A, setA[i]);

  }

  for(int i=0; i<n_b; i++){
    // scanf("%d",&x);
    set_inserir(B, setB[i]);

  }

  // scanf("%d", &op);
  
  switch(op){
    case 1: {
              int num;
              num = 6;
              // scanf("%d", &num);
              if(set_pertence(A,num)) 
                printf("Pertence.");
              else
                printf("Não Pertence.");
              break;
    }
    case 2: {
              SET *C = set_uniao(A,B);
              set_imprimir(C);
              set_apagar(&C);
              break;
    }
    case 3: {
              SET *C = set_interseccao(A, B);
              set_imprimir(C);
              set_apagar(&C);
              break;
    }
    case 4: { //Bônus
              int num;
              scanf("%d", &num);
              set_remover(A,num);
              set_imprimir(A); 
    }
  }

  set_apagar(&A);
  set_apagar(&B);
    
  return 0;
}
