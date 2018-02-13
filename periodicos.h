#include "arvore.h"
#define TAM 51 /* Tamanho da string */

typedef struct {
    int issn; /* identificador �nico da publica��o seriada*/
    char titulo[TAM]; /* titulo do periodico */
    char estrato[3]; /* Estrato: A1, A2, B1, B2, B3, B4, B5, C */
} periodico;

void exibir (tavl T, char *arquivotxt);
int printIndice (tavl indice, char *arquivotxt) ;
int pushPeriodico (tavl *indice, char *arquivo, periodico p);
int getPeriodicoManual (tavl *indice, char *arquivo);
void listar(char *arquivo, tavl indice);
void otimizar(char *arquivo, tavl indice);
void carregaIndice (char *arquivo, tavl *indice);
void importarCSV(char *enderecoCSV, char *arquivo,tavl *indice);
