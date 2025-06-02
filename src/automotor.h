#ifndef AUTOMOTOR_H
#define AUTOMOTOR_H


typedef struct
{
    int idVehiculo; //[PK]
    char dominio [10]; // Patente tipo vieja: 7 caracteres (PMV 745). 
    char marca [20]; // Marca: Volkswagen.
    char modelo [20]; // Modelo: Vento.
    char chasis [20]; // Numero de chasis: 17 caracteres (3VWRD61K98M135658).
    char motor [20]; // Numero de motor: 9 caracteres (BWA713474).
    int anioFabricacion;
    char paisOrigen [20];
    char tipoUso [15]; // Puede ser: PRIVADO, PROFESIONAL, PUBLICO, MAQUINARIA AGRICOLA.
    int peso; //en kg, usamos int para simplificar la impresion.
    int nroDocTitular; //[FK]
    int nroRegistro; //[FK] de registro
}Automotor;

void altaAutomotor();
int idVehiculoExiste(int idBuscado);
void listarTodos();
void bajaVehiculo();
void listarVehiculosConID();

#endif
