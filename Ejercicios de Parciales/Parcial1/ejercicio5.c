//ejercicio tdas
#include <stddef.h>
#include <stdbool.h>

int* merge_colas(cola_t* cola1, cola_t* cola2){
    size_t tamanio = 20;
    int* arreglo =malloc(sizeof(int) * tamanio);
    if (arreglo == NULL){
        return NULL;
    }

    int num1;
    int num2;
    int contador = 0;
    while(cola_esta_vacia(cola1) == false || cola_esta_vacia(cola2) == false){
        num1 = cola_desencolar(cola1);
        num2 = cola_desencolar(cola2);
        while (num1 < num2 && arreglo[contador] != num1){
            arreglo[contador] = num1;
            if (cola_esta_vacia(cola1) == false){    
                num1 = cola_desencolar(cola1);
            }
            contador++;
            if (contador == tamanio){
                tamanio = tamanio * 2;
                arreglo = realloc(arreglo, sizeof(int) * tamanio);
                if (arreglo == NULL) return NULL;
            }
        }
        while(num2 < num1 && arreglo[contador] != num2){
            arreglo[contador] = num2;
            if (cola_esta_vacia(cola2) == false){
                num2 = cola_desencolar(cola2);
            }
            contador++;
            if (contador == tamanio){
                tamanio = tamanio * 2;
                arreglo = realloc(arreglo,sizeof(int) * tamanio);
                if (arreglo == NULL) return NULL;
            }
        }
        if (num1 == num2 && arreglo[contador] != num1){
            arreglo[contador] = num1;
            contador++;
            if (contador == tamanio){
                tamanio = tamanio * 2;
                arreglo = realloc(arreglo, sizeof(int) * tamanio);
                if (arreglo == NULL) return NULL;
            }
        }
    }
    invertir_arreglo(arreglo, contador);
    return arreglo;
}

/* Primeramente tengo que si o si recorrer las 2 colas con por todos sus elementos
lo cual es O(n + m)
Por otra parte cada vez que uso las funciones malloc y realloc son O(tamanio) que es el
tamanio del arreglo actual.
El resto de las funciones son todas O(1) salvo invertir_arreglo que es O(contador / 2) ya
que se cambia el primer elemento del arreglo por el ultimo y asi sucesivamente hasta llegar
a la mitad.
Por todo esto y considerando que pueden haber muchos elementos repetidos en las colas,
O(n + m) sera si o si > O(contador / 2) y posiblemente mayor a O(tamanio) dependiendo de la
cantidad de elementos repetidos.
Por lo tanto es O(n + m)
*/