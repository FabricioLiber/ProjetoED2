#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  int i, issn = 12345678,temp;
  char issntxt[10] ="";

  temp = issn;
  sprintf(issntxt,"%d",issn);

  for(i=10;i>3;i--) {
    issntxt[i] = issntxt[i-1];
  }
  issntxt[4] = '-';

  printf("%s\n",issntxt );
  printf("%d\n",issn);
  printf("%d\n",temp);


  return 0;
}
