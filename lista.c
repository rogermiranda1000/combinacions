#include "lista.h"

// recibe el char comprimido
unsigned int getVecesUsado(Encrypted t) {
    unsigned int retorno = 0, size, x;
    String s;

    encryptedToString(t, s);

    size = strlen(s);
    for (x = 0; x < size; x++) {
        if (s[x] == 'x') retorno++;
    }

    return retorno;
}

// la idea es haciendo getCombi(c, a) el equivalente a c[a]
// retorna el puntero para poder cambiar el valor
Combinaciones* getCombi(Combinaciones *c, unsigned long index) {
    Combinaciones *current = c;
    unsigned long x = 0;

    while(x < index && current != NULL) {
        current = current->UP;

        x++;
    }

    return current;
}

void printComb(Combinaciones *c, unsigned long current) {
    String s;
    Combinaciones *tmp;
    unsigned long x;

    for(x = 0; x < current; x++) {
        tmp = getCombi(c, x);
        printf("%lu. ", x+1);
        if(tmp != NULL) {
            encryptedToString(tmp->valor.operacion, s);
            printf("%s [%.2f]\n", s, tmp->valor.resultado);
        }
        else {
            printf("ERROR\n");
        }
    }

    return;
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

Combinaciones* addCombiT(Combinaciones *c, unsigned long *index) {
    unsigned long my;
    clock_t start;
    Combinaciones *retorno = (Combinaciones*)malloc(sizeof(Combinaciones) * 1), *back;

    if (retorno == NULL) {
        printf("[e] Not enought memory.\n");
        exit(EXIT_FAILURE);
    }

    retorno->UP = NULL;
    retorno->DOWN = NULL;

    // asegurar que current se asigna correctamente
    pthread_mutex_lock(&mutex);
    my = (*index)++; // reserva el espacio

    if (my != 0) {
        //printf("[v] Reservando %lu...\n", my - 1);
        // si no existe, sigue intentandolo
        back = getCombi(c, my - 1);
        pthread_mutex_unlock(&mutex);
        if (back == NULL) {
            //start = (float)clock();
            printf("\n[e] Combination (%lu) not found, trying again...\n", my-1);
            while (back == NULL) {
                //if (((float)clock()-start)/CLOCKS_PER_SEC == 0.5) printf("\n[e] Combination (%lu) not found, try again...\n", my-1);
                back = getCombi(c, my - 1);
            }
            printf("\n[e] %lu found!\n", my-1);
        }
        retorno->DOWN = back;
        back->UP = retorno;
    }
    else {
        pthread_mutex_unlock(&mutex);
    }

    return retorno;
}

Combinaciones* addCombi(Combinaciones *c) {
    Combinaciones *retorno;
    unsigned long index = getMaxIndex(c);

    retorno = addCombiT(c, &index);

    return retorno;
}

// obtener el indice máximo + 1 (el número de objetos)
unsigned long getMaxIndex(Combinaciones *c) {
    unsigned long x = 0;
    Combinaciones *go = c;

    while (go != NULL) {
        x++;
        go = go->UP;
    }

    return x;
}

void freeCombiF(Combinaciones *c, unsigned long size) {
    unsigned long x;
    Combinaciones *current, *go = c;

    for (x = 0; x < size && go != NULL; x++) {
        current = go;
        go = go->UP;

        if(current->valor.operacion != NULL) {
            free(current->valor.operacion);
            current->valor.operacion = NULL;
        }
        if (current->DOWN != NULL) {
            free(current->DOWN);
            current->DOWN = NULL;
        }
    }

    return;
}

void freeCombi(Combinaciones *c) {
    unsigned long x = getMaxIndex(c);

    freeCombiF(c, x);

    return;
}

Encrypted concatenateString(Encrypted comb1, Encrypted comb2, char operacion) {
    String s, tmp;
    int size;
    Encrypted retorno;

    strcpy(s, "");
    if (*comb1 != '\0') {
        strcat(s, "(");

        encryptedToString(comb1, tmp);
        strcat(s, tmp);

        strcat(s, ")");
    }

    size = strlen(s);
    s[size] = operacion;
    s[size+1] = '\0';

    if (*comb2 != '\0') {
        strcat(s, "(");

        encryptedToString(comb2, tmp);
        strcat(s, tmp);

        strcat(s, ")");
    }

    //printf("[d] %s\n", s);

    retorno = allocateTextMemory(s);

    return retorno;
}