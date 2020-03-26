#include "combinatoria.h"

float factorial(float val)
{
    float retorno = 1, tmp;

    if (val < 0 || trunc(val) != val) {
        retorno = -1;
    }
    else {
        while (val > 1 && (tmp = retorno * val) / retorno == val) {
            retorno = tmp;

            val--;
        }
        if (val != 1) {
            retorno = -1;
        }
    }

    return retorno;
}

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

bool operar(Combinaciones *total, Combinacion c1, Combinacion c2, char op, unsigned long *current) {
    Combinaciones *r;
    String s;
    bool error = false, retorno = false;
    float tmp, resultado;

    resultado = c1.resultado;

    //printf("[v] Operacion!\n");
    switch (op) {
        case SUMA:
            resultado += c2.resultado;
            break;
        case RESTA:
            resultado -= c2.resultado;
            break;
        case MULTIPLICACION:
            if ((tmp = resultado*c2.resultado) / resultado == c2.resultado)
            {
                resultado = tmp;
            } else {
                error = 1;
            }
            break;
        case DIVISION:
            if (c2.resultado != 0) {
                resultado /= c2.resultado;
            } else {
                error = 1;
            }
            break;
        case EXPONENTE:
            resultado = (float)pow(resultado, c2.resultado);
            if (resultado > (float)MAX_FLOAT || resultado < (float)-MAX_FLOAT) {
                error = 1;
            }
            break;
        case FACTORIAL:
            // control de error integrado
            resultado = factorial(resultado);
            if (resultado == -1) {
                error = 1;
            }
            break;
        default:
            printf("[e] Operacion no definida\n");
            error = true;
    }

    if (!error) {
        // asegurar que current se asigna correctamente
        //pthread_mutex_lock(&mutex);
        r = addCombiT(total, current);
        //pthread_mutex_unlock(&mutex);

        if (r == NULL) {
            printf("[e] Not enought memory.\n");
            exit(EXIT_FAILURE);
        }

        r->valor.operacion = concatenateString(c1.operacion, c2.operacion, op);
        if (r->valor.operacion == NULL) {
            printf("[e] Not enought memory.\n");
            exit(EXIT_FAILURE);
        }

        r->valor.resultado = resultado;

        /*encryptedToString(r->valor.operacion, s);
        printf("[d] %s\n", s);*/
        if (resultado == RESULTAT && getVecesUsado(r->valor.operacion) == VEGADES_UTILITZAR) {
            encryptedToString(r->valor.operacion, s);
            printf("\n\n[*] Resultado obtenido: %s\n", s);
            retorno = true;
        }
    }
    /*else {
        printf("[e] Error en una operacion\n");
    }*/

    return retorno;
}

Combinacion operarNEW(Combinacion c1, Combinacion c2, char op) {
    Combinacion retorno;
    Encrypted s_dyn;
    bool error = false;
    float tmp;

    retorno.resultado = c1.resultado;

    switch (op) {
        case SUMA:
            retorno.resultado += c2.resultado;
            break;
        case RESTA:
            retorno.resultado -= c2.resultado;
            break;
        case MULTIPLICACION:
            if ((tmp = retorno.resultado*c2.resultado) / retorno.resultado == c2.resultado)
            {
                retorno.resultado = tmp;
            } else {
                error = 1;
            }
            break;
        case DIVISION:
            if (c2.resultado != 0) {
                retorno.resultado /= c2.resultado;
            } else {
                error = 1;
            }
            break;
        case EXPONENTE:
            retorno.resultado = (float)pow(retorno.resultado, c2.resultado);
            if (retorno.resultado > (float)MAX_FLOAT || retorno.resultado < (float)-MAX_FLOAT) {
                error = 1;
            }
            break;
        case FACTORIAL:
            // control de error integrado
            retorno.resultado = factorial(retorno.resultado);
            if (retorno.resultado == -1) {
                error = 1;
            }
            break;
        default:
            printf("[e] Operacion no definida\n");
    }

    if (!error) {
        retorno.operacion = concatenateString(c1.operacion, c2.operacion, op);
    }
    else {
        s_dyn = (Encrypted)malloc(sizeof(unsigned char) * 1);
        *s_dyn = '\0';
        retorno.operacion = s_dyn;
    }

    return retorno;
}

bool operacions(Combinaciones *total, Combinacion c1, Combinacion c2, unsigned long *current) {
    bool retorno = false;
    Combinacion nulo;
    nulo.resultado = 0;
    nulo.operacion = (Encrypted)malloc(sizeof(unsigned char) * 1);
    *nulo.operacion = '\0';

    if (getVecesUsado(c1.operacion) + getVecesUsado(c2.operacion) <= VEGADES_UTILITZAR) {
        retorno = operar(total, c1, c2, SUMA, current); // 0
        retorno = (!retorno ? operar(total, c1, c2, RESTA, current) : true); // 1
        retorno = (!retorno ? operar(total, c1, c2, MULTIPLICACION, current) : true); // 2
        retorno = (!retorno ? operar(total, c1, c2, DIVISION, current) : true); // 3
        retorno = (!retorno ? operar(total, c1, c2, EXPONENTE, current) : true); // 4

        // si c1 no es c2, giralo
        if (strcmp(c1.operacion, c2.operacion) != 0) {
            retorno = (!retorno ? operar(total, c2, c1, RESTA, current) : true); // 5
            retorno = (!retorno ? operar(total, c2, c1, DIVISION, current) : true); // 6
            retorno = (!retorno ? operar(total, c2, c1, EXPONENTE, current) : true); // 7
        }
    }

    // funciones consigo misma
    retorno = (!retorno ? operar(total, c1, nulo, FACTORIAL, current) : true); // 8
    retorno = (!retorno ? operar(total, nulo, c1, RESTA, current) : true); // 9

    free(nulo.operacion);
    return retorno;
}

Storage operacionsNEW(Combinacion c1, Combinacion c2) {
    int x = 0;
    char operacion;

    Storage s;
    s.found = false;
    s.combinaciones = (Combinacion*) malloc(sizeof(Combinacion) * 10);

    Combinacion nulo;
    nulo.resultado = 0;
    nulo.operacion = (Encrypted)malloc(sizeof(unsigned char) * 1);
    *nulo.operacion = '\0';

    if (getVecesUsado(c1.operacion) + getVecesUsado(c2.operacion) > VEGADES_UTILITZAR) x = 8;

    while (x < 10 && !s.found) {
        //printf("[d] %d\n", x);
        switch (x) {
            case 0:
                operacion = SUMA;
                break;
            case 2:
                operacion = MULTIPLICACION;
                break;
            case 3:
            case 6:
                operacion = DIVISION;
                break;
            case 4:
            case 7:
                operacion = EXPONENTE;
                break;
            case 8:
                operacion = FACTORIAL;
                break;
            default: // 1, 5 o 9
                operacion = RESTA;
                break;
        }

        if (x >= 5 && x <= 7) {
            if (strcmp(c1.operacion, c2.operacion) != 0) {
                s.combinaciones[x] = operarNEW(c2, c1, operacion);
            }
            else {
                // si no, salta directamente
                x = 7;
            }
        }
        else if (x == 8) {
            // factorial
            s.combinaciones[x] = operarNEW(c1, nulo, operacion);
        }
        else if (x == 9) {
            // resta
            s.combinaciones[x] = operarNEW(nulo, c1, operacion);
        }
        else {
            s.combinaciones[x] = operarNEW(c1, c2, operacion);
        }

        if (s.combinaciones[x].resultado == RESULTAT && getVecesUsado(s.combinaciones[x].operacion) == VEGADES_UTILITZAR) {
            String str;
            encryptedToString(s.combinaciones[x].operacion, str);
            printf("[*] FOUND! %s\n", str);
            s.found = true;
        }

        x++;
    }

    free(nulo.operacion);

    return s;
}

// dado un índice actual y el índice de la última conbinación del anterior ciclo (incluido),
// se genera su combinación con todas las otras
bool combine(Combinaciones *total, unsigned long current, unsigned long end, unsigned long *contador) {
    bool retorno = false;
    unsigned long x;
    Combinacion this = getCombi(total, current)->valor;

    for (x = 0; x <= end && !retorno; x++) {
        retorno = operacions(total, this, getCombi(total, x)->valor, contador);
    }

    return retorno;
}

// dado un 'Storage', cuenta los datos útiles
int countAvailable(Storage s) {
    int x, count = 0;

    for (x = 0; x < 10; x++) {
        if (s.combinaciones[x].operacion != NULL) {
            //printf("[d] %d...\n", x);
            if (*s.combinaciones[x].operacion != '\0') count++;
        }
    }

    return count;
}

bool combineNEW(Combinaciones *total, unsigned long current, unsigned long end, unsigned long *contador) {
    //bool retorno = false;
    Storage s;
    unsigned long x, init;
    int available;
    Combinaciones* save;
    Combinacion this = getCombi(total, current)->valor;

    s.found = false;

    for (x = 0; x <= end && !s.found; x++) {
        s = operacionsNEW(this, getCombi(total, x)->valor);
        if (!s.found) {
            available = countAvailable(s);
            init = *contador;
            *contador += available;

            for (x = 0; x < 10; x++) {
                if (s.combinaciones[x].operacion != NULL) {
                    if (*s.combinaciones[x].operacion != '\0') {
                        save = addCombiT(total, &init);
                        if (save == NULL) {
                            printf("[e] On allocating memory\n");
                            exit(EXIT_FAILURE);
                        }

                        save->valor.resultado = s.combinaciones[x].resultado;
                        save->valor.operacion = s.combinaciones[x].operacion;
                    } else {
                        // free unused
                        free(s.combinaciones[x].operacion);
                    }
                }
            }
        }
    }

    return s.found;
}