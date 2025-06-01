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


    printf("Ingrese id del vehiculo: ");
    scanf("%d", &nueva.idVehiculo);
    getchar(); // limpia el '\n' que queda en el buffer


    fprintf(archivo, "%d;%s;%s;%d\n",
        nueva.nroCedula,
        nueva.fechaEmision,
        nueva.fechaVencimiento,
        nueva.idVehiculo
    );

    fclose(archivo);
    printf("Cedula guardada exitosamente.\n");
}
