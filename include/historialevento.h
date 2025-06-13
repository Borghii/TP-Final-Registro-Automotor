#ifndef HISTORIALEVENTO_H
#define HISTORIALEVENTO_H

typedef struct {
    int idEvento;
    char dominioAutomotor[10];  // FK: dominio del automotor
    char tipoEvento[15];
    char descripcion[50];
    char fecha[15];
} HistorialEvento;

//Funciones Principales
void altaEvento();
void verHistorialEvento();

//Funciones Auxiliares
int leerRegistroHistorialEvento(FILE *archivo, HistorialEvento *evento);


#endif