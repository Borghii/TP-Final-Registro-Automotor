#include <stdio.h>
#include <string.h>
#include "cedula.h"
#include "automotor.h"
#include "utils.h"

void altaCedula() {
    FILE *archivo = fopen("cedulas.txt", "a");

    if (archivo == NULL) {
        printf("Error al abrir el archivo de cedulas.\n");
        return;
    }

    Cedula nueva;

    do
    {
        leerEnteroValidado("Ingrese numero de cedula: ", &nueva.nroCedula);

        if (cedulaExiste(nueva.nroCedula)) {
            printf("El numero de cedula ya existe. Ingrese uno diferente.\n");
        }

    } while (cedulaExiste(nueva.nroCedula));


    printf("Ingrese fecha de emision (dd/mm/aaaa): ");
    fgets(nueva.fechaEmision, sizeof(nueva.fechaEmision), stdin);
    nueva.fechaEmision[strcspn(nueva.fechaEmision, "\n")] = '\0';


    printf("Ingrese fecha de vencimiento (dd/mm/aaaa): ");
    fgets(nueva.fechaVencimiento, sizeof(nueva.fechaVencimiento), stdin);
    nueva.fechaVencimiento[strcspn(nueva.fechaVencimiento, "\n")] = '\0';


    do
    {
        printf("Ingrese dominio/patente del vehiculo: ");
        fgets(nueva.dominioAutomotor, sizeof(nueva.dominioAutomotor), stdin);
        nueva.dominioAutomotor[strcspn(nueva.dominioAutomotor, "\n")] = '\0';

        if (!dominioAutomotorExiste(nueva.dominioAutomotor)  ) {
            printf("El dominio ingresado no existe. Ingrese uno valido.\n");
        }

    } while (!dominioAutomotorExiste(nueva.dominioAutomotor));
    

    fprintf(archivo, "%d;%s;%s;%s\n",
        nueva.nroCedula,
        nueva.fechaEmision,
        nueva.fechaVencimiento,
        nueva.dominioAutomotor
    );

    fclose(archivo);
    printf("Cedula guardada exitosamente.\n");
}


int cedulaExiste(int nroCedula) {
    FILE *archivo = fopen("cedulas.txt", "r");
    if (archivo == NULL) {
        return 0; // No hay archivo aún: ningún registro
    }

    Cedula cedulaTemp;
    while (leerRegistroCedula(archivo, &cedulaTemp)) {
        if (cedulaTemp.nroCedula == nroCedula) {
            fclose(archivo);
            return 1; // Ya existe
        }
    }

    fclose(archivo);
    return 0; // No existe
}

int leerRegistroCedula(FILE *archivo, Cedula *cedula) {
    return fscanf(archivo, "%d;%10[^;];%10[^;];%19[^\n]\n",
                  &cedula->nroCedula,
                  cedula->fechaEmision,
                  cedula->fechaVencimiento,
                  cedula->dominioAutomotor) == 4;
}
