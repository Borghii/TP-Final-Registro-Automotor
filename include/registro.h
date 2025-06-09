#ifndef REGISTRO_H
#define REGISTRO_H

typedef struct
{
    int idRegistro; //[PK]
    int idDomicilio; //[FK] de domicilio
}Registro;


// Funciones principales
void altaRegistro();
void listarRegistros();
void reporteRegistrosCantidadAutos();
void buscarVehiculosPorRegistro();

// Auxiliar
int seleccionarRegistro();
int existenRegistros();

#endif
