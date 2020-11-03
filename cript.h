// Biblioteca AES em C
#ifndef _CRIPT_H
#define _CRIPT_H

// Include
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Prototipo das funções
long SubByte(long byte, bool status);
long RotByte(long word);
void ShiftRow(long t[4][4], int linha);
long FFmul (long a, long b );
void MixColumn (long t[4][4]);
void InvMixColumn (long t[4][4]);
void KeyExpansion (long key[4], long word[44]);
void XorRoundKey(long t[4][4], long word[44], int round); 
void InvShiftRow(long t[4][4], int linha);
void matrix2array(long t[4][4], unsigned char texto[]);
void array2matrix(unsigned char texto[], long t[4][4]);
void decifrar (long t[4][4], long w[]);
void cifrar (long t[4][4], long w[]);
int decifrafile(char *filename , char *newfile , unsigned char *chave);
int cifrafile(char *filename , char *newfile , unsigned char *chave);

#endif