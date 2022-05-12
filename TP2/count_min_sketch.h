#ifndef COUNT_MIN_SKETCH_H
#define COUNT_MIN_SKETCH_H
#include <stdlib.h>

typedef struct count_min_sketch count_min_sketch_t;

// Crea un Count min sketch
count_min_sketch_t* count_min_sketch_crear();

// Desstruye la estructura liberando la memoria pedida
// Pre: la estructura fue inicializada
// Pos: se libero la memoria
void count_min_sketch_destruir(count_min_sketch_t* cms);

// Recibe una clave, e incrementa su contador en 1
// Pre: la estructura fue inicializada
// Pos: 'clave' ahora tiene una cantidad mas
void count_min_sketch_incrementar(count_min_sketch_t* cms, const char *clave);

// Recibe una clave y devuelve la cantidad asociada
// Pre: la estructura fue inicializada
size_t count_min_sketch_obtener(const count_min_sketch_t* cms, const char*clave);

#endif
