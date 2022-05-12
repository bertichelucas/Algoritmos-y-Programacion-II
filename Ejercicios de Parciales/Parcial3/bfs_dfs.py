from typing import OrderedDict


def bfs(grafo, origen):
    visitados = set()
    padres = {}
    orden = {}
    padres[origen] = None
    origen[origen] = 0
    visitados.add(origen)
    q = Cola()
    q.encolar(origen)

    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                padres[w] = v
                orden[w] = orden[v] + 1
                visitados.add(w)
                q.encolar(w)
    return padres, orden

'''
Orden algoritmico de BFS. O(V + E) en no dirigido
2 * E en el peor caso de dirigido
Esto es suponiendo que grafo.adyacentes no nos afecta en la complejidad. Depende de como sea la 
implementacion interna del grafo
En matriz de adyacencia termina siendo o(v*v) y matriz de incidencia seria O(v*E)

'''
def _dfs(grafo, v, visitados, padres, orden):
    for w in grafo.adyacentes(v):
        if w not in visitados:
            padres[w] = v
            orden[w] = orden[v] + 1
            visitados.add(w)
            _dfs(grafo, w, visitados, padres, orden)

def dfs(grafo, origen):
    visitados = set()
    padres = {}
    orden = {}
    padres[origen] = None
    orden[origen] = 0
    visitados.add(origen)
    _dfs(grafo, origen, visitados, padres, orden)
    return padres, orden

'''
Orden O(V + E) en toda la ejecucion siempre y cuando sea con listas de adyacencia o diccionarios
'''

