#ifndef COMBINACIONS_LISTA_H
#define COMBINACIONS_LISTA_H

#include "main.h"
#include "texto.h"
#include "estructuras.h"
#include <pthread.h>

Combinaciones* getCombi(Combinaciones *c, unsigned long index);
void printComb(Combinaciones *c, unsigned long current);
void freeCombiF(Combinaciones *c, unsigned long size);
void freeCombi(Combinaciones *c);
unsigned int getVecesUsado(Encrypted t);
unsigned long getMaxIndex(Combinaciones *c);
Combinaciones* addCombiT(Combinaciones *c, unsigned long *index);
Combinaciones* addCombi(Combinaciones *c);
unsigned char* concatenateString(Encrypted comb1, Encrypted comb2, char operacion);

#endif //COMBINACIONS_LISTA_H
