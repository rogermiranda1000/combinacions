#ifndef COMBINACIONS_COMBINATORIA_H
#define COMBINACIONS_COMBINATORIA_H

#include "main.h"
#include "lista.h"
#include "texto.h"
#include <math.h>
#include "estructuras.h"
#include <stdbool.h>

#define MAX_FLOAT 2147483647

float factorial(float val);
bool operar(Combinaciones *total, Combinacion c1, Combinacion c2, char op, unsigned long *current);
bool operacions(Combinaciones *total, Combinacion c1, Combinacion c2, unsigned long *current);
bool combine(Combinaciones *total, unsigned long current, unsigned long last, unsigned long *contador);

#endif