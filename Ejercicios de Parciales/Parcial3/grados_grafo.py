def grado_vertices(grafo): # a
    resultado = {}
    for v in grafo.obtener_vertices():
        resultado[v] = len(grafo.adyacentes(v))
    return resultado


def grado_salida(grafo): # b
    resultado = {}
    for v in grafo.obtener_vertices():
        resultado[v] = len(grafo.adyacentes(v))
    return resultado

def grado_entrada(grafo): # c
    resultado = {}
    for v in grafo.obtener_vertices():
        for w in grafo.adyacentes(v):
                resultado[w] += 1
    return resultado