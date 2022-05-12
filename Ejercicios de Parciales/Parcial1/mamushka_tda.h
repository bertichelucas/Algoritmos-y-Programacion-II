#include <stdlib.h>
#include <stdbool.h>

typedef struct mamushka mamushka_t*;

typedef enum color{rojo,verde,amarillo}color_t; //ejemplo del typedef

mamushka_t* mamushka_crear(size_t tam, color_t color);

color_t mamushka_obtener_color(mamushka_t* mamushka);

bool mamushka_guardar(mamushka_t* contenedora, mamushka_t* a_guardar);