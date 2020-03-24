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
            if (resultado > MAX_FLOAT || resultado < -MAX_FLOAT) {
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
    }

    if (!error) {
        r = addCombiT(total, *current);

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

        if (resultado == RESULTAT && getVecesUsado(r->valor.operacion) == VEGADES_UTILITZAR) {
            encryptedToString(r->valor.operacion, s);
            printf("\n\n[*] Resultado obtenido: %s\n", s);
            retorno = true;
        }

        (*current)++;
    }
    /*else {
        printf("[e] Error en una operacion\n");
    }*/

    return retorno;
}

bool operacions(Combinaciones *total, Combinacion c1, Combinacion c2, unsigned long *current) {
    bool retorno = false;
    Combinacion nulo;
    nulo.resultado = 0;
    nulo.operacion = (char*)malloc(sizeof(char) * 1);
    *nulo.operacion = '\0';

    if (getVecesUsado(c1.operacion) + getVecesUsado(c2.operacion) <= VEGADES_UTILITZAR) {
        retorno = operar(total, c1, c2, SUMA, current);
        retorno = (!retorno ? operar(total, c1, c2, RESTA, current) : true);
        retorno = (!retorno ? operar(total, c1, c2, MULTIPLICACION, current) : true);
        retorno = (!retorno ? operar(total, c1, c2, DIVISION, current) : true);
        retorno = (!retorno ? operar(total, c1, c2, EXPONENTE, current) : true);

        // si c1 no es c2, giralo
        if (strcmp(c1.operacion, c2.operacion) != 0) {
            retorno = (!retorno ? operar(total, c2, c1, RESTA, current) : true);
            retorno = (!retorno ? operar(total, c2, c1, DIVISION, current) : true);
            retorno = (!retorno ? operar(total, c2, c1, EXPONENTE, current) : true);
        }
    }

    // funciones consigo misma
    retorno = (!retorno ? operar(total, c1, nulo, FACTORIAL, current) : true);
    retorno = (!retorno ? operar(total, nulo, c1, RESTA, current) : true);

    free(nulo.operacion);
    return retorno;
}

// dado un índice actual y el índice de la última conbinación del anterior ciclo (incluido),
// se genera su combinación con todas las otras
bool combine(Combinaciones *total, unsigned long current, unsigned long last, unsigned long *contador) {
    bool retorno = false;
    unsigned long x;
    Combinacion this = getCombi(total, current)->valor;

    for (x = 0; x <= last && !retorno; x++) {
        retorno = operacions(total, this, getCombi(total, x)->valor, contador);
    }

    return retorno;
}