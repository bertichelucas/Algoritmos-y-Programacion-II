#include "lista.h"

#include <stdlib.h>

// gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o pruebas *.c
// valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas

typedef struct nodo {
    void* dato;
    struct nodo* prox; 
} nodo_t;

struct lista {
    nodo_t* prim;
    nodo_t* ultimo;
    size_t largo;
};

lista_t* lista_crear(void){
    lista_t* lista = malloc(sizeof(lista_t));
    if (lista == NULL){
        return NULL;
    }
    lista->largo = 0;
    lista->prim = NULL;
    lista->ultimo = NULL;
    return lista;
}

bool lista_esta_vacia(const lista_t* lista){
    if (lista->largo == 0){
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

bool lista_insertar_primero(lista_t* lista, void* dato){
    nodo_t* nodo = crear_nodo(dato);
    if (nodo == NULL) {
        return false;
    }
    if (lista_esta_vacia(lista) == true){
        lista->prim = nodo;
        lista->ultimo = nodo;
    } else{
        nodo->prox = lista->prim;
        lista->prim = nodo;
    }
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t* lista, void* dato){
    nodo_t* nodo = crear_nodo(dato);
    if (nodo == NULL){
        return false;
    }
    if (lista_esta_vacia(lista) == true){
        lista->prim = nodo;
        lista->ultimo = nodo;
    } else{
        lista->ultimo->prox = nodo;
        lista->ultimo = nodo;
    }
    lista->largo++;
    return true;
}

void* lista_borrar_primero(lista_t* lista){
    if(lista_esta_vacia(lista) == true){
        return NULL;
    }
    void* dato = lista->prim->dato;
    nodo_t* nodo = lista->prim;
    if (lista->largo == 1){
        lista->prim = NULL;
        lista->ultimo = NULL;
    } else{
        lista->prim = lista->prim->prox;
    }
    free(nodo);
    lista->largo--;
    return dato;
}

void* lista_ver_primero(const lista_t* lista){
    if(lista_esta_vacia(lista) == true){
        return NULL;
    }
    return lista->prim->dato;
}

void* lista_ver_ultimo(const lista_t* lista){
    if(lista_esta_vacia(lista) == true){
        return NULL;
    }
    return lista->ultimo->dato;
}

size_t lista_largo(const lista_t* lista){
    return lista->largo;
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t* actual = lista->prim;
    void* dato;
    while(actual){
        dato = actual->dato;
        if (visitar(dato, extra) == false){
            break;
        }
        actual = actual->prox;
    }
}

void lista_destruir(lista_t* lista, void (*destruir_dato)(void*)){
    nodo_t* actual = lista->prim;
    nodo_t* anterior = NULL;
    while(actual){
        anterior = actual;
        if (destruir_dato != NULL){
            destruir_dato(anterior->dato);
        }
        actual = actual->prox;
        free(anterior);
    }
    free(lista);
}

struct lista_iter{
    lista_t* lista;
    nodo_t* anterior;
    nodo_t* actual;
};

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iterador = malloc(sizeof(lista_iter_t));
    if (iterador == NULL){
        return NULL;
    }
    iterador->lista = lista;
    iterador->actual = lista->prim;
    iterador-> anterior = NULL;
    return iterador;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if(iter->actual == NULL){
        return false;
    }
    iter->anterior = iter->actual;
    iter->actual = iter->actual->prox;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    if (iter->actual == NULL){
        return NULL;
    }
    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    if (iter->actual ==NULL){
        return true;
    }
    return false;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    if (iter->anterior == NULL && iter->actual == NULL){
        lista_insertar_primero(iter->lista, dato);
        iter->actual = iter->lista->prim;
        return true;
    }else if (iter->anterior == NULL){
        lista_insertar_primero(iter->lista, dato);
        iter->actual = iter->lista->prim;
        return true;
    } else if(iter->actual == NULL){
        lista_insertar_ultimo(iter->lista, dato);
        iter->actual = iter->lista->ultimo;
        return true;
    }
    nodo_t* nodo = crear_nodo(dato);
    if (nodo == NULL){
        return false;
    }
    iter->lista->largo++;
    iter->anterior->prox = nodo;
    nodo->prox = iter->actual;
    iter->actual = nodo;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
    if(iter->actual == NULL){
        return NULL;
    }
    if(iter->anterior == NULL){
        iter->actual = iter->actual->prox;
        return lista_borrar_primero(iter->lista);
    }
    iter->lista->largo--;
    nodo_t* nodo = iter->actual;
    if (iter->lista->ultimo == nodo){
        iter->lista->ultimo = iter->anterior;
    }
    void* dato = nodo->dato;
    iter->actual = iter->actual->prox;
    iter->anterior->prox = iter->actual;
    free(nodo);
    return dato;
}
