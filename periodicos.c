#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "periodicos.h"

void exibir (tavl T, char *arquivotxt){
  FILE *arq;


  if (T != NULL) {
    exibir (T->esq, arquivotxt);
    arq=fopen(arquivotxt,"a+");
    fprintf(arq,"|       %10.d  |               %d             |\n",T->info, T->endereco);
    fclose(arq);
    exibir (T->dir, arquivotxt);
  }
}

int printIndice (tavl indice, char *arquivotxt) {
  FILE *arq;

  arq=fopen(arquivotxt,"w+");

  fprintf(arq,"+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
  fprintf(arq,"|                    .::Tabela de índice::.                             |\n");
  fprintf(arq,"+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
  fprintf(arq,"|          ISSN         |               ENDEREÇO                        |\n");
  fprintf(arq,"+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");

  fclose(arq);
  exibir(indice,arquivotxt);
  exibirOrdemCrescente(indice);
  printf("Arquivo de índice salvo em %s\n",arquivotxt);
}

void listar(char *arquivo, tavl indice){
  periodico p;
  FILE *arq;
  arq = fopen(arquivo,"r");
  if (arq) {
    rewind(arq);
    while( fread(&p, sizeof(periodico),1,arq) == 1) { // Acesso sequencial às estruturas
        if (busca (indice, p.issn)) {
          printf("\n*************************************\n");
          printf("\nISSN: %ld", p.issn);
          printf("\nTítulo: %s", p.titulo);
          printf("\nEstrato: %s", p.estrato);
          printf("\n*************************************\n");
        }
    }
  }else {
    printf("Arquivo vazio\n");
  }
}

int pushPeriodico (tavl *indice, char *arquivo, periodico p) {
  int arquivoInexistente = 1;
  long int endereco;
  FILE* arq;

  if (!busca (*indice, p.issn)) {
    if((arq=fopen(arquivo,"ab+"))==NULL){
        arquivoInexistente = 0;
        if((arq=fopen(arquivo,"wb+"))==NULL){
            perror("Erro na abertura do arquivo:");
            return 0;
        }
    }
    if( arquivoInexistente ){
          if( fwrite(&p, sizeof(p), 1, arq) )
              printf("Gravacao do ISSN %d realizada com sucesso!\n", p.issn);
    inserir(indice, p.issn, (endereco = ftell(arq))-sizeof(p));
    fclose(arq);
    }
  }else{
    printf("ISSN %d não pode ser inserido: Já existente na base!\n", p.issn);
  }
  return 1;
}

int getPeriodicoManual (tavl *indice, char *arquivo) {
  periodico p;

  printf("Favor informar um ISSN que deseja acrescentar na base: ");
  scanf("%d",&p.issn);
  printf("Favor informar o título desse períodico que deseja acrescentar na base: ");
  scanf("%s",p.titulo);
  printf("Favor informar o estrato desse períodico que deseja acrescentar na base: ");
  scanf("%s",p.estrato);
  pushPeriodico (indice, arquivo,p);
  return 1;
}

void otimizar(char *arquivo, tavl indice){
    periodico p;
    char arquivoTemp[10] = "temp.bin";
    FILE *arq,*arqTemp;
    arq = fopen(arquivo,"r");

    if (arq) {
      rewind(arq);
      while( fread(&p, sizeof(periodico),1,arq) == 1) { // Acesso sequencial às estruturas
          if (busca (indice, p.issn)) {
            arqTemp = fopen(arquivoTemp,"ab+");
            fwrite(&p, sizeof(p), 1, arqTemp);
            fclose(arqTemp);
          }
      }
      fclose(arq);
      remove(arquivo);
      rename(arquivoTemp,arquivo);
    }
}

void carregaIndice (char *arquivo, tavl *indice){
    periodico p;
    FILE *arq;
    arq = fopen(arquivo,"r");
    long int endereco;

    if (arq) {
      rewind(arq);
      while( fread(&p, sizeof(periodico),1,arq) == 1) { // Acesso sequencial às estruturas
        inserir(indice, p.issn, (endereco = ftell(arq))-sizeof(p));
      }
    }
}

void importarCSV(char *enderecoCSV, char *arquivo,tavl *indice) {
  FILE *import;
  char r[99], temp[99];
  char *pointer;
  periodico p;

  import = fopen(enderecoCSV,"r");

  if (import) {
    while(fgets(r, 100, import) != NULL) {
      pointer = strtok(r,",");
      strcpy(temp,pointer);
      p.issn = atoi(temp);
      pointer = strtok(NULL,",");
      strcpy(p.titulo,pointer);
      pointer = strtok(NULL,",");
      strcpy(p.estrato,pointer);
      pushPeriodico(indice,arquivo,p);
    }
    fclose(import);
  }
}
