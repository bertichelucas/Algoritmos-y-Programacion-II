#include "lista.h"
#include <stdlib.h>

//Definicion de nodo
typedef struct nodo{
    void* dato;
    struct nodo* prox;
}nodo_t;

struct lista{
    nodo_t* prim;
    nodo_t* ult;
    size_t largo; 
};

//Funcion auxiliar para crear un nodo
//Devuelve el nodo con el dato guardado y prox
//apuntando al proximo nodo (o NULL)
nodo_t *_nodo_crear(void* dato, nodo_t* prox){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) {
        return NULL;
    }
    nodo->dato = dato;
    nodo->prox = prox;
    return nodo; 
}

//Funcion auxiliar para la destrucccion del nodo
//Si se pasa una funcion de destruccion se libera el dato
void _nodo_destruir(nodo_t* nodo, void (*destruir_dato)(void *)){
    if (destruir_dato != NULL) {
        destruir_dato(nodo->dato);
    } 
    free(nodo);
}

lista_t *lista_crear(void){
    lista_t* lista = malloc(sizeof(lista_t));
    if (lista == NULL) {
        return NULL;
    }

    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t* nodo = _nodo_crear(dato, lista->prim);
    if (nodo == NULL) {
        return NULL;
    }
    
    if (lista_esta_vacia(lista)) {
        lista->ult = nodo;
    }
    lista->prim = nodo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t* nodo = _nodo_crear(dato, NULL);
    if (nodo == NULL) {
        return false;
    }
    
    if (lista_esta_vacia(lista)) {
        lista->prim = nodo;
    }
    else {
        lista->ult->prox = nodo;
    }
    
    lista->ult = nodo;
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista){
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    void* dato = lista->prim->dato;
    nodo_t* tmp = lista->prim->prox;
    //Caso de un solo elemento
    if (tmp == NULL) {
        lista->ult = tmp;
    }
    _nodo_destruir(lista->prim, NULL);

    lista->prim = tmp;
    lista->largo--;
    return dato;
}

void *lista_ver_primero(const lista_t *lista){
    return lista_esta_vacia(lista) ? NULL : lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
    return lista_esta_vacia(lista) ? NULL : lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    while (!lista_esta_vacia(lista)) {
        void* dato = lista_borrar_primero(lista);
        if (destruir_dato != NULL) {
            destruir_dato(dato);
        }
    }
    free(lista);
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t* actual = lista->prim;
    while (actual != NULL) {
        if (!visitar(actual->dato, extra)) {
            break;
        }
        actual = actual->prox;
    }
}

// ITERADOR
struct lista_iter{
    lista_t* lista;
    nodo_t* anterior;
    nodo_t* actual;
};

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if (iter == NULL) {
        return NULL;
    }

    iter->lista = lista;
    iter->anterior = lista->prim;
    iter->actual = lista->prim;
    return iter;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if (lista_iter_al_final(iter)) {
        return false;
    }
    // Si anterior y actual son iguales, solo avanzo actual 
    // Este caso seria la cuando itero el primer elemento
    if (iter->anterior != iter->actual) {
        iter->anterior = iter->actual;
    }
    
    iter->actual = iter->actual->prox;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    return lista_iter_al_final(iter) ? NULL : iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->actual == NULL;
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_t* nodo = _nodo_crear(dato, iter->actual);
    if (nodo == NULL) {
        return false;
    }
    //Si agrego al final tengo que actualizar el ultimo de la lista
    if (lista_iter_al_final(iter)) {
        iter->lista->ult = nodo;
    }

    if (iter->actual == iter->lista->prim) {
        // En este caso actualizo el primero de la lista y el aneterior
        iter->anterior = nodo;
        iter->lista->prim = nodo;
    }
    
    else{
        iter->anterior->prox = nodo;
    }
    //En todos los casos actualizo actual
    iter->actual = nodo;
    iter->lista->largo++;

    return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
    if (lista_iter_al_final(iter)) {
        return NULL;
    }
    void* dato = iter->actual->dato;
    nodo_t* nodo = iter->actual;
    //Si es el primero actualizo el primero de la lista y el anterior
    if (nodo == iter->lista->prim) {
        iter->lista->prim = nodo->prox;
        iter->anterior = nodo;
    }

    // Si es el ultimo elemento tengo que actualizar el ultimo de la lista
    if(nodo == iter->lista->ult){
        iter->lista->ult = iter->anterior;
    }

    iter->actual = nodo->prox;
    iter->lista->largo--;
    iter->anterior->prox = iter->actual;

    _nodo_destruir(nodo, NULL);
    return dato;
}
