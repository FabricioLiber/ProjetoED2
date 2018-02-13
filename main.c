#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "periodicos.h"
#define ARQ_BINARIO "periodicos.bin"
#define ARQ_EXPORT_INDICE "indice.txt"

void pausaLinux () {
  printf("\nPressione ENTER \n");
  getchar();
}

int main(){

  char opcao='w', enderecoCSV[30];
  int issn,teste;
  tavl indice, enderecoArquivo;

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
             printf("(t) Exibir Tamanaho da Árvore do índice\n");
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
            importarCSV (enderecoCSV,ARQ_BINARIO,&indice);
            getchar();
            pausaLinux ();
            break;
        }
        case 'p': {
            printIndice(indice, ARQ_EXPORT_INDICE);
            pausaLinux ();
            break;
        }
        case 'a': {
            getPeriodicoManual (&indice, ARQ_BINARIO);
            getchar();
            pausaLinux ();
            break;
        }
        case 'c': {
            printf("Favor informar um ISSN que deseja CONSULTAR na base: ");
            scanf("%d",&issn);
            enderecoArquivo =  busca (indice, issn);
            if (enderecoArquivo) {
              printf("Endereço no arquivo %d  com sucesso!!!\n",enderecoArquivo->endereco);
            }else{
              printf("ISSN não pode ser CONSULTADO: Não existente na base!\n");
            }
            getchar();
            pausaLinux ();
            break;
          }
        case 'x': {
          printf("Favor informar um ISSN que deseja REMOVER da base: ");
          scanf("%d",&issn);
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
            printf("Lado esquerdo: %d\n",altura(indice->esq));
            printf("Lado direito: %d\n",altura(indice->dir));
            pausaLinux ();
            break;
        }
        case 's': {
            otimizar(ARQ_BINARIO,indice);
            return 0;
        }
    }
    opcao = 'w';
  }
}
