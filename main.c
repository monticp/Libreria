#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consola.h"
#include "libro.h"
#include "ventas.h"
#include "listas.h"



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
    ST_COLALIBROS * colaEnviosADomicilio;

    iniciarConsola(ptrArchivo, &listaRetirosEnSucursal , colaEnviosADomicilio);

    fclose(ptrArchivo);
    fclose(ptrArchivoa);
    return 0;
}
