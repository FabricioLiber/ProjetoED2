#include<stdio.h>
#include<string.h>
#include "periodicos.h"

int printIndice (tavl indice) {

  printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
  printf("|                    .::Tabela de índice::.                             |\n");
  printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
  printf("|          ISSN         |               ENDEREÇO                        |\n");
  printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");

  exibir(indice);
}

void listar(char *arquivo){
    periodico p;
    FILE *arq;
    arq = fopen(arquivo,"r");
    rewind(arq);
    while( fread(&p, sizeof(periodico),1,arq) == 1) { // Acesso sequencial às estruturas
        printf("\nissn %ld", p.issn);
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
              printf("Gravacao de %d periodicos realizada com sucesso!\n", 1);
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
