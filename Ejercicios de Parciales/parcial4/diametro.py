from grafo import Grafo
from cola import Cola

'''
El diametro de una red o grafo es el maximo de las distancias minimas 
entre todos los vertices de la misma. Permite obtener el diametro 
de una red en caso de grafo no dirigido y no pesado

El orden del algoritmo es O(V(V + E))
'''
def diametro(grafo):
    max_dist_min = 0
    for v in grafo:
        dist_min = caminos(grafo, v)
        for w in dist_min:
            if dist_min[w] > max_dist_min:
                max_dist_min = dist_min[w]
    return max_dist_min


def caminos(grafo, v):
    q = Cola()
    visitados = set()
    orden = {}
    visitados.add(v)
    orden[v] = 0
    q.encolar(v)

    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                orden[w] = orden[v] + 1
                visitados.add(w)
                q.encolar(w)
    
    return orden

def main():
    vertices = ['a', 'b', 'c', 'd', 'e', 'f']
    g = Grafo(lista_vertices=vertices, es_dirigido=False)
    g.agregar_arista('a', 'b', 3)
    g.agregar_arista('a', 'c', 5)
    g.agregar_arista('b', 'd', 1)
    g.agregar_arista('c', 'e', 1)
    g.agregar_arista('c', 'f', 4)
    g.agregar_arista('f', 'e', 2)
    g.agregar_arista('f', 'd', 7)
    print(diametro(g))
    return 0

main()