#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "testing.h"
#include "count_min_sketch.h"

static void pruebas_cms_vacio() {
    count_min_sketch_t *cms = count_min_sketch_crear();

    print_test("Obtener 'test' es 0", count_min_sketch_obtener(cms, "test") == 0);

    count_min_sketch_destruir(cms);
}


static void algunos_valores(){
    char *a = "hola", *b = "casa", *c = "gato", *d = "algoritmos";
    count_min_sketch_t *cms = count_min_sketch_crear();

    count_min_sketch_incrementar(cms, a);
    count_min_sketch_incrementar(cms, b);
    count_min_sketch_incrementar(cms, c);
    count_min_sketch_incrementar(cms, d);

    print_test("Obtener a  es 1", count_min_sketch_obtener(cms, a) == 1);
    print_test("Obtener b  es 1", count_min_sketch_obtener(cms, b) == 1);
    print_test("Obtener c  es 1", count_min_sketch_obtener(cms, c) == 1);
    print_test("Obtener d  es 1", count_min_sketch_obtener(cms, d) == 1);

    for(size_t i = 0; i < 99; i++) count_min_sketch_incrementar(cms, a);
    print_test("Obtener a  es 100", count_min_sketch_obtener(cms, a) == 100);
    print_test("Obtener b  es 1", count_min_sketch_obtener(cms, b) == 1);
    print_test("Obtener c  es 1", count_min_sketch_obtener(cms, c) == 1);
    print_test("Obtener d  es 1", count_min_sketch_obtener(cms, d) == 1);

    for(size_t i = 0; i < 99; i++){
        count_min_sketch_incrementar(cms, b);
        count_min_sketch_incrementar(cms, c);
        count_min_sketch_incrementar(cms, d);
    }

    print_test("Obtener a  es 100", count_min_sketch_obtener(cms, a) == 100);
    print_test("Obtener b  es 100", count_min_sketch_obtener(cms, b) == 100);
    print_test("Obtener c  es 100", count_min_sketch_obtener(cms, c) == 100);
    print_test("Obtener d  es 100", count_min_sketch_obtener(cms, d) == 100);


    count_min_sketch_destruir(cms);

}

size_t aleatorio_en_rango(size_t minimo, size_t maximo) {
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

void cadena_aleatoria(size_t longitud, char *destino) {
    char muestra[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size_t len = strlen(muestra);
    for (size_t x = 0; x < longitud; x++) {
        size_t indiceAleatorio = aleatorio_en_rango(0, len - 1);
        destino[x] = muestra[indiceAleatorio];
    }
}


static void volumen(){
    count_min_sketch_t *cms = count_min_sketch_crear();
    srand(getpid());

    const size_t largo_clave = 10, volumen = 500;
    char (*claves)[largo_clave] = calloc(volumen * largo_clave, sizeof(char));
    for (size_t i = 0; i < volumen; i++){
        cadena_aleatoria(largo_clave - 1, claves[i]);
        count_min_sketch_incrementar(cms, claves[i]);
    }
    size_t diferido = 1;
    for (size_t i = 0; i < volumen; i++) {
        if (count_min_sketch_obtener(cms, claves[i]) != 1) {
            diferido = count_min_sketch_obtener(cms, claves[i]);
            break;
        }
    }
    print_test("Prueba volumen, todas las claves estan en 1", diferido == 1);
    if (diferido != 1) {
        printf("obtenido: %zd, esperado: 1\n", diferido);
    } 
    free(claves);
    count_min_sketch_destruir(cms);
}


int main(){
    pruebas_cms_vacio();
    algunos_valores();
    volumen();
    return 0;
}