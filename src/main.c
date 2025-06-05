#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "automotor.h"
#include "titular.h"
#include "cedula.h"
#include "registro.h"
#include "domicilio.h"

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
        opcion = pedirOpcion(0, 5);

        switch (opcion) {
            case 1:
                menuTitulares();
                break;

            case 2:
                menuAutomotores();
                break;
            
            case 3:
                altaRegistro();
                break;
            
            case 4:
                altaCedula();
                break;

            case 5:
                menuReportes();
                break;

            case 0:
                printf("Saliendo del sistema...\n");
                break;   
        }

    } while (opcion != 0);
    return 0;
}
