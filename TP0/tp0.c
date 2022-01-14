#include "tp0.h"
#include <stdio.h>


/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}


int maximo(int vector[], int n) {
    if (n == 0){
        return -1;
    }
    int position = 0;
    int maxValue = vector[position];
    for (int i = 1; i < n; i++){
        if (maxValue < vector[i]) {
            maxValue = vector[i];
            position = i;
        }
    }
    return position;
}

int comparar(int vector1[], int n1, int vector2[], int n2) {
    int minLength = n1;
    int result = 0;
    if (n1 > n2){
        minLength = n2;
        result = 1;
    } else if (n2 > n1){
        result = -1;
    }
    for (int i = 0; i <minLength; i++){
        if (vector1[i] < vector2[i]){
            return -1;
        } else if (vector2[i] < vector1[i]) {
            return 1;
        }
    }
    return result;
}

void seleccion(int vector[], int n) {
    for (int i = 0; i < n; i++){
        int position = maximo(vector, n - i);
        swap(&vector[position], &vector[n - 1 - i]);
    }
}
