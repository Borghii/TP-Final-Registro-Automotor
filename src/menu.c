#include <stdio.h>
#include "menu.h"
void menuShow()
{
    printf("\n ---- REGISTRO AUTOMOTOR DNRPA---- \n");
    printf("1) Alta general.\n");
    printf("2) Alta vehiculo y cedula.\n");
    printf("3) Alta titular.\n");
    printf("4) Transferir vehiculo.\n");
    printf("5) Baja vehiculo y cedula.\n");
    printf("6) Listar TODOS.\n");
    printf("7) Buscar por documento.\n");
    printf("8) Buscar por dominio.\n");
    printf("9) Listar titulares.\n");
    printf("0) SALIR \n");
}
int pedirOpcion(int a, int b) //Pasamos los parametros entre los que oscila lo que buscamos. En el caso del menu 0 y 8
{
    int opcion;
    do
    {
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
    } while (opcion<a || opcion>b);
   
    return opcion;
}