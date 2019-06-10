#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libro.h"
#include "listas.h"
#define longTime 20
#define longNombreFactura 20
#define longNumeroFactura 10
#define longISBN 10

void crearLista (ST_LISTALIBROS ** cabecera){
        *cabecera = NULL;
}

ST_LISTALIBROS * crearNodoLista (ST_LIBRO * libro){
        ST_LISTALIBROS * nodo = (ST_LISTALIBROS*)malloc(sizeof(ST_LISTALIBROS));
        nodo->libro = *libro;
        nodo->ste = NULL;
        return nodo;
}

void crearListaVentas (ST_LISTAVENTAS ** cabecera){
        *cabecera = NULL;
}

ST_LISTAVENTAS * crearNodoVentas (int factura, ST_LISTALIBROS ** listaLibros){
            ST_LISTAVENTAS * nodoVentas = (ST_LISTAVENTAS*)malloc(sizeof(ST_LISTAVENTAS));
            nodoVentas ->IDFactura = factura;
            int cantLibros = 0;
            double precioTotal = 0;
            nodoVentas->listaLibro = *listaLibros;
            nodoVentas->ste = NULL;
            ST_LISTALIBROS * aux = *listaLibros;
            if (aux!=NULL){
                cantLibros++;
                precioTotal = precioTotal + aux->libro.precio;
            }
            while ((aux!=NULL)&&(aux->ste!=NULL)){
                aux = aux->ste;
                precioTotal = precioTotal + aux->libro.precio;
                cantLibros++;
            }
            nodoVentas->cantLibros = cantLibros;
            nodoVentas->precioTotal = precioTotal;
            return nodoVentas;
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
                        system("pause");
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
        printf ("Precio: $%4.2f\n", aux->libro.precio);
        printf ("Stock disponible: %i\n", aux->libro.stockDisponible);
        printf ("Stock reservado: %i\n", aux->libro.stockReservado);
    }
    while ((aux!=NULL)&&(aux->ste!=NULL)){
        printf ("ISBN: %s\n", aux->ste->libro.ISBN);
        printf ("Título: %s\n", aux->ste->libro.titulo);
        printf ("Autor: %s %s\n", aux->ste->libro.autor.nombre, aux->ste->libro.autor.apellido);
        printf ("Precio: $%4.2f\n", aux->ste->libro.precio);
        printf ("Stock disponible: %i\n", aux->ste->libro.stockDisponible);
        printf ("Stock reservado: %i\n", aux->ste->libro.stockReservado);
        aux = aux->ste;
    }

}

int generarFactura (ST_LISTALIBROS ** listaVenta){
        int factura = 1;
        printf ("\n Esta seguro que desea realizar la compra? '1'=confirmar - '0'= Cancelar\n");
        int confirmacion = 0;
        scanf ("%i", &confirmacion);
        if ((confirmacion == 1)&&(*listaVenta!=NULL)){
            char numeroFactura [longNumeroFactura];
            char nombreFactura [longNombreFactura] = "Factura";
            strcat(nombreFactura,enteroACadena(factura,numeroFactura));
            strcat(nombreFactura, ".txt");
            FILE * ptrFactura = NULL;
            while ((ptrFactura=fopen(nombreFactura, "rb+"))!=NULL){
                factura ++;
                strcpy(nombreFactura, "Factura");
                strcat(nombreFactura,enteroACadena(factura,numeroFactura));
                strcat(nombreFactura, ".txt");
            }
            if ((ptrFactura=fopen(nombreFactura, "a"))==NULL){
                exit(EXIT_FAILURE);
            }
            char buffTime[20];
            time_t Time;
            struct tm * timeInfo;
            time(&Time);
            timeInfo = localtime (&Time);
            strftime(buffTime, sizeof(buffTime), "%b %d %H:%M", timeInfo);
            fprintf(ptrFactura, "\n Factura %i \n Fecha: %s\n", factura, buffTime);
            ST_LISTALIBROS * cabecera = *listaVenta;
            double totalPrecio = 0;
            if (cabecera!=NULL){
                fprintf(ptrFactura, "\n ISBN: %s \t Titulo: %s \t Precio: %4.2f\n", cabecera->libro.ISBN, cabecera->libro.titulo, cabecera->libro.precio);
                totalPrecio = totalPrecio + cabecera->libro.precio;
                }
            while ((cabecera!=NULL)&&(cabecera->ste!=NULL)){
                fprintf(ptrFactura, "\n ISBN: %s \t Titulo: %s \t Precio: %4.2f\n", cabecera->ste->libro.ISBN, cabecera->ste->libro.titulo, cabecera->ste->libro.precio);
                totalPrecio = totalPrecio + cabecera->ste->libro.precio;
                cabecera = cabecera->ste;
            }
            fprintf(ptrFactura, "\n \t Total: \t  %4.2f \n", totalPrecio);
            fclose(ptrFactura);
        }
    return factura;
}

void actualizarStockPorISBN (FILE * ptrArchivo, char * ISBN, ST_LIBRO * libro){
        int libroIesimo = 0;
        fseek(ptrArchivo,0,SEEK_SET);
        fread(libro,sizeof(ST_LIBRO),1,ptrArchivo);
        while ((!feof(ptrArchivo))&&(strcmp(ISBN,libro->ISBN)!=0)){
            fread(libro,sizeof(ST_LIBRO),1,ptrArchivo);
            libroIesimo++;
            }
        libro->stockReservado++;
        libro->stockDisponible--;
        fseek(ptrArchivo,libroIesimo*sizeof(ST_LIBRO),SEEK_SET);
        fwrite(libro,sizeof(ST_LIBRO),1,ptrArchivo);
}

void actualizarStock (FILE*ptrArchivo, ST_LISTALIBROS ** listaVentas){
        ST_LIBRO libro;
        char ISBN [longISBN];
        ST_LISTALIBROS * aux = *listaVentas;
        if (aux != NULL){
            strcpy(ISBN, aux->libro.ISBN);
            actualizarStockPorISBN(ptrArchivo, ISBN, &libro);
        }
        while ((aux != NULL)&&(aux->ste != NULL)){
            strcpy(ISBN, aux->ste->libro.ISBN);
            actualizarStockPorISBN(ptrArchivo, ISBN, &libro);
            aux = aux->ste;
        }
}

void agregarVentaALista (int factura, ST_LISTALIBROS ** listaVenta, ST_LISTAVENTAS ** listaRetirosPorSucursal){
        ST_LISTAVENTAS * nodoVenta = crearNodoVentas(factura,listaVenta);
        nodoVenta->ste = *listaRetirosPorSucursal;
        *listaRetirosPorSucursal = nodoVenta;
}

void mostrarListaVentas (ST_LISTAVENTAS ** listaRetirosPorLocal){
        ST_LISTAVENTAS * aux = *listaRetirosPorLocal;
        if (aux != NULL){
            printf("\n Venta:\n");
            printf("Factura: %i\n", aux->IDFactura);
            printf("Cant. de libros: %i\n", aux->cantLibros);
            printf("Total: $%4.2f\n", aux->precioTotal);
        }
        while ((aux!=NULL)&&(aux->ste!=NULL)){
            aux = aux->ste;
            printf("\n Venta:\n");
            printf("Factura: %i\n", aux->IDFactura);
            printf("Cant. de libros: %i\n", aux->cantLibros);
            printf("Total: $%4.2f\n", aux->precioTotal);
        }
}

ST_LISTAVENTAS * buscarEnListaVentas (int factura, ST_LISTAVENTAS ** listaVentas){
            ST_LISTAVENTAS * aux = *listaVentas;
            while ((aux!=NULL)&&(aux->ste!=NULL)&&(factura!=aux->IDFactura)){
                aux = aux->ste;
            }
            if (factura==aux->IDFactura){
                return aux;
            }
            else{
                return NULL;
            }
}


void crearCola (ST_COLALIBROS * colaVentas){
    colaVentas->fin = NULL;
    colaVentas->inicio = NULL;
}

void agregarVentaACola (int factura, ST_LISTALIBROS ** listaVenta, ST_COLALIBROS * colaVentas){
            ST_LISTAVENTAS * nodo = crearNodoVentas(factura, listaVenta);
            if (colaVentas->inicio == NULL){
                colaVentas->fin = nodo;
                colaVentas->inicio = nodo;
            }
            else{
                colaVentas->fin->ste = nodo;
                colaVentas->fin = nodo;
            }
}

void mostrar5ElementosDeCola (ST_COLALIBROS * colaVentas){
        ST_LISTAVENTAS * aux = colaVentas->inicio;
        int cont = 0;
        if(aux!=NULL){
            printf("\n Venta:\n");
            printf("Factura: %i\n", aux->IDFactura);
            printf("Cant. de libros: %i\n", aux->cantLibros);
            printf("Total a pagar: %4.2f\n", aux->precioTotal);
        }
        while ((cont <4)&&(aux->ste!=NULL)){
            aux = aux->ste;
            printf("\n Venta:\n");
            printf("Factura: %i\n", aux->IDFactura);
            printf("Cant. de libros: %i\n", aux->cantLibros);
            printf("Total a pagar: %4.2f\n", aux->precioTotal);
            cont++;
        }
}

//Corregir
void eliminarVentaDeLista (FILE * ptrArchivo, ST_LISTAVENTAS ** listaVentas){
        int factura = 0;
        printf("\nIngrese el numero de factura que desea eliminar\n");
        scanf ("%i", &factura);
        ST_LISTAVENTAS * ventaSeleccionada = buscarEnListaVentas(factura, listaVentas);
        if (ventaSeleccionada!=NULL){
            system("cls");
            printf("\n Venta:\n");
            printf("Factura: %i\n", ventaSeleccionada->IDFactura);
            printf("Cant. libros: %i\n", ventaSeleccionada->cantLibros);
            printf("Total: $%4.2f", ventaSeleccionada->precioTotal);
            printf("\n Esta seguro que desea eliminar la venta? '1'=Si - '0'=No\n");
            int verificacion = 0;
            scanf("%i", &verificacion);
            if(verificacion == 1){
                ST_LISTAVENTAS * aux = *listaVentas;
                while ((aux->ste!=ventaSeleccionada)&&(aux->ste!=NULL)){
                    aux = aux->ste;
                }
                aux->ste = ventaSeleccionada->ste;
                while (ventaSeleccionada->listaLibro->ste!=NULL){
                    ST_LISTALIBROS * auxLibro = ventaSeleccionada->listaLibro;
                    ST_LIBRO libroSeleccionado;
                    int seleccionIesima = seleccionarLibroPorISBN(auxLibro->libro.ISBN, &libroSeleccionado, ptrArchivo);
                    libroSeleccionado.stockReservado--;
                    fseek(ptrArchivo,seleccionIesima*sizeof(ST_LIBRO),SEEK_SET);
                    fwrite(&libroSeleccionado, sizeof(ST_LIBRO),1, ptrArchivo);
                    ventaSeleccionada->listaLibro = ventaSeleccionada->listaLibro->ste;
                    free(auxLibro);
                }
                free(ventaSeleccionada);
            }
        }
        else{
            printf("\n Elemento no encontrado\n");
            system("pause");
        }
}

//Corregir
void remover5ElementosDeCola (ST_COLALIBROS * colaVentas){
        ST_LISTAVENTAS * auxVenta;
        int cont = 0;
        while ((colaVentas->inicio!=NULL)&&(cont<5)){
            auxVenta = colaVentas->inicio;
            ST_LISTALIBROS * aux;
            while (colaVentas->inicio->listaLibro!=NULL){
                aux = colaVentas->inicio->listaLibro;
                colaVentas->inicio->listaLibro = colaVentas->inicio->listaLibro->ste;
                free(aux);
            }
            colaVentas->inicio = colaVentas->inicio->ste;
            free(auxVenta);
            cont++;
        }
    }
