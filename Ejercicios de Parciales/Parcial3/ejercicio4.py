'''
Parte A:
Elijo un grafo en el que las paltas sean los vertices del mismo.
Las aristas corresponden a las conexiones con otras paltas que tenga cada vertice(palta) en la matriz
Las posibilidades serian que un vertice o palta tenga a 1 de distancia en la matriz
(horizontal y verticalmente) otra palta.
El grafo lo planteo con listas de adyacencia.
Planteo mi algoritmo:
'''

def paltas_minimas(grafo):
    visitados = set()
    total = 0
    for palta in grafo.obtener_vertices():
        if palta not in visitados:
            visitados.add(palta)
            total += 1
            visitados = bfs(grafo, palta, visitados)
            

def bfs(grafo, palta, visitados):
    q = Cola()
    q.encolar(palta)

    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes():
            if w not in visitados:
                visitados.add(w)
                q.encolar(w)

    return visitados

'''
La idea del algoritmo es por cada vertice si el vertice no fue visitado sumar 1 al total de paltas
necesarias y desde ese vertice hacer un bfs para recorrer a todas las paltas que podrian llegar a 
pudrirse a traves del vertice inicial. Esas paltas las agrego a visitados asi ya no las cuento para el
total.
Primeramente tengo O(V) porque estoy recorriendo todos los vertices. Luego por cada vertice veo sus
adyacentes. Por ende estoy viendo todas las aristas y todos los vertices. La complejidad final sera entonces
O(V + E) siendo V la cantidad de vertices y E la cantidad de aristas.
'''