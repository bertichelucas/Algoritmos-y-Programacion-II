'''
Dado un grafo no dirigido y un numero n menor a #v (cant vertices)
devuelva si es posible obtener un subconjunto de n vertices tal que ningun
par de vertices sea adyacente entre si

Se supone que los vertices estan identificados con numeros de 0 a v - 1
'''

from grafo import Grafo

def no_adyacentes(grafo, n):
    no_ad = set()
    v = grafo.vertice_aleatorio()
    if len(grafo.obtener_vertices()) < n: return False
    return _no_ad(grafo,v, n, no_ad)

def es_valido(grafo, v, no_ad):
    for w in no_ad:
        if v in grafo.adyacentes(w):
            return False
    return True

def _no_ad(grafo,v, n, no_ad):
    no_ad.add(v)
    if len(no_ad) == n:
        if es_valido(grafo, v, no_ad):
            return True
        else:
            no_ad.remove(v)
            return False

    if not es_valido(grafo,v, no_ad):
        no_ad.remove(v)
        return False

    for w in grafo:
        if w in no_ad: continue
        if _no_ad(grafo,w, n, no_ad):
            return True
    
    no_ad.remove(v)
    return False
    


def main():
    vertices = ['a', 'b', 'c', 'd', 'e', 'f']
    g = Grafo(lista_vertices=vertices, es_dirigido=False)
    g.agregar_arista('a', 'b', 3)
    g.agregar_arista('a', 'c', 5)
    g.agregar_arista('b', 'd', 1)
    g.agregar_arista('b', 'e', 4)
    g.agregar_arista('c', 'e', 1)
    g.agregar_arista('c', 'f', 4)
    g.agregar_arista('f', 'e', 2)
    g.agregar_arista('f', 'd', 7)
    g.agregar_arista('d', 'e', 6)
    print(no_adyacentes(g, 3))
    return 0

main()


    




