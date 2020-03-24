#ifndef COMBINACIONS_ESTRUCTURAS_H
#define COMBINACIONS_ESTRUCTURAS_H

#include "texto.h"

// fichero con todas las funciones de listas
typedef struct {
    Encrypted operacion;
    float resultado;
} Combinacion;

typedef struct tCombinaciones {
    struct tCombinaciones *DOWN;
    Combinacion valor;
    struct tCombinaciones *UP;
} Combinaciones;


#endif //COMBINACIONS_ESTRUCTURAS_H
