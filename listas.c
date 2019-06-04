#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libro.h"
#include "listas.h"


void crearLista (ST_LISTALIBROS ** cabecera){
        *cabecera = NULL;
}

ST_LISTALIBROS * crearNodoLista (ST_LIBRO * libro){
        ST_LISTALIBROS * nodo = (ST_LISTALIBROS*)malloc(sizeof(ST_LISTALIBROS));
        nodo->libro = *libro;
        nodo->ste = NULL;
        return nodo;
}

void agregarLibroALista (int libroIesimo, FILE * ptrArchivo, ST_LISTALIBROS ** listaLibro){
        int confirmacion = 0;
        ST_LIBRO libro;
        printf ("\nEsta seguro que desea agregar el libro a la lista de venta? '1'=si - '0'=no\n");
        scanf ("%i", &confirmacion);
        if (confirmacion==1){
                if(libroIesimo != -1){
                    fseek(ptrArchivo, libroIesimo*sizeof(ST_LIBRO), SEEK_SET);
                    fread(&libro, sizeof (ST_LIBRO), 1, ptrArchivo);
                    if (libro.stockDisponible>0){
                        ST_LISTALIBROS * nodo = crearNodoLista(&libro);
                        nodo->ste = *listaLibro;
                        *listaLibro = nodo;
                        }
                    else{
                        printf ("\n El artículo no se encuentra en stock \n");
                        }
                    }
                }

}

void mostrarListaLibros (ST_LISTALIBROS ** listaLibros){
    ST_LISTALIBROS * aux = *listaLibros;
    if (aux!=NULL){
        printf ("ISBN: %s\n", aux->libro.ISBN);
        printf ("Título: %s\n", aux->libro.titulo);
        printf ("Autor: %s %s\n", aux->libro.autor.nombre, aux->libro.autor.apellido);
        printf ("Precio: %4.2f\n", aux->libro.precio);
        printf ("Stock disponible: %i\n", aux->libro.stockDisponible);
        printf ("Stock reservado: %i\n", aux->libro.stockReservado);
    }
    while ((aux!=NULL)&&(aux->ste!=NULL)){
        printf ("ISBN: %s\n", aux->ste->libro.ISBN);
        printf ("Título: %s\n", aux->ste->libro.titulo);
        printf ("Autor: %s %s\n", aux->ste->libro.autor.nombre, aux->ste->libro.autor.apellido);
        printf ("Precio: %4.2f\n", aux->ste->libro.precio);
        printf ("Stock disponible: %i\n", aux->ste->libro.stockDisponible);
        printf ("Stock reservado: %i\n", aux->ste->libro.stockReservado);
        aux = aux->ste;
    }

}

void generarFactura (ST_LISTALIBROS ** listaVenta){
        printf ("\n Esta seguro que desea realizar la compra? '1'=confirmar - '0'= Cancelar\n");
        int confirmacion = 0;
        scanf ("%i", &confirmacion);
        if (confirmacion == 1){
            int aux = 1;


        }
}
