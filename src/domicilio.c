#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "domicilio.h"  
#include "utils.h"

int existeIdDomicilio(int idBuscado) {
    FILE *archivo = fopen("domicilios.txt", "r");
    if (!archivo) return 0; // Si no existe el archivo, entonces no hay conflicto

    int id;
    while (fscanf(archivo, "%d;%*[^;];%*[^;];%*d;%*[^;];%*d\n", &id) == 1) {
        if (id == idBuscado) {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}


int crearDomicilio() {
    srand(time(NULL));
    FILE *archivo = fopen("domicilios.txt", "a+");
    if (!archivo) {
        printf("Error al abrir el archivo de domicilios.\n");
        return -1;
    }

    Domicilio nuevo;
    do {
        nuevo.idDomicilio = rand() % 10000; // Ejemplo: ID aleatorio entre 0 y 9999
    } while (existeIdDomicilio(nuevo.idDomicilio));



    printf("Ingrese ciudad: ");
    fgets(nuevo.ciudad, sizeof(nuevo.ciudad), stdin);
    nuevo.ciudad[strcspn(nuevo.ciudad, "\n")] = '\0';

    printf("Ingrese provincia: ");
    fgets(nuevo.provincia, sizeof(nuevo.provincia), stdin);
    nuevo.provincia[strcspn(nuevo.provincia, "\n")] = '\0';

    leerEnteroValidado("Ingrese codigo postal: ", &nuevo.codigoPostal);

    printf("Ingrese calle: ");
    fgets(nuevo.calle, sizeof(nuevo.calle), stdin);
    nuevo.calle[strcspn(nuevo.calle, "\n")] = '\0';

    leerEnteroValidado("Ingrese numero de calle: ", &nuevo.numero);

    fprintf(archivo, "%d;%s;%s;%d;%s;%d\n",
            nuevo.idDomicilio, nuevo.ciudad, nuevo.provincia,
            nuevo.codigoPostal, nuevo.calle, nuevo.numero);

    fclose(archivo);
    printf("Domicilio creado con ID %d\n", nuevo.idDomicilio);
    return nuevo.idDomicilio;
}