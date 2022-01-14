#include "lista.h"
#include "testing.h"
#include "stdio.h"
#include <stdlib.h>

static void prueba_crear_lista(void){
    lista_t* lista = lista_crear();
    print_test("Prueba crear Lista", lista != NULL);
    lista_destruir(lista, NULL);
}

static void prueba_lista_vacia(void){
    lista_t* lista = lista_crear();
    print_test("Prueba lista Vacia", lista_esta_vacia(lista) == true);
    lista_destruir(lista, NULL);
}

static void prueba_lista_insertar_primero(void){
    lista_t* lista = lista_crear();
    int a = 1;
    lista_insertar_primero(lista, &a);
    print_test("Prueba insertar elemento al inicio", lista_ver_primero(lista) == &a);
    lista_destruir(lista, NULL);
}

static void prueba_lista_insertar_final(void){
    lista_t* lista = lista_crear();
    int a = 1;
    lista_insertar_ultimo(lista, &a);
    print_test("Prueba insertar elemento al final", lista_ver_ultimo(lista) == &a);
    lista_destruir(lista, NULL);
}

static void prueba_borrar_primero(void){
    lista_t* lista = lista_crear();
    int a = 1;
    lista_insertar_primero(lista, &a);
    print_test("Prueba Borrar primer elemento", lista_borrar_primero(lista) == &a);
    lista_destruir(lista, NULL);
}

static void prueba_volumen(void){
    lista_t* lista = lista_crear();
    int a = 1;
    int b = 2;
    bool resultado = true;

    for (int i = 0; i < 1000; i++){
        if (i % 2  == 0){
            lista_insertar_primero(lista, &a);
        } else {
            lista_insertar_primero(lista, &b);
        }
    }
    for(int i = 0; i < 1000; i++){
        void* dato = lista_borrar_primero(lista);
        if (i % 2 == 0 && dato != &b){
            resultado = false;
            break;
        } else if (i % 2 != 0 && dato != &a){
            resultado = false;
            break;
        }
    }
    print_test("Prueba Volumen", resultado == true);
    lista_destruir(lista, NULL);
}

static void prueba_insertar_NULL(void){
    lista_t* lista = lista_crear();
    lista_insertar_primero(lista, NULL);
    print_test("Prueba insertar primero NULL", lista_ver_primero(lista) == NULL);
    lista_destruir(lista, NULL);
}

static void prueba_destruir_datos(void){
    lista_t* lista = lista_crear();
    int* numero =malloc(sizeof(int));
    lista_insertar_primero(lista, numero);
    lista_destruir(lista, &free);
    print_test("Prueba destruir datos", true);
}

static void prueba_insertar_principio_iterador(void){
    lista_t* lista = lista_crear();
    lista_iter_t* iterador = lista_iter_crear(lista);
    int a = 1;
    lista_iter_insertar(iterador, &a);
    print_test("Prueba Insertar Iterador Principio", lista_ver_primero(lista) == &a);
    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

static void prueba_insertar_final_iterador(void){
    lista_t* lista = lista_crear();
    int a = 1;
    int b = 2;
    lista_insertar_primero(lista, &b);
    lista_iter_t* iterador = lista_iter_crear(lista);
    lista_iter_avanzar(iterador);
    lista_iter_insertar(iterador, &a);
    print_test("Prueba Insertar Iterador Final", lista_ver_ultimo(lista) == &a);
    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

static void prueba_insertar_medio_iterador(void){
    lista_t* lista = lista_crear();
    int a = 1;
    int b = 2;
    int c = 3;
    lista_insertar_primero(lista, &b);
    lista_insertar_primero(lista, &a);
    lista_iter_t* iterador = lista_iter_crear(lista);
    lista_iter_avanzar(iterador);
    lista_iter_insertar(iterador, &c);
    lista_borrar_primero(lista);
    print_test("Prueba Insertar Iterador Medio", lista_ver_primero(lista) == &c);
    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

static void prueba_insertar_medio(void){
    lista_t* lista = lista_crear();
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    lista_insertar_primero(lista, &b);
    lista_insertar_primero(lista, &a);
    lista_iter_t* iterador = lista_iter_crear(lista);
    lista_iter_avanzar(iterador);
    lista_iter_insertar(iterador, &c);
    lista_iter_insertar(iterador, &d);
    lista_borrar_primero(lista);
    lista_borrar_primero(lista);
    print_test("Prueba Insertar Varios Iterador Medio", lista_ver_primero(lista) == &c);
    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

static void prueba_borrar_iter_primero(void){
    lista_t* lista = lista_crear();
    int a = 1;
    lista_insertar_primero(lista, &a);
    lista_iter_t* iterador = lista_iter_crear(lista);
    lista_iter_borrar(iterador);
    print_test("Prueba borrar Iterador Primer elemento", lista_ver_primero(lista) == NULL);
    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

static void prueba_borrar_iter_ultimo(void){
    lista_t* lista = lista_crear();
    int a = 1;
    int b = 2;
    lista_insertar_primero(lista, &b);
    lista_insertar_primero(lista, &a);
    lista_iter_t* iterador = lista_iter_crear(lista);
    lista_iter_avanzar(iterador);
    lista_iter_borrar(iterador);
    print_test("Prueba borrar Ultimo Iterador", lista_ver_ultimo(lista) == &a);
    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

static void prueba_borrar_iter_medio(void){
    lista_t* lista = lista_crear();
    int a = 1;
    int b = 2;
    int c = 3;
    lista_insertar_primero(lista, &c);
    lista_insertar_primero(lista, &b);
    lista_insertar_primero(lista, &a);
    lista_iter_t* iterador = lista_iter_crear(lista);
    lista_iter_avanzar(iterador);
    lista_iter_borrar(iterador);
    lista_borrar_primero(lista);
    print_test("Prueba borrar medio Iterador", lista_ver_primero(lista) == &c);
    lista_iter_destruir(iterador);
    lista_destruir(lista, NULL);
}

bool sumatoria(void* elemento, void* extra){
    int numero = *(int*)elemento;
    *(int*)extra += numero;
    if (numero == 3){
        return false;
    }
    return true;
}

static void prueba_iterador_interno_sin_corte(void){
    lista_t* lista = lista_crear();
    int a = 1;
    int b = 2;
    int c = 4;
    lista_insertar_primero(lista, &c);
    lista_insertar_primero(lista, &b);
    lista_insertar_primero(lista, &a);
    int extra = 0;
    lista_iterar(lista, &sumatoria, &extra);
    print_test("Iterar Interno sin condicion de corte", extra == 7);
    lista_destruir(lista, NULL);
}

static void prueba_iterador_interno_con_corte(void){
    lista_t* lista = lista_crear();
    int a = 1;
    int b = 3;
    int c = 4;
    lista_insertar_primero(lista, &c);
    lista_insertar_primero(lista, &b);
    lista_insertar_primero(lista, &a);
    int extra = 0;
    lista_iterar(lista, &sumatoria, &extra);
    print_test("Iterar Interno con condicion de corte", extra == 4);
    lista_destruir(lista, NULL);
}

void pruebas_lista_estudiante(){
    prueba_crear_lista();
    prueba_lista_vacia();
    prueba_lista_insertar_primero();
    prueba_lista_insertar_final();
    prueba_borrar_primero();
    prueba_volumen();
    prueba_insertar_NULL();
    prueba_destruir_datos();
    prueba_insertar_principio_iterador();
    prueba_insertar_final_iterador();
    prueba_insertar_medio_iterador();
    prueba_insertar_medio();
    prueba_borrar_iter_primero();
    prueba_borrar_iter_ultimo();
    prueba_borrar_iter_medio();
    prueba_iterador_interno_con_corte();
    prueba_iterador_interno_sin_corte();
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif