#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void limpiarSaltoLinea(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void leerCadena(char *buffer, int tamano) {
    if (fgets(buffer, tamano, stdin) != NULL) {
        limpiarSaltoLinea(buffer);
    }
}

int esEntero(const char *str) {
    if (*str == '-' || *str == '+') str++;
    if (*str == '\0') return 0;

    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }

    return 1;
}

int esLong(const char *str) {
    char *endptr;

    if (*str == '\0' || isspace(*str)) return 0;

    strtol(str, &endptr, 10);

    // endptr debe apuntar al final si es un número válido
    return *endptr == '\0';
}


int leerEnteroValidado(const char *mensaje, int *resultado) {
    char buffer[100];

    while (1) {
        printf("%s", mensaje);
        leerCadena(buffer, sizeof(buffer));

        if (esEntero(buffer)) {
            *resultado = atoi(buffer);
            return 1;
        }

        printf("Entrada invalida. Ingresa un numero entero valido.\n");
    }
}


int leerLongValidado(const char *mensaje, long *resultado) {
    char buffer[100];

    while (1) {
        printf("%s", mensaje);
        leerCadena(buffer, sizeof(buffer));

        if (esLong(buffer)) {
            *resultado = strtol(buffer, NULL, 10);
            return 1;
        }

        printf("Entrada invalida. Ingresa un numero long valido.\n");
    }
}
