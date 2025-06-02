#include <stdio.h>
#include <string.h>
#include "automotor.h"
#include "historialevento.h"

void altaEvento(){
    FILE *fe = fopen("historial.txt", "a");
    if (!fe) {
        printf("Error al abrir el archivo de historial.\n");
        return;
    }

    HistorialEvento e;

    // Mostrar vehiculos
    listarVehiculosConID();

    // Validar ID ingresado
    do {
        printf("Ingrese ID del vehiculo: ");
        scanf("%d", &e.idVehiculo);
        printf("Leyendo ID: %d\n", e.idVehiculo);
        if (!idVehiculoExiste(e.idVehiculo)) {
            printf("ID invalido. Intente de nuevo.\n");
        }
    } while (!idVehiculoExiste(e.idVehiculo));
    getchar(); // limpiar buffer

    printf("Ingrese tipo de evento (Multa, Accidente, etc): ");
    fgets(e.tipoEvento, sizeof(e.tipoEvento), stdin);
    e.tipoEvento[strcspn(e.tipoEvento, "\n")] = '\0';

    printf("Ingrese descripcion del evento: ");
    fgets(e.descripcion, sizeof(e.descripcion), stdin);
    e.descripcion[strcspn(e.descripcion, "\n")] = '\0';

    printf("Ingrese fecha (dd/mm/aaaa): ");
    fgets(e.fecha, sizeof(e.fecha), stdin);
    e.fecha[strcspn(e.fecha, "\n")] = '\0';

    // Generar idEvento automaticamente
    FILE *fr = fopen("historial.txt", "r");
    int ultimoID = 0;
    if (fr) {
        HistorialEvento temp;
        while (fscanf(fr, "%d;%*d;%*[^;];%*[^;];%*s\n", &temp.idEvento) == 1) {
            ultimoID = temp.idEvento;
        }
        fclose(fr);
    }
    e.idEvento = ultimoID + 1;

    fprintf(fe, "%d;%d;%s;%s;%s\n",
            e.idEvento, e.idVehiculo, e.tipoEvento, e.descripcion, e.fecha);

    fclose(fe);
    printf("Evento registrado correctamente.\n");

}


void verHistorialEvento(){
    FILE *fe = fopen("historial.txt", "r");
    if (!fe) {
        printf("No se pudo abrir el archivo de historial.\n");
        return;
    }

    int idVehiculo;
     do {
        printf("Ingrese ID del vehiculo para ver su historial: ");
        scanf("%d", &idVehiculo);
        printf("Leyendo ID: %d\n", idVehiculo);
        if (!idVehiculoExiste(idVehiculo)) {
            printf("ID invalido. Intente de nuevo.\n");
        }
    } while (!idVehiculoExiste(idVehiculo));
    getchar(); // limpiar buffer

    HistorialEvento e;
    int encontrado = 0;

    while (fscanf(fe, "%d;%d;%[^;];%[^;];%[^\n]\n",
                  &e.idEvento, &e.idVehiculo, e.tipoEvento, e.descripcion, e.fecha) == 5) {
        if (e.idVehiculo == idVehiculo) {
            if (!encontrado) {
                printf("\n--- Historial del Vehiculo ID %d ---\n", idVehiculo);
                encontrado = 1;
            }
            printf("ID Evento: %d\nTipo: %s\nDescripcion: %s\nFecha: %s\n\n",
                   e.idEvento, e.tipoEvento, e.descripcion, e.fecha);
        }
    }

    if (!encontrado) {
        printf("No se encontraron eventos para este vehiculo.\n");
    }

    fclose(fe);
}