#ifndef COMBINACIONS_TEXTO_H
#define COMBINACIONS_TEXTO_H

#include <stddef.h> // macro NULL
#include <string.h>
#include <stdlib.h>

unsigned char charToComb(char c);
char combToChar(unsigned char c);
unsigned char* allocateTextMemory(char *txt);
void textToString(unsigned char *text, char *string);

#endif //COMBINACIONS_TEXTO_H
