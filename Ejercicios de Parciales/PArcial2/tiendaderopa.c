//Pila enorme de medias que hay que juntar de a pares por colores
//Dado un arreglo de cadenas donde cada cadena representa un color, donde
//cada elemento del arreglo representa una media de dicho color
//Implementar una funcion lineal en la cant de medias
//Que nos indiquen cuantos pares se pueden armar para cada color
//Se devuelve un diccionario clave, color
//Justificar la complejidad de la funcion implementada.
#include "hash.h"

hash_t* pila_medias(const char* arreglo[], size_t n){
    hash_t* hash = hash_crear(NULL);
    if (hash == NULL) return NULL;
    
    
    for (int i = 0; i < n; i++){
        size_t cantidad = 1;
        if (hash_pertenece(hash, arreglo[i])){
            cantidad = hash_obtener(hash, arreglo[i]);
            cantidad++;
        }
        hash_guardar(hash, arreglo[i], cantidad);
    }

   for(int i = 0; i < n; i++){
        size_t cantidad = hash_obtener(hash, arreglo[i]);
        cantidad /= 2;
        hash_guardar(hash, arreglo[i], cantidad);
    }
    return hash;
}