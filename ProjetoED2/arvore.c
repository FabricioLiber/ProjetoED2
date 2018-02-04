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

tavl busca(tavl T, telem dado){
  if (T == NULL) return NULL;
  if (T->info == dado) return T;
  if (T->info > dado)
    return busca(T->esq, dado);
  else
    return busca(T->dir, dado);
}

void exibir (tavl T){
  if (T != NULL) {
    exibir (T->esq);
    printf ("%d ",T->info);
    exibir (T->dir);
  }
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

int inserir(tavl *T, telem item){

  int ok;
  if (*T == NULL) {
    *T = (tno *) malloc(sizeof(tno));
    if (*T == NULL) return 0;
      (*T)->esq = NULL;
    (*T)->dir = NULL;
    (*T)->info = item;
    (*T)->bal = 0;
    return 1;
  }

  if ((*T)->info > item) { /* recursividade à esquerda */
    ok = inserir (&((*T)->esq), item);
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
      ok = inserir (&((*T)->dir), item);
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
