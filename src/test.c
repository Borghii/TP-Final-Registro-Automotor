#include <stdio.h>
#include "historialevento.h"
#include "automotor.h"
#include "cedula.h"
#include "domicilio.h"
#include "titular.h"
#include "registro.h"
#include "utils.h"

void testAutomotor();
void testHistorialEvento();
void testCedula();
void testDomicilio();
void testRegistro();
void testTitular();


// gcc test.c automotor.c cedula.c titular.c historialevento.c registro.c domicilio.c utils.c -o test

int main(){

    //testAutomotor();
    
    //testHistorialEvento();

    testCedula();

    //testDomicilio();

    //testTitular();

    //testRegistro();

    return 0;
};

void testAutomotor(){
    // transferirVehiculo();

    altaAutomotor();
    //listarTodos();
    //consultarInformacionConDominio();
    //bajaAutomotor();
}


void testHistorialEvento(){
    //altaEvento(); 
    verHistorialEvento();
}


void testCedula(){
    altaCedula();
}

void testDomicilio(){
    //crearDomicilio();
}

void testTitular(){
    altaTitular();
    //listarTitularesConVehiculos();
}

void testRegistro(){
    //altaRegistro();
    //listarRegistros();
    //reporteRegistrosCantidadAutos();
    //buscarVehiculosPorRegistro();
}




