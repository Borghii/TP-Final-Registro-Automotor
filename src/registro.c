#include <stdio.h>
#include "registro.h"
#include "domicilio.h"

void altaRegistro() {
    FILE *fr = fopen("registros.txt", "r");
    int ultimoID = 0;
    Registro temp;

    if (fr != NULL) {
        while (fscanf(fr, "%d;%d\n", &temp.idRegistro, &temp.idDomicilio) == 2) {
            if (temp.idRegistro > ultimoID)
                ultimoID = temp.idRegistro;
        }
        fclose(fr);
    }

    Registro r;
    r.idRegistro = ultimoID + 1;
    r.idDomicilio = crearDomicilio();

    fr = fopen("registros.txt", "a");
    if (!fr) {
        printf("Error al abrir registros.txt para escritura.\n");
        return;
    }

    fprintf(fr, "%d;%d\n", r.idRegistro, r.idDomicilio);
    fclose(fr);

    printf("Registro creado con ID: %d\n", r.idRegistro);
}



void listarRegistros() {
    FILE *fr = fopen("registros.txt", "r");
    FILE *fd = fopen("domicilios.txt", "r");
    if (!fr || !fd) {
        printf("Error al abrir archivos.\n");
        return;
    }

    Registro r;
    Domicilio d;

    while (fscanf(fr, "%d;%d\n", &r.idRegistro, &r.idDomicilio) == 2) {
        rewind(fd);
        int encontrado = 0;

        while (fscanf(fd, "%d;%[^;];%[^;];%d;%[^;];%d\n",
                      &d.idDomicilio, d.ciudad, d.provincia,
                      &d.codigoPostal, d.calle, &d.numero) == 6) {
            if (d.idDomicilio == r.idDomicilio) {
                printf("ID Registro: %d - Direccion: %s %d, %s (%d), %s\n",
                       r.idRegistro, d.calle, d.numero, d.ciudad, d.codigoPostal, d.provincia);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("ID Registro: %d - Domicilio no encontrado\n", r.idRegistro);
        }
    }

    fclose(fr);
    fclose(fd);
}


int seleccionarRegistro() {
    printf("\n Registros disponibles:");
    listarRegistros();
    int idSel;
    printf("Seleccione el ID del registro: ");
    scanf("%d", &idSel);
    return idSel;
}