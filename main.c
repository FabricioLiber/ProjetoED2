#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "periodicos.h"
#define ARQ_BINARIO "periodicos.bin"
#define ARQ_EXPORT_INDICE "indice.txt"
#define ARQ_LOG "log.txt"


void pausaLinux () {
  printf("\nPressione ENTER \n");
  getchar();
}

int main(){

  char opcao='w', enderecoCSV[30],issntxt[10];
  int issn;
  tavl indice;
  periodico p;

  criar(&indice);
  carregaIndice(ARQ_BINARIO, &indice);

  for (;;) {
    while (!strchr("ipacxelofts", opcao)) {
             printf("\e[H\e[2J");
             system("cls");
             printf("Indexação de periódicos v1.0\n");
             printf("=====================================\n");
             printf("(i) Importar arquivo CSV\n");
             printf("(p) Exportar tabela de índice\n");
             printf("(a) Adiconar manualmente um períodico\n");
             printf("(c) Consultar um periódico\n");
             printf("(x) Excluir um períodico\n");
             printf("(e) Eliminar todos os períodos\n");
             printf("(l) Listar Dados\n");
             printf("(o) Otimizar espaço em disco\n");
             printf("(f) Exibir Árvore do índice\n");
             printf("(t) Exibir Altura da Árvore do índice\n");
             printf("(s) Sair\n");
             printf("=====================================\n");
             printf("Favor informar uma opcao valida:[ ]\b\b");
             scanf("%[^\n]c",&opcao);
             getchar();
             opcao = tolower(opcao);
         }

    switch (opcao) {
        case 'i': {
            printf("Favor informar o endereço do arquivo CSV: ");
            scanf("%s",enderecoCSV);
            importarCSV (enderecoCSV,ARQ_BINARIO,&indice,ARQ_LOG);
            getchar();
            pausaLinux ();
            break;
        }
        case 'p': {
            printIndice(indice, ARQ_EXPORT_INDICE, ARQ_BINARIO);
            pausaLinux ();
            break;
        }
        case 'a': {
            getPeriodicoManual (&indice, ARQ_BINARIO, ARQ_LOG);
            getchar();
            pausaLinux ();
            break;
        }
        case 'c': {
            printf("Favor informar um ISSN que deseja CONSULTAR na base: ");
            scanf("%s",issntxt);
            issn = validaISSN(issntxt, ARQ_LOG);
            p = consultaPeriodico(indice,ARQ_BINARIO,issn);
            if (p.issn) {
              imprimePeriodico(p);
            }else{
              printf("ISSN não pode ser CONSULTADO: Não existente na base!\n");
            }
            getchar();
            pausaLinux ();
            break;
          }
        case 'x': {
          printf("Favor informar um ISSN que deseja REMOVER da base: ");
          scanf("%s",issntxt);
          issn = validaISSN(issntxt, ARQ_LOG);
          if (busca (indice, issn)) {
            removerBalanceado(&indice, issn);
            printf("Valor %d REMOVIDO com sucesso!!!\n",issn);
          }else{
            printf("ISSN não pode ser removido: Não existente na base!\n");
          }
          getchar();
          pausaLinux ();
          break;
        }
        case 'e': {
            esvaziar(&indice);
            printf("Todos os periódicos eliminados com sucesso!!!!\n");
            pausaLinux ();
            remove(ARQ_LOG);
            break;
        }
        case 'f': {
            vazia(indice) ? printf("Tabela de índice vazia!!!\n") : exibirArvore(indice);
            pausaLinux ();
            break;
        }
        case 'l': {
            listar(ARQ_BINARIO,indice);
            pausaLinux ();
            break;
        }
        case 'o': {
            otimizar(ARQ_BINARIO,indice);
            printf("Arquivo otimizado fisicamento com sucesso!!!!\n");
            pausaLinux ();
            break;
        }
        case 't': {
            if(!vazia(indice)) {
              printf("Altura lado esquerdo: %d\n",altura(indice->esq));
              printf("Altura lado direito: %d\n",altura(indice->dir));
            }else{
              printf("Indice Vazio\n");
            }
            pausaLinux ();
            break;
        }
        case 's': {
            otimizar(ARQ_BINARIO,indice);
            remove(ARQ_LOG);
            remove(ARQ_EXPORT_INDICE);
            return 0;
        }
    }
    opcao = 'w';
  }
}
