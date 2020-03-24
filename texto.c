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
        case SUMA:
            retorno =  2;
            break;
        case RESTA:
            retorno = 3;
            break;
        case MULTIPLICACION:
            retorno = 4;
            break;
        case DIVISION:
            retorno = 5;
            break;
        case EXPONENTE:
            retorno = 6;
            break;
        case FACTORIAL:
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
            retorno =  SUMA;
            break;
        case 3:
            retorno = RESTA;
            break;
        case 4:
            retorno = MULTIPLICACION;
            break;
        case 5:
            retorno = DIVISION;
            break;
        case 6:
            retorno = EXPONENTE;
            break;
        case 7:
            retorno = FACTORIAL;
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

// decodifica
void encryptedToString(Encrypted text, char *string) {
    int x, size = strlen(text);

    for (x = 0; x < size; x++) {
        string[2*x] = combToChar(text[x]/16);
        string[(2*x)+1] = combToChar(text[x]%16);
    }
    string[2*x] = '\0';

    return;
}

int getMemory(char *txt) {
    int memory = strlen(txt);

    if (memory % 2 == 1) {
        memory++;
    }
    memory /= 2;

    return memory;
}

// codifica
void stringToEncrypted(char *txt, Encrypted retorno) {
    int x, memory = getMemory(txt);
    unsigned char tmp;

    for (x = 0; x < memory; x++) {
        tmp = charToComb(txt[2*x]);
        tmp *= 16; // desplazar 4 bits
        tmp += charToComb(txt[(2*x)+1]);
        retorno[x] = tmp;
    }
    retorno[memory] = '\0';

    return;
}

// reserva la memoria y retorna su puntero
// esta función está montada de forma que cada caracter ocupa medio byte
// si los caracteres son impares, medio byte queda bacio
// + el \0 final
Encrypted allocateTextMemory(char *txt) {
    Encrypted retorno = (unsigned char*) malloc(sizeof(unsigned char) * (getMemory(txt)+1));

    if (retorno == NULL) {
        printf("[e] Not enought memory.\n");
        exit(EXIT_FAILURE);
    }

    stringToEncrypted(txt, retorno);

    return retorno;
}