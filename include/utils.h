#ifndef UTILS_H
#define UTILS_H

int esEntero(const char *str);
int esLong(const char *str);

void leerCadena(char *buffer, int tamano);

int leerEnteroValidado(const char *mensaje, int *resultado);
int leerLongValidado(const char *mensaje, long *resultado);

int validarFecha(const char *fecha, int *codigoError);
int leerFechaValidada(const char *mensaje, char *buffer, int tam);


#endif
