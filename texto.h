#ifndef COMBINACIONS_TEXTO_H
#define COMBINACIONS_TEXTO_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//#define NULL 0
#define SUMA '+'
#define RESTA '-'
#define MULTIPLICACION '*'
#define DIVISION '/'
#define EXPONENTE '^'
#define FACTORIAL '!'

// fichero con todo lo relacionado a encriptación/desencriptación
typedef unsigned char *Encrypted;

unsigned char charToComb(char c);
char combToChar(unsigned char c);
Encrypted allocateTextMemory(char *txt);
void encryptedToString(Encrypted text, char *string);
int getMemory(char *txt);
void stringToEncrypted(char *txt, Encrypted retorno);

#endif //COMBINACIONS_TEXTO_H
