#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "automotor.h"
#include "titular.h"
#include "cedula.h"
#include "registro.h"

int main() {
    int opcion;

    if (!existenRegistros()) {
        printf("No existe ningun registro en el sistema.\n");
        printf("Desea crear uno ahora? (s/n): ");
        char respuesta;
        scanf("%c", &respuesta);
        if (respuesta == 's' || respuesta == 'S') {
            altaRegistro(); // Creamos el primer registro
        } else {
            printf("No se puede continuar sin al menos un registro.\n");
            return 0;
        }
    }
    do {
        menuShow();
        opcion = pedirOpcion(0, 10);

        switch (opcion) {
            case 1:
                altaTitular();
                altaAutomotor();
                altaCedula();
                break;

            case 2:
                int dni;
                printf("Ingrese DNI del titular al que se le asignara el vehiculo: ");
                scanf("%d", &dni);
                if (!titularExiste(dni)) {
                    printf("ERROR: No existe un titular con el DNI %d. Debe darlo de alta primero.\n", dni);
                } else {
                    altaAutomotor();  // Se podria mejorar pasandole como parametro dni para no pedirlo de nuevo cuando se da de alta.
                    altaCedula();
                }
                break;
            
            case 3:
                altaTitular();
                break;

            //case 4:
            //    transferirVehiculo();
            //    break;

            case 5:
                bajaAutomotor();
                break;

            case 6:
                listarTodos();
                break;

            //case 7:
            //    buscarPorDocumento();
            //    break;

            //case 8:
            //    buscarPorDominio();
            //    break;

            case 9:
                listarTitularesConVehiculos();
                break;


            case 0:
                printf("Saliendo del sistema...\n");
                break;   

            default:
                printf("Opcion aun no implementada.\n");
        }

    } while (opcion != 0);
    return 0;
}
