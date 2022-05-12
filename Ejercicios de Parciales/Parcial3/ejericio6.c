
/*
6.

A) Falso, un grafo bipartito puede tener ciclos pero estos deben ser si o si ciclos pares. Cualquier

ciclo impar romperia con la propiedad de bipartito ya que seria imposible separar en dos grupos sin

tener aristas entre nodos del mismo grupo.


B) Verdadero, en cualquier lugar que se inserte un nuevo nodo con una arista ya sea de entrada o de

salida, si bien el orden topologico puede cambiar, siempre seguira habiendo algun orden ya que esta

nueva tarea tendra una precendencia determinada dentro del grafo.


C) Falso, determinar el grado de entrada o de salida de un vertice es O(E) ya que tengo que ir 

arista por arista  checkeando si entra o sale al vertice del cual quiero calcular su grado. 

*/

