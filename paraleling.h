#ifndef COMBINACIONS_PARALELING_H
#define COMBINACIONS_PARALELING_H


#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "combinatoria.h"
#include "main.h"
#include <unistd.h>

#define THREADS 6

typedef struct {
    Combinaciones *combinaciones_start;
    Combinaciones **combinaciones_end;
    unsigned long x;
    unsigned long end;
    unsigned long *current;
} ParalelStruct;

void paralel();
void *myFun(void *x);

void *execParalel(void *input);
void *clk(void *x);
bool processParalel(Combinaciones *combinaciones_start, Combinaciones **combinaciones_end, unsigned long last, unsigned long end, unsigned long *current);
bool processParalelNEW(Combinaciones *combinaciones_start, Combinaciones **combinaciones_end, unsigned long last, unsigned long end, unsigned long *current);


#endif //COMBINACIONS_PARALELING_H
