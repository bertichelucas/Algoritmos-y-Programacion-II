#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Funcion para la comparacion de dos enteros
int comparar_enteros(const void* a, const void* b){
    const int num_a = *(int*) a;
    const int num_b = *(int*) b;
    return num_a - num_b;
}

static void prueba_heap_crear_vacio(){
    printf("Prueba heap crear vacio\n");
    heap_t* heap = heap_crear(comparar_enteros);
    print_test("Prueba heap crear vacio", heap != NULL);
    print_test("Prueba heap vacio cantidad es  0", heap_cantidad(heap) == 0);
    print_test("Prueba heap vacio no se puede desencolar", heap_desencolar(heap) == NULL);
    print_test("Prueba heap ver max es NULL", heap_ver_max(heap) == NULL);
    heap_destruir(heap, NULL);
}

static void prueba_heap_algunos_elementos(){
    printf("Prueba heap algunos elementos\n");
    heap_t* heap = heap_crear(comparar_enteros);
    int a = 6, b = 4, c = 8, d = 15;
    print_test("Prueba heap encolar elemento a es true", heap_encolar(heap, &a));
    print_test("Prueba heap esta vacio es false", !heap_esta_vacio(heap));
    print_test("Prueba heap cantidad es 1 ", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver max es elemento a ", heap_ver_max(heap) == &a);
    print_test("Prueba heap desencolar elemento es a", heap_desencolar(heap) == &a);
    print_test("Prueba heap cantidad es  0", heap_cantidad(heap) == 0);
    print_test("Prueba heap no se puede desencolar", heap_desencolar(heap) == NULL);

    print_test("Prueba heap encolar elemento a es true", heap_encolar(heap, &a));
    print_test("Prueba heap encolar elemento b es true", heap_encolar(heap, &b));
    print_test("Prueba heap encolar elemento c es true", heap_encolar(heap, &c));
    print_test("Prueba heap encolar elemento d es true", heap_encolar(heap, &d));

    print_test("Prueba heap cantidad es 4 ", heap_cantidad(heap) == 4);
    print_test("Prueba heap ver max es elemento d ", heap_ver_max(heap) == &d);
    print_test("Prueba heap desencolar elemento es d", heap_desencolar(heap) == &d);
    print_test("Prueba heap desencolar elemento es c", heap_desencolar(heap) == &c);
    print_test("Prueba heap desencolar elemento es a", heap_desencolar(heap) == &a);
    print_test("Prueba heap desencolar elemento es b", heap_desencolar(heap) == &b);
    print_test("Prueba heap cantidad es  0", heap_cantidad(heap) == 0);
    print_test("Prueba heap no se puede desencolar", heap_desencolar(heap) == NULL);
    print_test("Prueba heap esta vacio es true", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
}

static void prueba_heap_borrar_dinamico(){
    printf("Prueba heap borrar dinamico \n");
    heap_t* heap = heap_crear(comparar_enteros);
    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    int* c = malloc(sizeof(int));
    int* d = malloc(sizeof(int));
    *a = 6;
    *b = 4;
    *c = 8;
    *d = 15;
    heap_encolar(heap, a);
    heap_encolar(heap, b);
    heap_encolar(heap, c);
    heap_encolar(heap, d);
    print_test("Prueba heap cantidad es 4 ", heap_cantidad(heap) == 4);
    print_test("Prueba heap ver max es elemento d ", heap_ver_max(heap) == d);
    heap_destruir(heap,free);
}

static void prueba_heap_con_arreglo(){
    printf("Prueba heap con arreglo\n");
    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    int* c = malloc(sizeof(int));
    int* d = malloc(sizeof(int));
    *a = 6;
    *b = 4;
    *c = 8;
    *d = 15;
    int* arreglo[] = {a, b ,c, d};
    heap_t* heap = heap_crear_arr((void**) arreglo, 4, comparar_enteros);
    print_test("Prueba heap cantidad es 4 ", heap_cantidad(heap) == 4);
    print_test("Prueba heap ver max es elemento d ", heap_ver_max(heap) == d);
    heap_destruir(heap,free);
}

//Crea un vector dinamico con numeros aleatorios para las pruebas
//de Heapsort
int **generar_vector(size_t n) {
    srand((unsigned int) time(NULL));
    int **arr = malloc(sizeof(int**) * n);
    for (size_t i = 0; i < n; i++) {
        arr[i] = malloc(sizeof(int*));
        *arr[i] = rand() % (int) n;
    }   
    return arr;
}

//Destruye el vector de numeros aleatorios.
void destruir_vector(int **arr, size_t n){
    for (size_t i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

static void prueba_heapsort(){
    printf("Prueba heapsort \n");
    int** arreglo = generar_vector(10);
    heap_sort((void**) arreglo, 10, comparar_enteros);
    bool ok = true;
    int anterior = *arreglo[0];
    int actual;
    for(int i = 1; i < 10; i++){
        actual = *arreglo[1];
        if (actual < anterior){
            ok = false;
            break;
        }
        anterior = actual;
    }
    destruir_vector(arreglo, 10);
    print_test("Prueba heapsort el arreglo esta ordenado", ok);
}

static void prueba_heapsort_volumen(){
    printf("Prueba heapsort volumen \n");
    int** arreglo = generar_vector(10000);
    heap_sort((void**) arreglo, 10000, comparar_enteros);
    bool ok = true;
    int anterior = *arreglo[0];
    int actual;
    for(int i = 1; i < 10000; i++){
        actual = *arreglo[1];
        if (actual < anterior){
            ok = false;
            break;
        }
        anterior = actual;
    }
    destruir_vector(arreglo, 10000);
    print_test("Prueba heapsort volumen el arreglo esta ordenado", ok);
}

static void prueba_heap_volumen(){
    printf("Prueba heap volumen\n");
    heap_t *heap = heap_crear(comparar_enteros);
    size_t tam = 10000;
    bool encolado = true, desencolado = true;
    size_t arreglo[tam];
    for (size_t i = 0; i < tam; i++) {
        arreglo[i] = i;
        encolado = heap_encolar(heap, &arreglo[i]);
        if(!encolado) break;
    }
    print_test("Pruebas heap volumen encolar muchos elementos", encolado);
    if(encolado) {
        for (size_t i = 0; i < tam; i++) {
            desencolado = heap_desencolar(heap) == &arreglo[tam - i - 1] ? true : false;
            if (!desencolado) break;
        }
        print_test("Pruebas heap volumen desencolar muchos elementos", desencolado);
    }
    heap_destruir(heap, NULL);
}

static void prueba_heap_con_arreglo_volumen(){
    printf("Prueba heap con arreglo volumen\n");
    size_t tam = 10000;
    int* arreglo[tam];
    for (int i = 0; i < tam; i++){
        int *elem = malloc(sizeof(int));
        *elem = i;
        arreglo[i] = elem;
    }
    heap_t* heap = heap_crear_arr((void**) arreglo, tam, comparar_enteros);
    print_test("Prueba heap cantidad es 10000 ", heap_cantidad(heap) == tam);
    print_test("Prueba heap ver max es 9999 ", *(int *)heap_ver_max(heap) == 9999);
    heap_destruir(heap,free);
}


void pruebas_heap_estudiante(void){
    prueba_heap_crear_vacio();
    prueba_heap_algunos_elementos();
    prueba_heap_borrar_dinamico();
    prueba_heap_con_arreglo();
    prueba_heapsort();
    prueba_heapsort_volumen();
    prueba_heap_volumen();
    prueba_heap_con_arreglo_volumen();
}

#ifndef CORRECTOR
int main(){
    pruebas_heap_estudiante();
    return failure_count() > 0;
}
#endif
