#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Escreve e cria um arquivo (Create And Write*/
void caw(char *nome, char *frase){
    char c;
    FILE *p;
    if (!(p = fopen(nome, "w"))) /*Caso ocorra algum erro na abertura*/
    {
        /*Aborta caso haja erro*/
        printf("[zFile]: Não foi possivel achar o arquivo.\n");
        exit(1);
    }
    /*Se não houver erro, continua o algoritmo*/
    fprintf(p, frase);
    fclose(p);
    /*Abre novamente para leitura*/
    p = fopen(nome, "r");
    printf("[zFile]: Salvo no arquivo:\n");
    while(!feof(p))
    {
        fscanf(p, "%c", &c);
        printf("%c", c);
    }
    printf("\n[zFile]: Processo completo.\n\a"); 
    fclose(p);
}

/*Le e imprimi um arquivo (Read And Print)*/
void rap(char *nome){
    FILE *p;
    char c;
    int indice = 0;
    char texto[1000];
    if (!(p = fopen(nome, "r"))) /*Caso ocorra algum erro na abertura*/
    {
        /*Aborta caso haja erro*/
        printf("[zFile]: Não foi possivel achar o arquivo.\n");
        exit(1);
    }
    /*Se não houver erro, continua o algoritmo*/
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

/*Escre e salva no fim do arquivo (Write And Save)*/
void was(char *nome, char *frase){
    char c;
    FILE *p;
    if (!(p = fopen(nome, "a"))) /*Caso ocorra algum erro na abertura*/
    {
        /*Aborta caso haja erro*/
        printf("[Erro]: Não foi possivel achar o arquivo.\n");
        exit(1);
    }
    /*Se não houver erro, continua o algoritmo*/
    fprintf(p, frase);
    fclose(p);
    /*Abre novamente para leitura*/
    p = fopen(nome, "r");
    printf("[zFile]: Salvo no arquivo:\n");
    while(!feof(p))
    {
        fscanf(p, "%c", &c);
        printf("%c", c);
    }
    printf("\n"); /*Serve pra dar linha no final*/
    fclose(p);
}

