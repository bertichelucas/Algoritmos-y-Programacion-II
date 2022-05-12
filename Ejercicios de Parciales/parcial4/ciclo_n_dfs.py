
def _dfs_ciclo_largo_n(grafo, v, origen, n, visitados, camino_actual):
    visitados.add(v)
    if len(camino_actual) == n:
        if origen in grafo.adyacentes(v):
            return camino_actual
        else:
            visitados.remove(v)
            return None
    
    for w in grafo.adyacentes(v):
        if w in visitados:
            continue
        solucion = _dfs_ciclo_largo_n(grafo, w, origen, n, visitados, camino_actual)
        if solucion is not None:
            return solucion
    
    visitados.remove(v)
    return None 