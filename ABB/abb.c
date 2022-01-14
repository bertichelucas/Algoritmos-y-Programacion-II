#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "abb.h"
#include "pila.h"


typedef struct nodo_abb {
    struct nodo_abb* izq;
    struct nodo_abb* der;
    char* clave;
    void* dato;
} nodo_abb_t;

struct abb {
    nodo_abb_t* raiz;
    size_t cant;
    abb_destruir_dato_t destruir;
    abb_comparar_clave_t comparar;
};

nodo_abb_t* nodo_crear(const char* clave, void* dato){
    nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));
    if (nodo == NULL) return NULL;
    nodo->clave = strdup(clave);
    if (nodo->clave == NULL) {
        free(nodo);
        return NULL;
    }
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

void nodo_destruir(nodo_abb_t*nodo, abb_destruir_dato_t destruir_dato){
    if (destruir_dato != NULL) destruir_dato(nodo->dato);
    free(nodo->clave);
    free(nodo);
}

// Busca un nodo en el abb y lo devuelve, si no devuelve NULL.
// Actualiza el nodo_padre de ese nodo, siempre se devuelve el conjunto (nodo, padre_nodo)
nodo_abb_t* buscar_nodo(nodo_abb_t** nodo_padre, nodo_abb_t* actual, const char* clave, abb_comparar_clave_t comparar){
    if (actual == NULL) return NULL;
    if (comparar(clave, actual->clave) == 0) return actual;
    
    if(nodo_padre != NULL) *nodo_padre = actual;

    if (comparar(clave, actual->clave) > 0){
        return buscar_nodo(nodo_padre, actual->der, clave, comparar);
    } 
    return buscar_nodo(nodo_padre, actual->izq, clave, comparar);
}   

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* abb = malloc(sizeof(abb_t));
    if (abb == NULL) return NULL;
    abb->raiz = NULL;
    abb->cant = 0;
    abb->destruir = destruir_dato;
    abb->comparar = cmp;
    return abb;
}

void _abb_destruir(nodo_abb_t *nodo, abb_destruir_dato_t destruir_dato) {
    if (nodo == NULL) return;
    _abb_destruir(nodo->izq, destruir_dato);
    _abb_destruir(nodo->der, destruir_dato);
    nodo_destruir(nodo, destruir_dato);
}

void abb_destruir(abb_t *arbol){
    _abb_destruir(arbol->raiz, arbol->destruir);
    free(arbol);
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    nodo_abb_t*padre = arbol->raiz;
    nodo_abb_t*nodo = buscar_nodo(&padre, arbol->raiz, clave, arbol->comparar);
    if (nodo == NULL) {
        nodo = nodo_crear(clave, dato);
        if (nodo == NULL) return false;
        arbol->cant++;
        
        if (arbol->raiz == NULL) arbol->raiz = nodo;
        else if (arbol->comparar(padre->clave, clave) < 0) padre->der = nodo;
        else padre->izq = nodo;
        return true;
    }
    if (arbol->destruir != NULL) arbol->destruir(nodo->dato);
    nodo->dato = dato;
    return true;
} 

void* abb_obtener(const abb_t *arbol, const char *clave){
    nodo_abb_t* nodo = buscar_nodo(NULL, arbol->raiz, clave, arbol->comparar);
    return nodo == NULL ? NULL : nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    return buscar_nodo(NULL, arbol->raiz, clave, arbol->comparar) != NULL;
}

size_t abb_cantidad(const abb_t *arbol){
    return arbol->cant;
}

// Recibe un nodo a borrar, su padre y la raiz del arbol
// Borra el nodo actualizando el hijo del padre y si ese nodo es la raiz, actualiza la raiz del arbol.
void borrar_auxiliar(nodo_abb_t* nodo_borrar, nodo_abb_t* nodo_padre, nodo_abb_t **raiz){
    nodo_abb_t* reemplazo = nodo_borrar->izq == NULL ? nodo_borrar->der : nodo_borrar->izq;
    if (nodo_padre->izq == nodo_borrar) nodo_padre->izq = reemplazo;
    else if (nodo_padre->der == nodo_borrar) nodo_padre->der = reemplazo; 
    else *raiz = reemplazo; // nodo_padre == nodo_borrar -> nodo_borrar es raiz
    nodo_destruir(nodo_borrar, NULL);
}

//Reemplaza los campos del nodo a borrar por su reemplazante
void reemplazar_datos(nodo_abb_t* nodo_borrar, char* clave_reemplazo, void* dato_reemplazo){
    free(nodo_borrar->clave);
    nodo_borrar->clave = clave_reemplazo;
    nodo_borrar->dato = dato_reemplazo;
}

void *abb_borrar(abb_t *arbol, const char *clave){
    nodo_abb_t* nodo_padre = arbol->raiz;
    nodo_abb_t* nodo_borrar = buscar_nodo(&nodo_padre, arbol->raiz, clave, arbol->comparar);
    if (nodo_borrar == NULL) return NULL;

    void* dato = nodo_borrar->dato;
    // Caso de un solo hijo o sin hijos
    if (nodo_borrar->der == NULL || nodo_borrar->izq == NULL){
        borrar_auxiliar(nodo_borrar, nodo_padre, &arbol->raiz);
    } else { //Caso de dos hijos
        // Busca el mayor de la izq y actualiza los datos del actual a borrar con el reemplazante
        // Borra el reemplazante
        nodo_abb_t* reemplazo = nodo_borrar->izq;
        nodo_padre = nodo_borrar;
        while(reemplazo->der != NULL){
            nodo_padre = reemplazo;
            reemplazo = reemplazo->der;   
        }
        char* clave_reemplazo = strdup(reemplazo->clave);
        void* dato_reemplazo = reemplazo->dato;
        //Queda el caso de borrar un nodo con un hijo o sin hijos, utilizamos la funcion de borrado auxiliar
        borrar_auxiliar(reemplazo, nodo_padre, &arbol->raiz);
        reemplazar_datos(nodo_borrar, clave_reemplazo, dato_reemplazo);
    }
    arbol->cant--;
    return dato;
}

bool _abb_in_order(nodo_abb_t*nodo, bool visitar(const char *, void *, void *), void *extra){
    if (nodo == NULL) return true;
    if (_abb_in_order(nodo->izq, visitar, extra)) {
        if (!visitar(nodo->clave, nodo->dato, extra)) return false;
        return _abb_in_order(nodo->der, visitar, extra);
    }
    return false;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    _abb_in_order(arbol->raiz, visitar, extra);
}

struct abb_iter {
    pila_t* pila;
};

// Recibe un nodo actual a apilar, apila el actual y todos los izq.
// Devuelve false si no pudo apilar
bool apilar_actual_izquierdos(abb_iter_t* iter, nodo_abb_t* actual){
    while(actual != NULL){
        if(!pila_apilar(iter->pila, actual)) return false;
        actual = actual->izq;
    }
    return true;
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(iter == NULL) return NULL;
    pila_t* pila = pila_crear();
    if (pila == NULL){
        free(iter);
        return NULL;
    }
    iter->pila = pila;
    nodo_abb_t* actual = arbol->raiz;
    if(!apilar_actual_izquierdos(iter, actual)){
        free(iter);
        pila_destruir(iter->pila);
        return NULL;
    }
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
    nodo_abb_t* desapilado = pila_desapilar(iter->pila);
    if (desapilado == NULL) return false;
    nodo_abb_t* actual = desapilado->der;
    return apilar_actual_izquierdos(iter, actual);;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    nodo_abb_t* actual = pila_ver_tope(iter->pila);
    return actual != NULL ? actual->clave : NULL;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    nodo_abb_t* actual = pila_ver_tope(iter->pila);
    return actual == NULL ? true : false; 
}

void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}
