#ifndef ABB_H
#define ABB_H

#include <stdlib.h>
#include <stdbool.h>
/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS ABB
 * *****************************************************************/
typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;

typedef int (*abb_comparar_clave_t) (const char*, const char*);
typedef void (*abb_destruir_dato_t) (void *);

// Crea una abb
// Post: devuelve un abb vacio
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Guarda un elemento en el abb, si la clave ya s encuentra en la estructura
// la reemplaza. De no poder guardarlo devuelve false.
// Pre: El arbol fue creado
// Post: Se almacenó el par (clave, dato)
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);


// Borra un elemento del abb, devuelve el dato asociado. Devuelve 
// NULL si el dato no estaba.
// Pre el arbol fue creado
// Post: el elemento fue borrado del arbol y se lo devolvió, en el 
// caso de que estuviera guardado.
void *abb_borrar(abb_t *arbol, const char *clave);

// Devuelve el dato asociado a una clave del abb. Devuelve 
// NULL si el dato no estaba.
// Pre el arbol fue creado
// Post: Se Devuelve el dato en caso de estar guardado.
void *abb_obtener(const abb_t *arbol, const char *clave);

// Devuelve si la clave esta en el abb o no.
// Pre el arbol fue creado
// Post: Devuelve true en caso de pertenecer al abb, false
// en caso contrario.
bool abb_pertenece(const abb_t *arbol, const char *clave);

// Devuelve la cantidad de elementos del abb.
// Pre el arbol fue creado.
size_t abb_cantidad(const abb_t *arbol);

// Destruye el arbol liberando la memoria pedida y llamando a la funcon destruir para cada
// par (clave, dato).
// Pre: El arbol fue creado.
// Post: El arbol fue destruido
void abb_destruir(abb_t *arbol);

// iteradores
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

//Recibe un arbol y crea un iterador in order para el arbol
// Pre El arbol fue creado
// Post: Devuelve el iterador o NULL en caso de error.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

//Devuelve True en caso de poder avanzar una posicion, false en caso contrario.
//Pre el iterador fue creado
// Post: Se avanzo una posicion en el abb segun el criterio in order
bool abb_iter_in_avanzar(abb_iter_t *iter);

//Devuelve la clave correspondiente al itema actual. En caso de estar al final
//Devuelve NULL
//Pre el iterador fue creado
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

//Devuelve true si el iterador esta al final, false en caso contrario
//Pre el iterador fue creado
bool abb_iter_in_al_final(const abb_iter_t *iter);

//Destruye el iterador
//Pre el iterador fue creado
void abb_iter_in_destruir(abb_iter_t* iter);

void pruebas_abb_estudiante(void);

#endif
