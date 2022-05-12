from grafo import Grafo

def camino_simple_mas_largo(grafo, v , w):
    visitados = set()
    padres = {}
    orden = {}
    orden[None] = 0
    orden[w] = 0
    _camino_simple_mas_largo(grafo,None, v, w, visitados, padres, orden)

def _camino_simple_mas_largo(grafo,ant, act, des, visitados, padres, orden):
    visitados.add(act)
    padres[act] = ant
    orden[act] = orden[ant] + 1

    if des in grafo.adyacentes(act) and 

    for w in grafo.adyacentes(act):
        if w == des:
            if orden[des] < orden[act] + 1:
                orden[des] = orden[act] + 1
                padres[des] = act 
            continue
        elif w not in visitados:
            if _camino_simple_mas_largo(grafo, act, w, des, visitados, padres, orden):
                return True