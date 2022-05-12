#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

cambio_t* _encontrar_causante(cambio_t** cambios, size_t inicio, size_t fin, bool (*prueba)(cambio_t**, size_t)){
    size_t mitad = (inicio + fin) / 2;

    if (mitad == fin){
        if (!pruebas(cambios, mitad)) return cambios[mitad];
        return NULL; //no se encontro el error
    }

    if (prueba(cambios, mitad) && !prueba(cambios, mitad + 1)){
        return cambios[mitad + 1];
    }
    
    if (!prueba(cambios, mitad)){
        return _encontrar_causante(cambios, inicio, mitad, prueba);
    }
    return _encontrar_causante(cambios, mitad +1, fin, prueba);    
}

cambio_t* encontrar_causante(cambio_t** cambios, size_t n, bool (*prueba)(cambio_t**, size_t)){
    return _encontrar_causante(cambios, 0 , n - 1, prueba);
}


/*
La complejidad la voy a ver segun el teorema maestro.
B = 2 ya que divido al arreglo en 2, llamo para una de las mitades del arreglo
A = 1 ya que por cada vez que llamo a la funcion hago uno de los dos llamados. 
El resto de las operaciones es O(1). No obstante, la prueba corre en O(n) (consigna).
por lo que C = 1 para que n ** 1 = n.

Por ende como el logaritmo en base 2 de 1 es 0 y es menor que C = 1, la complejidad es O(n ** c) == O(n).

