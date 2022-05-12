def obtener_ciclo_bfs(grafo):
    visitados = {}
    for v in grafo:
        if v not in visitados:
            ciclo = bfs_ciclo(grafo, v, visitados)
            if ciclo != None:
                return ciclo
    
    return None

def reconstruir_ciclo(padre, inicio, fin):
    v = fin 
    camino = []
    while v != None:
        camino.append(v)
        v = padre[v]
    camino.append(inicio)
    return camino


def bfs_ciclo(grafo, v ,visitados):
    q = Cola()
    q.encolar(v)
    visitados[v] = True
    padre = {}
    padre[v] = None

    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w in visitados:
                if w != padre[v]:
                    return reconstruir_ciclo(padre, w, v)
            else:
                q.encolar(w)
                visitados[v] = True
                padre[w] = v
    
    return None
