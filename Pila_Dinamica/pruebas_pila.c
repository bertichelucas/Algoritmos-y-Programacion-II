#include "pila.h"
#include "testing.h"
#include "stdio.h"

static void prueba_crear_destruir_pila(void){
    pila_t *pila = pila_crear();
    print_test("Se crea correctamente la pila", pila != NULL);
    pila_destruir(pila);
}

static void prueba_pila_vacia(void) {
    pila_t *pila = pila_crear();
    print_test("La pila esta vacia al crearse", pila_esta_vacia(pila));
    pila_destruir(pila);
}

static void prueba_apilar_desapilar(void){
    pila_t *pila = pila_crear();
    int a = 1;
    int b = 2;
    void* primero = &a;
    pila_apilar(pila, primero);
    print_test("Se apilo el 1", pila_ver_tope(pila) == primero);

    void* segundo = &b;
    pila_apilar(pila, segundo);
    print_test("Se apilo el 2", pila_ver_tope(pila) == segundo);

    print_test("Se desapilo el Ultimo elemento", pila_desapilar(pila) == segundo);

    print_test("Se mantiene el primer elemento", pila_ver_tope(pila) == primero);

    print_test("Se desapilo el Primer elemento", pila_desapilar(pila) == primero);

    print_test("Pila Vacia", pila_esta_vacia(pila));

    pila_destruir(pila);
} 

static void prueba_volumen(int cantidad){
    int a = 1;
    int b = 2;
    int counter = 0;
    pila_t *pila = pila_crear();
    for (int i = 0; i < cantidad; i++){
        if (i % 2  == 0){
            pila_apilar(pila, &a);
            if ( pila_ver_tope(pila) != &a){
                break;
            }
        } else {
            pila_apilar(pila, &b);
            if ( pila_ver_tope(pila) != &b){
                break;
            }
        }
        counter++;
    }
    print_test("Apilar Volumen", cantidad == counter);

    for (int i = 0; i < cantidad; i++){
        pila_desapilar(pila);
    }

    print_test("Desapilar Volumen", pila_esta_vacia(pila));

    pila_destruir(pila);
}

static void prueba_NULL(void){
    pila_t *pila = pila_crear();
    pila_apilar(pila,NULL);

    print_test("Se puede apilar el NULL", pila_ver_tope(pila) == NULL);
    pila_destruir(pila);
}

static void pruebas_desapilar_vertope_pila_vacia(void){
    pila_t *pila = pila_crear();

    print_test("No se puede desapilar Vacia", pila_desapilar(pila) == NULL);

    print_test("No se puede ver el tope de una pila vacia", pila_ver_tope(pila) == NULL);
    pila_destruir(pila);
}

static void prueba_apilar_desapilar_vacia(void){
    pila_t *pila = pila_crear();
    void *dato = NULL;
    pila_apilar(pila, dato);
    pila_desapilar(pila);

    print_test("Pila desapilada ya no se puede desapilar de nuevo", pila_desapilar(pila) == NULL);

    print_test("Pila desapilada no tiene tope", pila_ver_tope(pila) == NULL);
    pila_destruir(pila);
}

void pruebas_pila_estudiante() {
    prueba_crear_destruir_pila();
    prueba_apilar_desapilar();
    prueba_volumen(1000);
    prueba_NULL();
    pruebas_desapilar_vertope_pila_vacia();
    prueba_pila_vacia();
    prueba_apilar_desapilar_vacia();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
