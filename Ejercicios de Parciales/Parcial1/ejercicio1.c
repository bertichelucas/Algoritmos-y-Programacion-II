#include <stdio.h>
#include <stddef.h>


int cercano(int arreglo[], size_t inicio, size_t fin, int n){
    size_t mitad = (inicio + fin) / 2;
    if (mitad == fin){
        return arreglo[mitad];
    }
    if (arreglo[mitad] <= n && arreglo[mitad + 1] > n){
        if (n - arreglo[mitad] < arreglo[mitad + 1]- n){
            return arreglo[mitad];
        }
        return arreglo[mitad + 1];
    }
    if (arreglo[mitad] > n){
        return cercano(arreglo, inicio, mitad, n);
    }
    return cercano(arreglo, mitad + 1, fin, n);
}

int mas_cercano(int arreglo[], size_t largo, int n){
    return cercano(arreglo, 0, largo - 1, n);
}

/* Uso el teorema maestro para justificar su complejidad:
Primeramente B = 2 porque divido a la mitad el arreglo al realizar las llamadas recursivas
Luego A = 1 ya que si bien en el programa hay dos llamados recursivos, solo se ejecuta o el
primero o el segundo dependiendo de la comparacion.
Por otra parte todas las operaciones son 0(1) fuera de las llamadas recursivas. Por lo que 
C = 0 (de esta manera n ** c = 1)

Ya con los tres valores obtenidos hago la comparacion del logaritmo en base b de a con el C
me queda que log en base 2 de 1 = 0 = c
Como son iguales la complejidad temporal queda
O((n ** 0) log(n)) = O(n log (n))
*/