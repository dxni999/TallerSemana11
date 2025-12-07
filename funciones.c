#include <stdio.h>
#include <string.h>
#include "funciones.h"

// Función para leer cadenas y eliminar el salto de línea
void leerCadena(char *cadena, int n){
    fflush(stdin);
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    if(cadena[len] == '\n')
        cadena[len] = '\0';
}

// Función para mostrar el menú
void mostrarMenu() {
    printf("\n========== SISTEMA DE GESTION DE BIBLIOTECA ==========\n");
    printf("1. Registrar libro\n");
    printf("2. Mostrar todos los libros\n");
    printf("3. Buscar libro\n");
    printf("4. Actualizar estado de libro\n");
    printf("5. Eliminar libro\n");
    printf("6. Salir\n");
    printf("======================================================\n");
    printf("Seleccione una opcion: ");
}

// Función para verificar si un ID ya existe
int idExiste(Libro *libros, int contador, int id) {
    for(int i = 0; i < contador; i++) {
        if(libros[i].id == id) {
            return 1; // ID existe
        }
    }
    return 0; // ID no existe
}

// Función para registrar un libro
void registrarLibro(Libro *libros, int *contador) {
    if(*contador >= MAX_LIBROS) {
        printf("\nError: La biblioteca esta llena. No se pueden agregar mas libros.\n");
        return;
    }
    
    Libro nuevoLibro;
    
    printf("\n--- REGISTRAR NUEVO LIBRO ---\n");
    
    // Solicitar ID único y positivo
    int resultado;
    do {
        printf("Ingrese ID del libro (entero positivo): ");
        resultado = scanf("%d", &nuevoLibro.id);
        
        // Limpiar buffer si la entrada es inválida
        if(resultado != 1) {
            printf("Error: Debe ingresar un numero valido.\n");
            while(getchar() != '\n'); // Limpiar buffer
            nuevoLibro.id = -1; // Forzar repetición del bucle
            continue;
        }
        
        if(nuevoLibro.id <= 0) {
            printf("Error: El ID debe ser un numero positivo.\n");
        } else if(idExiste(libros, *contador, nuevoLibro.id)) {
            printf("Error: El ID %d ya existe. Ingrese un ID unico.\n", nuevoLibro.id);
        }
    } while(nuevoLibro.id <= 0 || idExiste(libros, *contador, nuevoLibro.id));
    
    // Limpiar buffer completamente
    while(getchar() != '\n');
    
    // Solicitar título con validación
    int tituloValido;
    do {
        tituloValido = 1;
        printf("Ingrese titulo del libro: ");
        fgets(nuevoLibro.titulo, 100, stdin);
        int len1 = strlen(nuevoLibro.titulo) - 1;
        if(nuevoLibro.titulo[len1] == '\n')
            nuevoLibro.titulo[len1] = '\0';
        
        if(strlen(nuevoLibro.titulo) == 0) {
            printf("Error: El titulo no puede estar vacio.\n");
            tituloValido = 0;
        }
    } while(!tituloValido);//!Bucle para validar titulo
    
    // Solicitar autor con validación
    int autorValido;
    do {
        autorValido = 1;
        printf("Ingrese autor del libro: ");
        fgets(nuevoLibro.autor, 50, stdin);
        int len2 = strlen(nuevoLibro.autor) - 1;
        if(nuevoLibro.autor[len2] == '\n')
            nuevoLibro.autor[len2] = '\0';
        
        if(strlen(nuevoLibro.autor) == 0) {
            printf("Error: El autor no puede estar vacio.\n");
            autorValido = 0;
        } else {
            // Validar que no sea solo números
            int soloNumeros = 1;
            int tieneLetras = 0;
            for(int i = 0; i < strlen(nuevoLibro.autor); i++) {
                if((nuevoLibro.autor[i] >= 'A' && nuevoLibro.autor[i] <= 'Z') || 
                   (nuevoLibro.autor[i] >= 'a' && nuevoLibro.autor[i] <= 'z')) {
                    tieneLetras = 1;
                    soloNumeros = 0;
                }
            }
            if(!tieneLetras || soloNumeros) {
                printf("Error: El autor debe contener letras, no solo numeros.\n");
                autorValido = 0;
            }
        }
    } while(!autorValido);
    
    // Solicitar año con validación
    do {
        printf("Ingrese año de publicacion (868-2025): ");
        resultado = scanf("%d", &nuevoLibro.anio);
        
        // Limpiar buffer si la entrada es inválida
        if(resultado != 1) {
            printf("Error: Debe ingresar un numero valido.\n");
            while(getchar() != '\n');
            nuevoLibro.anio = 0;
            continue;
        }
        
        if(nuevoLibro.anio < 868 || nuevoLibro.anio > 2025) {
            printf("Error: Ingrese un año valido entre 868 y 2025.\n");
        }
    } while(nuevoLibro.anio < 868 || nuevoLibro.anio > 2025);
    
    // Estado por defecto
    strcpy(nuevoLibro.estado, "Disponible");
    
    // Agregar libro al arreglo
    libros[*contador] = nuevoLibro;
    (*contador)++;
    
    printf("\nLibro registrado exitosamente!\n");
}

// Función para mostrar todos los libros
void mostrarLibros(Libro *libros, int contador) {
    if(contador == 0) {
        printf("\nNo hay libros registrados en la biblioteca.\n");
        return;
    }
    
    printf("\n========== LISTA DE LIBROS ==========\n");
    printf("%-5s %-30s %-20s %-6s %-15s\n", "ID", "TITULO", "AUTOR", "ANIO", "ESTADO");
    printf("-------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < contador; i++) {
        printf("%-5d %-30s %-20s %-6d %-15s\n", 
               libros[i].id,
               libros[i].titulo,
               libros[i].autor,
               libros[i].anio,
               libros[i].estado);
    }
    printf("===============================================================================\n");
}

// Función para buscar un libro
void buscarLibro(Libro *libros, int contador) {
    if(contador == 0) {
        printf("\nNo hay libros registrados en la biblioteca.\n");
        return;
    }
    
    int opcion;
    printf("\n--- BUSCAR LIBRO ---\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por titulo\n");
    printf("Seleccione opcion: ");
    scanf("%d", &opcion);
    
    // Validar opción
    if(opcion != 1 && opcion != 2) {
        printf("\nError: Opcion invalida. Debe seleccionar 1 o 2.\n");
        return;
    }
    
    int encontrado = 0;
    
    if(opcion == 1) {
        int id;
        printf("Ingrese ID del libro: ");
        scanf("%d", &id);
        
        for(int i = 0; i < contador; i++) {
            if(libros[i].id == id) {
                printf("\n--- LIBRO ENCONTRADO ---\n");
                printf("ID: %d\n", libros[i].id);
                printf("Titulo: %s\n", libros[i].titulo);
                printf("Autor: %s\n", libros[i].autor);
                printf("Anio: %d\n", libros[i].anio);
                printf("Estado: %s\n", libros[i].estado);
                encontrado = 1;
                break;
            }
        }
    } else {
        char titulo[100];
        printf("Ingrese titulo del libro: ");
        leerCadena(titulo, 100);
        
        // Validar que no esté vacío
        if(strlen(titulo) == 0) {
            printf("Error: El titulo no puede estar vacio.\n");
            return;
        }
        
        for(int i = 0; i < contador; i++) { // Comparación de cadenas
            if(strcmp(libros[i].titulo, titulo) == 0) {
                printf("\n--- LIBRO ENCONTRADO ---\n");
                printf("ID: %d\n", libros[i].id);
                printf("Titulo: %s\n", libros[i].titulo);
                printf("Autor: %s\n", libros[i].autor);
                printf("Año: %d\n", libros[i].anio);
                printf("Estado: %s\n", libros[i].estado);
                encontrado = 1;
                break;
            }
        }
    }
    
    if(!encontrado) {
        printf("\nLibro no encontrado.\n");
    }
}

// Función para actualizar el estado de un libro
void actualizarEstado(Libro *libros, int contador) {
    if(contador == 0) {
        printf("\nNo hay libros registrados en la biblioteca.\n");
        return;
    }
    
    int id;
    printf("\n--- ACTUALIZAR ESTADO DE LIBRO ---\n");
    printf("Ingrese ID del libro: ");
    scanf("%d", &id);
    
    int encontrado = 0;
    
    for(int i = 0; i < contador; i++) {
        if(libros[i].id == id) {
            printf("\nLibro encontrado: %s\n", libros[i].titulo);
            printf("Estado actual: %s\n", libros[i].estado);
            
            // Cambiar estado
            if(strcmp(libros[i].estado, "Disponible") == 0) {
                strcpy(libros[i].estado, "Prestado");
                printf("Estado actualizado a: Prestado\n");
            } else {
                strcpy(libros[i].estado, "Disponible");
                printf("Estado actualizado a: Disponible\n");
            }
            
            encontrado = 1;
            break;
        }
    }
    
    if(!encontrado) {
        printf("\nLibro no encontrado.\n");
    }
}

// Función para eliminar un libro
void eliminarLibro(Libro *libros, int *contador) {
    if(*contador == 0) {
        printf("\nNo hay libros registrados en la biblioteca.\n");
        return;
    }
    
    int id;
    printf("\n--- ELIMINAR LIBRO ---\n");
    printf("Ingrese ID del libro a eliminar: ");
    scanf("%d", &id);
    
    int encontrado = -1;
    
    // Buscar el libro
    for(int i = 0; i < *contador; i++) {
        if(libros[i].id == id) {
            encontrado = i;
            break;
        }
    }
    
    if(encontrado != -1) {
        printf("\nLibro encontrado: %s\n", libros[encontrado].titulo);
        printf("Esta seguro de eliminar este libro? 1.Si/2.No: ");
        int confirmar;
        scanf("%d", &confirmar);
        
        if(confirmar == 1) {
            // Mover todos los libros una posición hacia atrás
            for(int i = encontrado; i < *contador - 1; i++) {
                libros[i] = libros[i + 1];
            }
            (*contador)--;
            printf("\nLibro eliminado exitosamente.\n");
        } else {
            printf("\nOperacion cancelada.\n");
        }
    } else {
        printf("\nLibro no encontrado.\n");
    }
}