#include "arvore.h"
#define TAM 51 /* Tamanho da string */

typedef struct {
    int issn; /* identificador �nico da publica��o seriada*/
    char titulo[TAM]; /* titulo do periodico */
    char estrato[3]; /* Estrato: A1, A2, B1, B2, B3, B4, B5, C */
} periodico;

int printIndice (tavl indice);
int pushPeriodico (tavl *indice, char *arquivo,FILE* arq, periodico p);
int getPeriodicoManual (tavl *indice, char *arquivo, FILE* arq);
void listar(FILE *arq);
