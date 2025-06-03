#include <stdio.h>
#include <string.h>
#include "cedula.h"

void altaCedula() {
    FILE *archivo = fopen("cedulas.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de cedulas.\n");
        return;
    }

    Cedula nueva;

    printf("Ingrese numero de cedula: ");
    scanf("%d", &nueva.nroCedula);
    getchar(); // limpia el '\n' que queda en el buffer

    printf("Ingrese fecha de emision (dd/mm/aaaa): ");
    fgets(nueva.fechaEmision, sizeof(nueva.fechaEmision), stdin);
    nueva.fechaEmision[strcspn(nueva.fechaEmision, "\n")] = '\0';


    printf("Ingrese fecha de vencimiento (dd/mm/aaaa): ");
    fgets(nueva.fechaVencimiento, sizeof(nueva.fechaVencimiento), stdin);
    nueva.fechaVencimiento[strcspn(nueva.fechaVencimiento, "\n")] = '\0';


    printf("Ingrese dominio/patente del vehiculo: ");
    fgets(nueva.dominioAutomotor, sizeof(nueva.dominioAutomotor), stdin);
    nueva.dominioAutomotor[strcspn(nueva.dominioAutomotor, "\n")] = '\0';


    fprintf(archivo, "%d;%s;%s;%s\n",
        nueva.nroCedula,
        nueva.fechaEmision,
        nueva.fechaVencimiento,
        nueva.dominioAutomotor
    );

    fclose(archivo);
    printf("Cedula guardada exitosamente.\n");
}

