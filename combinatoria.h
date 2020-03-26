#ifndef COMBINACIONS_COMBINATORIA_H
#define COMBINACIONS_COMBINATORIA_H

#include "main.h"
#include "lista.h"
#include "texto.h"
#include <math.h>
#include "estructuras.h"
#include <stdbool.h>

#define MAX_FLOAT 2147483647
#define POW_ERROR (MAX_FLOAT-1)

typedef struct {
    Combinacion *combinaciones;
    bool found;
} Storage;

float exponent(float base, float exp);
float factorial(float val);
bool operar(Combinaciones **combinaciones_end, Combinacion c1, Combinacion c2, char op, unsigned long *current);
Combinacion operarNEW(Combinacion c1, Combinacion c2, char op);
bool operacions(Combinaciones **combinaciones_end, Combinacion c1, Combinacion c2, unsigned long *current);
Storage operacionsNEW(Combinacion c1, Combinacion c2);
bool combine(Combinaciones *combinaciones_start, Combinaciones **combinaciones_end, unsigned long current, unsigned long end, unsigned long *contador);
int countAvailable(Storage s);
//bool combineNEW(Combinaciones *total, unsigned long current, unsigned long end, unsigned long *contador);

#endif