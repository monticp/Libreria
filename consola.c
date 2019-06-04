#include "consola.h"
#include "libro.h"


void iniciarConsola (FILE*ptrArchivo, ST_LISTAVENTAS ** listaRetirosEnSucursal, ST_COLALIBROS * colaEnviosADomicilio){
        int N = -1;
        system("cls");
        printf("Bienvenidos al sistema\n");
        printf("Tamaño de ST_LIBRO = %i bytes\n", sizeof(ST_LIBRO)); //Despues borrar
        printf("[1] - Gestion de libros\n");
        printf("[2] - Venta de libros\n");
        printf("[3] - Entrega de libros comprados\n");
        printf("[4] - Salir\n");
        scanf("%i", &N);
        switch (N){
            case 1:
                system("cls");
                gestionConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
                break;
            case 2:
                system("cls");
                ST_LISTALIBROS * listaVentas;
                crearLista(&listaVentas);
                ventaLibro(ptrArchivo, &listaVentas, listaRetirosEnSucursal, colaEnviosADomicilio);
                break;
        }
}

void gestionConsola (FILE*ptrArchivo, ST_LISTAVENTAS ** listaRetirosEnSucursal, ST_COLALIBROS * colaEnviosADomicilio){
        int N = -1;
        printf("\n[1] - Crear libro\n");
        printf("[2] - Buscar libro\n");
        printf("[3] - Listar libros\n");
        printf("[4] - Editar libro\n");
        printf("[5] - Eliminar libro\n");
        printf("[6] - Volver\n");
        scanf("%d", &N);
        int libroiesimo;
        switch (N){
        case 1:
            crearLibroPorConsola(ptrArchivo);
            gestionConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 2:
            buscarLibro(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 3:
            system("cls");
            listarLibros(ptrArchivo);
            gestionConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 4:
            system("cls");
            libroiesimo = buscarLibroPorISBN (ptrArchivo);
            mostrarLibroIesimo(libroiesimo,ptrArchivo);
            editarLibro(libroiesimo,ptrArchivo);
            system("cls");
            gestionConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 5:
            system("cls");
            libroiesimo = buscarLibroPorISBN (ptrArchivo);
            mostrarLibroIesimo(libroiesimo,ptrArchivo);
            eliminarLibro(libroiesimo,ptrArchivo);
            system("cls");
            gestionConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 6:
            iniciarConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        }
}

void buscarLibro (FILE*ptrArchivo, ST_LISTAVENTAS ** listaRetirosEnSucursal, ST_COLALIBROS * colaEnviosADomicilio){
        int N = -1;
        system("cls");
        printf("\n[1] - Buscar libro por ISBN\n");
        printf("[2] - Buscar libro por titulo o autor\n");
        printf("[3] - Volver\n");
        scanf("%d", &N);
        int libroiesimo;
        switch (N){
        case 1:
            system("cls");
            libroiesimo = buscarLibroPorISBN (ptrArchivo);
            mostrarLibroIesimo(libroiesimo,ptrArchivo);
            gestionarLibro(libroiesimo, ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 2:
            system("cls");
            buscarLibroPorTituloOAutor(ptrArchivo);
            seleccionarLibro(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 3:
            system("cls");
            gestionConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
}

}

void seleccionarLibro (FILE*ptrArchivo, ST_LISTAVENTAS ** listaRetirosEnSucursal, ST_COLALIBROS * colaEnviosADomicilio){
        int N = -1;
        printf("\n[1] - Seleccionar libro por ISBN\n");
        printf("[2] - Buscar otro libro por titulo o autor\n");
        printf("[3] - Volver\n");
        scanf("%d", &N);
        int libroiesimo;
        switch (N){
        case 1:
            libroiesimo = buscarLibroPorISBN (ptrArchivo);
            mostrarLibroIesimo(libroiesimo,ptrArchivo);
            gestionarLibro(libroiesimo, ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 2:
            buscarLibroPorTituloOAutor(ptrArchivo);
            seleccionarLibro(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 3:
            gestionConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        }
}

void gestionarLibro (int libroiesimo, FILE*ptrArchivo, ST_LISTAVENTAS ** listaRetirosEnSucursal, ST_COLALIBROS * colaEnviosADomicilio){
        int N = -1;
        printf("\n[1] - Editar libro\n");
        printf("[2] - Eliminar libro\n");
        printf("[3] - Volver\n");
        scanf("%d", &N);
        switch (N){
        case 1:
            editarLibro(libroiesimo,ptrArchivo);
            system("cls");
            gestionConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 2:
            eliminarLibro(libroiesimo,ptrArchivo);
            system("cls");
            gestionConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
        case 3:
            system("cls");
            gestionConsola(ptrArchivo, listaRetirosEnSucursal , colaEnviosADomicilio);
            break;
}
}

void ventaLibro (FILE *ptrArchivo, ST_LISTALIBROS ** listaVentas, ST_LISTAVENTAS ** listaRetirosPorSucursal, ST_COLALIBROS * colaEnviosADomicilio){
        int N = -1;
        listarLibros(ptrArchivo);
        printf("\n[1] - Seleccionar libro por ISBN\n");
        printf("[2] - Buscar libro por titulo o autor\n");
        printf("[3] - Finalizar seleccion de libros\n");
        printf("[4] - Volver\n");
        scanf("%d", &N);
        switch (N){
        case 1:
            system("cls");
            int libroIesimo = buscarLibroPorISBN(ptrArchivo);
            mostrarLibroIesimo(libroIesimo, ptrArchivo);
            agregarLibroALista(libroIesimo, ptrArchivo, listaVentas);
            ventaLibro(ptrArchivo, listaVentas, listaRetirosPorSucursal, colaEnviosADomicilio);
            break;
        case 2:
            system("cls");
            buscarLibroPorTituloOAutor(ptrArchivo);
            int libroiesimo = buscarLibroPorISBN(ptrArchivo);
            system("cls");
            mostrarLibroIesimo(libroiesimo, ptrArchivo);
            agregarLibroALista(libroiesimo, ptrArchivo, listaVentas);
            ventaLibro(ptrArchivo, listaVentas, listaRetirosPorSucursal, colaEnviosADomicilio);
            break;
        case 3:
            system ("cls");
            mostrarListaLibros(listaVentas);
            ventaLibro(ptrArchivo, listaVentas, listaRetirosPorSucursal, colaEnviosADomicilio);
            break;
        case 4:
            system("cls");
            iniciarConsola(ptrArchivo, listaRetirosPorSucursal , colaEnviosADomicilio);
            break;
}
}
