#include "main.h"

// ./combinacions número_a_utilitzar vegades_a_utilitzar_el_número resultat
int main(int argc, char **argw) {
    int counter = 0;
    unsigned long current = 0, last = 0, end = 0, x;
    Combinaciones *combinaciones;
    bool found = false;
    clock_t start = (float)clock();

    combinaciones = addCombiT(NULL, &current);
    combinaciones->valor.resultado = (float)NUMERO_UTILITZAR;
    combinaciones->valor.operacion = allocateTextMemory("x");

    while (!found) {
        if (VERBOSE) printf("\n[v] Ciclo %d (%ld combinaciones)", ++counter, (end - last + 1)*10*end);
        //printComb(combinaciones, current);
        //printf("[d] End: %lu, last: %lu\n", end, last);

        // multi-processor
        found = processParalel(combinaciones, last, end, &current);
        //found = processParalelNEW(combinaciones, last, end, &current);

        // single CPU
        /*for (x = last; x <= end && !found; x++) {
            //printf("\n[d] %lu\n", end - x + 1);
            if ((end - x + 1) % 50 == 0 && VERBOSE) printf(".");
            //start = (float)clock();
            found = combine(combinaciones, x, end, &current);
            //printf("[v] Tiempo de ejecucion: %.2f\n", ((float)clock() - start)/CLOCKS_PER_SEC);
        }*/

        last = end + 1;
        end = current - 1;
    }


    //operacions(combinaciones, combinaciones->valor, combinaciones->valor, &current);

    if (VERBOSE) {
        printf("END\n");
        printf("[v] %lu combinaciones creadas\n", current);
        printf("[v] Tiempo de ejecucion: %.2f\n", ((float)clock() - start)/CLOCKS_PER_SEC);
    }
    //printComb(combinaciones, current);

    freeCombiF(combinaciones, current);

    return 0;
}

