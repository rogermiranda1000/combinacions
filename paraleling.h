#ifndef COMBINACIONS_PARALELING_H
#define COMBINACIONS_PARALELING_H


#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "combinatoria.h"
#include "main.h"

#define THREADS 4

typedef struct {
    Combinaciones *combinaciones;
    unsigned long x;
    unsigned long end;
    unsigned long *current;
} ParalelStruct;

void paralel();
void *myFun(void *x);

void *execParalel(void *input);
bool processParalel(Combinaciones *combinaciones, unsigned long last, unsigned long end, unsigned long *current);
bool processParalelNEW(Combinaciones *combinaciones, unsigned long last, unsigned long end, unsigned long *current);


#endif //COMBINACIONS_PARALELING_H
