from grafo import Grafo

def largo_camino_minimo(grafo, v, w):
    visitados = set()
    largo = 1
    verdad, largo = _largo_camino_minimo(grafo, v, w, largo, visitados)
    return largo if verdad else None


def _largo_camino_minimo(grafo, act, des, largo, visitados):
    visitados.add(act)
    largo+= 1
    if des in grafo.adyacentes(act):
        print('entre')
        return True, largo
    
    for w in grafo.adyacentes(act):
        if w not in visitados:
            verdad, largo = _largo_camino_minimo(grafo, w, des, largo, visitados)
            if verdad:
                return True, largo
    
    visitados.remove(act)
    largo -= 1
    return False, largo

def main():
    vertices = ['a', 'b', 'c', 'd', 'e', 'g']
    g = Grafo(lista_vertices=vertices, es_dirigido=False)
    g.agregar_arista('a', 'b', 1)
    g.agregar_arista('a', 'd', 1)
    g.agregar_arista('d', 'e', 1)
    g.agregar_arista('e', 'g', 1)
    g.agregar_arista('b', 'c', 1)
    g.agregar_arista('b', 'g', 1)
    g.agregar_arista('a', 'g', 1)
    print(largo_camino_minimo(g, 'a', 'g'))

main()