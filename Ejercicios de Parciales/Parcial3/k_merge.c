#include "heap.h"

//Escribir una funcion k_merge que reciba k arreglos ordenados
//y devuelva uno nuevo con todos los elementos ordenados.

typedef struct minimo {
    size_t pos;
    size_t k;
    int valor; 
} minimo_t;

minimo_t* crear_minimo(size_t pos, size_t k, int valor){
    minimo_t* minimo = malloc(sizeof(minimo_t));
    if (minimo == NULL) return NULL;
    minimo->pos = pos;
    minimo->k = k;
    minimo->valor = valor;
    return minimo;
}

int cmp_min_arr(int a, int b){
    return a - b;
}

int* k_merge(int** arr, size_t k, size_t tam){
    heap_t* heap = heap_crear(cmp_min_arr);
    if (heap == NULL) return NULL;
    int* resultado = malloc(sizeof(int) * k * tam);
    if (resultado == NULL){
        heap_destruir(heap, NULL);
        return NULL;
    }

    for(int i = 0; i < k; i++){
        heap_encolar(heap, crear_minimo(0, i, arr[i][0]));
    }
    
    for(int count = 0; count < k*tam; count++){
        minimo_t* minimo = heap_desencolar(heap);
        resultado[count] = minimo;
        if (minimo->pos + 1 == tam)  minimo = heap_desencolar(heap);
        heap_encolar(heap, crear_minimo(minimo->pos + 1, minimo->k, arr[k][minimo->pos + 1]));
        free(minimo);
    }

    heap_destruir(heap, NULL);
    return resultado;
}