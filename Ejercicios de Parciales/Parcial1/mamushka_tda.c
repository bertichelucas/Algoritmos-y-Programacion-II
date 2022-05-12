#include <stdlib.h>
#include <stdbool.h>

typedef enum color{rojo,verde,amarillo}color_t; //ejemplo del typedef

typedef struct mamushka {
    size_t tam;
    color_t color;
    struct mamushka* interior; 
} mamushka_t;


mamushka_t* mamushka_crear(size_t tam, color_t color){
    // O(1), Crea la mamushka 
    mamushka_t* mamushka = malloc(sizeof(mamushka_t));
    if (mamushka == NULL) return NULL;

    mamushka->tam = tam;
    mamushka->color = color;
    mamushka->interior = NULL;
    return mamushka;
}

color_t mamushka_obtener_color(mamushka_t* mamushka){
    // O(1), obtiene el color de la mamushka
    return mamushka->color;
}

bool mamushka_guardar(mamushka_t* contenedora, mamushka_t* a_guardar){
    // Guardar la mamushka es O(n) siendo n la cantidad de mamushkas que se encuentran
    // dentro. Ejemplo tengo 10 mamushkas, si quiero meter la 11 tengo que ir viendo
    // una por una hasta llegar a la ultima y ahi recien la puedo guardar.
    if (contenedora->interior != NULL) return mamushka_guardar(contenedora->interior, a_guardar);

    if (contenedora->tam <= a_guardar->tam) return false;

    contenedora->interior = a_guardar;
    return true;
}

mamushka_t* mamushka_obtener_guardada(mamushka_t* mamushka){
    // O(1), devuelve la mamushka interior de una mamushka dada.
    return mamushka->interior;
}

void mamushka_destruir(mamushka_t* mamushka){
    // Por el mismo motivo de guardar es o(n), tengo que borrar todas las mamushkas interiores.
    // una por una.
    if (mamushka->interior != NULL) {
        mamushka_t* a_destruir  = mamushka->interior;
        mamushka->interior = NULL;
        mamushka_destruir(a_destruir);
    }
    free(mamushka);
}