#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // Utilizada pelo tolower()
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

  char opcao='w', enderecoCSV[30], issntxt[10];
  int issn;
  tavl avlIndice;
  periodico p;

  criar(&avlIndice);
  carregaIndice(ARQ_BINARIO, &avlIndice);

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
            importarCSV (enderecoCSV,ARQ_BINARIO,&avlIndice,ARQ_LOG);
            getchar();
            pausaLinux ();
            break;
        }
        case 'p': {
            printIndice(avlIndice, ARQ_EXPORT_INDICE, ARQ_BINARIO);
            pausaLinux ();
            break;
        }
        case 'a': {
            getPeriodicoManual (&avlIndice, ARQ_BINARIO, ARQ_LOG);
            getchar();
            pausaLinux ();
            break;
        }
        case 'c': {
            printf("Favor informar um ISSN que deseja CONSULTAR na base: ");
            scanf("%s",issntxt);
            issn = validaISSN(issntxt, ARQ_LOG);
            p = consultaPeriodico(avlIndice,ARQ_BINARIO,issn);
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
          if (busca (avlIndice, issn)) {
            removerBalanceado(&avlIndice, issn);
            printf("Valor %d REMOVIDO com sucesso!!!\n",issn);
          }else{
            printf("ISSN não pode ser removido: Não existente na base!\n");
          }
          getchar();
          pausaLinux ();
          break;
        }
        case 'e': {
            esvaziar(&avlIndice);
            printf("Todos os periódicos eliminados com sucesso!!!!\n");
            pausaLinux ();
            remove(ARQ_LOG);
            break;
        }
        case 'f': {
            vazia(avlIndice) ? printf("Tabela de índice vazia!!!\n") : exibirArvore(avlIndice);
            pausaLinux ();
            break;
        }
        case 'l': {
            listar(ARQ_BINARIO,avlIndice);
            pausaLinux ();
            break;
        }
        case 'o': {
            otimizar(ARQ_BINARIO,avlIndice);
            printf("Arquivo otimizado fisicamento com sucesso!!!!\n");
            pausaLinux ();
            break;
        }
        case 't': {
            if(!vazia(avlIndice)) {
              printf("Altura lado esquerdo: %d\n",altura(avlIndice->esq));
              printf("Altura lado direito: %d\n",altura(avlIndice->dir));
            }else{
              printf("Indice Vazio\n");
            }
            pausaLinux ();
            break;
        }
        case 's': {
            otimizar(ARQ_BINARIO,avlIndice);
            remove(ARQ_LOG);
            remove(ARQ_EXPORT_INDICE);
            return 0;
        }
    }
    opcao = 'w';
  }
}
