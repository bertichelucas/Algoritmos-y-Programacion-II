from grafo import Grafo
from funciones_grafos import camino_bfs, camino_minimo_BF, camino_minimo_dijkstra, cfc, flujo_ff, kruskal, label_propagation, prim, puntos_articulacion

def grafo_lineal():
    grafo = Grafo()
    vertices = ["Fede", "Juan", "Martin", "Eze"]
    for nombre in vertices:
        grafo.agregar_vertice(nombre)
    grafo.agregar_arista("Fede", "Juan")
    grafo.agregar_arista("Juan", "Martin")
    grafo.agregar_arista("Martin", "Eze")

    p_art = puntos_articulacion(grafo)
    print(p_art)

def grafo_ciclo():
    grafo = Grafo()
    vertices = ["Fede", "Juan", "Martin", "Eze"]
    for nombre in vertices:
        grafo.agregar_vertice(nombre)
    grafo.agregar_arista("Fede", "Juan")
    grafo.agregar_arista("Juan", "Martin")
    grafo.agregar_arista("Martin", "Eze")
    grafo.agregar_arista("Eze", "Fede")
    p_art = puntos_articulacion(grafo)
    print(p_art)

def grafo_cfc():
    grafo = Grafo(es_dirigido=True)
    vertices = ["Fede", "Juan", "Martin"]
    for nombre in vertices:
        grafo.agregar_vertice(nombre)
    grafo.agregar_arista("Fede", "Martin")
    grafo.agregar_arista("Martin", "Juan")
    grafo.agregar_arista("Juan", "Martin")
    print(cfc(grafo))

def grafo_cm():
    vertices = ['a', 'b', 'c', 'd', 'e', 'f']
    g = Grafo(lista_vertices=vertices)
    g.agregar_arista('a', 'b', 3)
    g.agregar_arista('a', 'c', 5)
    g.agregar_arista('b', 'd', 1)
    g.agregar_arista('b', 'e', 4)
    g.agregar_arista('c', 'e', 1)
    g.agregar_arista('c', 'f', 4)
    g.agregar_arista('f', 'e', 2)
    g.agregar_arista('f', 'd', 7)
    g.agregar_arista('d', 'e', 6)
    print(camino_bfs(g, 'a', 'd'))
    print(camino_minimo_dijkstra(g, origen = 'a'))

def grafo_bell():
    vertices = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
    g = Grafo(lista_vertices=vertices, es_dirigido=True) 
    g.agregar_arista('a', 'b', 3)
    g.agregar_arista('c', 'a', 4)
    g.agregar_arista('b', 'd', 4)
    g.agregar_arista('b', 'e', 1)
    g.agregar_arista('e', 'd', 1)
    g.agregar_arista('c', 'g', 3)
    g.agregar_arista('f', 'e', -2)
    g.agregar_arista('d', 'g', -7)
    g.agregar_arista('g', 'f', 10)
    g.agregar_arista('d', 'f', 2)
    
    print(camino_minimo_BF(g, origen='a'))

def grafo_tendido_min():
    vertices = ['a', 'b', 'x', 'z', 'r', 'w', 'h', 'k']
    g = Grafo(lista_vertices=vertices)
    g.agregar_arista('a','x',2)
    g.agregar_arista('a','z',1)
    g.agregar_arista('z','r', 3)
    g.agregar_arista('z','x', 2)
    g.agregar_arista('x','k', 7)
    g.agregar_arista('x', 'b',5)
    g.agregar_arista('r', 'w', 4)
    g.agregar_arista('z', 'w', 5)
    g.agregar_arista('w','b',3)
    g.agregar_arista('w','h',1)
    g.agregar_arista('b', 'h', 3)
    g.agregar_arista('h', 'k', 4)

    #nuevo_grafo = kruskal(g)
    nuevo_grafo = prim(g)
    visitados = set()
    for v in nuevo_grafo:
        print(v + ':')
        visitados.add(v)
        for w in nuevo_grafo.adyacentes(v):
            if w not in visitados:
                print(v + '->' + w)


def grafo_ff():
    vertices = ['s', 'v', 'w', 't', 'z', 'u', 'x', 'fu', 'a']
    g = Grafo(lista_vertices=vertices, es_dirigido= True)
    g.agregar_arista('s','v',6)
    g.agregar_arista('v','t',3)
    g.agregar_arista('v','w',1)
    g.agregar_arista('z','w',1)
    g.agregar_arista('w','t',6)
    g.agregar_arista('fu','s',float('inf'))
    g.agregar_arista('fu','x',float('inf'))
    g.agregar_arista('x','z',3)
    g.agregar_arista('z','a',4)
    g.agregar_arista('a','u',4)
    g.agregar_arista('u','z',2)
    g.agregar_arista('u','w',6)
    g.agregar_arista('s','u',3)

    print(flujo_ff(g, 'fu' ,'t'))
    

def grafo_label_propagation():
    vertices = ['a', 'b', 'x', 'z', 'r', 'w', 'h', 'k']
    g = Grafo(lista_vertices=vertices)
    g.agregar_arista('a','x',2)
    g.agregar_arista('a','z',1)
    g.agregar_arista('z','r', 3)
    g.agregar_arista('z','x', 2)
    g.agregar_arista('x','k', 7)
    g.agregar_arista('x', 'b',5)
    g.agregar_arista('r', 'w', 4)
    g.agregar_arista('z', 'w', 5)
    g.agregar_arista('w','b',3)
    g.agregar_arista('w','h',1)
    g.agregar_arista('b', 'h', 3)
    g.agregar_arista('h', 'k', 4)

    print(label_propagation(g, 2))

def main():
    print("Label Propagation")
    grafo_ff()
    '''
    print("Flujo Grafo FF")
    grafo_ff()
    print("Grafo lineal:")
    grafo_lineal()
    print("Grafo ciclo, (sin pa)")
    grafo_ciclo()
    print("CFC")
    grafo_cfc()
    print("camino minimo")
    grafo_cm()
    print("camino minimo bellman")
    grafo_bell()
    print("arbol tend minimo")
    grafo_tendido_min()
    '''
main()