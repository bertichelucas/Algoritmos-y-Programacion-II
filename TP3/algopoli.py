#!/usr/bin/python3
import sys
import csv
from grafo import Grafo
import funciones_grafos


def main():
    if len(sys.argv) != 2:
        raise ValueError('Parametros Invalidos')
    
    grafo = crear_grafo(sys.argv[1])

    funciones = {
        'min_seguimientos': min_seguimientos,
        'mas_imp': mas_importante,
        'persecucion': persecucion_rapida,
        'comunidades': comunidades,
        'divulgar': divulgar_rumores,
        'divulgar_ciclo': divulgar_ciclo,
        'cfc': componentes_fconexas
    }

    scores = []
    while True:
        try:
            linea = input()
        except:
            break
        comandos = linea.split()
        funciones[comandos[0]](grafo, comandos, scores)

def min_seguimientos(grafo, argumentos, _):
    if len(argumentos) != 3:
        raise ValueError("Parametros invalidos")
    origen, destino = argumentos[1], argumentos[2]
    camino = funciones_grafos.camino_bfs(grafo, origen, destino)
    if camino == None:
        print("Seguimiento imposible")
    else:
        print(*camino, sep=' -> ')

def calcular_scores(grafo, scores):
    #Funcion auxiliar para calcular el page rank.
    pr = funciones_grafos.page_rank(grafo)
    temp = sorted(pr, key=pr.get, reverse=True)
    for v in temp:
        if v == '422' or v == '762' or v == '179170':
            print(pr[v], v)
        scores.append(v)


def mas_importante(grafo, argumentos, scores):
    if len(argumentos) != 2:
        raise ValueError("Parametros invalidos")
    cant = int(argumentos[1])
    if len(scores) == 0:
        calcular_scores(grafo, scores)
    print(scores[0], end='\0')
    for i in range(1, cant):
        print(f", {scores[i]}", end='\0')
    print()
    return scores

def persecucion_rapida(grafo, argumentos, scores):
    if len(argumentos) != 3:
        raise ValueError("Parametros invalidos")
    agentes = argumentos[1].split(',')
    k = int(argumentos[2])
    if len(scores) == 0:
        calcular_scores(grafo, scores)
    
    caminos_agentes = {}
    for agente in agentes:
        for i in range(k):
            camino = funciones_grafos.camino_bfs(grafo, agente, scores[i])
            if camino == None:
                continue
            if agente not in caminos_agentes:
                caminos_agentes[agente] = camino
            elif len(camino) == len(caminos_agentes[agente]):
                if scores.index(camino[-1]) < scores.index(caminos_agentes[agente][-1]):
                    caminos_agentes[agente] = camino
            elif len(camino) < len(caminos_agentes[agente]):
                caminos_agentes[agente] = camino

    mas_corto = float('inf')
    camino_mas_corto = None
    for agente in caminos_agentes:
        act = len(caminos_agentes[agente])
        if act < mas_corto:
            camino_mas_corto = caminos_agentes[agente]
            mas_corto = act
        if act == mas_corto:
            if scores.index(camino_mas_corto[-1]) > scores.index(caminos_agentes[agente][-1]):
                camino_mas_corto = caminos_agentes[agente]
                mas_corto = act  
    print(*camino_mas_corto, sep=' -> ')
    

def comunidades(grafo, argumentos, _):
    if len(argumentos) != 2:
        raise ValueError("Parametros invalidos")
    n = int(argumentos[1])
    comunidades = funciones_grafos.label_propagation(grafo)
    i = 1
    for comunidad in comunidades:
        if len(comunidades[comunidad]) >= n:
            print(f"Comunidad {i}: ", end = '\0')
            print(*comunidades[comunidad], sep=', ')
            i += 1

def divulgar_rumores(grafo, argumentos, _):
    if len(argumentos) != 3:
        raise ValueError("Parametros invalidos")
    origen = argumentos[1]
    n = int(argumentos[2])
    padres = funciones_grafos.bfs_por_nivel(grafo, origen, n)
    delincuentes = list(padres.keys())
    delincuentes.pop(0)
    print(*delincuentes, sep=', ')


def divulgar_ciclo(grafo, argumentos, _):
    if len(argumentos) != 3:
        raise ValueError("Parametros invalidos")
    origen = argumentos[1]
    n = int(argumentos[2])
    camino = funciones_grafos.ciclo_largo_n(grafo,origen,n)
    if camino is None:
        print("No se encontro recorrido")
    else:
        print(*camino, sep=' -> ')


def componentes_fconexas(grafo, argumentos,_):
    if len(argumentos) != 1:
        raise ValueError("Parametros invalidos")
    cfcs = funciones_grafos.cfc(grafo)
    i = 1
    for c in cfcs:
        print(f"CFC {1}: ", end='\0')
        print(*c, sep=', ')
        i += 1

def crear_grafo(datos_archivo):
    #Crea un grafo a partir de un archivo tsv
    #Devuelve el grafo.
    with open(datos_archivo) as datos:
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
