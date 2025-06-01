#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "automotor.h"
#include "registro.h"

int idVehiculoExiste(int idBuscado) {
    FILE *archivo = fopen("registro.txt", "r");
    if (archivo == NULL) {
        return 0; // Si no existe el archivo, no hay IDs registrados aún
    }

    Automotor temp;

    while (fscanf(archivo, "%d;%[^;];%[^;];%[^;];%[^;];%[^;%d;%[^;];%[^;];%d;%d;%d\n",
            &temp.idVehiculo,
            temp.dominio,
            temp.marca,
            temp.modelo,
            temp.chasis,
            temp.motor,
            &temp.anioFabricacion,
            temp.paisOrigen,
            temp.tipoUso,
            &temp.peso,
            &temp.nroDocTitular,
            &temp.nroRegistro) == 12)
    {
        if (temp.idVehiculo == idBuscado) {
            fclose(archivo);
            return 1; // Ya existe
        }
    }

    fclose(archivo);
    return 0; // No existe
}

void altaAutomotor() {
    FILE *archivo = fopen("registro.txt", "a"); // modo append
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Automotor autoNuevo;

    do {        
        autoNuevo.idVehiculo = rand() % 10000; // Ejemplo: ID aleatorio entre 0 y 9999
    } while (idVehiculoExiste(autoNuevo.idVehiculo));


    getchar();

    printf("Ingrese dominio: ");
    fgets(autoNuevo.dominio, sizeof(autoNuevo.dominio), stdin);
    autoNuevo.dominio[strcspn(autoNuevo.dominio, "\n")] = '\0';

    printf("Ingrese marca: ");
    fgets(autoNuevo.marca, sizeof(autoNuevo.marca), stdin);
    autoNuevo.marca[strcspn(autoNuevo.marca, "\n")] = '\0';

    printf("Ingrese modelo: ");
    fgets(autoNuevo.modelo, sizeof(autoNuevo.modelo), stdin);
    autoNuevo.modelo[strcspn(autoNuevo.modelo, "\n")] = '\0';

    printf("Ingrese numero de chasis: ");
    fgets(autoNuevo.chasis, sizeof(autoNuevo.chasis), stdin);
    autoNuevo.chasis[strcspn(autoNuevo.chasis, "\n")] = '\0';


    printf("Ingrese numero de motor: ");
    fgets(autoNuevo.motor, sizeof(autoNuevo.motor), stdin);
    autoNuevo.motor[strcspn(autoNuevo.motor, "\n")] = '\0';


    printf("Ingrese anio de fabricacion: ");
    scanf("%d", &autoNuevo.anioFabricacion);
    getchar(); // limpia el '\n' que queda en el buffer

    printf("Ingrese pais de origen: ");
    fgets(autoNuevo.paisOrigen, sizeof(autoNuevo.paisOrigen), stdin);
    autoNuevo.paisOrigen[strcspn(autoNuevo.paisOrigen, "\n")] = '\0';

    printf("Ingrese tipo de uso: ");
    fgets(autoNuevo.tipoUso, sizeof(autoNuevo.tipoUso), stdin);
    autoNuevo.tipoUso[strcspn(autoNuevo.tipoUso, "\n")] = '\0';

    printf("Ingrese peso (kg): ");
    scanf("%d", &autoNuevo.peso);

    printf("Ingrese Nro. Documento del titular: ");
    scanf("%d", &autoNuevo.nroDocTitular);

    autoNuevo.nroRegistro = seleccionarRegistro();

    // Escribir en el archivo (formato de texto plano)
    fprintf(archivo, "%d;%s;%s;%s;%s;%s;%d;%s;%s;%d;%d;%d\n",
        autoNuevo.idVehiculo,
        autoNuevo.dominio,
        autoNuevo.marca,
        autoNuevo.modelo,
        autoNuevo.chasis,
        autoNuevo.motor,
        autoNuevo.anioFabricacion,
        autoNuevo.paisOrigen,
        autoNuevo.tipoUso,
        autoNuevo.peso,
        autoNuevo.nroDocTitular,
        autoNuevo.nroRegistro
    );

    fclose(archivo);
    printf("Automotor guardado exitosamente.\n");
}

void listarTodos() {
    FILE *archivo = fopen("registro.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de registros.\n");
        return;
    }

    Automotor autoLeido;
    char linea[256];

    printf("\n--- LISTADO DE AUTOMOTORES ---\n");

    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%d;%9[^;];%19[^;];%19[^;];%19[^;];%19[^;];%d;%19[^;];%14[^;];%d;%d;%d",
            &autoLeido.idVehiculo,
            autoLeido.dominio,
            autoLeido.marca,
            autoLeido.modelo,
            autoLeido.chasis,
            autoLeido.motor,
            &autoLeido.anioFabricacion,
            autoLeido.paisOrigen,
            autoLeido.tipoUso,
            &autoLeido.peso,
            &autoLeido.nroDocTitular,
            &autoLeido.nroRegistro
        );

        printf("\nID Vehiculo: %d\n", autoLeido.idVehiculo);
        printf("Dominio: %s\n", autoLeido.dominio);
        printf("Marca: %s\n", autoLeido.marca);
        printf("Modelo: %s\n", autoLeido.modelo);
        printf("Chasis: %s\n", autoLeido.chasis);
        printf("Motor: %s\n", autoLeido.motor);
        printf("Anioo de Fabricacion: %d\n", autoLeido.anioFabricacion);
        printf("Pais de Origen: %s\n", autoLeido.paisOrigen);
        printf("Tipo de Uso: %s\n", autoLeido.tipoUso);
        printf("Peso: %d kg\n", autoLeido.peso);
        printf("DNI Titular: %d\n", autoLeido.nroDocTitular);
        printf("Nro. de registro: %d\n", autoLeido.nroRegistro);
    }

    fclose(archivo);
}

void bajaVehiculo() {
    int idEliminar;
    printf("Ingrese el ID del vehiculo que desea dar de baja: ");
    scanf("%d", &idEliminar);

    FILE *original = fopen("registro.txt", "r");
    FILE *temporal = fopen("temp.txt", "w");

    if (original == NULL || temporal == NULL) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    Automotor a;
    int encontrado = 0;

    while (fscanf(original, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;];%d;%d;%d\n",
                  &a.idVehiculo,
                  a.dominio,
                  a.marca,
                  a.modelo,
                  a.chasis,
                  a.motor,
                  &a.anioFabricacion,
                  a.paisOrigen,
                  a.tipoUso,
                  &a.peso,
                  &a.nroDocTitular,
                  &a.nroRegistro) == 12) {

        if (a.idVehiculo == idEliminar) {
            encontrado = 1;
            continue; // No lo escribimos, lo "eliminamos"
        }

        fprintf(temporal, "%d;%s;%s;%s;%s;%s;%d;%s;%s;%d;%d;%d\n",
                a.idVehiculo,
                a.dominio,
                a.marca,
                a.modelo,
                a.chasis,
                a.motor,
                a.anioFabricacion,
                a.paisOrigen,
                a.tipoUso,
                a.peso,
                a.nroDocTitular,
                a.nroRegistro);
    }

    fclose(original);
    fclose(temporal);

    // Reemplazar archivo original
    remove("registro.txt");
    rename("temp.txt", "registro.txt");

    if (encontrado) {
        printf("Vehiculo con ID %d dado de baja exitosamente.\n", idEliminar);
    } else {
        printf("No se encontro un vehículo con ese ID.\n");
    }
}