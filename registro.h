#ifndef REGISTRO_H
#define REGISTRO_H

typedef struct
{
    int idRegistro; //[PK]
    int idDomicilio; //[FK] de domicilio
}Registro;



void altaRegistro();
void listarRegistros();
int seleccionarRegistro();

#endif
