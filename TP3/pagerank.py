from grafo import Grafo

def page_rank(grafo):
    pr = {}
    cant = len(grafo.obtener_vertices())
    for v in grafo:
        pr[v] = 1 / cant
    
    new_pr = {}
    for i in range(cant):
        for v in grafo:
            new_pr[v] = 0
            for w in grafo.adyacentes(v):
                ady = len(grafo.adyacentes(w))
                print(ady)
                if ady > 0:
                    new_pr[v] += (pr[w] / len(grafo.adyacentes(w)))
        
        pr = new_pr
        new_pr = {}
    
    return pr