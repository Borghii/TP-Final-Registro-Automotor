#ifndef CEDULA_H
#define CEDULA_H


typedef struct 
{
    int nroCedula; //[PK]
    char fechaEmision[11];
    char fechaVencimiento[11];
    int idVehiculo;  // [FK] de automotor
}Cedula;


void altaCedula();

#endif
