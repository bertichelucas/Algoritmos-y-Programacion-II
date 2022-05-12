from random import shuffle


def label_propagation(grafo, num):
    labels = {}
    comunidades = {}
    i = 0
    for v in grafo:
        labels[v] = i
        i += 1
    
    while len(comunidades) != num:
        comunidades = {}
        vertices = shuffle(grafo.obtener_vertices())
    
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

            labels[v] = key

        for v in labels:
            if labels[v] not in comunidades:
                comunidades[labels[v]] = []
            comunidades[labels[v]].append(v)
       
    return comunidades