#include <stdio.h>
#include "historialevento.h"

#include "automotor.h"

void testConsultarinformacionVehiculo();
void testAltaHistorialEvento();

int main(){

    testConsultarinformacionVehiculo();
    
    return 0;
}


void testConsultarinformacionVehiculo(){
    consultarInformacionConDominio();
}

void testAltaHistorialEvento(){
    altaEvento();
    verHistorialEvento();
}

