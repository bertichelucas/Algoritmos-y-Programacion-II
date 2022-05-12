#include <stdbool.h>
#include <stddef.h>

lista_t* slice(lista_t* lista, size_t inicio, size_t fin){

    int contador = 0;
    lista_t* resultado = lista_crear();
    if (fin <= inicio){
        return resultado;
    }
    lista_iter_t* iterador = lista_iter_crear(lista);

    while(contador != fin){
        if (contador >= inicio){
            int* dato = (int*)lista_iter_ver_actual(iterador);
            lista_insertar_ultimo(resultado, dato);
        }
        if(lista_iter_avanzar(iterador) == false){
            break;
        }
        contador++;
    }
    lista_iter_destruir(iterador);
    return resultado;
}

/*El algoritmo es O(n) siendo n la cantidad de elementos a iterar ya sea
que se necesite iterar toda la lista o n elementos de la lista hasta llegar al fin
El resto de las operaciones realizadas son 0(1) tanto las comparaciones como 
el uso de las primitivas de la lista y el uso de las primitivas del iterador externo.
*/
