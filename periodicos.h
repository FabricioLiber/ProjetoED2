#include "arvore.h"
#define TAM 51 /* Tamanho da string */

typedef struct {
    int issn; /* identificador �nico da publica��o seriada*/
    char titulo[TAM]; /* titulo do periodico */
    char estrato[3]; /* Estrato: A1, A2, B1, B2, B3, B4, B5, C */
} periodico;

void exibir (tavl T, char *arquivotxt,char *arquivobin);
int printIndice (tavl avlIndice, char *arquivotxt, char *arquivobin);
int pushPeriodico (tavl *avlIndice, char *arquivo, periodico p, char *arquivolog);
int getPeriodicoManual (tavl *avlIndice, char *arquivo, char* arquivolog);
void imprimePeriodico (periodico p);
void listar(char *arquivo, tavl avlIndice);
void otimizar(char *arquivo, tavl avlIndice);
void carregaIndice (char *arquivo, tavl *avlIndice);
void importarCSV(char *enderecoCSV, char *arquivo,tavl *avlIndice,char* arquivolog);
periodico consultaPeriodico (tavl avlIndice, char *arquivo, int ISSN);
int validaISSN (char *issn, char*arquivolog);
void converteStringIssn (int issn, char * issntxt);
void validaTitulo (char *titulo);
int validaEstrato (int issn,char *estrato, char* arquivolog);
void horaagora(char* hora);
void excecaoString (char *string, char *issn, char *titulo, char* estrato);
