// Kruskal's minimum Spanning tree (mst) algorithm
// using find and union operations
// connected, undirected and weighted graph
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a structure to represent the weighted edge in graph
struct Edge
{
  int src, dest, weight;
};

// structre to represent connected, undirected and weighted graph
struct Graph
{
  int V, E;   // V=number of vertices, E=number of edges
  struct Edge* edge;  // graph will be array of edges and since it is undirected
                      // edge is unidirectional
};

// the actual graph to represent
struct Graph* createGraph(int V, int E)
{
  struct Graph* graph = malloc(sizeof(struct Graph));  // equivalent to = new Graph;
  graph->V = V;
  graph->E = E;

  graph->edge = malloc(E*sizeof(struct Edge));  // equivalent to = new Edge[E]

  return graph;
}

// structure to represent subset for union-find
struct subset
{
  int parent, rank;
};

// find will find set of an element i
int find(struct subset subsets[], int i)
{
  // find root and make root as parent of i
  if (subsets[i].parent != i)
    subsets[i].parent = find(subsets, subsets[i].parent);
  return subsets[i].parent;
}

// function to union two sets of x and y
void Union(struct subset subsets[], int x, int y)
{
  int xroot = find(subsets, x);
  int yroot = find(subsets, y);

  // attach smaller rank tree under foot of high rank tree (union by rank)
  if (subsets[xroot].rank < subsets[yroot].rank)
    subsets[xroot].parent = yroot;
  else if (subsets[xroot].rank > subsets[yroot].rank)
    subsets[yroot].parent = xroot;
  // if rank are same, then make one as root
  else
  {
    subsets[yroot].parent = xroot;
    subsets[xroot].rank++;
  }
}

// compare two edges according to their weights. used for qsort()
int myComp(const void* a, const void* b)
{
  struct Edge* a1 = (struct Edge*)a;
  struct Edge* b1 = (struct Edge*)b;
  return a1->weight > b1->weight;
}

// the main function to construct MST using kruskal's
void kruskalMst(struct Graph* graph)
{
  int V = graph->V;
  struct Edge result[V];    // to store resultant mst
  int e = 0;    // index variable used for result[]
  int i = 0;    // index variable used for sorted edges

  // Step 1. sort all edges in non-decreasing order
  qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);   // qsort sorts an array

  // allocate memory for creating V subsets
  struct subset *subsets = malloc(V * sizeof(struct subset));
  for (int v = 0; v < V; v++)
  {
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }

  while (e < V - 1 && i < graph->E)
  {
    // step 2: pick smallest edge. increment inde for next iteration
    struct Edge next_edge = graph->edge[i++];

    int x = find(subsets, next_edge.src);
    int y = find(subsets, next_edge.dest);

    // if edge doesnt cause cycle, include it. and increment index of result
    if (x != y)
    {
      result[e++] = next_edge;
      Union(subsets, x, y);
    }
    // else discard the next_edge
  }
  free(subsets);

  printf("Edges in the constructed mst\n");
  for (i = 0; i < e; ++i)
    printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
  return;
}

int main()
{
  int v, e;
  int a, b, c;
  printf("Enter V, E: ");
  scanf("%d %d",&v,&e);

  struct Graph* graph = createGraph(v,e);

  for (int i = 0; i < e; i++)
  {
    printf("Enter src dest weight[%d]: ", i);
    scanf("%d %d %d",&a,&b,&c);
    graph->edge[i].src = a;
    graph->edge[i].dest = b;
    graph->edge[i].weight = c;

  }

  /*// add edge 0-1
  graph->edge[0].src = 0;
  graph->edge[0].dest = 1;
  graph->edge[0].weight = 10;

  // add edge 0-2
  graph->edge[1].src = 0;
  graph->edge[1].dest = 2;
  graph->edge[1].weight = 6;

  // add edge 0-3
  graph->edge[2].src = 0;
  graph->edge[2].dest = 3;
  graph->edge[2].weight = 5;

  // add edge 1-3
  graph->edge[3].src = 1;
  graph->edge[3].dest = 3;
  graph->edge[3].weight = 15;

  // add edge 2-3
  graph->edge[4].src = 2;
  graph->edge[4].dest = 3;
  graph->edge[4].weight = 4;
*/
  kruskalMst(graph);

  if (graph != NULL)
      free(graph->edge);
  free(graph);


  return 0;
}



// remember to free Graph
// remember to free subsets
