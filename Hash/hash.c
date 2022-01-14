#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hash.h"
#include "lista.h"

#define TAM 21
#define CRIT_REDIM 3 //Criterio de redimension
#define REDIM 2 // Proporcion a redimensionar
#define CRIT_ACHIC 4 //Criterio para achicar
/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS HASH ABIERTO
 * *****************************************************************/

// campo_hash_t almacena la clave y el dato asociado
typedef struct {
    char* clave;
    void* dato;
} campo_hash_t;

struct hash {
    lista_t** tabla;
    size_t tam;
    size_t cant;
    hash_destruir_dato_t destruir_dato;
};

// https://en.wikipedia.org/wiki/Jenkins_hash_function 
// Lo unico que se modifico es que devuelva un size_t y que reciba char*
size_t jenkins_one_at_a_time_hash(const char* key, size_t length) {
  size_t i = 0;
  size_t hash = 0;
  while (i != length) {
    hash += (key[i++]);
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}
/* ******************************************************************
 *                          FUNCIONES AUXILIARES
 * *****************************************************************/
// Busca un elemento en el hash, si lo encuentra devuelve el campo (clave, dato) correspondiente.
// Si borrar es true se encarga de eliminar el campo del hash y devolverlo.
// Si no lo encuentra devuelve NULL.
// En caso de falla de devuelve NULL.
campo_hash_t* buscar_elemento(const hash_t* hash, const char *clave, bool borrar) {
    size_t pos = jenkins_one_at_a_time_hash(clave, strlen(clave)) % hash->tam;
    lista_t* lista = hash->tabla[pos];
    lista_iter_t* iter = lista_iter_crear(lista);
    if (iter == NULL) return NULL;

    campo_hash_t* actual = (campo_hash_t*)lista_iter_ver_actual(iter);
    while (actual != NULL) {
        if (strcmp(actual->clave, clave) == 0){
            if (borrar) lista_iter_borrar(iter);
            break;
        }
        lista_iter_avanzar(iter);
        actual = (campo_hash_t*)lista_iter_ver_actual(iter);
    }
    lista_iter_destruir(iter);
    return actual;
}
// Crea un campo a almacenar en el Hash, con clave y dato
// Si falla devuelve NULL
campo_hash_t* campo_crear(const char* clave, void* dato){
    campo_hash_t* campo = malloc(sizeof(campo_hash_t));
    if (campo == NULL) return NULL;
    if ((campo->clave = strdup(clave)) == NULL) {
        free(campo);
        return NULL;
    }
    campo->dato = dato;
    return campo;
}

// Destruye un campo especifico. Si destruir_dato es NULL, no se destruye el dato
void campo_destruir(campo_hash_t *campo, hash_destruir_dato_t destruir_dato){
    if (destruir_dato != NULL) destruir_dato(campo->dato);
    free(campo->clave);
    free(campo);
}
// Crea una tabla de hash, de tamaño tam. Si falla devuelve NULL.
lista_t **tabla_crear(size_t tam){
    lista_t **tabla = malloc(sizeof(lista_t*) * tam);
    if (tabla == NULL) return NULL;
    // Para cada posicion en la tabla del hash creo una lista vacia
    for (int i = 0; i < tam; i++){
        tabla[i] = lista_crear();

        if (tabla[i] == NULL) {
            for (int j = 0; j < i; j++){
                free(tabla[j]);
            }
            free(tabla);
            return NULL;
        }
    }
    return tabla;
}
// Destruye  una tabla, si destruir_dato es != NULL destruye el dato. Si destruir_campo es false,
// destruye la lista sin destruir el campo. (Esta condicion se usa para casos de redimension)
void tabla_destruir(lista_t** tabla, size_t n, hash_destruir_dato_t destruir_dato, bool destruir_campo){
    for (int i = 0; i < n ; i++){
        lista_t* lista = tabla[i];
        if (destruir_campo == true) {
            while (!lista_esta_vacia(lista)) {
                campo_hash_t* campo = lista_borrar_primero(lista);
                campo_destruir(campo, destruir_dato);
            }
        }
        lista_destruir(lista, NULL);
    }
    free(tabla);
}
// Redimensiona la tabla de hash al tamaño nuevo tam. Si falla no se modifica la 
// tabla original. Si todo sale bien el hash tiene una nueva tabla con los mismos 
// datos. Devuelve false en caso de fallo.
bool hash_redimensionar(hash_t* hash, size_t tam) {
    lista_t** nueva_tabla = tabla_crear(tam);
    if (nueva_tabla == NULL) return false;
    for (size_t i = 0; i < hash->tam; i++) {
        lista_iter_t *iter = lista_iter_crear(hash->tabla[i]);
        if (iter == NULL) {
            tabla_destruir(nueva_tabla, tam, hash->destruir_dato, false);
            return false;
        }
        while (!lista_iter_al_final(iter)) {
            campo_hash_t* actual = lista_iter_ver_actual(iter);
            size_t numero_hash = jenkins_one_at_a_time_hash(actual->clave, strlen(actual->clave)) % tam;
            lista_t *lista = nueva_tabla[numero_hash];
            if(lista_insertar_ultimo(lista, actual) == false) {
                tabla_destruir(nueva_tabla, tam, hash->destruir_dato, false);
                return false;
            }
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);
    }
    tabla_destruir(hash->tabla, hash->tam, NULL, false);
    hash->tabla = nueva_tabla;
    hash->tam = tam;
    return true;
}
/* ******************************************************************
 *                  FIN FUNCIONES AUXILIARES
 * *****************************************************************/
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));
    if (hash == NULL) return NULL;
    hash->cant = 0;
    hash->tam = TAM;
    hash->destruir_dato = destruir_dato;
    hash->tabla = tabla_crear(hash->tam);
    if(hash->tabla == NULL) {
        free(hash);
        return NULL;
    }
    return hash;
}

void hash_destruir(hash_t* hash){
    tabla_destruir(hash->tabla, hash->tam, hash->destruir_dato, true);
    free(hash);
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    float fact_carga = (float) (hash->cant / hash->tam);
    if (fact_carga >= CRIT_REDIM) {
        if (!hash_redimensionar(hash, REDIM * hash->tam)) return false;
    }

    campo_hash_t* actual = buscar_elemento(hash, clave, false);
    if (actual != NULL){
        if (hash->destruir_dato != NULL) hash->destruir_dato(actual->dato);
        actual->dato = dato;
        return true;
    }
    // Si la clave no esta en la lista, se crea un nuevo
    // campo a guardar y se inserta en la ultima posicion de la lista.
    size_t pos = jenkins_one_at_a_time_hash(clave, strlen(clave)) % hash->tam;
    actual = campo_crear(clave, dato);
    if (!lista_insertar_ultimo(hash->tabla[pos], actual)) {
        campo_destruir(actual, NULL);
        return false;
    }
    hash->cant++;
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
    if(hash_cantidad(hash) == 0) return NULL;
    if (hash->cant * CRIT_ACHIC <= hash->tam && hash->tam > TAM) {
        hash_redimensionar(hash, hash->tam / CRIT_REDIM);
    }

    campo_hash_t* actual = buscar_elemento(hash, clave, true);
    if (actual == NULL) return NULL;

    void* dato = actual->dato;
    campo_destruir(actual, NULL);
    hash->cant--;
    
    return dato;
}

void *hash_obtener(const hash_t *hash, const char *clave){
    if(hash_cantidad(hash) == 0) return NULL;

    campo_hash_t* actual = buscar_elemento(hash, clave, false);

    return actual != NULL ? actual->dato : NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
    if(hash_cantidad(hash) == 0) return false;
    
    campo_hash_t* actual = buscar_elemento(hash, clave, false);
    
    return actual == NULL ? false : true;
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cant;
}

struct hash_iter {
    const hash_t* hash;
    size_t pos_tabla;
    lista_iter_t* iterador;
};

/* ********************************
*   FUNCION AUXILIAR ITERADOR
***********************************/
// Se encarga de encontrar la primera lista no vacia
// dentro de la tabla y crea un iterador para esa lista, guardandolo en
// la estructura de hash_iter. Devuelve true en caso de encontrarla.
// Caso contrario devuelve False
bool buscar_lista( hash_iter_t* iter){
    if (iter->pos_tabla == iter->hash->tam) return false;
    lista_t* lista = iter->hash->tabla[iter->pos_tabla];
    while (lista_esta_vacia(lista) && iter->pos_tabla != (iter->hash->tam - 1)){
        iter->pos_tabla++;
        lista = iter->hash->tabla[iter->pos_tabla];
    }
    if(iter->pos_tabla == (iter->hash->tam -1)){
        //Estan todas las listas vacias
        return false;
    }

    lista_iter_t* iterador = lista_iter_crear(lista);
    if (iterador == NULL){
        free(iter);
        return false;
    }
    iter->iterador = iterador;
    return true;
}
// Fin funcion auxiliar iterador

hash_iter_t *hash_iter_crear(const hash_t* hash){
    hash_iter_t* iter = malloc(sizeof(hash_iter_t));
    if (iter == NULL) return NULL;
    iter->hash = hash;
    iter->pos_tabla = 0;
    iter->iterador = NULL;
    buscar_lista(iter);
    return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
    // Si la lista se encuentra al final, cambia de lista
    // con la funcion buscar lista.
    if (iter->iterador == NULL) return false;
    lista_iter_avanzar(iter->iterador);
    if (lista_iter_al_final(iter->iterador)){
        lista_iter_destruir(iter->iterador);
        iter->iterador = NULL;
        iter->pos_tabla++;
        return buscar_lista(iter);
    }
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
    if (iter->iterador == NULL) return NULL;
    campo_hash_t* campo = lista_iter_ver_actual(iter->iterador);
    return campo->clave; 
}

bool hash_iter_al_final(const hash_iter_t *iter){
    return iter->iterador == NULL;
}

void hash_iter_destruir(hash_iter_t *iter){
    //Si hay iterador de lista lo libera, si no solamente libera
    //El iterador de hash
    if(iter->iterador != NULL) lista_iter_destruir(iter->iterador);
    free(iter);
}
