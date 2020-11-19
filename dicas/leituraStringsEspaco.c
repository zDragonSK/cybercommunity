/*
 * Este é um exemplo do uso do %[] no C.
 * Este elemento no C, consegue ler um conjunto de chars
 * permitindo parar ao ler um char X ou apenas ler chars Y.
 *
 * Posso permitir que apenas GAP seja aceito usando %[gap] ou negar os mesmo usando %[^gap].
 * Também, é possivel limitar o tamanho da string desta forma; %60[^\n]
 * assim apenas 60 chars serão lidos.
 * Podemos ler "strings" com ESPAÇO usando %[^\n] assim a leitura só vai
 * acabar quando uma nova linha (enter) ser usada.
*/

// Headers
#include <stdio.h>

// Funçoes
int main(void){
  // Variaveis locais (automaticas)
  char name[21];
  
  // Source de leitura simples
  printf("Digite uma string de até 20 chars usando espaço.\n\nDigite um nome:\t ");
  
  scanf("%[^\n]", &name); // Ler strings com espaço
  
  setbuf(stdin, NULL); // Limpar o buffer (Neste caso é necessario por uso do %[]
  
  printf("\nDigitou; %s\n", name); // Imprimi o valor do ponteiro
  
  return 0;
}

