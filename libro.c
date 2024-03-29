#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libro.h"

char * enteroACadena (int valor, char * cadena){
    int cont = 0;
    char cad [10];
    int aux = valor;
    char numero;
    while ((aux/10)!=0){
        cont++;
        aux = aux/10;
    }
    cad [cont+1] = '\0';
    while ((valor/10)!=0){
        numero = (valor%10) + 48;
        cad [cont] = numero;
        valor = valor/10;
        cont --;
    }
    numero = (valor%10) + 48;
    cad[cont] = numero;
    strcpy(cadena,cad);
    return cadena;
}

void abrirLibro (FILE * nombrePtr, const char * nombreArchivo, const char * tipoApertura){
        if ((nombrePtr =fopen(nombreArchivo, tipoApertura))==NULL){
        exit(EXIT_FAILURE);
    }

}

int contarCadena (const char * cadena){
        int cont = 0;
        while (*cadena!='\0'){
            cadena++;
            cont++;
        }
    return cont;
}

bool buscarCoincidencia (const char *cadenaIngresada, const char*cadenaExistente){
        bool coincidencia = 0;
        int cont = 0;
        int tamanioCadenaIngresada = contarCadena(cadenaIngresada);
        const char *posicionInicial = cadenaIngresada;
        while((*cadenaExistente!='\0')&&(*cadenaIngresada!='\0')){
            if((*cadenaIngresada==*cadenaExistente)||((*cadenaIngresada<=90)&&(*cadenaIngresada>=65)&&(*cadenaIngresada == *cadenaExistente-32))||((*cadenaIngresada<=122)&&(*cadenaIngresada>=97)&&(*cadenaIngresada == *cadenaExistente+32))){
                cadenaExistente++;
                cadenaIngresada++;
                cont ++;
            }
            else {
                cadenaExistente++;
                cadenaIngresada = posicionInicial;
                cont = 0;
            }
        }
        if (cont == tamanioCadenaIngresada){
            coincidencia = 1;
        }
    return coincidencia;
}

void buscarLibroPorTituloOAutor (FILE*ptrArchivo){
    ST_LIBRO libro;
    char ingreso [50];
    printf("Ingrese el titulo o autor que desea buscar \n");
    scanf("%s",ingreso);
    fseek(ptrArchivo, 0, SEEK_SET);
    fread(&libro,sizeof(ST_LIBRO), 1, ptrArchivo);
    while (!feof(ptrArchivo)){
        bool coincidenciaTitulo = buscarCoincidencia(ingreso,libro.titulo);
        bool coincidenciaNombre = buscarCoincidencia(ingreso,libro.autor.nombre);
        bool coincidenciaApellido = buscarCoincidencia(ingreso,libro.autor.apellido);
        if ((coincidenciaTitulo == 1)||(coincidenciaNombre == 1) || (coincidenciaApellido ==1)){
            mostrarLibro(libro);
        }
        fread(&libro,sizeof(ST_LIBRO), 1, ptrArchivo);
    }
}




int buscarLibroVacio (FILE*ptrArchivo){
    int cont = -1;
    ST_LIBRO libro;
    fseek(ptrArchivo,0,SEEK_SET);
    while (!feof(ptrArchivo)){
        fread(&libro, sizeof(ST_LIBRO),1,ptrArchivo);
        cont ++;
        if (strcmp(libro.ISBN,"")==0){
            return cont;
            }

        }
    return cont;
}


int contarLibros (FILE*ptrArchivo){
    ST_LIBRO libro;
    int cant = 0;
    fseek(ptrArchivo,0,SEEK_SET);
    while (!feof(ptrArchivo)){
        fread(&libro, sizeof(ST_LIBRO), 1,ptrArchivo);
        cant++;
    }
    return cant;
}

ST_LIBRO crearLibro (){
    ST_LIBRO libro;
    printf("Ingresar el ISBN del libro\n");
    scanf("%s", libro.ISBN);
    printf("Ingresar el titulo del libro\n");
    scanf(" %[^\t\n]s", libro.titulo);
    printf("Ingresar el nombre del autor del libro\n");
    scanf(" %[^\t\n]s", libro.autor.nombre);
    printf("Ingresar el apellido del autor del libro\n");
    scanf(" %[^\t\n]s", libro.autor.apellido);
    printf("Ingresar el precio del libro\n");
    scanf("%lf", &libro.precio);
    printf("Ingresar el stock disponible\n");
    scanf("%d", &libro.stockDisponible);
    return libro;
}

void crearLibroPorConsola(FILE *ptrArchivo){
    int cont = buscarLibroVacio(ptrArchivo);
    ST_LIBRO libro;
    libro = crearLibro();
    fseek(ptrArchivo,cont*sizeof(ST_LIBRO),SEEK_SET);
    fwrite(&libro,sizeof(ST_LIBRO),1,ptrArchivo);
}



void listarLibros(FILE*ptrArchivo){
    ST_LIBRO libro;
    fseek(ptrArchivo,0,SEEK_SET);
    fread(&libro, sizeof(ST_LIBRO), 1,ptrArchivo);
    while (!feof(ptrArchivo)){
        if (strcmp(libro.ISBN,"")!=0){
                mostrarLibro(libro);
            }
        fread(&libro, sizeof(ST_LIBRO), 1,ptrArchivo);
    }
}

int seleccionarLibroPorISBN(char * ISBN, ST_LIBRO * libro, FILE * ptrArchivo){
    int cont = 0;
    fseek(ptrArchivo,0,SEEK_SET);
    fread(libro,sizeof(ST_LIBRO),1,ptrArchivo);
    while ((!feof(ptrArchivo))&&(strcmp(ISBN,libro->ISBN)!=0)){
        fread(libro,sizeof(ST_LIBRO),1,ptrArchivo);
        cont++;
    }
    if (strcmp(libro->ISBN, ISBN)!=0){
        return -1;
    }
    return cont;
}

int buscarLibroPorISBN (FILE*ptrArchivo){
    ST_LIBRO libro;
    char ISBN [10];
    printf("Escriba ISBN \n");
    scanf("%s", ISBN);
    int cont = seleccionarLibroPorISBN(ISBN, &libro, ptrArchivo);
    return cont;
}

void mostrarLibro (ST_LIBRO libro){
    printf("\n Libro: \n");
    printf ("ISBN: %s\n", libro.ISBN);
    printf ("T�tulo: %s\n", libro.titulo);
    printf ("Autor: %s %s\n", libro.autor.nombre, libro.autor.apellido);
    printf ("Precio: %4.2f\n", libro.precio);
    printf ("Stock disponible: %i\n", libro.stockDisponible);
    printf ("Stock reservado: %i\n", libro.stockReservado);
}

void mostrarLibroIesimo (int i, FILE *ptrArchivo){
        ST_LIBRO libro;
        if(i>=0){
            fseek(ptrArchivo,i*sizeof(ST_LIBRO),SEEK_SET);
            fread(&libro,sizeof(ST_LIBRO),1,ptrArchivo);
            mostrarLibro(libro);
        }
        else{
            perror("\nEl libro ingresado no existe\n");
        }
}

void eliminarLibro (int i, FILE*ptrArchivo){
            ST_LIBRO libro;
        if (i>=0){
            strcpy(libro.ISBN, "");
            strcpy(libro.titulo, "");
            strcpy(libro.autor.apellido, "");
            strcpy(libro.autor.nombre, "");
            libro.precio = 0;
            libro.stockDisponible = 0;
            libro.stockReservado = 0;
            printf("�Esta seguro que desea eliminar el libro? Y/N \n");
            char confirmacion = 'N';
            while (getchar()!='\n');
                scanf ("%c", &confirmacion);
                if ((confirmacion == 'Y')||(confirmacion == 'y')){
                    fseek(ptrArchivo,i*sizeof(ST_LIBRO),SEEK_SET);
                    fwrite(&libro,sizeof(ST_LIBRO),1,ptrArchivo);
                }
            }
        }


void editarLibro (int libroiesimo, FILE*ptrArchivo){
    if (libroiesimo>=0){
        fseek(ptrArchivo,libroiesimo*(sizeof(ST_LIBRO)),SEEK_SET);
        printf ("Ingrese 0 en caso de no querer cambiar ISBN, titulo o autor \n");
        ST_LIBRO libroNuevo = crearLibro();
        ST_LIBRO libroViejo;
        fread(&libroViejo,sizeof(ST_LIBRO),1,ptrArchivo);
        if (strcmp(libroNuevo.ISBN, "0") == 0){
            strcpy(libroNuevo.ISBN, libroViejo.ISBN);
        }
        if (strcmp(libroNuevo.titulo, "0") == 0){
            strcpy(libroNuevo.titulo, libroViejo.titulo);
        }
        if (strcmp(libroNuevo.autor.nombre, "0") == 0){
            strcpy(libroNuevo.autor.nombre, libroViejo.autor.nombre);
        }
        if (strcmp(libroNuevo.autor.apellido, "0") == 0){
            strcpy(libroNuevo.autor.apellido, libroViejo.autor.apellido);
        }
        if (libroNuevo.precio == 0){
            libroNuevo.precio = libroViejo.precio;
        }
        libroNuevo.stockReservado = libroViejo.stockReservado;
        printf("Libro nuevo:\n");
        mostrarLibro(libroNuevo);
        printf("\nLibro actual:\n");
        mostrarLibro(libroViejo);
        printf("�Esta seguro que desea realizar los cambios? Y/N \n");
        char confirmacion = 'N';
        while (getchar()!='\n');
        scanf ("%c", &confirmacion);
        if ((confirmacion == 'Y')||(confirmacion == 'y')){
            fseek(ptrArchivo,libroiesimo*(sizeof(ST_LIBRO)),SEEK_SET);
            fwrite(&libroNuevo,sizeof(ST_LIBRO),1,ptrArchivo);
            }
        }
    }



