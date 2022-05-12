#include <stdlib.h>
#include <stdbool.h>

bool tiene_hijos(const ab_t* ab){
    if (ab == NULL) return false;
    if (ab->izq != NULL || ab->der != NULL) return true;
    return false;
}

size_t ab_sin_nietos(const ab_t* ab){
    if (ab == NULL) return 0;

    size_t resultado = 0;
    
    if(!tiene_hijos(ab->izq) && !tiene_hijos(ab->der)) resultado++;
    
    resultado += ab_sin_nietos(ab->izq);
    resultado += ab_sin_nietos(ab->der);
    return resultado;
}

//Todas las operaciones son O(1)
//En cuanto a los llamados recursivos, es O(n) ya que yo tengo que si o si checkear
//Para cada nodo si tiene o no nietos. Es decir, si hay n nodos checkeo n veces que tenga nietos
