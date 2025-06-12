#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void limpiarSaltoLinea(char *str) {
    str[strcspn(str, "\n")] = '\0';
}


void leerCadena(char *buffer, int tam) {

    fflush(stdin);  
    

    int c;
    while ((c = getchar()) != '\n' && c != EOF && c != ' ' && c != '\t') {
        ungetc(c, stdin); 
        break;
    }
    
    if (fgets(buffer, tam, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } else {
        while ((c = getchar()) != '\n' && c != EOF);
        buffer[0] = '\0';
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

    return *endptr == '\0';
}

int leerEnteroValidado(const char *mensaje, int *resultado) {
    char buffer[100];

    while (1) {
        printf("%s", mensaje);
        fflush(stdout);  // IMPORTANTE: Forzar que se muestre el mensaje
        
        leerCadena(buffer, sizeof(buffer));

        // Verificar si el buffer está vacío (posible lectura automática)
        if (strlen(buffer) == 0) {
            printf("No se detecto entrada. Intenta de nuevo.\n");
            continue;
        }

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
        fflush(stdout);  // IMPORTANTE: Forzar que se muestre el mensaje
        
        leerCadena(buffer, sizeof(buffer));

        // Verificar si el buffer está vacío
        if (strlen(buffer) == 0) {
            printf("No se detecto entrada. Intenta de nuevo.\n");
            continue;
        }

        if (esLong(buffer)) {
            *resultado = strtol(buffer, NULL, 10);
            return 1;
        }

        printf("Entrada invalida. Ingresa un numero long valido.\n");
    }
}

enum CodigoFecha {
    FECHA_OK = 0,
    FORMATO_INVALIDO,
    DIA_INVALIDO,
    MES_INVALIDO,
    ANIO_INVALIDO,
    DIA_EXCEDE_MAXIMO
};

int validarFecha(const char *fecha, int *codigoError) {
    if (strlen(fecha) != 10) {
        *codigoError = FORMATO_INVALIDO;
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (fecha[i] != '/') {
                *codigoError = FORMATO_INVALIDO;
                return 0;
            }
        } else if (!isdigit(fecha[i])) {
            *codigoError = FORMATO_INVALIDO;
            return 0;
        }
    }

    char diaStr[3], mesStr[3], anioStr[5];
    strncpy(diaStr, fecha, 2); diaStr[2] = '\0';
    strncpy(mesStr, fecha + 3, 2); mesStr[2] = '\0';
    strncpy(anioStr, fecha + 6, 4); anioStr[4] = '\0';

    int dia = atoi(diaStr);
    int mes = atoi(mesStr);
    int anio = atoi(anioStr);

    if (mes < 1 || mes > 12) {
        *codigoError = MES_INVALIDO;
        return 0;
    }
    if (dia < 1 || dia > 31) {
        *codigoError = DIA_INVALIDO;
        return 0;
    }
    if (anio < 1) {
        *codigoError = ANIO_INVALIDO;
        return 0;
    }

    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        *codigoError = DIA_EXCEDE_MAXIMO;
        return 0;
    }

    if (mes == 2) {
        int bisiesto = (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
        int maxDia = bisiesto ? 29 : 28;
        if (dia > maxDia) {
            *codigoError = DIA_EXCEDE_MAXIMO;
            return 0;
        }
    }

    *codigoError = FECHA_OK;
    return 1;
}

int leerFechaValidada(const char *mensaje, char *buffer, int tam) {
    int error;

    while (1) {
        printf("%s", mensaje);
        fflush(stdout);  // IMPORTANTE: Forzar que se muestre el mensaje
        
        leerCadena(buffer, tam);

        // Verificar si el buffer está vacío
        if (strlen(buffer) == 0) {
            printf("No se detecto entrada. Intenta de nuevo.\n");
            continue;
        }

        if (validarFecha(buffer, &error)) {
            return 1;
        }

        switch (error) {
            case FORMATO_INVALIDO:
                printf("Error: El formato debe ser dd/mm/aaaa (con digitos y '/').\n");
                break;
            case DIA_INVALIDO:
                printf("Error: DDia invalido (debe estar entre 1 y 31).\n");
                break;
            case MES_INVALIDO:
                printf("Error: Mes invalido (debe estar entre 1 y 12).\n");
                break;
            case ANIO_INVALIDO:
                printf("Error: Año invalido.\n");
                break;
            case DIA_EXCEDE_MAXIMO:
                printf("Error: El dia excede el maximo permitido para ese mes.\n");
                break;
            default:
                printf("Error desconocido.\n");
        }
    }
}