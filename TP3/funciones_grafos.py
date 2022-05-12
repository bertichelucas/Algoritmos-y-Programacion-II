from cola import Cola
from pila import Pila
import random


'''
Recibe un grafo y un vertice de origen y recorre todos los vertices 
posibles a partir del origen que pertenezcan a niveles inferiores o iguales
al dado por parametro. Devuelve un diccionario con los padres de cada
vertice recorrido.
'''
def bfs_por_nivel(grafo, origen, nivel):
    visitados = set()
    padres = {}
    orden = {}
    q = Cola()
    v = origen
    visitados.add(v)
    padres[v] = None
    orden[v] = 0
    q.encolar(v)
    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                orden[w] = orden[v] + 1
                if orden[w] == nivel + 1:
                    break
                visitados.add(w)
                padres[w] = v
                q.encolar(w)
    return padres

'''
Recibe un grafo y dos vertices. Recorre el camino minimo
en cantidad de aristas desde el vertice de origen hasta el
vertice de destino. Devuelve el camino desde el origen
hasta el destino. Si no hay camino devuelve None.
'''

def camino_bfs(grafo, origen, des):
    visitados = set()
    padres = {}
    camino = []
    q = Cola()
    visitados.add(origen)
    padres[origen] = None
    q.encolar(origen)
    while not q.esta_vacia():
        v = q.desencolar()
        if v == des:
            break
        for w in grafo.adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                padres[w] = v
                q.encolar(w)

    if des not in visitados:
        return None
    v = des
    while v != None:
        camino.insert(0, v)
        v = padres[v]
    return camino

'''
Recibe un grafo. Devuelve los grados de salida
para cada vertice en forma de diccionario. En caso de ser
no dirigido simplemente devuelve los grados.
'''
def grados_salida(grafo):
    grados = {}
    for v in grafo:
        grados[v] = len(grafo.adyacentes(v))
    return grados
       
'''
Funcion recursiva de cfc.
'''

def _cfc(grafo, v, mb, orden, visitados, apilados, pila, orden_global, componentes):
    visitados.add(v)
    apilados.add(v)
    pila.apilar(v)
    mb[v] = orden[v] = orden_global
    orden_global += 1
    
    for w in grafo.adyacentes(v):
        if w not in visitados:
            orden_global = _cfc(grafo, w, mb, orden, visitados, apilados, pila, orden_global, componentes)
        if w in apilados:
            if mb[w] < mb[v]:
                mb[v] = mb[w]

    if mb[v] == orden[v] and (not pila.esta_vacia()):
        nueva_cfc = []
        while True:
           w = pila.desapilar()
           apilados.remove(w)
           nueva_cfc.append(w)
           if w == v:
                break
        componentes.append(nueva_cfc)

    return orden_global

'''
Recibe un grafo. Calcula sus componentes fuertemente conexas y las devuelve.
'''

def cfc(grafo):
    apilados = set()
    visitados = set()
    pila = Pila()
    orden = {}
    mb = {}
    componentes = []
    or_glo = 0
    for v in grafo:
        if v not in visitados:
            or_glo = _cfc(grafo,v,mb,orden,visitados,apilados,pila,or_glo,componentes)
    return componentes


'''
Recibe un grafo. Calcula y devuelve las comunidades del mismo.
(vertices altamente conectados entre si).
'''
def label_propagation(grafo):
    labels = {}
    comunidades = {}
    i = 0

    for v in grafo:
        labels[v] = i
        i += 1
    
    i = 0 
    while i != 10:
        i += 1
        comunidades = {}
        vertices =grafo.obtener_vertices()
        random.shuffle(vertices)
    
        for v in vertices:
            freq = {}
            for w in grafo.adyacentes(v):
                if labels[w] not in freq:
                    freq[labels[w]] = 1
                else:
                    freq[labels[w]] += 1

            max = 0
            clave = None
            for key in freq:
                if freq[key] > max:
                    max = freq[key]
                    clave = key
            
            labels[v] = clave

        for v in labels:
            if labels[v] not in comunidades:
                comunidades[labels[v]] = []
            comunidades[labels[v]].append(v)
       
    return comunidades

'''
Recibe un grafo y devuelve los vertices de entrada
para cada vertice del mismo.
'''
def vertices_entrada(grafo):
    v_entrada = {}
    for v in grafo:
        if v not in v_entrada:
            v_entrada[v] = set()

        for w in grafo.adyacentes(v):
            if w not in v_entrada:
                v_entrada[w] = set()

            v_entrada[w].add(v)
    return v_entrada
            
'''
Recibe un grafo y calcula un ranking de importancia para cada vertice dentro
del grafo. Devuelve ese ranking en forma de diccionario.
'''

def page_rank(grafo):
    pr = {}
    cant = len(grafo.obtener_vertices())
    for v in grafo:
        pr[v] = 1 / cant
    
    entrada = vertices_entrada(grafo)
    
    new_pr = {}
    for i in range(50): #cantidad de iteraciones para converger
        for v in grafo:
            new_pr[v] = (1 - 0.85) / cant
            visitados = set()
            for w in entrada[v]:
                if w == v:
                    continue
                new_pr[v] += 0.85 * (pr[w] / len(grafo.adyacentes(w)))
        pr = new_pr
        new_pr = {}
    
    return pr


'''
Funcion recursiva para calcular ciclo de largo n.
'''
def _dfs_ciclo_largo_n(grafo, v, origen, n, visitados, camino_actual):
    camino_actual.append(v)
    visitados.add(v)
    if len(camino_actual) == n:
        if origen in grafo.adyacentes(v):
            camino_actual.append(origen)
            return camino_actual
        else:
            camino_actual.pop()
            visitados.remove(v)
            return None
    
    for w in grafo.adyacentes(v):
        if w not in visitados:
            solucion = _dfs_ciclo_largo_n(grafo, w, origen, n, visitados, camino_actual)
            if solucion is not None:
                return solucion
    camino_actual.pop()
    visitados.remove(v)
    return None



'''
Recibe un grafo y un vertice. Busca un camino simple que tenga longitud
n y empiece y termine en el vertice dado. De no encontrar el camino 
devuelve None.
'''
def ciclo_largo_n(grafo, origen ,n):
    return _dfs_ciclo_largo_n(grafo, origen , origen,n, set(), [])
    