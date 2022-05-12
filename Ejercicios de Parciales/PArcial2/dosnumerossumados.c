//Implementar una funcion que reciba un arreglo de N numeros enteros
//Y un numero K y determine en tiempo lineal de n si existe un par de elementos del
//Arreglo que sumen exactamente K
// Justificar la complejidad de la funcion implementada.
#include <stdbool.h>
#include <stdio.h>
#include "hash.h"

bool suma_k(const int arreglo[], size_t n, int k){
    hash_t* hash = hash_crear(NULL);
    if(hash == NULL) return NULL;
    for(size_t i = 0; i < n; i++){
        if (hash_pertence(hash, k - arreglo[i])){
            hash_destruir(hash);
            return true;
        }
        hash_guardar(hash, arreglo [i], NULL);
    }
    hash_destruir(hash);
    return false;
}