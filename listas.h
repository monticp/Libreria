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
        int cantLibros;
        double precioTotal;
        ST_LISTALIBROS * listaLibro;
} ST_LISTAVENTAS;

typedef struct {
        ST_LISTAVENTAS * inicio;
        ST_LISTAVENTAS * fin;
} ST_COLALIBROS;


ST_LISTALIBROS * crearNodoLista (ST_LIBRO * libro);

void crearLista (ST_LISTALIBROS ** cabecera);

void crearListaVentas (ST_LISTAVENTAS ** cabecera);

void agregarLibroALista (int libroIesimo, FILE * ptrArchivo, ST_LISTALIBROS ** listaVentas);

void mostrarListaLibros (ST_LISTALIBROS ** listaLibros);

void actualizarStock (FILE*ptrArchivo, ST_LISTALIBROS ** listaVentas);

int generarFactura (ST_LISTALIBROS ** listaVenta);

void mostrarListaVentas (ST_LISTAVENTAS ** listaRetirosPorLocal);

void agregarVentaALista (int factura, ST_LISTALIBROS ** listaVentas, ST_LISTAVENTAS ** listaRetirosPorSucursal);

void eliminarVentaDeLista (FILE * ptrArchivo, ST_LISTAVENTAS ** listaVentas);

void crearCola (ST_COLALIBROS * colaVentas);

void agregarVentaACola (int factura, ST_LISTALIBROS ** listaVenta, ST_COLALIBROS * colaVentas);

void mostrar5ElementosDeCola (ST_COLALIBROS * colaVentas);

#endif // LISTAS_H_INCLUDED
