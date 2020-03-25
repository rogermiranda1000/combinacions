#include "paraleling.h"

void *myFun(void *x)
{
    int tid;

    tid = *((int *) x);
    printf("Hi from thread %d!\n", tid);

    return NULL;
}

void paralel() {
    int x = 1;
    /* this variable is our reference to the second thread */
    pthread_t inc_x_thread;

    /* create a second thread which executes inc_x(&x) */
    if(pthread_create(&inc_x_thread, NULL, &myFun, &x)) {
        printf("[e] Thread creation error\n");
    }
    else {
        /* wait for the second thread to finish */
        if (pthread_join(inc_x_thread, NULL)) {
            printf("[e] On joining thread\n");
        }
    }
    printf("[v] END\n");
}

void *execParalel(void *input) {
    ParalelStruct ps = *(ParalelStruct*)input;
    bool found;

    //printf("[v] Thread as %lu\n", ps.x);
    found = combine(ps.combinaciones, ps.x, ps.end, ps.current);
    //found = combineNEW(ps.combinaciones, ps.x, ps.end, ps.current);

    return (void*) found;
}

// el 'x++' del primer bucle está mal
bool processParalel(Combinaciones *combinaciones, unsigned long last, unsigned long end, unsigned long *current) {
    unsigned long x, d;
    int tmp, thread;
    bool retorno = false;
    void *status;
    pthread_t threads[THREADS];
    ParalelStruct ps_send[THREADS];
    clock_t start;

    x = last;
    while (x <= end && !retorno) {
        start = (float)clock();

        // start threads
        for(thread = 0; thread < THREADS && x <= end; thread++, x++) {
            if (x != 0 && x % 25000 == 0) printf(".");

            // init
            ps_send[thread].combinaciones = combinaciones;
            ps_send[thread].x = x;
            ps_send[thread].end = end;
            ps_send[thread].current = current;

            if(pthread_create(&threads[thread], NULL, &execParalel, &ps_send[thread])) {
                printf("\n[e] Thread creation error\n");
                x--;
                thread--;
            }
        }

        // kill threads (& get retorno)
        for (tmp = 0; tmp < thread; tmp++) {
            if (!pthread_join(threads[tmp], &status)) {
                if ((bool)status) {
                    retorno = true;
                }
            }
            else {
                printf("\n[e] Thread joining error\n");
                tmp--;
            }
        }
        //printf("\n[v] Tiempo de ejecucion medio: %.2fs\n", (((float)clock() - start)/CLOCKS_PER_SEC)/THREADS);
    }

    return retorno;
}

bool processParalelNEW(Combinaciones *combinaciones, unsigned long last, unsigned long end, unsigned long *current) {
    unsigned long x;
    int thread;
    bool retorno = false, first = true;
    void *status;
    pthread_t threads[THREADS];
    ParalelStruct ps_send[THREADS];

    x = last;
    while (x <= end && !retorno) {
        for(thread = 0; thread < THREADS && x <= end; thread++, x++) {
            if (!first) {
                if (!pthread_join(threads[thread], &status)) {
                    if ((bool)status) {
                        retorno = true;
                    }
                }
                else {
                    printf("\n[e] Thread joining error\n");
                    exit(EXIT_FAILURE);
                }
            }

            if (!retorno) {
                // init
                ps_send[thread].combinaciones = combinaciones;
                ps_send[thread].x = x;
                ps_send[thread].end = end;
                ps_send[thread].current = current;

                if (pthread_create(&threads[thread], NULL, &execParalel, &ps_send[thread])) {
                    printf("\n[e] Thread creation error\n");
                    exit(EXIT_FAILURE);
                }
            }
        }

        first = false;
    }

    return retorno;
}