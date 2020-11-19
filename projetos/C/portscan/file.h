/*
    Gerenciamento e manipulações de arquivos
*/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5096
FILE *arquivo;

// Checar se existe um arquivo retornando 1 para sim
int checkFile(const char *local, const char *op, const int exit){
    FILE *arquivo;
    
    if (arquivo = fopen(local, op)){
        if(exit != 0) printf("[Verificado]: %s foi localizado!\n", local);
        return 1;
    }
    if(exit != 0) printf("[Erro]: %s não foi encontrado!\n", local);
    return 0;
}

int countlines(const char *name)
{
    char buffer[MAX_SIZE];
    unsigned int c = 0;
    
    checkFile(name, "r", 0);

    fseek(arquivo, 0, SEEK_SET);
    while(fgets(buffer, MAX_SIZE, arquivo))
    {
        c++;
    }
    fclose(arquivo);
    return c;
}

char** readlines(const char *name, const int c)
{
    checkFile(name, "r", 0);
    
    char buffer[MAX_SIZE];
    char** dest = (char**)calloc(c, sizeof(char*));
    
    fseek(arquivo, 0, SEEK_SET);
    for(int i = 0; i < c; i++)
    {
        fgets(buffer, MAX_SIZE, arquivo);
        dest[i] = (char*)calloc(strlen(buffer), sizeof(char));
        strncpy(dest[i], buffer, strlen(buffer));
    }

    fclose(arquivo);
    return dest; //User should free this after using it
}


/*Escreve e salva no fim do arquivo (WRITE AND SAVE)*/
void was(const char *nome, const char *frase)
{
    char c;
    FILE *p;
    if (!(p = fopen(nome, "a"))) /*Caso ocorra algum erro na abertura*/
    {
        /*Aborta automaticamente*/
        printf("[Erro]: Não foi possivel achar o arquivo.\n");
        exit(1);
    }
    /*Se nao houver erro, escreve no arquivo*/
    fprintf(p, frase);
    fclose(p);
    /*Abre novamente para leitura*/
}


/*Le e imprimi o arquivo (READ AND PRINT)*/
void rap(const char *nome)
{
    FILE *p;
    char c;
    int indice = 0;
    char texto[MAX_SIZE];

    if (!(p = fopen(nome, "r"))) /*Caso ocorra algum erro na abertura*/
    {
        /*Aborta automaticamente*/
        printf("[Erro]: Não foi possivel achar o arquivo.\n");
        exit(1);
    }
    /*Se nao houver erro, le o arquivo*/
    printf("\n");
    while(!feof(p))
    {
        fscanf(p, "%c", &c);
        texto[indice] = c;
        indice++;
    }
    printf("%s\n", &texto);
    fclose(p);
}


void caw(const char *nome, const char *frase)
{
    char c;
    FILE *p;
    if (!(p = fopen(nome, "w"))) /*Caso ocorra algum erro na abertura*/
    {
        /*Aborta automaticamente*/
        printf("[Erro]: Não foi possivel achar o arquivo.\n");
        exit(1);
    }
    /*Se nao houver erro, escreve no arquivo*/
    fprintf(p, frase);
    fclose(p);
}
