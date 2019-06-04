#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#include "libro.h"

typedef struct listaLibros {
        ST_LIBRO libro;
        struct listaLibros * ste;
}ST_LISTALIBROS;

typedef struct listaVentas {
        struct listaVentas * ste;
        int IDFactura;
        ST_LISTALIBROS * listaLibro;
} ST_LISTAVENTAS;

typedef struct {
        ST_LISTAVENTAS * inicio;
        ST_LISTAVENTAS * fin;
} ST_COLALIBROS;


ST_LISTALIBROS * crearNodoLista (ST_LIBRO * libro);

void crearLista (ST_LISTALIBROS ** cabecera);

void agregarLibroALista (int libroIesimo, FILE * ptrArchivo, ST_LISTALIBROS ** listaVentas);

void mostrarListaLibros (ST_LISTALIBROS ** listaLibros);

#endif // LISTAS_H_INCLUDED
