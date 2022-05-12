class _Nodo:
    def __init__(self, dato, prox):
        self.dato = dato
        self.prox = prox

class Cola:
    def __init__(self):
        #invariante: o los dos son None o los dos apuntan a un nodo 
        # (pueden apuntar al mismo nodo si tiene un solo elemento)
        self.frente = None
        self.ultimo = None

    def esta_vacia(self):
        return self.frente is None

    def encolar(self, x):
        n = _Nodo(x, None)
        if self.esta_vacia():
            self.ultimo = n
            self.frente = n
        else:
            self.ultimo.prox = n
            self.ultimo = n

    def desencolar(self):
        if self.esta_vacia():
            raise ValueError("Cola vacia")

        dato = self.frente.dato
        self.frente = self.frente.prox
        if self.frente is None:
            self.ultimo = None
        return dato

    def ver_primero(self):
        return self.frente.dato
