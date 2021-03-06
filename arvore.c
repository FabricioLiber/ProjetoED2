#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void criar (tavl *T){
  *T = NULL;
}

int vazia (tavl T){
  return (T == NULL);
}

int quantidadeNos (tavl T) {

    if(T == NULL)
        return 0;
   else
        return quantidadeNos(T->esq) +1+ quantidadeNos(T->dir);
}


void exibirOrdemCrescente (tavl T){

  if (T != NULL) {
    exibirOrdemCrescente (T->esq);
    printf("%d ",T->info);
    exibirOrdemCrescente (T->dir);
  }
}

tavl busca(tavl T, telem dado){
  if (T == NULL) return NULL;
  if (T->info == dado) return T;
  if (T->info > dado)
    return busca(T->esq, dado);
  else
    return busca(T->dir, dado);
}

void imprimirEspacos(int x){
    int i;
	for (i = 0; i < x; ++i){
		printf(" ");
	}
}

int numeroDeEspacos(int x){
	int i, j = 1;
	for (i = 0; i < x; ++i){
		j = j*2;
	}
	j--;
	return j;
}

int pw(int x, int y){
	if(y == 0){
		return 1;
	}
	int i, r = 1;
	for (i = 0; i < y; ++i){
		r = r * x;
	}
	return r;
}

void imprimirNivel(tavl T, int nivel, int n){
	if (nivel == 0){
		imprimirEspacos(n);
		if(T != NULL){
        	printf("%d", T->info);
    	}else{
        	printf("-");
    	}
		imprimirEspacos(n);
    }
    else{
    	if(T == NULL){
    		imprimirNivel(NULL, nivel - 1, n);
    	}else{
	        imprimirNivel(T->esq, nivel - 1, n);
    	}
        printf(" ");
        if(T == NULL){
	        imprimirNivel(NULL, nivel - 1, n);
        }else{
        	imprimirNivel(T->dir, nivel - 1, n);
        }
    }
}

void exibirArvore(tavl T){
	if(T == NULL){
		printf("Árvore vazia\n");
		return;
	}
    int i, j, k;
    int height = altura(T);
    for(i = 0; i < height; i++){
    	int n = numeroDeEspacos(height-i);
    	int t = numeroDeEspacos(height-i-1);
        imprimirNivel(T, i, n);
    	printf(" ");
        printf("\n");

        for (j = 0; j < t; j++){
        	int pw1 = pw(2,i);
        	for (k = 0; k < pw1; ++k){
	        	imprimirEspacos(n-j-1);
	        	printf("/");
	        	imprimirEspacos(j);
	        	imprimirEspacos(1);
	        	imprimirEspacos(j);
	        	printf("\\");
	        	imprimirEspacos(n-j-1);
        		printf(" ");

        	}
        	printf("\n");
        }
    }
	printf("\n");
}

void esvaziar(tavl *T){
  if (*T == NULL) return;
  esvaziar(&(*T)->esq);
  esvaziar(&(*T)->dir);
  free(*T);
  *T = NULL;
}

void rot_dir (tavl *T){
  tavl u;
  u = (*T)->esq;
  (*T)->esq = u->dir;
  u->dir = *T;
  (*T)->bal = 0;
  *T = u;
}

void rot_esq_dir (tavl *T){
  tavl u,v;
  u = (*T)->esq;
  v = u->dir;
  u->dir = v->esq;
  v->esq = u;
  (*T)->esq = v->dir;
  v->dir = *T;
  if (v->bal == -1)
    (*T)->bal = 1;
  else
    (*T)->bal = 0;
  if (v->bal == 1)
    u->bal = -1;
  else
    u->bal = 0;
  *T = v;
}

void rot_esq (tavl *T){
  tavl u;
  u = (*T)->dir;
  (*T)->dir = u->esq;
  u->esq = *T;
  (*T)->bal = 0;
  *T = u;
}

void rot_dir_esq (tavl *T){
  tavl u,v;
  u = (*T)->dir;
  v = u->esq;
  u->esq = v->dir;
  v->dir = u;
  (*T)->dir = v->esq;
  v->esq = *T;
  if (v->bal == 1)
    (*T)->bal = -1;
  else
    (*T)->bal = 0;
  if (v->bal == -1)
    u->bal = 1;
  else
    u->bal = 0;
  *T = v;
}

void caso1(tavl *T){
/* item foi inserido à esquerda de T e causa desbalanceamento FB(T)=-2 */

  tavl u;
  u = (*T)->esq;

  if (u->bal == -1)
    rot_dir(&(*T)); /* Caso 1.1 sinais iguais e negativo */
  else
    rot_esq_dir(&(*T)); /* Caso 1.2 sinais diferentes */

  (*T)->bal = 0;
}

void caso2(tavl *T){
/* item foi inserido à direita de T e causa desbalanceamento FB(T)=2 */
  tavl u;
  u = (*T)->dir;
  if (u->bal == 1)
    rot_esq(&(*T)); /* Caso 2.1 sinais iguais e positivo */
  else
    rot_dir_esq(&(*T)); /* Caso 2.2 sinais diferentes */
  (*T)->bal = 0;
}

int inserir(tavl *T, telem item, long int end){

  int ok;
  if (*T == NULL) {
    *T = (tno *) malloc(sizeof(tno));
    if (*T == NULL) return 0;
      (*T)->esq = NULL;
    (*T)->dir = NULL;
    (*T)->info = item;
    (*T)->endereco = end;
    (*T)->bal = 0;
    return 1;
  }

  if ((*T)->info > item) { /* recursividade à esquerda */
    ok = inserir (&((*T)->esq), item, end);
  if (ok)
    switch ((*T)->bal) { /* próxima raiz a se verificar o FB */
      case 1 : (*T)->bal = 0; /* era mais alto à direita, fica com FB=0 */
        ok = 0; /* interrompe propagação de balanceamento */
        break;
      case 0 : (*T)->bal = -1; /* ficou com a esquerda maior e propaga FB */
        break;
      case -1: caso1(&(*T)); /* FB(p)=-2 */
        ok = 0; /* nao propaga mais */
        break;
      }
  }
  else
    if ((*T)->info < item) { /* recursividade à direita */
      ok = inserir (&((*T)->dir), item, end);
    if (ok)
      switch ((*T)->bal) { /* próxima raiz a se verificar o FB */
        case -1: (*T)->bal = 0; /* era mais alto à esquerda, fica com FB=0 */
          ok = 0; /* interrompe propagação de balanceamento */
          break;
        case 0 : (*T)->bal = 1; /* ficou com a direita maior e propaga FB */
          break;
        case 1 : caso2(&(*T)); /* FB(p)=2 */
          ok = 0; /* nao propaga mais */
          break;
        }
    }
    else
      ok = 0;
    return ok;
}

int altura ( tavl T ){    /*retorna a altura da arvore*/
    int esq, dir;

    if ( T == NULL ) return 0;

    esq = altura ( T->esq );
    dir = altura ( T->dir );

    if ( esq > dir )
        return esq + 1;
    else
        return dir + 1;
}

tavl remover(tavl *T, int info){
	if((*T) == NULL){
		return NULL;
	}else{
		if((*T)->info > info){
			(*T)->esq = remover(&((*T)->esq), info);
		}else if((*T)->info < info){
			(*T)->dir = remover(&((*T)->dir), info);
		}else{
			if((*T)->esq == NULL && (*T)->dir == NULL){
				tavl aux = (*T);
				(*T) = NULL;
				free(aux);
			}else{
				if((*T)->esq == NULL){
					tavl aux = (*T);
					(*T) = (*T)->dir;
					free(aux);
				}else if((*T)->dir == NULL){
					tavl aux = (*T);
					(*T) = (*T)->esq;
					free(aux);
				}else{
					tavl aux = (*T)->esq;
					while(aux->dir != NULL){
						aux = aux->dir;
					}
					(*T)->info = aux->info;
					(*T)->esq = remover(&((*T)->esq), (*T)->info);
				}
			}
		}
	}
	return (*T);
}

tavl balRemove (tavl *T) {
  if((*T) == NULL){
		return NULL;
	}else{
    (*T)->bal = altura((*T)->dir)-altura((*T)->esq);
    balRemove (&(*T)->esq);
    balRemove (&(*T)->dir);
  }
}

void BalancRemove (tavl *T) {
  if ((*T)->bal>1) {
    caso2(&(*T));
    balRemove (&(*T));
  }
  if ((*T)->bal<-1) {
    caso1(&(*T));
    balRemove (&(*T));
  }
}

void removerBalanceado (tavl *T, int valor) {
  tavl aux;

  if((*T)->esq == NULL && (*T)->dir == NULL){
    tavl aux = (*T);
    (*T) = NULL;
    free(aux);
  }else {
    remover(&(*T),valor);
    balRemove(&(*T));
    BalancRemove (&(*T));
  }
}
