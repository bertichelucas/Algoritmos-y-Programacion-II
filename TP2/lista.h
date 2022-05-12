
#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS LISTA
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

typedef struct lista lista_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una lista vacia
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elmentos, false en caso contrario.
// Pre: la lista fue creada
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al inicio de la lista. Devuelve false en caso de error.
// Pre: la lista fue creada
// Post: se agrego un elemento al inicio de la lista, la lista tiene un elemento mas.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve false en caso de error.
// Pre: la lista fue creada
// Post: se agrego un elemento al final de la lista, la lista tiene un elemento mas.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Si la lista no esta vacia, borra el primer elemento de la lista y devuelve el dato. 
// Si la lista esta vacia devuelve NULL.
// Pre: la lista fue creada
// Post: se devolvio el primer dato y la lista tiene un elemento menos
void *lista_borrar_primero(lista_t *lista);

// Obtiene el primer elemento de la lista. Si la lista tiene elmentos, se devuelve el dato del primero
// Si esta vacia devuelve NULL.
// Pre: la lista fue creada
// Post: se devolvio el primer elemento de la lista, sin modificar la misma.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el ultimo elemento de la lista. Si la lista tiene elmentos, se devuelve el dato del ultimo
// Si esta vacia devuelve NULL.
// Pre: la lista fue creada
// Post: se devolvio el ultimo elemento de la lista, sin modificar la misma.
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista
// Pre: la lista fue creada
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lsita, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// Itera la lista y aplica la funcion visitar a cada dato,
// hasta llegar al final o hasta que visitar devuelva false, lo que suceda primero.
// extra es un extra utilizado por la funcion visistar
// Pre: la lista fue creada. se recibio una funcion de visita valida
// Post: se itero la lista hasta el final o hasta que visitar devolvio false
// y se le aplico la funcion a cada dato.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/* *****************************************************************
 *                 DEFINICION DE TIPOS DE DATO ITERADOR EXTERNO
 * *****************************************************************/

typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                  PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/
// Crea un iterador de lista
// Pre: la lista fue creada
// Post: devuelve un iterador asociado a la lista
lista_iter_t *lista_iter_crear(lista_t *lista);

// Destruye el iterador
// Pre: el iterador fue creado
// Post: se libero la memoria asociada al iterador
void lista_iter_destruir(lista_iter_t *iter);

// Avanza el iterador hacia el siguiente elemento y devuelve true, si no hay mas elementos devuelve false.
// Pre: el iterador fue creado
// Post: si no esta en el final de la lista, se avanzo al sigueiente elemento y devuelve true.
// Si no devuelve false.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el dato del actual elemento, si llego al final devuelve NULL
// Pre: el iterador fue creado
// Post: se devuelve el dato del elemento actual o NULL si el iterador llego al final
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve verdadero si el iterador se encuentra al 
// final de la lista o false en caso contrario
// Pre: el iterador fue creado
bool lista_iter_al_final(const lista_iter_t *iter);

// Inserta el dato antes del actual elemento. Devuelve false en caso de falla.
// Pre: el iterador fue creado
// Post: se inserto el dato antes que el elemnto actual, la lista
// contiene un elemento mas.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Si el iterador no esta al final, elimina el elemento actual y devuelve el dato.
// Si el iterador llego al final, devuelve NULL.
// Pre: el iterador fue creado
// Post: si el iterador no esta al final, se devolvio el dato actual.
// La lista tiene un elemento menos.
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
void pruebas_lista_estudiante(void);

#endif
