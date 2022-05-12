import random

class Grafo():
    
    #Implementacion de Grafo con diccionario de diccionarios.
    def __init__(self,lista_vertices = None, es_dirigido = False):
        self.dirigido = es_dirigido
        self.vertices = {}
        if lista_vertices is not None:
            for v in lista_vertices:
                self.agregar_vertice(v)

    #Agrega un vertice al grafo.
    def agregar_vertice(self, v):
        if v in self.vertices:
            raise ValueError("El vertice ya esta en el grafo")
        self.vertices[v] = {}
    
    def vertice_pertenece(self, v):
        return v in self.vertices

    #Borra un vertice del grafo.
    def borrar_vertice(self, v):
        if v not in self.vertices:
            raise IndexError("El vertice no esta en el grafo")
        for vertice in self.vertices:
            if v in self.vertices[vertice]:
                self.vertices[vertice].pop(v)
        self.vertices.pop(v)
    
    #Agregar una arista entre dos vertices del grafo.
    def agregar_arista(self, v, w, peso = 1):
        if v not in self.vertices or w not in self.vertices:
            raise IndexError("El vertice no esta en el grafo")

        self.vertices[v][w] = peso

        if not self.dirigido:
            self.vertices[w][v] = peso

    #Actualizar peso usa la misma logica que agregar arista.
    def actualizar_peso(self, v , w, nuevo_peso = 1):
        self.agregar_arista(v, w, nuevo_peso) 

    #Borra una arista entre dos vertices del grafo.
    def borrar_arista(self, v, w):
        if v not in self.vertices or w not in self.vertices:
            raise IndexError("El vertice no esta en el grafo")
        
        if w not in self.vertices[v]:
            raise IndexError("La arista no esta en el grafo")
        self.vertices[v].pop(w)

        if not self.dirigido:
            if v not in self.vertices[w]:
                raise IndexError("La arista no esta en el grafo")
            self.vertices[w].pop(v)
        
    #Se fija si dos vertices estan unidos por alguna arista.
    def estan_unidos(self, v, w):
        if v not in self.vertices or w not in self.vertices:
            raise IndexError("El vertice no esta en el grafo")

        return self.vertices[v].get(w) != None

    #Se fija el peso de la arista entre dos vertices.
    def peso_arista(self, v, w):
        if v not in self.vertices or w not in self.vertices:
            raise IndexError("El vertice no esta en el grafo")
        return self.vertices[v][w]

    #Devuelve todos los vertices del grafo en forma de lista.
    def obtener_vertices(self):
        return list(self.vertices)
    
    #Devuelve todos los adyacentes a un vertice dado en forma de lista.
    def adyacentes(self, v):
        if v not in self.vertices:
            raise IndexError("El vertice no esta en el grafo")
        return list(self.vertices[v])

    #Devuelve un vertice aleatorio.
    def vertice_aleatorio(self):
        if len(self.vertices) == 0:
            raise IndexError("El grafo esta vacio")
        return random.choice(list(self.vertices))

    #Metodo para crear un iterador.
    def __iter__(self):
        self.iterador = iter(self.vertices)
        return self.iterador
    
    #Proximo en el iterador.
    def __next__(self):
        next(self.iterador)