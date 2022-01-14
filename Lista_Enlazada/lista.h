#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

// DEFINICION DE LOS TIPOS DE DATOS

struct lista;
typedef struct lista lista_t;

// PRIMITIVAS DE LA LISTA

//Crea una lista enlazada
//Devuelve la lista vacia o NULL en caso de error
lista_t* lista_crear(void);

//Pre: la lista fue creada
//Devuelve true si la lista esta vacia, false en caso contrario
bool lista_esta_vacia(const lista_t* lista);

//Pre: la lista fue creada
// Se inserta el dato pasado por parametro al principio de la lista
// Devuelve false en caso de fallo, de lo contrario devuelve true
bool lista_insertar_primero(lista_t* lista, void* dato);

//Pre: la lista fue creada
// Se inserta el dato pasado por parameto al final de la lista
// Devuelve false en caso de fallo, de lo contrario devuelve true
bool lista_insertar_ultimo(lista_t* lista, void* dato);

//Pre: La lista fue creada
//Se encarga de eliminar el primer dato de la lista y lo devuelve por parametro
//En caso de error por lista vacia devuelve NULL 
void *lista_borrar_primero(lista_t *lista);

//Pre: La lista fue creada
//Obtiene el valor del primer elemento de la lista y lo devuelve por parametro
//En caso de error por lista vacia devuelve NULL
void *lista_ver_primero(const lista_t *lista);

//Pre: La lista fue creada
//Obtiene el valor del ultimo elemento de la lista y lo devuelve por parametro
//En caso de error por lista vacia devuelve NULL
void *lista_ver_ultimo(const lista_t* lista);

//Pre: La lista fue creada
//Obtiene el largo de la lista y lo devuelve por parametro
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

//Pre: La lista fue creada. Visitar es una funcion que recibe el dato alojado en la lista,
// y un puntero extra con funciones adicionales. El visitar propone una condicion de corte y
// devuelve true si se quiere seguir iterando. En caso contrario es devuelve false.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


// PRIMITIVAS ITERADOR

struct lista_iter;
typedef struct lista_iter lista_iter_t;

//Pre: La lista fue creada. Crea un iterador que recorre la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

//Pre: el iterador fue creado
// Avanza un item en la lista. Devuelve false en caso de estar al final y no poder avanzar.
bool lista_iter_avanzar(lista_iter_t *iter);

//Pre el iterador fue creado.
//Devuelve el dato sobre el cual se encuentra la posicion actual del iterador.
//Devuelve NULL en caso encontrarse en una posicion no valida (al final)
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Pre el iterador fue creado.
//Devuelve true cuando el iterador esta al final (cuando se avance a un elemento no valido)
//Devuelve false en caso contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

//Pre el iterador fue creado.
//Se encarga de destruir el iterador.
void lista_iter_destruir(lista_iter_t *iter);

//Pre: el iterador fue creado.
//Devuelve false si hubo algun error. Se encarga de insertar el nuevo elemento entre el anterior
// y el actual.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Pre: El iterador fue creado.
//Devuelve el dato que esta alojado en la posicion actual de la lista y lo elimina de la lista.
//Devuelve NULL si la posicion que se esta intentando borrar es invalida. 
void *lista_iter_borrar(lista_iter_t *iter);


void pruebas_lista_estudiante(void);
