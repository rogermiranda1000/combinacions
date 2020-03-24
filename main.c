#include "main.h"

// ./combinacions número_a_utilitzar vegades_a_utilitzar_el_número resultat
int main(int argc, char **argw) {
    String s;
    int numero_a_utilitzar, vegades_a_utilitzar_el_numero, resultat;

    // tests
    char *comprimir = "(x+x)/x!*(x^(x-x))", *comprimir2 = "x!";
    unsigned char *var1, *var2, *add;

    var1 = allocateTextMemory(comprimir);
    var2 = allocateTextMemory(comprimir2);
    textToString(var1, s);
    printf("%s > %s\n", comprimir, s);
    printf("%d bytes reservados, frente a %d\n", strlen(var1)+1, strlen(comprimir)+1);
    printf("%d veces el numero\n", getVecesUsado(var1));
    add = concatenateString(var1, var2, '+');
    textToString(add, s);
    printf("%s\n", s);

    free(add);
    free(var1);
    free(var2);



    if (argc != 4) {
        printf("[e] Debes especificar 3 parametros [numero_a_utilitzar vegades_a_utilitzar_el_numero resultat]\n");
    }
    else {
        numero_a_utilitzar = atoi(argw[1]);
        vegades_a_utilitzar_el_numero = atoi(argw[2]);
        resultat = atoi(argw[3]);
        if ((numero_a_utilitzar == 0 && argw[1][0] != '0') || (vegades_a_utilitzar_el_numero == 0 && argw[2][0] != '0') || (resultat == 0 && argw[3][0] != '0')) {
            printf("[e] Uno o mas parametros no son enteros.\n");
        }
        else {

        }
    }

    return 0;
}
