from grafo import Grafo
import funciones_grafos

def sumatoria(entrada, v, pr, cant, grafo):
    suma = 0
    for w in entrada[v]:
        suma += (pr[w]/ len(grafo.adyacentes(w)))

    return suma


def page_rankv2(grafo):
    pr = {}
    cant = len(grafo.obtener_vertices())
    for v in grafo:
        pr[v] = 1 / cant
    
    entrada = funciones_grafos.vertices_entrada(grafo)
    
    new_pr = {}
    C = (1 - 0.85) / cant
    for i in range(60): #cantidad de iteraciones para converger
        for v in grafo:
            new_pr[v] = C + 0.85 * (sumatoria(entrada, v, pr, cant, grafo))
            pr[v] = new_pr[v]
    new_pr = {}
    
    return pr

def main():
    g = Grafo(es_dirigido=True)
    g.agregar_vertice('a')
    g.agregar_vertice('b')
    g.agregar_vertice('c')
    g.agregar_vertice('d')
    g.agregar_vertice('g')
    g.agregar_arista('a','g',1)
    g.agregar_arista('a','b',1)
    g.agregar_arista('b','c',1)
    g.agregar_arista('b','d',1)
    g.agregar_arista('d','c',1)
    g.agregar_arista('d','a',1)
    g.agregar_arista('b','a',1)
    g.agregar_arista('c','a',1)
    dict = funciones_grafos.vertices_entrada(g)
    for clave in dict:
        print(clave, dict[clave])
        print('')
    pr = page_rankv2(g)
    for vertice in pr:
        print(vertice, pr[vertice])


main()
'''
def sumatoria(entrada, v, pr, cant, grafo):
    sum = 0
    for w in entrada[v]:
        sum += pr[w]/len(grafo.adyacentes(w))

    return (1- 0.85)/cant + 0.85(sum)
'''