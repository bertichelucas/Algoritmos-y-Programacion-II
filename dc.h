#ifndef DC
#define DC
#include "calc_helper.h"

// recibe un arreglo de strings.
// Libera todas las strings. Luego libera el arreglo.

void destruir_arreglo_infix(char** arreglo);

//Se encarga de realizar las operaciones correspondientes a los tokens oper.
//Apila el resultado de la operacion y devuelve falso en caso de error.
bool operar(pilanum_t* pila, struct calc_token* destino);

//Recibe un arreglo de strings y un numero donde almacenara el resultado final de la linea
//De haber algun error en los calculos devuelve falso.
bool calcular_linea(char** arreglo, calc_num* resultado);

//Recibe operaciones posfix con stdin y se encarga de convertirlas a 
//notacion posfix.
void calculadora_polaca();
#endif
