#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dc.h"
#include <string.h>
#include <ctype.h>

 
//gcc dc.c -Wall -Werror -o dc

bool operar(pilanum_t* pila, struct calc_token* destino){
    calc_num num1= 0;
    calc_num num2= 0;
    double resultado;
    if (desapilar_num(pila, &num2) == false) return false;
    if(destino->oper.op == OP_RAIZ){
        if (num2 < 0) return false;
        apilar_num(pila, (calc_num) (resultado =sqrt((double) num2)));
        return true;
    }
    if (desapilar_num(pila, &num1) == false) return false;
    if (destino->oper.op == OP_LOG){
        if (num2 <= 0 || num2 == 1) return false;
        apilar_num(pila, (calc_num) (resultado = log((double) num1)/ log((double) num2)));
    }
    if(destino->oper.op == OP_ADD){
        apilar_num(pila, num1 + num2);
    }
    if(destino->oper.op == OP_SUB){
        apilar_num(pila, num1 - num2);
    }
    if(destino->oper.op == OP_DIV){
        if (num2 == 0) return false;
        apilar_num(pila, num1 / num2);
    }
    if(destino->oper.op == OP_MUL){
        apilar_num(pila, num1 * num2);
    }
    if(destino->oper.op == OP_POW){
        if (num2 < 0) return false;
        apilar_num(pila, (calc_num) (resultado = pow((double) num1,(double) num2)));
    } else if (destino->oper.op == OP_TERN){
        calc_num num3 = 0;
        if (desapilar_num(pila, &num3) == false) return false;
        apilar_num(pila, num3 ? num1 : num2);
    }
    return true;
}

bool calcular_linea(char** arreglo, calc_num* resultado){
    pilanum_t* pila = pilanum_crear();
    if (pila == NULL) return false;
    struct calc_token* destino = malloc(sizeof(struct calc_token));
    if (destino == NULL)return false;
    size_t i = 0;
    while(arreglo[i] != NULL){
        if(calc_parse(arreglo[i], destino) == false){
            free(destino);
            pilanum_destruir(pila);
            return false;
        }
        if (destino->type == TOK_NUM){
            apilar_num(pila, destino->value);
        } else{
            if (operar(pila, destino) == false){
                free(destino);
                pilanum_destruir(pila);
                return false;
            }
        }
        i++;
    }
    free(destino);
    desapilar_num(pila, resultado);
    if (desapilar_num(pila, resultado) == true){
        pilanum_destruir(pila);
        return false;
    } 
    pilanum_destruir(pila);
    return true;
}

void destruir_arreglo(char** arreglo){
    size_t i = 0;
    while(arreglo[i] != NULL){
        free(arreglo[i]);
        i++;
    }
    free(arreglo);
}

void calculadora_polaca(){
    char* lin = NULL;
    size_t tam = 0;
    calc_num* resultado = malloc(sizeof(calc_num));
    if (resultado == NULL) return;
    while(getline(&lin, &tam, stdin) != EOF){
        if (strcmp(lin, "\n") == 0) break;
        char** arreglo = dc_split(lin);
        if(calcular_linea(arreglo, resultado) == false){
            fprintf(stdout, "%s", "ERROR\n");
        } else{
            fprintf(stdout, "%ld\n", *resultado);
        }
        destruir_arreglo(arreglo);
    }
    free(resultado);
    free(lin);
}


int main(){
    calculadora_polaca();
    return 0;
}


//gcc -Wall -Werror -o pruebas *.c
//gcc -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -o pruebas *.c -lm