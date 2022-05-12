#include <stdbool.h>
#include "lista.h"
#include "hash.c"


lista_t* obtener_selectivo(const hash_t* hash, int k, bool (*debe_devolver_dato)(const char* clave)){
    lista_t* lista = lista_crear();
    if (lista == NULL) return NULL;
    
    int cantidad = 0;

    for(int i = 0; i < hash->tam; i++){
        // En nuestra implementacion, hash tam indica el tamanio de la tabla
        // No la cantidad de elementos que puede tener el hash
        if (cantidad == k) break;

        lista_iter_t* iter =  lista_iter_crear(hash->tabla[i]);
        if (iter == NULL){
            lista_destruir(lista, NULL);
            return NULL;
        }

        while(!lista_iter_al_final(iter) && cantidad < k){
            campo_hash_t* campo = (campo_hash_t*) lista_iter_ver_actual(iter);
            if (debe_devolver_dato(campo->clave) == true){
                lista_insertar_ultimo(lista, campo->dato);
                cantidad++;
            }
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);
    }

    while(cantidad != k){
        lista_insertar_ultimo(lista, NULL);
        cantidad++;
    }

    return lista;
 }

 /* Tiempos:
    Las primitivas usadas tanto de la lista como del iterador de la lista son O(1).
    Por otra parte se itera el hash lista por lista y dentro de las listas elemento por elemento
    Hay dos opciones. La primera es que recorra una cierta cantidad de elementos del hash
    y consiga los k elementos que necesita antes de terminar de recorrer. En este caso seria 
    O(cant elementos recorridos)
    La segunda es que recorra todos los elementos de la lista y encuentre m elementos con m < k.
    En este caso una vez que deje de iterar en el hash va a rellenar la lista con k - m veces NULL
    En el peor caso de que ningun elemento del hash sirva para agregarse a la lista el tiempo termina
    en  O(n + k) ya que tiene que poner k - 0 veces el NULL en la lista y ya recorrio los n elementos del
    hash.
    Suponiendo que k es despreciable con respecto a n (es decir que el hash tiene muchisimos mas elementos
    de los que se esta pidiendo devolver) el tiempo seria O(n).
*/