#ifndef TITULAR_H
#define TITULAR_H

typedef struct 
{
    char nombre [20];
    long int cuit;
    char tipoDocumento [10];
    int nroDocumento; //[PK]
    char fechaNacimiento [20]; //Se puede usar DATE
    int idDomicilio; //[FK] Domicilio
}Titular;
  
// Funciones principales
void altaTitular();
void listarTitularesConVehiculos();

// Auxiliar
int titularExiste(int dni);

#endif