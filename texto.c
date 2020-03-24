#include "texto.h"

// dado un caracter, retorna su valor en la tabla definida
unsigned char charToComb(char c) {
    // !! retorno NO puede superar el 15 !!
    unsigned char retorno;

    switch(c) {
        case '\0':
            retorno = 0;
            break;
        case 'x':
            retorno =  1;
            break;
        case '+':
            retorno =  2;
            break;
        case '-':
            retorno = 3;
            break;
        case '*':
            retorno = 4;
            break;
        case '/':
            retorno = 5;
            break;
        case '^':
            retorno = 6;
            break;
        case '!':
            retorno = 7;
            break;
        case '(':
            retorno = 8;
            break;
        case ')':
            retorno = 9;
            break;
        default:
            retorno = 15;
    }

    return retorno;
}

char combToChar(unsigned char c) {
    char retorno;

    switch(c) {
        case 0:
            retorno = '\0';
            break;
        case 1:
            retorno =  'x';
            break;
        case 2:
            retorno =  '+';
            break;
        case 3:
            retorno = '-';
            break;
        case 4:
            retorno = '*';
            break;
        case 5:
            retorno = '/';
            break;
        case 6:
            retorno = '^';
            break;
        case 7:
            retorno = '!';
            break;
        case 8:
            retorno = '(';
            break;
        case 9:
            retorno = ')';
            break;
        default:
            retorno = '?';
    }

    return retorno;
}

void textToString(unsigned char *text, char *string) {
    int x, size = strlen(text);

    for (x = 0; x < size; x++) {
        string[2*x] = combToChar(text[x]/16);
        string[(2*x)+1] = combToChar(text[x]%16);
    }
    string[2*x] = '\0';

    return;
}

// reserva la memoria y retorna su puntero
unsigned char* allocateTextMemory(char *txt) {
    unsigned char *retorno = NULL;
    unsigned char tmp;
    unsigned int memory = strlen(txt), x;

    // esta función está montada de forma que cada caracter ocupa medio byte
    // si los caracteres son impares, medio byte queda bacio
    // + el \0 final
    if (memory % 2 == 1) {
        memory++;
    }
    memory /= 2;

    retorno = (unsigned char*) malloc(sizeof(unsigned char) * (memory+1));

    for (x = 0; x < memory; x++) {
        tmp = charToComb(txt[2*x]);
        tmp *= 16; // desplazar 4 bits
        tmp += charToComb(txt[(2*x)+1]);
        retorno[x] = tmp;
    }
    retorno[memory] = '\0';

    return retorno;
}