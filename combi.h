#ifndef COMBINACIONS_COMBI_H
#define COMBINACIONS_COMBI_H

#include "texto.h"
#include "main.h"

typedef struct {
    unsigned char *operacion;
    float resultado;
} Combinacion;

int getVecesUsado(unsigned char *t);

unsigned char* concatenateString(unsigned char *comb1, unsigned char *comb2, char operacion);

#endif //COMBINACIONS_COMBI_H
