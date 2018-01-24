#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
char opcao='w';

for (;;) {
    while (!strchr("ipacxels", opcao)) {
             system("cls");
             printf("Indexação de periódicos v1.1\n");
             printf("=====================================\n");
             printf("(i) Importar arquivo CSV\n");
             printf("(p) Exportar tabela de índice\n");
             printf("(a) Adiconar manualmente um períodico\n");
             printf("(c) Consultar um periódico\n");
             printf("(x) Excluir um períodico\n");
             printf("(e) Eliminar todos os períodos\n");
             printf("(l) Listar Dados\n");
             printf("(s) Sair\n");
             printf("=====================================\n");
             printf("Favor informar uma opcao valida:[ ]\b\b");
             scanf("%[^\n]c",&opcao);
             getchar();
             opcao = tolower(opcao);
         }

    switch (opcao) {
        case 'i': {
            printf("Funçao (i) menu ok");
            system("pause");
            break;
        }
        case 'p': {
            printf("Funçao (p) menu ok");
            system("pause");
            break;
        }
        case 'a': {
            printf("Funçao (a) menu ok");
            system("pause");
            break;
        }
        case 'c': {
            printf("Funçao (c) menu ok");
            system("pause");
            break;
        }
        case 'x': {
            printf("Funçao (x) menu ok");
            system("pause");
            break;
        }
        case 'e': {
            printf("Funçao (e) menu ok");
            system("pause");
            break;
        }
        case 'l': {
            printf("Funçao (l) menu ok");
            system("pause");
            break;
        }
        case 's': {
            return 0;
        }
    }
    opcao = 'w';
  }
}
