/* Usando estruturas em C 
  By: zDragonsk

  O uso de limpar buffer de saida em todos os scanfs se deve ao fato que quando usamos %[] por motivos que não irei aprofundar, o proximo scanf (pedido por uma entrada) o programa pode acabar saindo nem preencher o valor ou até mesmo repetir o valor.

*/

// Headers
#include <stdio.h>
#include <stdlib.h>

struct registro{ // Gerando a estrutura
  char nome[101];
  int idade;
  char profissao[101];
}; // É importante que tenha ";" no fim do bloco da estrutura

// Blocos
int main(void){
  struct registro pessoa; // Declarando o objeto usando a struct
  
  printf("Digite seu nome: ");
  scanf("%[^\n]", &pessoa.nome); // Lendo string com espaço
  // Limpando buffer de entrada (essencial para usar %^[]
  setbuf(stdin, NULL);

  printf("\nIdade: ");
  scanf("%i", &pessoa.idade); // Lendo valor para idade 
  setbuf(stdin, NULL); // Ao usar o %[] acima vai precisar 

  printf("\nProfissão: ");
  scanf("%[^\n]", &pessoa.profissao); // Lendo valor para profissão
  setbuf(stdin, NULL); // Novamente teremos que usar

  // Imprimindo os valores usados
  printf("\nSeu nome é %s e você tem %i anos trabalhando com %s!\n", pessoa.nome, pessoa.idade, pessoa.profissao);

  return 0;
}
