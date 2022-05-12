#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "hash.h"
#include "heap.h"
#include "count_min_sketch.h"
#include "strutil.h"

typedef struct tag {
    const char* tag_str;
    size_t apariciones;
} tag_tt;

// Recibe una linea que representa un tweet y procesa los tags incrementando las 
// ocurrencias de cada uno y guardandolos en un hash.
// Devuelve false en caso de error.
bool procesar_tweet(char* linea, count_min_sketch_t* ocurrencias, hash_t* tts);

// Crea un tag que contiene su cadena y la cantidad de apariciones aproximada por cms
// Devuelve NULL en caso de error.
tag_tt* tag_crear(const char* tag_str, size_t apariciones);

// Recibe un vector de tags de n elementos y lo destruye.
void vector_tags_destruir(tag_tt** tags, size_t n);

// Convierte las claves del hash en un vector de tags. El tamaño del vector es la 
// cantidad de elementos en el hash.
// Devuelve NULL en caso de error
tag_tt** obtener_tags_hash(const hash_t* tts, const count_min_sketch_t* ocurrencias);

// Compara dos tags segun sus apariciones y en caso de ser iguales
// Compara alfabeticamente.
int cmp_tags(const void* a, const void* b);

// Imprime los k tts con mayor cantidad de ocurrencias contenidos en el hash
// Devuelve false en caso de error.
bool imprimir_tts(const count_min_sketch_t* ocurrencias, const hash_t* tts, size_t k);

int main(int argc, char* argv[]){
    if (argc != 3) return -1;
    size_t n = atoll(argv[1]);
    size_t k = atoll(argv[2]);
    
    char* linea = NULL;
    size_t tam;
    size_t contador = 0;
    size_t ciclo = 1;
    hash_t* tts = hash_crear(NULL);
    if (tts == NULL) return -1;

    count_min_sketch_t* ocurrencias = count_min_sketch_crear();
    if (ocurrencias == NULL){
        hash_destruir(tts);
        return -1;
    } 

    while(getline(&linea, &tam, stdin) != EOF){

        procesar_tweet(linea, ocurrencias, tts);
        contador++;

        if (contador == n){
            // Fin de ciclo de n lineas
            // Se imprimen los k tts con mas ocurrencias.
            // Se reinicia el contador y se destruye el hash.
            printf("--- %zd\n", ciclo++);
            contador = 0;
            if (!imprimir_tts(ocurrencias, tts, k)) break;
            hash_destruir(tts);
            // Inicia un nuevo ciclo por lo que se 
            // crea un nuevo hash que contendra las claves.
            tts = hash_crear(NULL);
            if (tts == NULL) break;
        }
    }

    if (contador != 0) {
        // Al llegar al final del archivo imprime
        // los tts restantes si es que los hay.
        printf("--- %zd\n", ciclo);
        imprimir_tts(ocurrencias, tts, k);
    }

    if (tts != NULL) hash_destruir(tts);
    count_min_sketch_destruir(ocurrencias);
    free(linea);
    return 0;
}

bool procesar_tweet(char* linea, count_min_sketch_t* ocurrencias, hash_t* tts){
    char** tweet = split(linea, ',');
    if (tweet == NULL) return false;

    for (size_t i = 1; tweet[i] != NULL; i++){
        char* tag = tweet[i];
        count_min_sketch_incrementar(ocurrencias, tag);
        if (!hash_pertenece(tts, tag)){
            if (!hash_guardar(tts, tag, NULL)){
                free_strv(tweet);
                return false;
            }
        }
    }

    free_strv(tweet);
    return true;
}

tag_tt* tag_crear(const char* tag_str, size_t apariciones){
    tag_tt* tag = malloc(sizeof(tag_tt));
    if (tag == NULL) return NULL;

    tag->tag_str = tag_str;
    tag->apariciones = apariciones;
    return tag;
}

void vector_tags_destruir(tag_tt** tags, size_t n){
    for (size_t i = 0; i < n; i++){
        free(tags[i]);
    }
    free(tags);
}
    
tag_tt** obtener_tags_hash(const hash_t* tts, const count_min_sketch_t* ocurrencias){
    
    tag_tt** tags = malloc(sizeof(tag_tt*) * hash_cantidad(tts));
    if (tags == NULL) return NULL;
    hash_iter_t *iter = hash_iter_crear(tts);
    if (iter == NULL){
        free(tags);
        return NULL;
    }

    size_t i = 0;
    while (!hash_iter_al_final(iter)){
        const char* actual = hash_iter_ver_actual(iter);
        tags[i] = tag_crear(actual, count_min_sketch_obtener(ocurrencias, actual));
        if (tags[i] == NULL){
            vector_tags_destruir(tags, i);
            hash_iter_destruir(iter);
            return NULL;
        }
        i++;
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    return tags;
}

int cmp_tags(const void* a, const void* b){
    tag_tt* tag_a = (tag_tt*) a;
    tag_tt* tag_b = (tag_tt*) b;
    if (tag_a->apariciones == tag_b->apariciones) return strcmp(tag_b->tag_str, tag_a->tag_str);
    return (int) tag_a->apariciones - (int) tag_b->apariciones;
}

bool imprimir_tts(const count_min_sketch_t* ocurrencias, const hash_t* tts, size_t k){

    tag_tt** tags = obtener_tags_hash(tts, ocurrencias);
    if (tags == NULL) return false;
    
    
    heap_t* heap = heap_crear_arr((void**) tags, hash_cantidad(tts), cmp_tags);
    if (heap == NULL){
        vector_tags_destruir(tags, hash_cantidad(tts));
        return false;
    }
    
    for (size_t i = 0; i < k && !heap_esta_vacio(heap); i++){
        tag_tt* actual =  (tag_tt*) heap_desencolar(heap);
        printf("%zd %s\n", actual->apariciones, actual->tag_str);
    }

    heap_destruir(heap, NULL);
    vector_tags_destruir(tags, hash_cantidad(tts));
    return true;
}
