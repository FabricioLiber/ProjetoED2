#include "arvore.h"
#define TAM 51 /* Tamanho da string */

typedef struct {
    int issn; /* identificador �nico da publica��o seriada*/
    char titulo[TAM]; /* titulo do periodico */
    char estrato[3]; /* Estrato: A1, A2, B1, B2, B3, B4, B5, C */
} periodico;

void exibir (tavl T, char *arquivotxt,char *arquivobin,char tipo);
int printIndice (tavl indice, char *arquivotxt, char *arquivobin,char tipo);
int pushPeriodico (tavl *indice, char *arquivo, periodico p, char *arquivolog);
int getPeriodicoManual (tavl *indice, char *arquivo, char* arquivolog);
void imprimePeriodico (periodico p);
void listar(char *arquivo, tavl indice);
void otimizar(char *arquivo, tavl indice);
void carregaIndice (char *arquivo, tavl *indice);
void importarCSV(char *enderecoCSV, char *arquivo,tavl *indice,char* arquivolog);
periodico consultaPeriodico (tavl indice, char *arquivo, int ISSN);
int validaISSN (char *issn, char*arquivolog);
void converteStringIssn (int issn, char * issntxt);
void validaTitulo (char *titulo);
int validaEstrato (int issn,char *estrato, char* arquivolog);
void horaagora(char* hora);
void quebraStringComDelimitador (char *str, char *issn, char *titulo, char* estrato, char delimitador);
double tempoExecucao (clock_t temp[]);
