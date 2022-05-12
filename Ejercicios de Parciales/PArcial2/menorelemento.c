
//Implementar una funcion que dada un arreglo de N numeros positivos
//Encuentre en tiempo lineal el menor numero posible (tambien entero positivo)
//Que no se encuentre en el arreglo. Justificar la complejidad de la funcion
#include <stdio.h>
#include <stdbool.h>
#include "hash.h"

int menor_elemento(const void* arreglo[], size_t* n){
    hash_t* hash = hash_crear(NULL);
    if (hash == NULL) return NULL;
    for (size_t i = 0; i < n; i++){
        hash_guardar(hash, arreglo[i], NULL);
    }
    size_t menor = 0;
    size_t contador = 1;
    while(menor == 0){
        if (!hash_pertenece(hash, contador)) menor = contador;
        contador++;
    }
    hash_destruir(hash);
    return menor;
}

//complejidad en el mejor caso O(n). En el peor caso
//Crear guardar y pertenece son O(1).
//ejemplo numeros del 1 al 15 estan en el arreglo y el 16 es el menor numero que no se encuentra
// En este caso guarda en el hash los 15 numeros. O(n)
// Luego va a ir desde el 1 hasta el 16 recorriendo nuevamente O(n)
// Entonces termina siendo O(2n)
// que podria simplificarse como O(n)