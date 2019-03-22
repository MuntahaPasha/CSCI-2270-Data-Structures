GRAPHS

 - We started off learning trees.
	 - Root, children, leaf nodes at bottom
	 - Binary, 0,1,2 children

But with graphs, we need to represent an arbitrary number of connections. We need to be able to start anywhere.
 - Vertices instead of nodes                                                          Ft. Collins
 - Edges connect vertices                                                         /          |          \
 - Any vertex can be the root.                                              Denver --------------------  Lincoln nebraska
 - Edges between two vertices means they re adjacent.                             \          |          /
    ex: Denver is adjacent to Ft. Collins but not Pueblo                              Co. Springs  <-- /
 - When traversing a graph you go from adjacent vertex                                       |        /
                                                                                           Pueblo <- /
FORMAL DEFINITION:
Graph defined as 
G={V, E} where V is a set of vertices and E is a set of edges
<V1, V2, V3> and <E1, E2, E3>
 * Edges are basically the lines connecting vertices

GRAPH REPRESENTATIONS
 - Adjacency Matrix - Good to know, takes a lot of memory and computation time.
 	* Unweighted graph (All edges have a uniform weight = 1)
 	 ~ 2D Matrix. All vertices listed on horizontal and vertical axis. 
 	 ~ Just captures whether there is a connection at all.
 	  1) Vertical axis is starting
 	  2) Horizontal axis is ending
 	  3) UNDIRECTED egde goes in both directions (V1 -> V5) means that (V5 -> V1)
 	  4) 0 means no connection, 1 means connection
 	  -- OPEN IMAGE graphsUnweightedImage.jpeg
 	* Weighted graph (Each edge has a value, ex: distance b/w 2 vertices if graph is a map)
 	 ~ No edge is represented by -1
 	 ~ Replace 1 with edge weight
 	 ~ 0 going diagonal means that the vertices have a connection to themselves, self loops.
 	 -- OPEN IMAGE graphsWeightedImage.jpeg
 - Adjacency List - Faster (What we will focus on)
   * If there aren't any edges there will be many 0,-1's in the adjacency matrix.
   * Will have lots of computation time to loop through matrix unnecessarily.
    ~ Adjacency list only stores information about adjacent edges.
     - For each vertex, store a list of adjacent vertices.
 - Directed Graph
  * Edge can go in only one direction
   ex: Edge V1-V5 doesn't necessarily mean V5-V1

Dynamically establish an arbitrary # of vertices.
Adjacency List-Store a list(vector) of vertices. In each vertex is a list (vector) of the vertices that it connects to.

Graph Class 
Private: 
	vertices - includes all information about the vertices and the edges.
Public:
Graph()
insertVertex(value)     |A|-- 
insertEdge()



