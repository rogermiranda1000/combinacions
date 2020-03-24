#include "main.h"

int main() {
    unsigned char *var;
    char String[80];

    char *comprimir = "(x+x)/x!*(x^(x-x))";

    var = allocateTextMemory(comprimir);
    textToString(var, String);
    printf("%s > %s\n", comprimir, String);
    printf("%d bytes reservados, frente a %d\n", strlen(var)+1, strlen(comprimir)+1);

    free(var);

    return 0;
}
