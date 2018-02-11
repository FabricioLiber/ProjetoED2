#include<stdio.h>
#include "periodicos.h"

int printIndice (tavl indice) {

  printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
  printf("|                    .::Tabela de índice::.                             |\n");
  printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
  printf("|          ISSN         |               ENDEREÇO                        |\n");
  printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");

  exibir(indice);
}
