#ifndef CONSOLA_H_INCLUDED
#define CONSOLA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"

void iniciarConsola (FILE*ptrArchivo, ST_LISTAVENTAS ** listaRetirosEnSucursal, ST_COLALIBROS * colaRetirosADomicilio);
void gestionConsola (FILE*ptrArchivo, ST_LISTAVENTAS ** listaRetirosEnSucursal, ST_COLALIBROS * colaEnviosADomicilio);
void buscarLibro (FILE*ptrArchivo, ST_LISTAVENTAS ** listaRetirosEnSucursal, ST_COLALIBROS * colaEnviosADomicilio);
void seleccionarLibro (FILE*ptrArchivo, ST_LISTAVENTAS ** listaRetirosEnSucursal, ST_COLALIBROS * colaEnviosADomicilio);
void gestionarLibro (int libroiesimo, FILE *ptrArchivo, ST_LISTAVENTAS ** listaRetirosEnSucursal, ST_COLALIBROS * colaEnviosADomicilio);
void ventaLibro (FILE *ptrArchivo, ST_LISTALIBROS ** listaVentas, ST_LISTAVENTAS ** listaRetirosPorSucursal, ST_COLALIBROS * colaEnviosADomicilio);

#endif // CONSOLA_H_INCLUDED
