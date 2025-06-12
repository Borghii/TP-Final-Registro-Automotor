#include <stdio.h>
#include "registro.h"
#include "domicilio.h"
#include "automotor.h"

int existenRegistros() {
    FILE *fr = fopen("data/registros.txt", "r");
    if (fr == NULL)
        return 0;

    int id, idDomicilio;
    int existe = fscanf(fr, "%d;%d", &id, &idDomicilio) == 2;
    fclose(fr);
    return existe;
}


void altaRegistro() {
    FILE *fr = fopen("data/registros.txt", "r");
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

    fr = fopen("data/registros.txt", "a");
    if (!fr) {
        printf("Error al abrir registros.txt para escritura.\n");
        return;
    }

    fprintf(fr, "%d;%d\n", r.idRegistro, r.idDomicilio);
    fclose(fr);

    printf("Registro creado con ID: %d\n", r.idRegistro);
}



void listarRegistros() {
    FILE *fr = fopen("data/registros.txt", "r");
    FILE *fd = fopen("data/domicilios.txt", "r");
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
    printf("\nRegistros disponibles:\n");
    listarRegistros(); // Asumo que esta función lista todos los registros con sus IDs

    int idSel;
    int encontrado = 0;
    FILE *fr = fopen("data/registros.txt", "r");
    if (!fr) {
        printf("Error al abrir archivo de registros.\n");
        return -1; // Código de error
    }

    do {
        printf("\nSeleccione el ID del registro: ");
        scanf("%d", &idSel);

        

        rewind(fr);
        encontrado = 0;
        int idRegistroAux, idDomicilioAux;
        while (fscanf(fr, "%d;%d\n", &idRegistroAux, &idDomicilioAux) == 2) {
            if (idRegistroAux == idSel) {
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("ID invalido. Por favor, ingrese un ID existente.\n");
        }
    } while (!encontrado);

    fclose(fr);
    return idSel;
}


void reporteRegistrosCantidadAutos() {
    FILE *fr = fopen("data/registros.txt", "r");
    FILE *fd = fopen("data/domicilios.txt", "r");
    FILE *fa = fopen("data/automotores.txt", "r");

    if (!fr || !fd || !fa) {
        printf("Error al abrir archivos.\n");
        if (fr) fclose(fr);
        if (fd) fclose(fd);
        if (fa) fclose(fa);
        return;
    }

    Registro r;
    Domicilio d;
    Automotor a;

    printf("ID  | Direccion                                          | Cant. Autos\n");
    printf("-------------------------------------------------------------------------\n");

    while (fscanf(fr, "%d;%d\n", &r.idRegistro, &r.idDomicilio) == 2) {
        // Buscar domicilio correspondiente
        rewind(fd);
        char direccion[100] = "No encontrada";

        while (fscanf(fd, "%d;%[^;];%[^;];%d;%[^;];%d\n",
                      &d.idDomicilio, d.ciudad, d.provincia, &d.codigoPostal, d.calle, &d.numero) == 6) {
            if (d.idDomicilio == r.idDomicilio) {
                snprintf(direccion, sizeof(direccion), "%s %d, %s (%d), %s",
                         d.calle, d.numero, d.ciudad, d.codigoPostal, d.provincia);
                break;
            }
        }

        // Contar cuántos automotores tiene ese registro
        rewind(fa);
        int contador = 0;
        while (leerRegistroAutomotor(fa, &a)) {
            if (a.nroRegistro == r.idRegistro) {
                contador++;
            }
        }

        // Imprimir línea del reporte
        printf("%-3d | %-50s | %d\n", r.idRegistro, direccion, contador);
    }

    fclose(fr);
    fclose(fd);
    fclose(fa);
}

void buscarVehiculosPorRegistro() {
    int idBusqueda = seleccionarRegistro();
    

    FILE *fa = fopen("data/automotores.txt", "r");
    if (!fa) {
        printf("Error al abrir el archivo de automotores.\n");
        return;
    }

    Automotor a;
    int encontrado = 0;


    printf("\nVehiculos en el registro %d:\n", idBusqueda);
    printf("Dominio    | Marca               | Modelo              | Anioo| Tipo Uso\n");
    printf("-----------------------------------------------------------------------\n");

    while (leerRegistroAutomotor(fa, &a)) {
        if (a.nroRegistro == idBusqueda) {
            encontrado = 1;
            printf("%-10s | %-19s | %-19s | %-3d | %s\n",
                   a.dominio, a.marca, a.modelo, a.anioFabricacion, a.tipoUso);
        }
    }

    if (!encontrado) {
        printf("No se encontraron vehiculos para ese registro.\n");
    }

    fclose(fa);
}
