#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "automotor.h"
#include "titular.h"
#include "cedula.h"
#include "registro.h"

int main() {
    int opcion;


    altaRegistro();

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
                altaAutomotor();
                altaCedula();
                break;
            case 3:
                altaTitular();
                break;
            case 5:
                bajaVehiculo();
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            case 6:
                listarTodos();
                break;
            case 9:
                listarTitularesConVehiculos();
                break;
            default:
                printf("Opcion aun no implementada.\n");
        }

    } while (opcion != 0);

    return 0;
}
