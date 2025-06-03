#ifndef TITULAR_H
#define TITULAR_H

typedef struct 
{
    char nombre [20];
    int cuit;
    char tipoDocumento [10];
    int nroDocumento; //[PK]
    char fechaNacimiento [20]; //Se puede usar DATE
    int idDomicilio; //[FK] Domicilio
}Titular;
    
void altaTitular();
void listarTitularesConVehiculos();
int titularExiste(int dni);

#endif