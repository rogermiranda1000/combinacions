#ifndef COMBINACIONS_COMBINATORIA_H
#define COMBINACIONS_COMBINATORIA_H

#include "main.h"
#include "lista.h"
#include "texto.h"
#include <math.h>
#include "estructuras.h"
#include <stdbool.h>

#define MAX_FLOAT 2147483647

typedef struct {
    Combinacion *combinaciones;
    bool found;
} Storage;

float factorial(float val);
bool operar(Combinaciones *total, Combinacion c1, Combinacion c2, char op, unsigned long *current);
Combinacion operarNEW(Combinacion c1, Combinacion c2, char op);
bool operacions(Combinaciones *total, Combinacion c1, Combinacion c2, unsigned long *current);
Storage operacionsNEW(Combinacion c1, Combinacion c2);
bool combine(Combinaciones *total, unsigned long current, unsigned long end, unsigned long *contador);
int countAvailable(Storage s);
bool combineNEW(Combinaciones *total, unsigned long current, unsigned long end, unsigned long *contador);

#endif