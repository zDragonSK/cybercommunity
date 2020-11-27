/*Este código é um exemplo do uso de como ler diretorios com dirent.h*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // header usado para DIR e DIRENT

void erro(const unsigned char *mensagem){
  fprintf(stderr, "[Erro]: %s\n", mensagem);
  exit(1);
}

int main(int argc, char *argv[]){
  DIR *dir; // Ponteiro para o tipo DIRETORIO
  struct dirent *diretorio; // Estrutura para diretorio

  if(argc <2) // Verificar os argumentos
    erro("Use:\n./programa /direterio");
  
  // Tentar ler o diretorio com OPENDIR
  dir = opendir(argv[1]);
  if(!(dir)) erro("Diretorio não existe!");

  // Loop para varrer o diretorio lendo ele com readdir()
  while (( diretorio = readdir (dir)) != NULL){
    char local[1024]; // Criar variavel pro valor

    // Filtrar os diretorio "." e ".." no Linux
    if( strcmp(diretorio->d_name, ".") ==0 || strcmp(diretorio->d_name, "..") ==0 )
      continue;

    // Concatenar em local ENDERECO + D_NAME
    sprintf(local, "%s/%s", argv[1] , diretorio->d_name);
    printf("%s \n", local); // Imprimir o resultado
  }
  closedir(dir); // fechar o diretorio

  return 0;
}
