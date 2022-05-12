import sys
import csv
from grafo import Grafo
import funciones_grafos


def main():
    if len(sys.argv) != 2:
        raise ValueError('Parametros Invalidos')
    
    grafo = crear_grafo(sys.argv[1])
    print(funciones_grafos.label_propagation(grafo))
     
def crear_grafo(datos_archivo):
    try:
        datos = open(datos_archivo)
    except:
        print("F")
        return None
    
    lector = csv.reader(datos, delimiter='\t')

    g = Grafo(es_dirigido=True)

    for linea in lector:
        v, w = linea[0], linea[1]
        if not g.vertice_pertenece(v):
            g.agregar_vertice(v)
        if not g.vertice_pertenece(w):
            g.agregar_vertice(w)
        
        g.agregar_arista(v, w)

    return g

main()
