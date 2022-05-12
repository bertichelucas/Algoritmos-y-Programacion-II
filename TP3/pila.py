
class _Nodo:
    def __init__(self, dato, prox):
        self.dato = dato
        self.prox = prox

class Pila:
    def __init__(self):
        self.tope = None

    def esta_vacia(self):
        return self.tope is None

    def apilar(self, x):
        self.tope = _Nodo(x, self.tope) 

    def desapilar(self):
        if self.esta_vacia():
            raise ValueError('Pila Vacia')
        viejo_tope = self.tope
        self.tope = self.tope.prox
        return viejo_tope.dato

    def ver_tope(self):
        if self.esta_vacia():
            raise ValueError('Pila Vacia')
        return self.tope.dato
