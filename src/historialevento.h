#ifndef HISTORIALEVENTO_H
#define HISTORIALEVENTO_H

typedef struct {
    int idEvento;
    int idVehiculo;
    char tipoEvento [15];
    char descripcion [50];
    char fecha[15];
} HistorialEvento;

void altaEvento();
void verHistorialEvento();


#endif