#include "main.h"

// ./combinacions número_a_utilitzar vegades_a_utilitzar_el_número resultat
int main(int argc, char **argw) {
    Combinaciones *combinaciones = addCombiT(NULL, 0);
    unsigned long current = 1, last = 0, end = 0, x;
    int counter = 0;
    bool found = false;
    clock_t start = (float)clock();

    combinaciones->valor.resultado = (float)NUMERO_UTILITZAR;
    combinaciones->valor.operacion = allocateTextMemory("x");

    while (!found) {
        if (VERBOSE) printf("\n[v] Ciclo %d (%ld iteraciones)", ++counter, end - last + 1);

        for (x = last; x <= end && !found; x++) {
            //printf("\n[d] %lu\n", end - x + 1);
            if ((end - x + 1) % 50 == 0 && VERBOSE) printf(".");
            found = combine(combinaciones, x, end, &current);
        }
        last = end + 1;
        end = current - 1;
    }


    //operacions(combinaciones, combinaciones->valor, combinaciones->valor, &current);

    if (VERBOSE) {
        printf("[v] %lu combinaciones creadas\n", current);
        printf("[v] Tiempo de ejecucion: %.2f\n", ((float)clock() - start)/CLOCKS_PER_SEC);
    }
    //printComb(combinaciones, current);

    freeCombiF(combinaciones, current);

    return 0;
}

