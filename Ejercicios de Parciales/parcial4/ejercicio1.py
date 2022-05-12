
'''
Para modelarlo con un grafo haria que cada vertice sea un casillero
Luego las aristas conectarian a cada casillero con sus adyacentes y el peso de las 
mismas seria el cansancio que produce moverse desde un casillero al otro.
'''

def camino_minimo(grafo, or , des):
    distancias = {}
    padres = {}
    distancias[or] = 0
    padres[or] = None
    
    heap = Heap()
    heap.encolar((distancias[or], or))

    while not heap.esta_vacio():
        orden, v = heap.desencolar()
        if v == des:
            break
        for w in grafo.adyacentes(v):
            if w not in distancias:
                distancias[w] = infinito
            if distancias[w] > distancias[v] + grafo.peso_arista(v, w):
                distancias[w] = distancias[v] + grafo.peso_arista(v, w)
                padres[w] = v
            heap.encolar(w)
    return padres, distancias
'''
Me devuelve la los padres de cada vertice con los que puedo reconstruir el camino
Hago una funcion que me devuelva el camino si la preciso.
'''

def camino(destino, padres):
    #Reconstruye el desde el final hasta el principio y lo da vuelta para dar el resultado final
    resultado = []
    while destino != None:
        resultado.append(destino)
        destino = padres[destino]
    resultado.reverse()
    return resultado

'''
Si el cansancio fuera el mismo en cualquier direccion e igual para  todos los casilleros 
Entonces el camino minimo simplemente seria el mas corto en cantidad de casilleros ya que no depe
nde del cansancio.
De ese caso en vez de plantear un algoritmo de tipo djkstra se podria buscar el camino por bfs,
ya que de esta manera consigo el resultado de manera mas eficaz y veloz. Estoy reduciendo 
mi complejidad algoritmica de un O(E log V) a O(V + E) que es bfs.
'''