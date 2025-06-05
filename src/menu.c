#include <stdio.h>
#include "titular.h"
#include "automotor.h"
#include "menu.h"
#include "cedula.h"
#include "registro.h"
#include "historialevento.h"
#include "utils.h"

void menuShow()
{
    printf("\n ---- REGISTRO AUTOMOTOR DNRPA---- \n");
    printf("1) GESTION TITULARES\n");
    printf("2) GESTION AUTOMOTORES\n");
    printf("3) ALTA REGISTRO \n");
    printf("4) ALTA CEDULA\n");
    printf("5) REPORTES\n");
    printf("0) SALIR\n");
}

int pedirOpcion(int a, int b) //Pasamos los parametros entre los que oscila lo que buscamos. En el caso del menu 0 y 8
{
    int opcion;
    do
    {
        leerEnteroValidado("Ingrese una opcion: ", &opcion);

    } while (opcion<a || opcion>b);
   
    return opcion;
}

void menuTitulares()
{
    int op=1;
    do
    {
        printf("\n\n1) Alta titular.\n");
        printf("2) Mostrar titulares con vehiculos.\n");
        printf("0) Volver.\n");
        op = pedirOpcion(0,3);
        switch (op)
        {
        case 1:
            altaTitular();
            break;

        case 2:
            listarTitularesConVehiculos();
            break;

        case 0:
            op=0;
            break;
        
        default:
            printf("\n Opcion incorrecta. \n");
            break;
        }
    } while (op!=0);    
}

void menuAutomotores()
{   
    int op=1;
    do
    {
        printf("\n\n1) Alta automotor.\n");
        printf("2) Baja automotor.\n");
        printf("3) Transferir vehiculo.\n");
        printf("4) Buscar con dominio.\n");
        printf("5) Listar todos los vehiculos.\n");
        printf("6) Registrar evento. \n");
        printf("7) Ver historial de eventos. \n");
        printf("0) Volver.\n");
        op = pedirOpcion(0,7);
        switch (op)
        {
        case 1:
                
            altaAutomotor();  
            altaCedula();
                
            break;

        case 2:
            bajaAutomotor();
            break;

        case 3:
            transferirVehiculo();
            break;
        
        case 4:
            consultarInformacionConDominio();
            break;
        
        case 5:
            listarTodos();
            break;
        
        case 6:
            altaEvento();
            break;

        case 7:
            verHistorialEvento();
            break;

        case 0:
            op=0;
            break;
        
        default:
            printf("\n Opcion incorrecta. \n");
            break;
        }
    } while (op!=0);
}

void menuReportes()
{
    int op=1;
    do
    {
        printf("\n\n1) Listar vehiculos por registro.\n");
        printf("2) Reporte cantidad de vehiculos registrados.\n");
        printf("0) Volver.\n");
        op = pedirOpcion(0,3);
        switch (op)
        {
        case 1:
            listarRegistros();
            break;

        case 2:
            reporteRegistrosCantidadAutos();
            break;

        case 0:
            op=0;
            break;
        
        default:
            printf("\n Opcion incorrecta. \n");
            break;
        }
    } while (op!=0);
}