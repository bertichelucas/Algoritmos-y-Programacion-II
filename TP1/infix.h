#ifndef INFIX
#define INFIX
#include "cola.h"
#include "pila.h"


// recibe un arreglo de strings.
// Libera todas las strings. Luego libera el arreglo.

void destruir_arreglo_infix(char** arreglo);

//Recibe un token y compara su precedencia con el del tope de la pila
//Devuelve true si el token de la pila tiene menor precedencia. En caso
// contrario devuelve false.
bool calcular_precedencia(pila_t* pila, struct calc_token* destino);

//recibe un arreglo de strings y una cola.
//Por cada string en el arreglo llama a calcular precedencia y en base
// a eso opera. Devuelve false en caso de error.
bool convertir_notacion(char** arreglo, cola_t* cola);

//Recibe una cola de strings y va imprimiendo en stdout una por una
// las strings.
void imprimir_notacion(cola_t* cola);

//Recibe operaciones infix con stdin y se encarga de convertirlas a 
//notacion posfix.
void calc_infix_a_polaca();
#endif
