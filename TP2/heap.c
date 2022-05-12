#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

#define TAM 15
#define CRIT_REDIM 2
#define CRIT_ACHIC 4

struct heap{
    void** datos;
    size_t tam;
    size_t cant;
    cmp_func_t comparar;
};
/*
    FUNCIONES AUXILIARES
*/
void swap(void** a, void** b){
    void* aux = *a;
    *a = *b;
    *b = aux;
}

void down_heap(void **arreglo, size_t pos, size_t n, cmp_func_t comparar){
    size_t hijo_izq = (2 * pos) + 1;
    size_t hijo_der =  hijo_izq + 1;
    size_t mayor_hijos;
    // Si el hijo izq es mayor o igual que n, no tiene hijos
    if (hijo_izq >= n) return;
    // Si el hijo derecho es mayor o igual que n, el mayor de los hijos
    // es el unico hijo que es el izq
    if (hijo_der >= n) mayor_hijos = hijo_izq;
    else{
        mayor_hijos = comparar(arreglo[hijo_izq], arreglo[hijo_der]) >= 0 ? hijo_izq : hijo_der;
    }   

    if (comparar(arreglo[pos], arreglo[mayor_hijos]) < 0) {
        swap(&arreglo[pos], &arreglo[mayor_hijos]);
        down_heap(arreglo, mayor_hijos, n, comparar);
    }
}

void upheap(void** datos, size_t pos, cmp_func_t comparar){
    if (pos == 0) return;
    size_t pos_padre = (pos - 1) / 2;
    void* padre = datos[pos_padre];
    if (comparar(datos[pos], padre) > 0){
        swap(&datos[pos], &datos[pos_padre]);
        upheap(datos, pos_padre, comparar);
    }
}

void heapify(void *arreglo[], size_t n, cmp_func_t comparar){
    for (size_t i = 0; i < n; i++) {
        down_heap(arreglo, (n - 1 - i), n, comparar);
    }
}

bool heap_redimension(heap_t* heap, size_t tam){
    void** nuevos_datos = realloc(heap->datos, sizeof(void *) * tam);
    if (nuevos_datos == NULL) return false;

    heap->datos = nuevos_datos;
    heap->tam = tam;
    return true;
}

// Crea un heap donde el tamaño del arreglo de datos es n
// Devuelve NULL si falla
heap_t *heap_crear_aux(cmp_func_t cmp, size_t n){
    heap_t* heap = malloc(sizeof(heap_t));
    if (heap == NULL) return NULL;
    heap->datos = malloc(sizeof(void*) * n);
    if (heap->datos == NULL){
        free(heap);
        return NULL;
    }

    heap->tam = n;
    heap->cant = 0;
    heap->comparar = cmp;
    return heap;
}

heap_t *heap_crear(cmp_func_t cmp){
    return heap_crear_aux(cmp, TAM);
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t * heap = heap_crear_aux(cmp, n);
    if (heap == NULL) return NULL;
    heap->cant = n;
    for (size_t i = 0; i < n; i++) {
        heap->datos[i] = arreglo[i];
    }
    heapify(heap->datos, heap->cant, heap->comparar);
    return heap;
}

bool heap_encolar(heap_t *heap, void *elem){
    if (heap->cant == heap->tam){
        if (!heap_redimension(heap, heap->tam * CRIT_REDIM)) return false;
    }
    heap->datos[heap->cant] = elem;
    upheap(heap->datos, heap->cant, heap->comparar);
    heap->cant++;
    return true;
}

void *heap_desencolar(heap_t *heap){
    if (heap_esta_vacio(heap)) return NULL;
    if (heap->cant * CRIT_ACHIC <= heap->tam && heap->tam > TAM){
        heap_redimension(heap, heap->tam / CRIT_REDIM);
    }

    void *dato = heap->datos[0];
    heap->cant--;
    swap(&heap->datos[0], &heap->datos[heap->cant]);
    down_heap(heap->datos, 0,heap->cant, heap->comparar);
    return dato;
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
    return heap->cant == 0;
}

void *heap_ver_max(const heap_t *heap){
    return heap_esta_vacio(heap) ? NULL : heap->datos[0];
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    if (destruir_elemento != NULL){
        for(int i = 0; i < heap->cant; i++){
            destruir_elemento(heap->datos[i]);
        }
    }
    free(heap->datos);
    free(heap);
}


void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heapify(elementos,cant, cmp);
    while(cant != 0){
        swap(&elementos[0], &elementos[cant-1]);
        cant--;
        down_heap(elementos, 0, cant, cmp);
    }
}
