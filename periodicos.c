#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "periodicos.h"

void exibir (tavl T, char *arquivotxt, char *arquivobin){
  FILE *arq;
  char issntxt2[10]="";
  periodico p;

  if (T != NULL) {
    exibir (T->esq, arquivotxt, arquivobin);
    arq=fopen(arquivotxt,"a+");
    p = consultaPeriodico (T,arquivobin,T->info);
    converteStringIssn(T->info,issntxt2);
    fprintf(arq,"|     %s         |    %s    | %s |\n",issntxt2, p.titulo,p.estrato);
    fclose(arq);
    exibir (T->dir, arquivotxt, arquivobin);
  }
}

int printIndice (tavl indice, char *arquivotxt, char *arquivobin) {
  FILE *arq;

  otimizar(arquivobin,indice);//para que o arquivo fisico condiza com o indice que sera impresso
  arq=fopen(arquivotxt,"w+");

  fprintf(arq,"+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
  fprintf(arq,"|                    .::Tabela de índice::.                             |\n");
  fprintf(arq,"+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
  fprintf(arq,"|       ISSN            |          TÍTULO             |    ESTRATO      |\n");
  fprintf(arq,"+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");

  fclose(arq);
  exibir(indice,arquivotxt,arquivobin);
  printf("Arquivo de índice salvo em %s\n",arquivotxt);
}

void imprimePeriodico (periodico p){
  char issntxt[10]="";

  converteStringIssn(p.issn, issntxt);
  printf("\n*************************************\n");
  printf("\nISSN: %s", issntxt);
  printf("\nTítulo: %s", p.titulo);
  printf("\nEstrato: %s", p.estrato);
  printf("\n*************************************\n");
}

void listar(char *arquivo, tavl indice){
  periodico p;
  FILE *arq;
  arq = fopen(arquivo,"r");
  if (arq) {
    rewind(arq);
    while( fread(&p, sizeof(periodico),1,arq) == 1) { // Acesso sequencial às estruturas
      if (busca (indice, p.issn)) {
        imprimePeriodico(p);
      }
    }
  }else {
    printf("Arquivo vazio\n");
  }
}

int pushPeriodico (tavl *indice, char *arquivo, periodico p, char* arquivolog) {
  int arquivoInexistente = 1;
  long int endereco;
  FILE* arq;
  char hora[25]="";
  horaagora(hora);

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
    inserir(indice, p.issn, (endereco = ftell(arq))-sizeof(p));
    fclose(arq);
    //(arquivo,*indice);
    }
    return 1;
  }else{
    arq=fopen(arquivolog,"a+");
    fprintf(arq,"%s ",hora);
    fprintf(arq,"ISSN %d não pode ser inserido: Já existente na base!\n", p.issn);
    fclose(arq);
    return 0;
  }
}

int getPeriodicoManual (tavl *indice, char *arquivo, char* arquivolog) {
  periodico p;
  char temp[100]="";
  int issn;

  printf("Favor informar um ISSN que deseja acrescentar na base: ");
  scanf("%s",temp);
  issn = validaISSN(temp,arquivolog);
  if (issn) {
    p.issn = issn;
    printf("Favor informar o título desse períodico que deseja acrescentar na base: ");
    scanf("%s",temp);
    validaTitulo(temp);
    strcpy(p.titulo,temp);
    printf("Favor informar o estrato desse períodico que deseja acrescentar na base: ");
    scanf("%s",p.estrato);
    if (pushPeriodico (indice, arquivo,p,arquivolog)){
      printf("Gravacao do ISSN %d realizada com sucesso!\n", p.issn);
      return 1;
    }else {
      printf("ISSN %d não pode ser inserido: Já existente na base!\n", p.issn);
      return 0;
    }
  }else {
    printf("Favor informar o ISSN em um formato aceito: ");
    printf("O ISSN é composto por oito dígitos distribuídos em dois grupos de quatro dígitos cada, separados por um hífen. Exemplo: ISSN 1018-4783.\n");
    return 0;
  }
}

void otimizar(char *arquivo, tavl indice){
    periodico p;
    char arquivoTemp[10] = "temp.bin";
    FILE *arq,*arqTemp;
    arq = fopen(arquivo,"r");

    if (arq) {
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

void importarCSV(char *enderecoCSV, char *arquivo,tavl *indice, char* arquivolog) {
  FILE *import;
  char r[145]="", temp[145]="";
  char *pointer;
  int issnValido,j=0,i=0;
  periodico p;

  import = fopen(enderecoCSV,"r");

  if (import) {
    while(fgets(r, 151, import) != NULL) {
      pointer = strtok(r,",");
      strcpy(temp,pointer);
      issnValido = validaISSN(temp,arquivolog);
      if (issnValido) {
        p.issn = issnValido;
        pointer = strtok(NULL,",");
        strcpy(temp,pointer);
        strcpy(temp,validaTitulo(temp));
        strcpy(p.titulo,temp);
        pointer = strtok(NULL,",");
        strcpy(temp,pointer);
        if (validaEstrato(p.issn,temp,arquivolog)){
          strcpy(p.estrato,temp);
          pushPeriodico(indice,arquivo,p,arquivolog) ? i++:j++;
        }
      }
      j++;
    }
    fclose(import);
    printf("Números de períodicos importados: %d\n", i);
    printf("Números de períodicos com falha na importação: %d\n", j-1-i);
  }
}

periodico consultaPeriodico (tavl indice, char *arquivo, int issn) {
  periodico p;
  tavl indPeriodico;
  long int endereco;
  FILE *arq;

  indPeriodico = busca(indice, issn);
  if (indPeriodico != NULL) {
    endereco = indPeriodico->endereco;

    arq = fopen(arquivo,"r");

    fseek (arq, endereco,SEEK_SET);
    fread (&p,sizeof(p),1,arq);

    fclose(arq);
  }else {
      p.issn = 0;
  }
  return p;
}

int validaISSN (char *issn, char* arquivolog) {
  int i,j,tam,teste=1, numISSN;
  char temp[10]="";
  FILE* arq;
  char hora[25]="";
  horaagora(hora);

  for (i = 0; i < strlen(issn); i++) {
    if (!isdigit(issn[i])&&i!=4) teste = 0;
  }

  if ((strchr(issn,'-')-issn)==4&&strlen(issn)==9&&teste==1) {
    tam = strlen(issn);
    for (i=0,j=0;i<tam;i++) {
      if (i!=4){
        temp[j]=issn[i];
        j++;
      }
    }
    numISSN = atoi(temp);
    return numISSN;
  }else{
    arq=fopen(arquivolog,"a+");
    fprintf(arq,"%s ",hora);
    fprintf(arq,"ISSN %s não é valido.",issn);
    fprintf(arq,"Favor informar o ISSN em um formato aceito: ");
    fprintf(arq,"O ISSN é composto por oito dígitos distribuídos em dois grupos de quatro dígitos cada, separados por um hífen. Exemplo: ISSN 1018-4783.\n");
    fclose(arq);
    return 0;
  }
}

void converteStringIssn (int issn, char * issntxt){
//adaptado - https://pt.stackoverflow.com/questions/260415/convertendo-int-em-string

    char temp;
    int i =0;
    while (issn > 0) {
        int digito = issn % 10;
        issntxt[i] = digito + '0';
        issn /= 10;
        i++;
    }
   i = 0;
   int j = strlen(issntxt) - 1;

   while (i < j) {
      temp = issntxt[i];
      issntxt[i] = issntxt[j];
      issntxt[j] = temp;
      i++;
      j--;
   }

   i = strlen(issntxt);
   j = i-4;
   for(i;i>j;i--) {
     issntxt[i] = issntxt[i-1];
   }
   issntxt[j] = '-';
}

char* validaTitulo (char *titulo) {
  int indice;
  char temp[TAM]="";

  if (strlen(titulo)>TAM) {
    strncpy(temp,titulo,41);
    strcat(temp," .trunc");
    strcpy(titulo,temp);
    return titulo;
  }else{
    return titulo;
  }
}

int validaEstrato (int issn, char *estrato, char* arquivolog) {
  FILE* arq;
  char hora[25]="";
  horaagora(hora);

  if (strlen(estrato)>3) {
    arq=fopen(arquivolog,"a+");
    fprintf(arq,"%s ",hora);
    fprintf(arq,"ISSN %d não importado, estrato inválido\n",issn);
    fclose(arq);
    return 0;
  }else{
    return 1;
  }
}

void horaagora (char* hora) {
//adptado de - https://pt.stackoverflow.com/questions/158195/como-pegar-hora-do-sistema-e-guardar-em-uma-vari%C3%A1vel
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  strcpy(hora,asctime(timeinfo));
}
