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

int getPeriodicoManual (tavl *indice, char *arquivo) {
  periodico p;
  int arquivoInexistente = 0;
  long int endereco;
  FILE* arq;

  if (strcmp (arquivo,"")) {
    printf("Favor informar um ISSN que deseja acrescentar na base: ");
    scanf("%d",&p.issn);
    printf("Favor informar o título desse períodico que deseja acrescentar na base: ");
    scanf("%d",&p.titulo);
    printf("Favor informar o estrato desse períodico que deseja acrescentar na base: ");
    scanf("%d",&p.estrato);
    if (!busca (*indice, p.issn)) {
      if((arq=fopen(arquivo,"rb+"))==NULL){
          arquivoInexistente = 1;
          if((arq=fopen(arquivo,"wb+"))==NULL){
              perror("Erro na abertura do arquivo:");
              return 0;
          }
      }
      if( arquivoInexistente ){
            if( fwrite(&p, sizeof(p), 1, arq) )
                printf("Gravacao de %d periodicos realizada com sucesso!\n", 1);
      inserir(indice, p.issn, (endereco = ftell(arq))-sizeof(p));
      }
    }else{
      printf("ISSN não pode ser inserido: Já existente na base!\n");
    }
  }else {
    printf("Favor informar o enderço do arquivo que deseja criar uma base: ");
    scanf("%d",*arquivo);

    if (strcmp (arquivo,"")) {
      printf("Favor informar um ISSN que deseja acrescentar na base: ");
      scanf("%d",&p.issn);
      printf("Favor informar o título desse períodico que deseja acrescentar na base: ");
      scanf("%d",&p.titulo);
      printf("Favor informar o estrato desse períodico que deseja acrescentar na base: ");
      scanf("%d",&p.estrato);
      if (!busca (*indice, p.issn)) {
        if((arq=fopen(arquivo,"rb+"))==NULL){
            arquivoInexistente = 1;
            if((arq=fopen(arquivo,"wb+"))==NULL){
                perror("Erro na abertura do arquivo:");
                return 0;
            }
        }
        if( arquivoInexistente ){
              if( fwrite(&p, sizeof(p), 1, arq) )
                  printf("Gravacao de %d periodicos realizada com sucesso!\n", 1);
        inserir(indice, p.issn, (endereco = ftell(arq))-sizeof(p));
        }
      }else{
        printf("ISSN não pode ser inserido: Já existente na base!\n");
      }
    }
    printf("\nTESTE \n");
    getchar();
  }
  return 1;
}
