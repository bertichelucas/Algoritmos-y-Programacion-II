#include "strutil.h"
#include <stdlib.h>
#include "string.h"
#include <stdio.h>
//gcc strutil.c -Wall -Werror -o strutil
//gcc  strutil.c -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o strutil

char *substr(const char *str, size_t n){
    char* cadena = strndup(str, n);
    return cadena;
}


char **split(const char *str, char sep){
    size_t letras = strlen(str);
    size_t contador = 0;
    for (int i = 0; i < letras; i++){
        if (str[i] == sep) contador++;
    }
    char **strv = malloc(sizeof(char*) * (contador + 2));
    if (strv == NULL){
        return NULL;
    }

    size_t pos_inicial = 0;
    size_t pos_arreglo = 0;

    if (letras == 0){
        strv[pos_arreglo] = strndup("", 0);
        pos_arreglo++;
        strv[pos_arreglo] = NULL;
        return strv;
    }

    for (size_t pos_actual = 0; pos_actual <= letras; pos_actual++){
        if (pos_actual == letras){
            strv[pos_arreglo] = strndup(&str[pos_inicial], pos_actual - pos_inicial);
            pos_arreglo++;
        }
        if (str[pos_actual] == sep && sep != '\0'){
            strv[pos_arreglo] = strndup(&str[pos_inicial], pos_actual - pos_inicial);
            pos_arreglo++;
            pos_inicial = pos_actual + 1;
        }
    }
    strv[pos_arreglo] = NULL;
    return strv;
}

char *join(char **strv, char sep){
    size_t pos_vector = 0;
    size_t len = 1;
    while(strv[pos_vector] != NULL){
        if(pos_vector != 0) len++;
        len += strlen(strv[pos_vector]);
        pos_vector++;
    }

    char* resultado = malloc(sizeof(char) * (len));
    if (resultado == NULL) return NULL;
    
    pos_vector = 0;
    int pos = 0;
    size_t letras = 0;
    while(strv[pos_vector] != NULL){
        letras = strlen(strv[pos_vector]);
        for(int i = 0; i < letras; i++){
            resultado[pos] = strv[pos_vector][i];
            pos++;
        }
        if (pos < len - 1 && sep != '\0'){
            resultado[pos] = sep;
            pos++;
        }
        pos_vector++;
    }
    resultado[pos] = '\0';
    return resultado;
}

void free_strv(char *strv[]){
    int posicion = 0;
    while(strv[posicion] != NULL){
        free(strv[posicion]);
        posicion++;
    }
    free(strv);
}


