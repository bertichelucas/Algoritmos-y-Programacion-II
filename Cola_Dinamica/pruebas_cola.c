#include "cola.h"
#include "testing.h"
#include "stdio.h"
#include <stdlib.h>

static void prueba_crear_cola(void){
    cola_t * cola = cola_crear();
    print_test("Prueba crear cola", cola != NULL);
    cola_destruir(cola, NULL);
}

static void prueba_cola_vacia(void){
    cola_t * cola = cola_crear();
    print_test("Prueba cola vacia", cola_esta_vacia(cola) == true);
    cola_destruir(cola, NULL);
}

static void prueba_encolar_unitario(void){
    cola_t* cola = cola_crear();
    int a = 1;
    void* dato = &a;
    cola_encolar(cola, dato);
    print_test("Prueba Encolar unico dato", cola_ver_primero(cola) == dato);
    cola_destruir(cola, NULL);
}

static void prueba_desencolar_unitario(void){
    cola_t* cola = cola_crear();
    int a = 1;
    cola_encolar(cola, &a);
    print_test("Prueba Desencolar unico dato", &a == cola_desencolar(cola));
    cola_destruir(cola, NULL);
}

static void prueba_desencolar_vacio(void){
    cola_t* cola = cola_crear();
    print_test("Prueba desencolar vacio", NULL == cola_desencolar(cola));
    cola_destruir(cola, NULL);
}

static void prueba_volumen(void){
    cola_t* cola = cola_crear();
    int a = 1;
    int b = 2;
    bool resultado = true;

    for (int i = 0; i < 1000; i++){
        if (i % 2  == 0){
            cola_encolar(cola, &a);
        } else {
            cola_encolar(cola, &b);
        }
    }
    for(int i = 0; i < 1000; i++){
        void* dato = cola_desencolar(cola);
        if (i % 2 == 0 && dato != &a){
            resultado = false;
            break;
        } else if (i % 2 != 0 && dato != &b){
            resultado = false;
            break;
        }
    }
    print_test("Prueba Volumen", resultado == true);
    cola_destruir(cola, NULL);
}

static void prueba_encolar_NULL(void){
    cola_t* cola = cola_crear();
    cola_encolar(cola, NULL);
    print_test("Prueba encolar NULL", cola_ver_primero(cola) == NULL);
    cola_destruir(cola, NULL);
}

static void prueba_encolar_desencolar_encolar(void){
    cola_t* cola = cola_crear();
    int a = 1;
    int b = 2;
    cola_encolar(cola, &a);
    cola_encolar(cola, &b);
    cola_desencolar(cola);
    cola_desencolar(cola);
    cola_encolar(cola, &a);
    print_test("Prueba Encolar Desencolar Encolar", cola_ver_primero(cola) == &a);
    cola_destruir(cola, NULL);
}

static void prueba_destruir_datos(void){
    cola_t* cola = cola_crear();
    void* numero = malloc(sizeof(int));
    cola_encolar(cola, numero);
    cola_destruir(cola, &free);
    print_test("Prueba Destruir Datos", true);
}



void pruebas_cola_estudiante(){
    prueba_crear_cola();
    prueba_cola_vacia();
    prueba_encolar_unitario();
    prueba_desencolar_unitario();
    prueba_desencolar_vacio();
    prueba_volumen();
    prueba_encolar_NULL();
    prueba_encolar_desencolar_encolar();
    prueba_destruir_datos();
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif