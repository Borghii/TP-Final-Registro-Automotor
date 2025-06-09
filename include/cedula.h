#ifndef CEDULA_H
#define CEDULA_H

//Formato del txt: nroCedula;fechaEmision;fechaVencimiento;dominioAutomotor

typedef struct 
{
    int nroCedula; //[PK]
    char fechaEmision[11];
    char fechaVencimiento[11];
    char dominioAutomotor[20];  // [FK] dominio de automotor
}Cedula;

//Funcines principales
void altaCedula();

//Funciones auxiliares
int leerRegistroCedula(FILE *archivo, Cedula *cedula);
int cedulaExiste(int nroCedula);


#endif
