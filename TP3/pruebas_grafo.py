from grafo import Grafo


def pruebas_grafo_no_dirigido():
    g = Grafo()
    g.agregar_vertice(10)
    print(f'{g.obtener_vertices()[0]} == 10')
    g.agregar_vertice(15)
    for v in g.obtener_vertices():
        print(f'{v} obtener vertices')
    for v in g:
        print(f'{v} Iterador')

    g.agregar_arista(10, 15)
    print(f'{g.estan_unidos(10,15)} estan unidos')
    print(f'{g.peso_arista(10, 15)} peso arista')
    
    print(g.adyacentes(15))
    print(g.adyacentes(10))

    g.borrar_arista(10, 15)
    print(f'{g.estan_unidos(10,15)} estan unidos')
    print(f'{g.estan_unidos(15,10)} estan unidos')

    print(g.adyacentes(10), g.adyacentes(15))

    g.borrar_vertice(10)
    print(g.obtener_vertices())

    g.agregar_vertice(12)
    g.agregar_arista(12, 15)

    g.borrar_vertice(15)

    print(g.obtener_vertices())
    print(g.adyacentes(12))

    for i in range(100):
        if i not in g.obtener_vertices():
            g.agregar_vertice(i)
    
    print(f'{g.vertice_aleatorio()} vertice aleatorio')
    g.agregar_arista(12, 12)
    print(f'{g.adyacentes(12)} adyacentes de 12')
    
    print(g.obtener_vertices())


def pruebas_grafo_dirigido():
    g = Grafo(es_dirigido=True)
    g.agregar_vertice(10)
    print(f'{g.obtener_vertices()[0]} == 10')
    g.agregar_vertice(15)
    for v in g.obtener_vertices():
        print(f'{v} obtener vertices')
    for v in g:
        print(f'{v} Iterador')

    g.agregar_arista(10, 15)
    print(f'{g.estan_unidos(10,15)} estan unidos')
    print(f'{g.estan_unidos(15,10)} estan unidos')
    print(f'{g.peso_arista(10, 15)} peso arista')
    
    print(g.adyacentes(15))
    print(g.adyacentes(10))

    g.borrar_arista(10, 15)
    print(f'{g.estan_unidos(10,15)} estan unidos')
    print(f'{g.estan_unidos(15,10)} estan unidos')

    print(g.adyacentes(10), g.adyacentes(15))

    g.borrar_vertice(10)
    print(g.obtener_vertices())

    g.agregar_vertice(12)
    g.agregar_arista(12, 15)

    g.borrar_vertice(15)

    print(g.obtener_vertices())
    print(g.adyacentes(12))

    for i in range(100):
        if i not in g.obtener_vertices():
            g.agregar_vertice(i)
    
    g.agregar_arista(12, 12)
    print(f'{g.adyacentes(12)} adyacentes de 12')
    
    print(g.obtener_vertices())

    g.agregar_arista(0, 1, 2)
    g.agregar_arista(1, 0, 4)

    print(f'{g.adyacentes(0)} adyacentes de 0')
    print(f'{g.adyacentes(1)} adyacentes de 1')

    print(g.peso_arista(0, 1) , g.peso_arista(1, 0))

def pruebas_grafo_volumen():
    g = Grafo()
    for i in range(50000):
        if i not in g.obtener_vertices():
            g.agregar_vertice(i)
            if i != 0:
                g.agregar_arista(i -1, i, 1)

    for  i in range(50000):
        if i not in g.obtener_vertices():
                print('Elvertice no se encuentra')
                return
        if i != 0:
            if not g.estan_unidos(i- 1, i):
                print('fallo')
                return
    
    print("Todo ok volumen")
        
def main():
    print('Pruebas Grafo No dirigido')
    pruebas_grafo_no_dirigido()
    print()
    print('Pruebas Grafo dirigido')
    pruebas_grafo_dirigido()
    print('Pruebas Grafo Volumen')
    pruebas_grafo_volumen()
main()