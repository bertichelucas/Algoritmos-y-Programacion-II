#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc_helper.h"
#include <string.h>
#include <ctype.h>
#include "infix.h"

void destruir_arreglo_infix(char** arreglo){
    size_t i = 0;
    while (arreglo[i] != NULL){
        free(arreglo[i]);
        i++;
    }
    free(arreglo);
}

void calc_infix_a_polaca(){
    char* lin = NULL;
    size_t tam = 0;
    cola_t* cola = cola_crear();
    if (cola == NULL) return;
    while(getline(&lin, &tam, stdin) != EOF){
        if (strcmp(lin, "\n") == 0) break;
        char** arreglo = infix_split(lin);
        convertir_notacion(arreglo, cola);
        imprimir_notacion(cola);
        destruir_arreglo_infix(arreglo);
    }
    free(lin);
    cola_destruir(cola, NULL);
}

bool convertir_notacion(char** arreglo, cola_t* cola){
    pila_t* pila = pila_crear();
    if (pila == NULL) return false;
    struct calc_token* destino = malloc(sizeof(struct calc_token));
    if (destino == NULL)return false;
    
    size_t i = 0;
    while(arreglo[i] != NULL){
        calc_parse(arreglo[i], destino);
        if (destino->type == TOK_NUM){
            cola_encolar(cola, arreglo[i]);
        } else if (destino->type == TOK_OPER){
            while(calcular_precedencia(pila, destino) == true){
                cola_encolar(cola, pila_desapilar(pila));
            }
            pila_apilar(pila, arreglo[i]);
        } else if (destino->type == TOK_LPAREN){
            pila_apilar(pila, arreglo[i]);
        } else if (destino->type == TOK_RPAREN){
            while(strcmp("(", (char*) pila_ver_tope(pila)) != 0){
                cola_encolar(cola, pila_desapilar(pila));
            }
            pila_desapilar(pila);
        }
        i++;
    }
    while(pila_esta_vacia(pila) == false){
        cola_encolar(cola, pila_desapilar(pila));
    }
    pila_destruir(pila);
    free(destino);
    return true;
}

bool calcular_precedencia(pila_t* pila, struct calc_token* destino){
    if (pila_esta_vacia(pila) == true) return false;
    struct calc_token* destino2 = malloc(sizeof(struct calc_token));
    if (destino == NULL)return false;
    calc_parse(pila_ver_tope(pila), destino2);
    if (destino2->type == TOK_LPAREN) {
        free(destino2);
        return false;
    }
    if (destino->oper.op == OP_POW){
        if(destino->oper.precedencia < destino2->oper.precedencia){
        free(destino2);
        return true;
        } else{
            free(destino2);
            return false;
        }
    }
    if (destino->oper.precedencia <= destino2->oper.precedencia){
        free(destino2);
        return true;
    }
    free(destino2);
    return false;
}

void imprimir_notacion(cola_t* cola){
    while(cola_esta_vacia(cola) == false){
        fprintf(stdout, "%s ", (char*) cola_desencolar(cola));
    }
    fprintf(stdout, "\n");
}


int main(){
    calc_infix_a_polaca();
    return 0;
}
