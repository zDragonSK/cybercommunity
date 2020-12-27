/* Conversão de arrays de char(string) para INT */

#include <stdio.h>
#include <stdlib.h>

void main(void){
  char valor_str[] = "15"; // Valor em array de chars
  int valor = atoi(valor_str); // Convertendo o valor

  printf("Valor final: %i\n", valor); // Imprimindo valor

}
