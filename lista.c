#include "lista.h"

// recibe el char comprimido
unsigned int getVecesUsado(Encrypted t) {
    unsigned int retorno = 0, size, x;
    String s;

    encryptedToString(t, s);

    size = strlen(s);
    for (x = 0; x < size; x++) {
        if (s[x] == 'x') retorno++;
    }

    return retorno;
}

// la idea es haciendo getCombi(c, a) el equivalente a c[a]
// retorna el puntero para poder cambiar el valor
Combinaciones* getCombi(Combinaciones *c, unsigned long index) {
    Combinaciones *current = c;
    unsigned long x = 0;

    while(x < index && current != NULL) {
        current = current->UP;

        x++;
    }

    return current;
}

void printComb(Combinaciones *c, unsigned long current) {
    String s;
    Combinaciones *tmp;
    unsigned long x;

    for(x = 0; x < current; x++) {
        tmp = getCombi(c, x);
        printf("%lu. ", x+1);
        if(tmp != NULL) {
            encryptedToString(tmp->valor.operacion, s);
           printf("%s [%.2f]\n", s, tmp->valor.resultado);
        }
        else {
            printf("ERROR\n");
        }
    }

    return;
}

Combinaciones* addCombiT(Combinaciones *c, unsigned long index) {
    Combinaciones *retorno = (Combinaciones*)malloc(sizeof(Combinaciones) * 1), *back;

    if (retorno == NULL) {
        printf("[e] Not enought memory.\n");
        exit(EXIT_FAILURE);
    }

    retorno->UP = NULL;
    retorno->DOWN = NULL;

    if (index != 0) {
        back = getCombi(c, index-1);
        retorno->DOWN = back;
        back->UP = retorno;
    }

    return retorno;
}

Combinaciones* addCombi(Combinaciones *c) {
    Combinaciones *retorno;

    retorno = addCombiT(c, getMaxIndex(c));

    return retorno;
}

// obtener el indice máximo + 1 (el número de objetos)
unsigned long getMaxIndex(Combinaciones *c) {
    unsigned long x = 0;
    Combinaciones *go = c;

    while (go != NULL) {
        x++;
        go = go->UP;
    }

    return x;
}

void freeCombiF(Combinaciones *c, unsigned long size) {
    unsigned long x;
    Combinaciones *current, *go = c;

    for (x = 0; x < size && go != NULL; x++) {
        current = go;
        go = go->UP;

        if(current->valor.operacion != NULL) {
            free(current->valor.operacion);
            current->valor.operacion = NULL;
        }
        if (current->DOWN != NULL) {
            free(current->DOWN);
            current->DOWN = NULL;
        }
    }

    return;
}

void freeCombi(Combinaciones *c) {
    unsigned long x = getMaxIndex(c);

    freeCombiF(c, x);

    return;
}

Encrypted concatenateString(Encrypted comb1, Encrypted comb2, char operacion) {
    String s, tmp;
    int size;
    Encrypted retorno;

    if (*comb1 != '\0') {
        strcpy(s, "(");

        encryptedToString(comb1, tmp);
        strcat(s, tmp);

        strcat(s, ")");
    }

    size = strlen(s);
    s[size] = operacion;
    s[size+1] = '\0';

    if (*comb2 != '\0') {
        strcat(s, "(");

        encryptedToString(comb2, tmp);
        strcat(s, tmp);

        strcat(s, ")");
    }

    //printf("[d] %s\n", s);

    retorno = allocateTextMemory(s);

    return retorno;
}