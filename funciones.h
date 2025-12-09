#define MAX_LIBROS 10

// Estructura para representar un libro
typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[20]; // "Disponible" o "Prestado"
} Libro;

// Función para leer cadenas con validación
void leerCadena(char *cadena, int n);

void registrarLibro(Libro *libros, int *contador);
void mostrarLibros(Libro *libros, int contador);
void buscarLibro(Libro *libros, int contador);
void actualizarEstado(Libro *libros, int contador);
void eliminarLibro(Libro *libros, int *contador);
void mostrarMenu();
