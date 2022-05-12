#include "cola.h"
#include <stdbool.h>
#include <stdlib.h>

//Como la cola es una cola de enteros asumo que
// esta implementada de manera que a la hora de encolar
// se encolen enteros y no void*.

bool es_piramidal(cola_t* cola){
    
    bool piramidal = true;

    if(cola_esta_vacia(cola)) return piramidal;
    
    cola_t* cola_aux = cola_crear();
    if (cola_aux == NULL) return false;

    int actual = cola_desencolar(cola);
    cola_encolar(cola_aux, actual);
    
    int anterior;

    while(!cola_esta_vacia(cola)){
        anterior = actual;
        actual = cola_desencolar(cola);
        cola_encolar(cola_aux, actual);
        if (actual <= anterior) piramidal = false;
    }

    while(!cola_esta_vacia(cola_aux)){
        cola_encolar(cola, cola_desencolar(cola_aux));
    }

    cola_destruir(cola_aux, NULL);
    return piramidal;
}

/* El tiempo es O(n). Desencola todos los elemetnos de la cola y los va encolando en una cola auxiliar. O(n)
Luego el resto de las operaciones son O(1)
Por ultimo vuelve a desencolar la cola_aux hasta estar vacia y va encolando nuevamente en la cola original.
De esta manera se mantiene el estado de la cola original. Esto tambien es O(n). El total seria O(2n) que se puede
tomar como O(n).
*/