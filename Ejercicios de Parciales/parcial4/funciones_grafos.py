from grafo import Grafo
from cola import Cola
from pila import Pila
from union_find import UnionFind
import heapq as heap
import random

def bfs_completo(grafo):
    visitados = set()
    padres = {}
    orden = {}
    q = Cola()
    for v in grafo:
        if v not in visitados:
            visitados.add(v)
            padres[v] = None
            orden[v] = 0
            q.encolar(v)

            while not q.esta_vacia():
                v = q.desencolar()
                for w in grafo.adyacentes(v):
                    if w not in visitados:
                        visitados.add(w)
                        padres[w] = v
                        orden[w] = orden[v] + 1
                        q.encolar(w)
    return padres, orden

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

def _dfs(grafo, v, visitados, padres, orden):
    visitados.add(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            padres[w] = v
            orden[w] = orden[v] + 1
            _dfs(grafo, w, visitados, padres, orden)

def dfs(grafo, origen):
    visitados = set()
    padres = {}
    orden = {}
    padres[origen] = None
    orden[origen] = 0
    _dfs(grafo, origen, visitados, padres, orden)
    return padres, orden

def recorrido_dfs_completo(grafo):
    visitados = set()
    padres = {}
    orden = {}
    for v in grafo:
        if v not in visitados:
            padres[v] = None
            orden[v] = 0
            _dfs(grafo, v, visitados, padres, orden)
    return padres, orden

def grados_entrada(grafo):
    grados = {}
    for v in grafo:
        if v not in grados:
            grados[v] = 0
        for w in grafo.adyacentes(v):
            if w not in grados:
                grados[w] = 0
            grados[w] += 1
    return grados

def grados_salida(grafo):
    grados = {}
    for v in grafo:
        grados[v] = len(grafo.adyacentes(v))
    return grados

def grados_vertices(grafo): #Grafo no dirigido
    return grados_salida(grafo)

def orden_topologico(grafo):
    grados = grados_entrada(grafo)
    q = Cola()
    for v in grados:
        if grados[v] == 0:
            q.encolar(v)
    resultado = []
    while not q.esta_vacia():
        v = q.desencolar()
        resultado.append(v)
        for w in grafo.adyacentes(v):
            grados[w] -= 1
            if grados[w] == 0:
                q.encolar(w)
    return resultado            

def _dfs_pa(grafo, v, visitados, padres, orden, mb, puntos_articulacion ,es_raiz):
    visitados.add(v)
    hijos = 0
    mb[v] = orden[v]
    for w in grafo.adyacentes(v):
        if w not in visitados:
            padres[w] = v
            orden[w] = orden[v] + 1
            hijos += 1
            _dfs_pa(grafo, w, visitados, padres ,orden, mb, puntos_articulacion, False)
            if mb[w] >= orden[v] and es_raiz == False:
                puntos_articulacion.add(v)
            mb[v] = min(mb[v], mb[w])
        else:
            if mb[w] < mb[v] and padres[v] != w:
                mb[v] = mb[w]
    if es_raiz and hijos > 1:
        puntos_articulacion.add(v)

def puntos_articulacion(grafo):
    visitados = set()
    padres = {}
    orden = {}
    mb = {}
    puntos_articulacion = set()
    v = grafo.vertice_aleatorio()
    padres[v] = None
    orden[v] = 0
    mb[v] = 0
    _dfs_pa(grafo, v, visitados, padres ,orden, mb, puntos_articulacion ,True)
    return puntos_articulacion

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

    if mb[v] == orden[v]:
        nueva_cfc = []
        while pila.ver_tope() != v:
            nueva_cfc.append(pila.desapilar())
        nueva_cfc.append(pila.desapilar())
        componentes.append(nueva_cfc)

    return orden_global

def cfc(grafo):
    apilados = set()
    visitados = set()
    pila = Pila()
    orden = {}
    mb = {}
    componentes = []
    v = grafo.obtener_vertices()[0]
    _cfc(grafo,v,mb,orden,visitados,apilados,pila,0,componentes)
    return componentes
    
def camino_minimo_dijkstra(grafo, origen = None, destino = None):
    origen = origen if origen is not None else grafo.vertice_aleatorio()
    dist = {}
    padres = {}
    for v in grafo:
        dist[v] = float('inf')
    dist[origen] = 0
    padres[origen] = None
    a = (dist[origen], origen)
    q = []
    heap.heappush(q, a)
    while q:
        orden, v = heap.heappop(q)
        if v == destino and destino != None:
            break
        for w in grafo.adyacentes(v):
            if dist[v] + grafo.peso_arista(v,w) < dist[w]:
                dist[w] = dist[v] + grafo.peso_arista(v,w) 
                padres[w] = v
                heap.heappush(q, (dist[w], w))
    return padres, dist

def obtener_aristas(grafo):
    aristas = set()
    for v in grafo:
        for w in grafo.adyacentes(v):
            aristas.add((v, w, grafo.peso_arista(v,w)))
    return aristas

def camino_minimo_BF(grafo, origen = None):
    origen = origen if origen is not None else grafo.vertice_aleatorio()
    dist = {}
    padres = {}
    padres[origen] = None
    for v in grafo:
        dist[v] = float('inf')
    dist[origen] = 0
    aristas = obtener_aristas(grafo)
    for _ in grafo:
        for v, w, peso in aristas:
            if dist[v] + peso < dist[w]:
                padres[w] = v
                dist[w] = dist[v] + peso
    for v, w, peso in aristas:
        if dist[v] + peso < dist[w]:
            raise ValueError("Ciclo negativo")
    return padres, dist

def prim(grafo):
    visitados = set()
    q = []
    g = Grafo(lista_vertices=grafo.obtener_vertices())
    origen = grafo.vertice_aleatorio()
    visitados.add(origen)
    for w in grafo.adyacentes(origen):
        heap.heappush(q, (grafo.peso_arista(origen, w), origen, w))
    while q:
        peso, v, w = heap.heappop(q)
        if w not in visitados:
            g.agregar_arista(v,w, peso)
            visitados.add(w)
            for ady in grafo.adyacentes(w):
                if ady not in visitados:
                    heap.heappush(q, (grafo.peso_arista(w, ady), w, ady))
    return g

def kruskal(grafo):
    aristas = list(obtener_aristas(grafo))
    aristas.sort(key=lambda x: x[2])
    u = UnionFind(grafo.obtener_vertices())
    g = Grafo(lista_vertices=grafo.obtener_vertices())
    for v,w, peso in aristas:
        if u.find(v) != u.find(w):
            g.agregar_arista(v,w, peso)
            u.union(v, w)
    return g

def copiar_grafo(grafo):
    copia = Grafo(lista_vertices = grafo.obtener_vertices() , es_dirigido= True)
    for v, w, peso in obtener_aristas(grafo):
        copia.agregar_arista(v, w ,peso)
    return copia

def peso_min(grafo, camino):
    #devuelve el peso minimo de todas las aristas en un camino
    peso_min = float('inf')
    for i in range(1, len(camino)):
        actual = grafo.peso_arista(camino[i-1], camino[i])
        if actual < peso_min:
            peso_min = actual
    return peso_min


def actualizar_grafo_ff(grafo, v, w, peso_min):
    peso = grafo.peso_arista(v, w)
    if peso == peso_min:
        grafo.borrar_arista(v, w)
    else:
        grafo.actualizar_peso(v, w, peso - peso_min)

    if not grafo.estan_unidos(w, v):
        grafo.agregar_arista(w, v, peso_min)
    else:
        grafo.actualizar_peso(w, v, grafo.peso_arista(w,v) + peso_min)

def flujo_ff(grafo, s, t):
    red = copiar_grafo(grafo)
    flujos = {}
    for v, w, _ in obtener_aristas(red):
        flujos[(v, w)] = 0
    
    camino = camino_bfs(red, s , t)

    while camino != None:
        min_pes = peso_min(red, camino)
        for i in range(1, len(camino)):
            w, v = camino[i], camino[i - 1]
            if grafo.estan_unidos(v, w):
                flujos[(v, w)] += min_pes
                actualizar_grafo_ff(red, v, w, min_pes)
            else:
                flujos[(w, v)] -= min_pes
                actualizar_grafo_ff(red, w, v, min_pes)
        camino = camino_bfs(red, s ,t)
    return flujos

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