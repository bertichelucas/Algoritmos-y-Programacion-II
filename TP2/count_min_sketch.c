#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "count_min_sketch.h"
#define CANT_TABLAS 4
#define TAM_TABLAS 1000

typedef size_t (*fun_hash_t)(const char *);

struct count_min_sketch{
    size_t **tablas_contadoras;
    fun_hash_t hashes[CANT_TABLAS];
};

size_t jenkins_one_at_a_time_hash_v2(const char* key) {
    size_t length = strlen(key);
    size_t i = 0;
    size_t hash = 0;
    while (i != length) {
        hash += (key[i++]);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

// https://en.wikipedia.org/wiki/PJW_hash_function
size_t elf_hash(const char *s) {
    size_t h = 0, high;
    while (*s) {
        h = (h << 4) + *s++;
        if ((high = (h & 0xF0000000)))
            h ^= high >> 24;
        h &= ~high;
    }
    return h;
}

size_t djb2_hash(const char *str){
  size_t hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

size_t sdbm(const char* s){
        unsigned long hash = 0;
        int c;
        while ((c = *s++))
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;
    }

void destruir_tablas(size_t **tablas, size_t n) {
    for (size_t i = 0; i < n; i++) {
        free(tablas[i]);
    }
    free(tablas);
}

count_min_sketch_t* count_min_sketch_crear() {
    count_min_sketch_t *cms = malloc(sizeof(count_min_sketch_t));
    if (cms == NULL) return NULL;
    cms->tablas_contadoras = malloc(sizeof(size_t**) * CANT_TABLAS);
    if (cms->tablas_contadoras == NULL) {
        free(cms);
        return NULL;
    }
    for (size_t i = 0; i < CANT_TABLAS; i++) {
        cms->tablas_contadoras[i] = calloc(TAM_TABLAS, sizeof(size_t*));
        if (cms->tablas_contadoras[i] == NULL) {
            destruir_tablas(cms->tablas_contadoras, i);
            free(cms);
            return NULL;
        }
    }
    cms->hashes[0] = jenkins_one_at_a_time_hash_v2;
    cms->hashes[1] = elf_hash;
    cms->hashes[2] = djb2_hash;
    cms->hashes[3] = sdbm;

    return cms;
}

void count_min_sketch_destruir(count_min_sketch_t*cms) {
    destruir_tablas(cms->tablas_contadoras, CANT_TABLAS);
    free(cms);
}

void count_min_sketch_incrementar(count_min_sketch_t* cms, const char *clave){
    size_t pos;
    for(size_t i = 0; i < CANT_TABLAS ; i++){
        pos = cms->hashes[i](clave) % TAM_TABLAS;
        cms->tablas_contadoras[i][pos]++;
    }
}

size_t count_min_sketch_obtener(const count_min_sketch_t* cms, const char*clave){
    size_t pos = cms->hashes[0](clave) % TAM_TABLAS;
    size_t min_contador = cms->tablas_contadoras[0][pos]; 

    for(size_t i = 1; i < CANT_TABLAS ; i++){
        pos = cms->hashes[i](clave) % TAM_TABLAS;
        size_t actual = cms->tablas_contadoras[i][pos];
        if (min_contador > actual) min_contador = actual;
    }
    return min_contador;
}
