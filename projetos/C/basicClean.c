/*
	zClean é um projeto para limpar caches e lixo do UNIX. Este projeto não esta seguindo o padrão de programação
	do C Ansi. Eu fiz de uma forma preguiçosa e pode ser considerada poluida. Por isso deixo isso claro a qualquer 
	pessoa que queira usar ele como boa referencia.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define NAME "==[zClear]== ; Sistema de limpeza rapida"
#define VERSION "1.0v"

// Desmarque essa opção para alternativa de limpeza
//#define UNIX

int load(void);
int limpar(const unsigned char *endereco);
void erro(const unsigned char *mensagem, const int code);

//void teste(void);

int main(void){
  if (load()) erro("Problema ao carregar. Encerrando. \n", 1);
  //teste();
  limpar("/tmp/");
  limpar("~/.mozilla/firefox/l3kur3ff.default-esr/bookmarkbackups/");
  limpar("~/.cache/thumbnails/normal/");
  limpar("~/.cache/thumbnails/large/");
  limpar("~/.cache/");
  limpar("/var/lib/apt/lists/partial/");
  limpar("/var/lib/apt/lists/auxfiles/");
  
  // Este é uma alternativa para erro das função acima
  #ifdef UNIX
  	system("sudo rm /var/lib/apt/lists/* 2>> log_error;sudo rm /var/lib/apt/auxfiles/* 2>> log_error;sudo rm ~/.cache/* 2>> log_error;sudo rm ~/tmp/* 2>> log_error");
  #endif
  
  return 0;
}

// Função usada para executar ações necessarias ao iniciar
int load(void){
  int st = 0;
  printf("%s - %s \n", NAME, VERSION); 
  //if (st != 0) return 1;
  return 0;
}

// Limpar os arquivos de um diretorio
int limpar(const unsigned char *endereco){
	// variaveis
	DIR *dir;
	struct dirent *diretorio;
	
	// Limpando os arquivos
	printf("[zClean]: Iniciando limpeza no diretorio %s \n", endereco);
	dir = opendir(endereco);
	if(dir == NULL) return 0;
	while (( diretorio = readdir (dir)) != NULL){
		char local[1024];
		if (strcmp(diretorio->d_name, ".") ==0 || strcmp(diretorio->d_name, "..") == 0)
			continue;
		sprintf(local, "%s%s", endereco ,diretorio->d_name);
		if(remove(local))
			printf("[Deletado]: %s \n", local);
		else
			fprintf(stderr, "[Erro]: Não foi possivel deletar %s\n", local);
	}
	closedir(dir);
	return 1;
}

// Função para erros que necessitam sair
void erro(const unsigned char *mensagem, const int code){
  fprintf(stderr, "[Erro]: %s : %i \n", mensagem, code);
}

