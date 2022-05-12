#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strutil.h"

char *substr(const char *str, size_t n){
    return strndup(str, n);
}

// Funcion que cuenta la cantidad de subcadenas a separar
size_t contar_subcadenas(const char *str, char sep){
     size_t cantidad = 2; //Inicia en 2 - uno para el NULL y otro para la primera subcadena
    //Recorro para ver cuantas subcadenas hay
    for (size_t i = 0; str[i]; i++) {
        if (str[i] == sep) {
            cantidad++;
        }
    }
    return cantidad;
}

char **split(const char *str, char sep){
    size_t cantidad = contar_subcadenas(str, sep);

    char **vec = calloc(cantidad, sizeof(char*));
    if (vec == NULL) {
        return NULL;
    }

    size_t pos_vec = 0, start = 0, orig_lenght = strlen(str) + 1;
    // Recorro toda la cadena y si me encuentro con un separador, copio
    // desde el anterior separador(o inicio de cadena), hasta el actual separador.
    for (size_t i = 0; i < orig_lenght; i++) {
        if (str[i] == sep || str[i] == '\0') {
            size_t tam = i - start;
            if (str[i] == '\0') tam--;
            vec[pos_vec] = substr(str + start, (tam));
            if (vec[pos_vec] == NULL) {
                free_strv(vec);
                return NULL;
            }

            pos_vec++;
            start = i + 1;
        }
    }
    return vec;
}

// Funcion que calcula el largo de la cadena a unir.
size_t calcular_largo(char **strv){
    size_t total_lenght = 0;
    // Busco el largo de la cadena total
    for (size_t i = 0; strv[i] != NULL; i++) {
        total_lenght += (strlen(strv[i]) + 1);
    }
    // Este chequeo es por el caso de vector vacio
    return total_lenght == 0 ? 1 : total_lenght;
}

char *join(char **strv, char sep){
    size_t total_lenght = calcular_largo(strv);

    char * joined = malloc(sizeof(char) * total_lenght);
    if (joined == NULL) {
        return NULL;
    }
    
    char * end = joined;
    for (size_t i = 0; strv[i] != NULL; i++) {
        end = stpcpy(end, strv[i]);
        if (sep != '\0') {
            *end = sep;
            end++;
        }
    }

    joined[total_lenght-1] = '\0';
    return joined;
}

void free_strv(char *strv[]){
    size_t i = 0;
    while(strv[i] != NULL) {
        free(strv[i++]);
    }
    free(strv);
}
