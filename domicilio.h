#ifndef DOMICILIO_H
#define DOMICILIO_H

typedef struct
{
    int idDomicilio; //[PK] Voy a probar de hacerla con un random
    char ciudad [20];
    char provincia [20];
    int codigoPostal;
    char calle [20];
    int numero;
}Domicilio;

int existeIdDomicilio(int idBuscado);
int crearDomicilio();


#endif