
def _coloreo(grafo, v, colores, color, k):
    colores[v] = color
    if len(colores) == len(grafo.obtener_vertices()):
        if es_valido(grafo, v, colores):
            return True
        else:
            colores.pop(v)
            return False
        
    if not es_valido(grafo, v, colores):
        colores.pop(v)
        return False
    
    for w in grafo.adyacentes(v):
        if w in colores: continue
        for color_opcion in range(k):
            if _coloreo(grafo, w, colores, color_opcion, k):
                return True

    colores.pop(v)
    return False

def es_valido(grafo, v, colores):
    for w in grafo.adyancentes(v):
        if w in colores and colores[w] == colores[v]:
            return False
    return True
            

