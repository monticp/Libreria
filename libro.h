#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char nombre[20];
    char apellido[20];
}ST_AUTOR;

typedef struct{
    char titulo[50];
    ST_AUTOR autor;
    double precio;
    char ISBN[10];
    int stockDisponible;
    int stockReservado;
}ST_LIBRO;

char * enteroACadena (int valor, char * cadena);
int contarLibros (FILE*ptrArchivo);
int contarCadena (const char * cadena);
bool buscarCoincidencia (const char *cadenaIngresada, const char*cadenaExistente);
void mostrarLibroIesimo (int i, FILE *ptrArchivo);
void eliminarLibro (int i, FILE*ptrArchivo);
void editarLibro (int libroiesimo, FILE*ptrArchivo);
void buscarLibroPorTituloOAutor (FILE*ptrArchivo);
void crearLibroPorConsola(FILE *ptrArchivo);
void listarLibros(FILE*ptrArchivo);
int seleccionarLibroPorISBN(char * ISBN, ST_LIBRO * libro, FILE * ptrArchivo);
int buscarLibroPorISBN (FILE*ptrArchivo);
void abrirLibro (FILE * nombrePtr, const char * nombreArchivo, const char * tipoApertura);


#endif // LIBRO_H_INCLUDED
