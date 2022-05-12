from grafo import Grafo

'''
Camino Ham es un camino en el cual visito todos los vertices
del grafo una sola vez. Si ademas de recorrer todos los vertices
puedo volver al primero, entonces es un ciclo hamiltoniano.
'''

def camino_hamiltoniano_dfs(grafo, v, visitados, camino):
    visitados.add(v)
    camino.append(v)
    if len(visitados) == len(grafo.obtener_vertices()):
        return True

    for w in grafo.adyacentes(v):
        if w not in visitados: # Poda del Backtracking
            if camino_hamiltoniano_dfs(grafo,w, visitados, camino):
                return True
    
    visitados.remove(v) # Sacarlo permite volver a visitarlo
    camino.remove(v)    # por otro camino
    return False
