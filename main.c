#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main(int argc, char *argv[]) {
    Libro biblioteca[MAX_LIBROS];
    int contadorLibros = 0;
    int opcion;
    int resultado;
    
    printf("=======================================================\n");
    printf("  Bienvenido al Sistema de Gestion de Biblioteca\n");
    printf("=======================================================\n");
    
    do {
        mostrarMenu();
        
        // Validar que se ingrese un número
        resultado = scanf("%d", &opcion);
        
        // Limpiar buffer en caso de entrada inválida
        if(resultado != 1) {
            printf("\nError: Debe ingresar un numero valido.\n");
            while(getchar() != '\n'); // Limpiar buffer
            continue;
        }
        
        // Validar rango de opciones
        if(opcion < 1 || opcion > 6) {
            printf("\nError: Opcion invalida. Seleccione entre 1 y 6.\n");
            continue;
        }
        
        switch(opcion) {
            case 1:
                registrarLibro(biblioteca, &contadorLibros);
                break;
            case 2:
                mostrarLibros(biblioteca, contadorLibros);
                break;
            case 3:
                buscarLibro(biblioteca, contadorLibros);
                break;
            case 4:
                actualizarEstado(biblioteca, contadorLibros);
                break;
            case 5:
                eliminarLibro(biblioteca, &contadorLibros);
                break;
            case 6:
                printf("\n=======================================================\n");
                printf("  Gracias por usar el sistema. Tenga buen dia!\n");
                printf("=======================================================\n");
                break;
        }
        
    } while(opcion != 6);
        
    return 0;
}