#include "pila.h"

#include <stdlib.h>

// gcc -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -o pruebas *.c
// valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(void){
    pila_t* pila = malloc(sizeof(pila_t));
    if (pila == NULL){
        return NULL;
    }
    pila->capacidad = 10;
    pila->cantidad = 0;
    pila->datos = malloc(sizeof(void*) * pila->capacidad);
    if (pila->datos == NULL){
        free(pila);
        return NULL;
    }
    return pila;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    if (pila->cantidad == 0){
        return true;
    }
    return false;
}

bool pila_redimensionar(pila_t *pila, size_t tam) {
    void* nuevos_datos = realloc(pila->datos, tam * sizeof(void*));
    if (nuevos_datos == NULL) {
        return false;
    }
    pila->datos = nuevos_datos;
    pila->capacidad = tam;
    return true;
}

bool pila_apilar(pila_t *pila, void *valor){
    if (pila->cantidad == pila->capacidad){
        bool intento = pila_redimensionar(pila, pila->capacidad * 2);
        if (intento == false){
            return false;
        }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void *pila_ver_tope(const pila_t *pila){
    if (pila->cantidad > 0){
        return pila->datos[pila->cantidad -1];
    }
    return NULL;
}

void *pila_desapilar(pila_t *pila){
    if (pila->cantidad * 4 < pila->capacidad){
        bool intento = pila_redimensionar(pila, pila->capacidad / 2);
        if (intento == false){
            return NULL;
        }
    }
    if (pila_esta_vacia(pila) == true){
        return NULL;
    }
    void * tope = pila->datos[pila->cantidad - 1];
    pila->cantidad--;
    return tope;
}


