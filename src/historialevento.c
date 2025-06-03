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
    listarTodos();

     // Validar dominio ingresado
    do {
        printf("Ingrese DOMINIO del vehiculo: ");
        fgets(e.dominioAutomotor, sizeof(e.dominioAutomotor), stdin);
        e.dominioAutomotor[strcspn(e.dominioAutomotor, "\n")] = '\0'; 
        if (!dominioAutomotorExiste(e.dominioAutomotor)) {
            printf("Dominio invalido. Intente de nuevo.\n");
        }
    } while (!dominioAutomotorExiste(e.dominioAutomotor));
    

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
        while (fscanf(fr, "%d;%9[^;];%14[^;];%49[^;];%14s\n", &temp.idEvento, temp.dominioAutomotor, temp.tipoEvento, temp.descripcion, temp.fecha) == 5){
            ultimoID = temp.idEvento;
        }
        fclose(fr);
    }
    e.idEvento = ultimoID + 1;

    fprintf(fe, "%d;%s;%s;%s;%s\n",
            e.idEvento, e.dominioAutomotor, e.tipoEvento, e.descripcion, e.fecha);

    fclose(fe);
    printf("Evento registrado correctamente.\n");

}


void verHistorialEvento(){
    FILE *fe = fopen("historial.txt", "r");
    if (!fe) {
        printf("No se pudo abrir el archivo de historial.\n");
        return;
    }

    char dominio[10];
    do {
        printf("Ingrese el DOMINIO del vehiculo para ver su historial: ");
        fgets(dominio, sizeof(dominio), stdin);
        dominio[strcspn(dominio, "\n")] = '\0';
        if (!dominioAutomotorExiste(dominio)) {
            printf("Dominio invalido. Intente de nuevo.\n");
        }
    } while (!dominioAutomotorExiste(dominio));
    
    HistorialEvento e;
    int encontrado = 0;

     while (fscanf(fe, "%d;%[^;];%[^;];%[^;];%[^\n]\n",
                  &e.idEvento, e.dominioAutomotor, e.tipoEvento, e.descripcion, e.fecha) == 5) {
        if (strcmp(e.dominioAutomotor, dominio) == 0) {
            if (!encontrado) {
                printf("\n--- Historial del Vehiculo Dominio %s ---\n", dominio);
                encontrado = 1;
            }
            printf("ID Evento: %d  |  Tipo: %s  |  Descripcion: %s  |  Fecha: %s\n",
                   e.idEvento, e.tipoEvento, e.descripcion, e.fecha);
        }
    }

    if (!encontrado) {
        printf("No se encontraron eventos para este vehiculo.\n");
    }

    fclose(fe);
}