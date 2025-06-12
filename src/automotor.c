#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "automotor.h"
#include "registro.h"
#include "cedula.h"
#include "titular.h"
#include "historialevento.h"
#include <time.h>
#include "utils.h"



void altaAutomotor() {

    FILE *archivo = fopen("data/automotores.txt", "a"); // modo append
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Automotor autoNuevo;

    do{
       
        printf("Ingrese dominio: ");
        fgets(autoNuevo.dominio, sizeof(autoNuevo.dominio), stdin);
        autoNuevo.dominio[strcspn(autoNuevo.dominio, "\n")] = '\0';

        if (dominioAutomotorExiste(autoNuevo.dominio))
        {
            printf("El dominio ya existe. Ingrese un dominio diferente.\n");
        }

    } while (dominioAutomotorExiste(autoNuevo.dominio));


    printf("Ingrese marca: ");
    fgets(autoNuevo.marca, sizeof(autoNuevo.marca), stdin);
    autoNuevo.marca[strcspn(autoNuevo.marca, "\n")] = '\0';

    printf("Ingrese modelo: ");
    fgets(autoNuevo.modelo, sizeof(autoNuevo.modelo), stdin);
    autoNuevo.modelo[strcspn(autoNuevo.modelo, "\n")] = '\0';

    printf("Ingrese numero de chasis: ");
    fgets(autoNuevo.chasis, sizeof(autoNuevo.chasis), stdin);
    autoNuevo.chasis[strcspn(autoNuevo.chasis, "\n")] = '\0';

    printf("Ingrese numero de motor: ");
    fgets(autoNuevo.motor, sizeof(autoNuevo.motor), stdin);
    autoNuevo.motor[strcspn(autoNuevo.motor, "\n")] = '\0';

    leerEnteroValidado("Ingrese anio de fabricacion: ", &autoNuevo.anioFabricacion);

    printf("Ingrese pais de origen: ");
    fgets(autoNuevo.paisOrigen, sizeof(autoNuevo.paisOrigen), stdin);
    autoNuevo.paisOrigen[strcspn(autoNuevo.paisOrigen, "\n")] = '\0';

    printf("Ingrese tipo de uso: ");
    fgets(autoNuevo.tipoUso, sizeof(autoNuevo.tipoUso), stdin);
    autoNuevo.tipoUso[strcspn(autoNuevo.tipoUso, "\n")] = '\0';

    leerEnteroValidado("Ingrese peso (kg): ", &autoNuevo.peso);

    do
    {
        leerEnteroValidado("Ingrese Nro. Documento del titular: ", &autoNuevo.nroDocTitular);

        if (!titularExiste(autoNuevo.nroDocTitular)) {
            printf("El titular con DNI %d no existe. Debe darlo de alta primero.\n", autoNuevo.nroDocTitular);
            altaTitular(); 
        }

    } while (!titularExiste(autoNuevo.nroDocTitular));



    autoNuevo.nroRegistro = seleccionarRegistro();

    // Escribir en el archivo (formato de texto plano)
    fprintf(archivo, "%s;%s;%s;%s;%s;%d;%s;%s;%d;%d;%d\n",
        autoNuevo.dominio,
        autoNuevo.marca,
        autoNuevo.modelo,
        autoNuevo.chasis,
        autoNuevo.motor,
        autoNuevo.anioFabricacion,
        autoNuevo.paisOrigen,
        autoNuevo.tipoUso,
        autoNuevo.peso,
        autoNuevo.nroDocTitular,
        autoNuevo.nroRegistro
    );


    fclose(archivo);
    printf("Automotor guardado exitosamente.\n");
}


void bajaAutomotor() {
    char dominioEliminar [10];
    do
    {
        printf("Ingrese el dominio a eliminar del automotor a dar de baja:  \n");
        fgets(dominioEliminar, sizeof(dominioEliminar), stdin);
        dominioEliminar[strcspn(dominioEliminar, "\n")] = '\0';

    } while (!dominioAutomotorExiste(dominioEliminar));

    // 1) Eliminar línea de automotores.txt
    FILE *original = fopen("data/automotores.txt", "r");
    FILE *temporal = fopen("data/temp.txt", "w");
    if (!original || !temporal) {
        printf("Error al abrir los archivos de automotores.\n");
        if (original) fclose(original);
        if (temporal) fclose(temporal);
        return;
    }

    Automotor a;
    while (leerRegistroAutomotor(original, &a))
    {

        if (strcmp(a.dominio, dominioEliminar) == 0) {
            continue;// No copiamos esta línea al temporal: quedará "eliminada"
        }

        // Copiamos todo lo demás al archivo temporal
        fprintf(temporal,
                "%s;%s;%s;%s;%s;%d;%s;%s;%d;%d;%d\n",
                a.dominio,
                a.marca,
                a.modelo,
                a.chasis,
                a.motor,
                a.anioFabricacion,
                a.paisOrigen,
                a.tipoUso,
                a.peso,
                a.nroDocTitular,
                a.nroRegistro);
    }

    fclose(original);
    fclose(temporal);

    // Reemplazamos el archivo original por el temporal
    remove("data/automotores.txt");
    rename("data/temp.txt", "data/automotores.txt");

    printf("Vehículo con dominio '%s' dado de baja en automotores.txt\n", dominioEliminar);


    // 2) Eliminar línea en cedulas.txt que contenga ese dominio
    FILE *ced = fopen("data/cedulas.txt", "r");
    FILE *ced_tmp = fopen("data/temp_cedulas.txt", "w");

    Cedula cedula;

    if (!ced || !ced_tmp){
        if (ced) fclose(ced);
        if (ced_tmp) fclose(ced_tmp);
        printf("No se pudo procesar cedulas.txt (quizá no exista).\n");

    }


    while (leerRegistroCedula(ced, &cedula)) {
        // Si NO encontramos el dominio dentro de la línea, la copiamos
        if (strcmp(cedula.dominioAutomotor, dominioEliminar) == 0) {
            continue;// No copiamos esta línea al temporal: quedará "eliminada"
        }

        // Copiamos todo lo demás al archivo temporal
        fprintf(ced_tmp,
                "%d;%s;%s;%s\n",
                cedula.nroCedula,
                cedula.fechaEmision,
                cedula.fechaVencimiento,
                cedula.dominioAutomotor);
    }

    fclose(ced);
    fclose(ced_tmp);
    remove("data/cedulas.txt");
    rename("data/temp_cedulas.txt", "data/cedulas.txt");
    printf("Registros en cedulas.txt relacionados al dominio '%s' eliminados.\n", dominioEliminar);
    
    

    // 3) Eliminar historial de eventos asociados a ese dominio
    FILE *hist = fopen("data/historial.txt", "r");
    FILE *hist_tmp = fopen("data/temp_historial.txt", "w");
    if (!hist || !hist_tmp){
        if (hist) fclose(hist);
        if (hist_tmp) fclose(hist_tmp);
        printf("No se pudo procesar historial.txt (quizá no exista).\n");
    } 

    HistorialEvento he;


    while (leerRegistroHistorialEvento(hist, &he)) {

        if (strcmp(he.dominioAutomotor, dominioEliminar) == 0) {
            continue;// No copiamos esta línea al temporal: quedará "eliminada"
        }

        // Copiamos el resto de los registros al archivo temporal
        fprintf(hist_tmp, "%d;%s;%s;%s;%s\n",
                he.idEvento,
                he.dominioAutomotor,
                he.tipoEvento,
                he.descripcion,
                he.fecha);

    }

    fclose(hist);
    fclose(hist_tmp);
    remove("data/historial.txt");
    rename("data/temp_historial.txt", "data/historial.txt");
    printf("Historial de eventos del vehículo con dominio '%s' eliminado.\n", dominioEliminar);

}




void listarTodos() {
    FILE *f = fopen("data/automotores.txt", "r");
    if (!f) {
        printf("No se pudo abrir el archivo de vehiculos.\n");
        return;
    }

    Automotor a;
    printf("\n--- Vehiculos registrados ---\n");
    while (leerRegistroAutomotor(f,&a)) {
        printf("Dominio: %s | Marca: %s | Modelo: %s | Anio: %d | Registro: %d\n",
               a.dominio, a.marca, a.modelo, a.anioFabricacion, a.nroRegistro);
    }

    fclose(f);
}




void consultarInformacionConDominio(){

    char dominio [10];

    do
    {
        printf("Ingrese el dominio del automotor a consultar informacion: \n");
        fgets(dominio, sizeof(dominio), stdin);
        dominio[strcspn(dominio, "\n")] = '\0';

    } while (!dominioAutomotorExiste(dominio));


    listarVehiculoConDominio(dominio);

}


int dominioAutomotorExiste(const char dominio[10]) {
    FILE *archivo = fopen("data/automotores.txt", "r");
    if (archivo == NULL) {
        return 0; // No hay archivo aún: ningún automotor registrado
    }

    Automotor temp;
    
    while (leerRegistroAutomotor(archivo, &temp))
    {
        if (strcmp(temp.dominio, dominio) == 0) {
            fclose(archivo);
            return 1; // Ya existe
        }
    }

    fclose(archivo);
    return 0; // No se encontró
}


// Función que lee un registro del archivo
int leerRegistroAutomotor(FILE *archivo, Automotor *automotor) {
    return fscanf(archivo, "%9[^;];%49[^;];%49[^;];%49[^;];%49[^;];%d;%49[^;];%49[^;];%d;%d;%d\n",
                  automotor->dominio,
                  automotor->marca,
                  automotor->modelo,
                  automotor->chasis,
                  automotor->motor,
                  &automotor->anioFabricacion,
                  automotor->paisOrigen,
                  automotor->tipoUso,
                  &automotor->peso,
                  &automotor->nroDocTitular,
                  &automotor->nroRegistro) == 11; // Retorna 1 si leyó correctamente, 0 si no
}



void listarVehiculoConDominio(const char dominio[10]){

    FILE *archivo = fopen("data/automotores.txt", "r");
    if (archivo == NULL) {
        return ; 
    }

    Automotor autoLeido;
    
    while (leerRegistroAutomotor(archivo, &autoLeido)){

        if (strcmp(autoLeido.dominio, dominio) == 0) {
            printf("\n--- Informacion del vehiculo ---\n");
            printf("Dominio: %s\n", autoLeido.dominio);
            printf("Marca: %s\n", autoLeido.marca);
            printf("Modelo: %s\n", autoLeido.modelo);
            printf("Chasis: %s\n", autoLeido.chasis);
            printf("Motor: %s\n", autoLeido.motor);
            printf("Anioo de Fabricacion: %d\n", autoLeido.anioFabricacion);
            printf("Pais de Origen: %s\n", autoLeido.paisOrigen);
            printf("Tipo de Uso: %s\n", autoLeido.tipoUso);
            printf("Peso: %d kg\n", autoLeido.peso);
            printf("DNI Titular: %d\n", autoLeido.nroDocTitular);
            printf("Nro. de registro: %d\n", autoLeido.nroRegistro);
        }
    }

    fclose(archivo);
}

void transferirVehiculo() {
    char dominio[12];
    int nuevoDNI;

    printf("Ingrese dominio del automotor a transferir: ");

        fgets(dominio, sizeof(dominio), stdin);
        dominio[strcspn(dominio, "\n")] = '\0';
    if (!dominioAutomotorExiste(dominio)) {
        printf("El dominio ingresado no existe.\n");
        return;
    }

    leerEnteroValidado("Ingrese DNI del nuevo titular: ", &nuevoDNI);

    if (!titularExiste(nuevoDNI)) {
        printf("No existe un titular con ese DNI. Debe darlo de alta primero.\n");
        altaTitular();
    }

    // Actualizar el titular del automotor
    FILE *fa = fopen("data/automotores.txt", "r");
    FILE *temp = fopen("data/temp_auto.txt", "w");
    if (!fa || !temp) {
        printf("Error al acceder a los archivos de automotores.\n");
        return;
    }

    Automotor a;
    int modificado = 0;
    while (leerRegistroAutomotor(fa, &a)) {
        if (strcmp(a.dominio, dominio) == 0) {
            a.nroDocTitular = nuevoDNI;
            modificado = 1;
        }
        fprintf(temp, "%s;%s;%s;%s;%s;%d;%s;%s;%d;%d;%d\n",
                a.dominio, a.marca, a.modelo, a.chasis, a.motor,
                a.anioFabricacion, a.paisOrigen, a.tipoUso,
                a.peso, a.nroDocTitular, a.nroRegistro);
    }

    fclose(fa);
    fclose(temp);
    remove("data/automotores.txt");
    rename("data/temp_auto.txt", "data/automotores.txt");

    if (modificado) {
        printf("Transferencia realizada correctamente.\n");
    } else {
        printf("Error: no se modificó el titular del automotor.\n");
        return;
    }

    // Eliminar cédulas viejas del dominio
    FILE *fc = fopen("data/cedulas.txt", "r");
    FILE *fc_temp = fopen("data/temp_cedulas.txt", "w");

    if (fc && fc_temp) {
        char linea[256];
        while (fgets(linea, sizeof(linea), fc)) {
            if (!strstr(linea, dominio)) {
                fputs(linea, fc_temp);
            }
        }
        fclose(fc);
        fclose(fc_temp);
        remove("data/cedulas.txt");
        rename("data/temp_cedulas.txt", "data/cedulas.txt");
        printf("Cédula anterior eliminada.\n");
    }

    // Crear nueva cédula
    altaCedula();

    // Registrar en historial
    FILE *hist = fopen("data/historial.txt", "a");
    if (hist) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char fecha[11];
        snprintf(fecha, sizeof(fecha), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
        int nuevoId = 1;
        FILE *hist_r = fopen("data/historial.txt", "r");
        if (hist_r) {
            HistorialEvento tempEvt;
            while (fscanf(hist_r, "%d;%[^;];%[^;];%[^;];%[^\n]",
                          &tempEvt.idEvento, tempEvt.dominioAutomotor,
                          tempEvt.tipoEvento, tempEvt.descripcion, tempEvt.fecha) == 5) {
                nuevoId = tempEvt.idEvento + 1;
            }
            fclose(hist_r);
        }

        fprintf(hist, "%d;%s;%s;%s;%s\n", nuevoId, dominio, "Transferencia", "Cambio de titular del automotor", fecha);
        fclose(hist);
        printf("Evento de transferencia registrado en historial.\n");
    }
}



