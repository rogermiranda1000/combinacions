#include "combi.h"

// recibe el char comprimido
int getVecesUsado(unsigned char *t) {
    int retorno = 0, size, x;
    String s;

    textToString(t, s);

    size = strlen(s);
    for (x = 0; x < size; x++) {
        if (s[x] == 'x') retorno++;
    }

    return retorno;
}

unsigned char* concatenateString(unsigned char *comb1, unsigned char *comb2, char operacion) {
    String s, tmp;
    int size;
    unsigned char* retorno;

    strcpy(s, "(");

    textToString(comb1, tmp);
    strcat(s, tmp);

    strcat(s, ")");

    size = strlen(s);
    s[size] = operacion;
    s[size+1] = '\0';

    strcat(s, "(");

    textToString(comb2, tmp);
    strcat(s, tmp);

    strcat(s, ")");

    //printf("[d] %s\n", s);

    retorno = allocateTextMemory(s);

    return retorno;
}