#ifndef AUTOMOTOR_H
#define AUTOMOTOR_H


typedef struct
{
    char dominio [10]; // [PK] Patente tipo vieja: 7 caracteres (PMV 745). 
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

// Funciones Principales

void altaAutomotor();
void listarTodos();
void listarTodosFormateados();
void consultarInformacionConDominio();

// void bajaAutomotor();


//Auxiliares

int dominioAutomotorExiste(const char dominio[10]);
void listarVehiculoConDominio(const char dominio[10]);
int leerRegistroAutomotor(FILE *archivo, Automotor *automotor);

#endif
