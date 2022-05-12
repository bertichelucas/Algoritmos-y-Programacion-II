#include "heap.h"

int comparar(int a, int b){
    return a - b;
}



int obtener_ganador(int* cartas_1, int* cartas_2, size_t n, size_t k){
    size_t score1 = 0;
    size_t score2 = 0;
    size_t rondas = 0;
    heap_t* heap_1 = heap_crear_arr(cartas_1, n, comparar);
    heap_t* heap_2 = heap_crear_arr(cartas_2, n, comparar);

    while (rondas != k) {
        int a = heap_desencolar(heap_1);
        int b = heap_desencolar(heap_2);
        // En este caso cada vez que se desencole tendra que ser el mayor valor
        // Es decir, sera un heap de maximos.
        if (comparar(a, b) > 0){
            score1++;
        } else if (comparar(a, b) < 0){
            score2++;
        }
        rondas++;
    }        
    
    if (comparar(score1, score2) > 0){
        return 1;
    } else if (comparar(score1, score2) < 0){
        return -1;
    }
    return 0;
}

//En cuanto a la complejidad es O(n) el crear heap con arreglo ya que hace heapify del arreglo
//que se le pasa y heapify es O(n) mientras que el resto de las operaciones es O(1).
//Por otra parte se desencola k veces. El coste de desencolar es O( log n) por lo que la complejidad
//Termina siendo k * log n.
//Por lo tanto la complejidad total termina siendo O(n + k log n).