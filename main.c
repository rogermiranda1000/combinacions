#include "main.h"

// ./combinacions número_a_utilitzar vegades_a_utilitzar_el_número resultat
int main(int argc, char **argw) {
    int counter = 0;
    unsigned long current = 0, last = 0, end = 0, x;
    Combinaciones *combinaciones_start, *combinaciones_end;
    bool found = false, clock_created = true;
    pthread_t clock_thread;
    clock_t start = (float)clock();

    combinaciones_start = addCombiT(NULL, &current);
    combinaciones_start->valor.resultado = (float)NUMERO_UTILITZAR;
    combinaciones_start->valor.operacion = allocateTextMemory("x");
    combinaciones_end = combinaciones_start;

    /*if(pthread_create(&clock_thread, NULL, &clk, &current)) {
        printf("[e] Clock thread creation error\n");
        clock_created = false;
    }*/

    while (!found) {
        if (VERBOSE) {
            printf("[v] Ciclo %d (%ld combinaciones)\n", ++counter, (end - last + 1)*10*end);
            if (counter == 4) printf("[w] Este programa pierde mucha eficiencia con el ciclo 4 o superior\n");
        }
        //printComb(combinaciones, current);
        //printf("[d] End: %lu, last: %lu\n", end, last);

        // multi-processor
        //found = processParalel(combinaciones, last, end, &current);
        found = processParalelNEW(combinaciones_start, &combinaciones_end, last, end, &current);

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

    /*if (clock_created) {
        pthread_cancel(start);
    }*/


    //operacions(combinaciones, combinaciones->valor, combinaciones->valor, &current);

    if (VERBOSE) {
        printf("END\n");
        printf("[v] %lu combinaciones creadas\n", current);
        printf("[v] Tiempo de ejecucion: %.2f\n", ((float)clock() - start)/CLOCKS_PER_SEC);
    }
    //printComb(combinaciones, current);

    freeCombiF(&combinaciones_start, current);

    return 0;
}

