#include <stdio.h>
#include "titular.h"
#include "automotor.h"
#include "menu.h"
#include "cedula.h"
#include "registro.h"
#include "historialevento.h"
#include "utils.h"

int condition = 1; // Variable para controlar si se muestra el mensaje de bienvenida

void menuShow()
{
    if (condition)
    {
        printf("\n\n ---- BIENVENIDO AL SISTEMA DE REGISTRO AUTOMOTOR DNRPA ---- \n\n");
        printf("Este sistema permite gestionar titulares, automotores y sus registros.\n");
        printf("Puede realizar altas, bajas, transferencias y consultar informacion de vehiculos.\n");
        printf("Ademas, permite registrar eventos y generar reportes sobre los vehiculos.\n");
        printf("Para comenzar, seleccione una de las opciones del menu.\n");
        condition = 0; // Cambiamos la variable para que no se vuelva a mostrar el mensaje

    }
    
    printf("\n\n ---- REGISTRO AUTOMOTOR DNRPA---- \n\n");
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
        leerEnteroValidado("\nIngrese una opcion: ", &opcion);

        if (opcion < a || opcion > b) 
        {
            printf("Opcion incorrecta. Debe ser un numero entre %d y %d.\n", a, b);
        }


    } while (opcion<a || opcion>b);
   
    return opcion;
}

void menuTitulares()
{
    int op=1;
    do
    {
        printf("\n\n---- MENU TITULARES ----\n\n");
        printf("1) Alta titular.\n");
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
        
        }
    } while (op!=0);    
}

void menuAutomotores()
{   
    int op=1;
    do
    {
        printf("\n\n---- MENU AUTOMOTORES ----\n\n");
        printf("1) Alta automotor.\n");
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
        
        }
    } while (op!=0);
}

void menuReportes()
{
    int op=1;
    do
    {
        printf("\n\n---- MENU REPORTES ----\n\n");
        printf("1) Listar vehiculos por registro.\n");
        printf("2) Reporte cantidad de vehiculos registrados.\n");
        printf("0) Volver.\n");
        op = pedirOpcion(0,3);
        switch (op)
        {
        case 1:
            buscarVehiculosPorRegistro();
            break;

        case 2:
            reporteRegistrosCantidadAutos();
            break;

        case 0:
            op=0;
            break;
        
        }
    } while (op!=0);
}