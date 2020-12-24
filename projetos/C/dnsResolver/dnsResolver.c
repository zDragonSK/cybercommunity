/*
  DNSResolver - dnshunter - Script melhorado e adaptado- zDragonSK
  O script é simples mas pode ser muito bem trabalhado, já que é mais rapido que alguns scripts.

  Se a maioria da wordlist ser reconhecida e não existir em si o dominio, é por causa que a host esta respondendo nesse dominio e isso pode ser resolvido trabalhando no script para verificar se a conexão der código 200 ou não. Fica como desafio a quem quiser.
*/

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SPATH "dns.txt" // Arquivo padrão de leitura para wordlist

// Funções
void erro(const int code);

// Blocos
int main(int argc, char *argv[]){
  // Variaveis Locais
  char *alvo, *link, buffer[101], *path;
  FILE *arquivo;
  struct hostent *host;

  printf("\033[1;31mSe a maioria da wordlist ser reconhecida e não existir em si o dominio, é por causa que a host esta respondendo nesse dominio e isso pode ser resolvido trabalhando no script para verificar se a conexão trazer o código 200 ou não. Fica como desafio a quem quiser.\033[0;00m\n\n");

  if(argc<2) erro(1); // Testando se tem menos de 2 argumentos
  else{
    alvo = argv[1];
    // Verificando se o usuario declarou o wordlist ou vai usar o padrao
    if(argv[2]) path=argv[2]; // declarando do usuario
    else path=SPATH; // declarando o padrão defino abaixo dos include
    // Tentando abrir o wordlist
    if(!(arquivo=fopen(path, "r"))) erro(2);
    else{
      // Leitura do arquivo wordlist ate o EOF(fim)
      while(fscanf(arquivo, "%s", &buffer) != EOF){
        strcat(buffer, "."); // Colocando "." no fim para ficar exemplo: www.google e não wwwgoogle
        link = (char *) strcat(buffer, alvo); // Juntando a palavra do wordlist com o alvo
        host=gethostbyname(link); // capturando o ip usando o DNS
        if(host == NULL) continue; // Verificando se o host existe
        printf("%s ===> %s\n", link, inet_ntoa(*((struct in_addr*) host->h_addr))); // Imprimindo o DNS e IP
      }
    }
  }
  return 0;
}

void erro(const int code){
  if(code == 1)// Para erros no uso
    fprintf(stderr, "[Erro]: Faltam argumentos!\nUse: programa [host(sem www)] [wordlist(*opcional)] \nExemplo: dnshunter google.com wordlist.txt\n");
  
  else if(code == 2) // Para erro de abertura de arquivo
    fprintf(stderr, "[Erro]: O arquivo da wordlist não existe ou não tem permissão para abrir.\n");

  return;
}
