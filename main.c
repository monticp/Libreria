#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consola.h"
#include "libro.h"
#include "listas.h"

// Arreglar eliminar nodos de listas y colas

int main()
{
    FILE *ptrArchivoa = NULL;
    if ((ptrArchivoa=fopen("libros", "ab+"))==NULL){
        exit(EXIT_FAILURE);
    }
    FILE *ptrArchivo = NULL;
    if ((ptrArchivo=fopen("libros", "rb+"))==NULL){
        exit(EXIT_FAILURE);
    }


    ST_LISTAVENTAS * listaRetirosEnSucursal;
    crearListaVentas(&listaRetirosEnSucursal);
    ST_COLALIBROS colaEnviosADomicilio;
    crearCola(&colaEnviosADomicilio);

    iniciarConsola(ptrArchivo, &listaRetirosEnSucursal , &colaEnviosADomicilio);

    fclose(ptrArchivo);
    fclose(ptrArchivoa);
    return 0;
}
