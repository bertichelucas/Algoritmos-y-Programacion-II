#include "cola.h"

#include <stdlib.h>
// gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o pruebas *.c
// valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas

typedef struct nodo {
    void* dato;
    struct nodo* prox; 
} nodo_t;

struct cola {
    nodo_t* prim;
    nodo_t* ultimo;

};

cola_t* cola_crear(){
    cola_t* cola = malloc(sizeof(cola_t));
    if (cola == NULL){
        return NULL;
    }
    cola->prim = NULL;
    cola->ultimo =NULL;
    return cola;
}

void cola_destruir(cola_t* cola, void (*destruir_dato)(void*)){
    nodo_t* actual = cola->prim;
    nodo_t* anterior = NULL;
    while(actual){
        anterior = actual;
        if (destruir_dato != NULL){
            destruir_dato(anterior->dato);
        }
        actual = actual->prox;
        free(anterior);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t* cola){
    if (cola->prim == NULL){
        return true;
    }
    return false;
}

nodo_t* crear_nodo(void* valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL){
        return NULL;
    }
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

bool cola_encolar(cola_t* cola, void* valor){
    nodo_t* nodo = crear_nodo(valor);
    if(nodo == NULL){
        return false;
    }

    if (cola->prim == NULL){
        cola->prim = nodo;
    }
    if (cola->ultimo != NULL){
        cola->ultimo->prox = nodo;
    }
    cola->ultimo = nodo;
    return true;
}

void* cola_ver_primero(const cola_t* cola){
    if (cola_esta_vacia(cola)){
        return NULL;
    }
    void* dato = cola->prim->dato;
    return dato;
}

void* cola_desencolar(cola_t* cola){
    if (cola_esta_vacia(cola)){
        return NULL;
    }
    if (cola->prim == cola->ultimo){
        cola->ultimo = NULL;
    }
    void* resultado = cola->prim->dato;
    nodo_t* prox = cola->prim->prox;
    free(cola->prim);
    cola->prim = prox;
    return resultado;
}