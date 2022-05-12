#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hash.h"
#include "strutil.h"

#define TAM_USUARIO 16
#define CANT_CARACTERES 126



typedef struct {
    char *usuario;
    size_t tags;
} usuarios_tt;

// Puntero a funcion para utilizar en counting sort.
typedef size_t (*obtener_valor_ord_t)(const usuarios_tt usuario, void *extra);

//Wrapper para destruir un hash de tags.
void destruir_tags(void *hash_tags);

//Recibe una linea y un hash de usuarios. Procesa el usuario y
//guarda los nuevos tags (no repetidos).
//Si falla devuelve false.
bool procesar_usuario(char* linea, hash_t* usuarios);

//Recibe un vector de usuarios y la cantidad de usuarios en el vector
//y lo destruye.
void vector_usuarios_destruir(usuarios_tt* vec_usuarios, size_t n);

//Recibe un diccionario de usuarios y devuelve un vector con todos los usuarios
//Y la cantidad de tags para cada uno. Guarda en max_tags la maxima cantidad de
//tags entre todos los usuarios.
//Si falla devuelve NULL
usuarios_tt *obtener_usuarios(hash_t *dic_usuarios, size_t* max_tags);

//Ordenamiento de counting. Recibe una funcion que devuelve el valor a utilizar en el ordenamiento.
//Recibe extra, para uso de la funcion obtener_valor.
//En caso contrario, pos corresponde a la posicion del nombre de usuario
//por la que se va a ordenar. Devuelve false en caso de error.
bool counting_sort(usuarios_tt** vec_usuarios, size_t n, size_t max, obtener_valor_ord_t obtener_valor, void* extra);

//Ordena el vector de usuarios. Devuelve false en caso de error.
bool ordenar(usuarios_tt** vec_usuarios, size_t n, size_t max_tags);

//Funcion para utilizar en ordenar con counting sort. Recibe un usuario y un extra,
//donde extra va a representar la posicion de la cadena por la cual se esta ordenando.
//Devuelve el valor ASCII del caracter.
size_t valor_cadena(const usuarios_tt usuario, void *extra);

//Funcion para utilizar en ordenar con counting sort. Recibe un usuario y un extra,
//donde extra no va a representar nada.
//Devuelve la cantidad de tags del usuario.
size_t valor_tag(const usuarios_tt usuario, void *extra);

//Imprime todos los usuarios y sus cantidades de tags.
void imprimir(usuarios_tt *usuarios, size_t n);

int main(int argc, char* argv[]){
    if (argc != 2) return -1;
    char *file = argv[1];
    FILE* tweets = fopen(file, "r");
    if (tweets == NULL) return -1; 

    char *linea = NULL;
    size_t tam;
    
    hash_t *dic_usuarios = hash_crear(destruir_tags);
    if (dic_usuarios == NULL){
        fclose(tweets);
        return -1;
    }

    while (getline(&linea, &tam, tweets) != EOF) {
        if (!procesar_usuario(linea, dic_usuarios)){
            hash_destruir(dic_usuarios);
            free(linea);
            fclose(tweets);
            return -1;
        }
    }
    
    fclose(tweets);
    free(linea);

    size_t max_tags;
    size_t cant_usuarios = hash_cantidad(dic_usuarios);
    usuarios_tt * vec_usuarios = obtener_usuarios(dic_usuarios, &max_tags);
    hash_destruir(dic_usuarios);
    if (vec_usuarios == NULL) return -1;

    if (!ordenar(&vec_usuarios, cant_usuarios, max_tags)) {
        vector_usuarios_destruir(vec_usuarios, cant_usuarios);
        return -1;
    }

    imprimir(vec_usuarios, cant_usuarios);
    vector_usuarios_destruir(vec_usuarios, cant_usuarios);
    
    return 0;
}

void destruir_tags(void *hash_tags) {
    hash_destruir((hash_t*)hash_tags);
}

bool procesar_usuario(char* linea, hash_t* usuarios){
    char **tweet = split(linea, ',');
    if (tweet == NULL) return false;
    char *usuario = tweet[0];
    hash_t* tts = NULL;
    if (!hash_pertenece(usuarios, usuario)){
        tts = hash_crear(NULL);
        if (tts == NULL){
            free_strv(tweet);
            return false;
        }
        if (!hash_guardar(usuarios, usuario, tts)) {
            hash_destruir(tts);
            free_strv(tweet);
            return false;
        }
    }
    else tts = (hash_t*)hash_obtener(usuarios, usuario);

    for (size_t i = 1; tweet[i] != NULL; i++) {
        if (!hash_guardar(tts, tweet[i], NULL)){
            free_strv(tweet);
            return false;
        }
    }
    free_strv(tweet);
    return true;
}

void vector_usuarios_destruir(usuarios_tt* vec_usuarios, size_t n){
    for (size_t i = 0; i < n; i++) free(vec_usuarios[i].usuario);
    free(vec_usuarios);
}

usuarios_tt *obtener_usuarios(hash_t *dic_usuarios, size_t *max_tags){
    *max_tags = 0;
    usuarios_tt* vec_usuarios = malloc(sizeof(usuarios_tt) * hash_cantidad(dic_usuarios));
    if (vec_usuarios == NULL) return NULL;
    
    hash_iter_t *iter = hash_iter_crear(dic_usuarios);
    if (iter == NULL){
        free(vec_usuarios);
        return NULL;
    }

    size_t i = 0;
    while (!hash_iter_al_final(iter)){
        char *usuario = calloc(sizeof(char), TAM_USUARIO);
        if (usuario == NULL){
            vector_usuarios_destruir(vec_usuarios, i);
            return NULL;
        }
        const char* actual = hash_iter_ver_actual(iter); 
        strcpy(usuario, actual); 
        hash_t *tags = (hash_t*)hash_obtener(dic_usuarios, actual);
        vec_usuarios[i].usuario = usuario;
        vec_usuarios[i].tags = hash_cantidad(tags);
        if (vec_usuarios[i].tags > *max_tags) *max_tags = vec_usuarios[i].tags;
        i++;
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    return vec_usuarios;
}

bool counting_sort(usuarios_tt** vec_usuarios, size_t n, size_t max, obtener_valor_ord_t obtener_valor, void* extra) {
    usuarios_tt* actual = *vec_usuarios;
    size_t contador[max+1];
    for (size_t i = 0; i < (max+1); i++) contador[i] = 0;

    for (size_t i = 0; i < n; i++) {
        size_t num = obtener_valor(actual[i], extra);
        contador[num]++;
    }

    size_t sum_acum[max+1];
    sum_acum[0] = 0;
    for (size_t i = 1; i < (max+1); i++){
        size_t cant = contador[i-1];
        sum_acum[i] = cant + sum_acum[i-1];
    }

    usuarios_tt * ordenado = malloc(sizeof(usuarios_tt) * n);
    if (ordenado == NULL) return false;
    for (size_t i = 0; i < n; i++){
        size_t valor = obtener_valor(actual[i], extra);

        size_t pos_ordenado = sum_acum[valor];
        sum_acum[valor]++;
        ordenado[pos_ordenado].usuario = actual[i].usuario;
        ordenado[pos_ordenado].tags = actual[i].tags;
    }
    free(actual);
    *vec_usuarios = ordenado;
    //Mantenemos actualizado el vector que nos pasa.
    return true;
}

size_t valor_cadena(const usuarios_tt usuario, void *extra){
    size_t pos = (size_t)extra;
    return usuario.usuario[pos];
}

size_t valor_tag(const usuarios_tt usuario, void *extra){
    return usuario.tags;
}

bool ordenar(usuarios_tt** vec_usuarios, size_t n, size_t max_tags) {
    // Orden alfabetico
    for (int i = TAM_USUARIO; i > 0; i--) {
        size_t pos = i-1;
        if (!counting_sort(vec_usuarios, n, CANT_CARACTERES, valor_cadena, (void*)pos)) return false;
    }
    // Orden por cantidad de tags
    return counting_sort(vec_usuarios, n, max_tags, valor_tag, NULL);
}

void imprimir(usuarios_tt *usuarios, size_t n){
    size_t cant_tags = 0;
    for (size_t i = 0; i < n; i++) {
        if (cant_tags == usuarios[i].tags) {
            printf(", %s", usuarios[i].usuario);
        }
        else {
            if (cant_tags != 0) putchar('\n');
            printf("%zd: %s", usuarios[i].tags, usuarios[i].usuario);
            cant_tags = usuarios[i].tags;
        }
    }
    putchar('\n');
}
