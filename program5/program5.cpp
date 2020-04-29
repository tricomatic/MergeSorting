// Name........Yafet Kubrom
// EUID........11334602
// Date........4/28/2020
// Course......CSCE3110.002
//.Topological Ordering....

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

#define V 50

int stack[50], n = 50, top = -1;
int pop();
void send(int val);

struct node
{
  int vertex;
  struct node* next;
};
struct node* createNode(int v);

struct Graph
{
  int v;
  struct node** adj;
};

struct Graph* createGraph(int v);
void addEdge(struct Graph* graph, int src, int dest);
void topUtil(struct Graph* graph, int v, bool visited[]);
void topSort(struct Graph* graph, int v, ofstream& write);
void freed(struct Graph* graph, int v);
int main()
{
  int a = 0, b = 0;
  string line;
  int k;
  ifstream read("data5.txt");
  ofstream write("out5.txt");

  if(!read)
  {
    cout << "data5.txt does not exist on current directory" << endl;
    exit(1);
  }
  struct Graph* graph = createGraph(V);

  while (getline(read, line))
  {
    stringstream tmp (line);
    tmp >> a;
    b++;
   while(tmp >> k)
    addEdge(graph, a, k);
  }
  read.close();
  topSort(graph, b, write);
  write.close();



  freed(graph, V);
}

void freed(struct Graph* graph, int v)
{
	for(int i = 0; i < v; i++)
		free(graph->adj[i]);

	free(graph);
}

struct node* createNode(int v)
{
  struct node* newNode = (node*) malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

struct Graph* createGraph(int v)
{
  struct Graph* graph = (Graph*) malloc(sizeof(struct Graph));
  graph->v = v;
  graph->adj = (node**) malloc(v * sizeof(struct node*));

  int i;
  for (i = 0; i < v; i++)
    graph->adj[i] = NULL;

  return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
  if(graph->adj[src-1] == NULL)
  {
    struct node* newNode = createNode(src);
    graph->adj[src-1] = newNode;
  }

  struct node* newNode = createNode(dest);
  graph->adj[src-1]->next = newNode;
}

void topUtil(struct Graph* graph, int v, bool visited[])
{
  int i;
  visited[v] = true;

  struct node* tmp = graph->adj[v];
  while(tmp)
  {
    if(!visited[(tmp->vertex)-1])
      topUtil(graph, (tmp->vertex)-1, visited);
    tmp = tmp->next;
  }

  send(v+1);
}

void topSort(struct Graph* graph, int v, ofstream& write)
{
  int i, k;
  bool *visited = new bool[v];
  for (i = 0; i < v; i++)
    visited[i] = false;

  for (i = 0; i < v; i++)
    if (visited[i] == false)
      topUtil(graph, i, visited);

  while((k = pop()) != -1)
    write << k << " ";
  write << endl;
}

void send(int val)
{
	if(top >= n-1)
		cout << "stack overflow" << endl;
	else
	{
		top++;
		stack[top] = val;
	}
}

int pop()
{
	if (top <= -1)
		return -1;
	else
		return stack[top--];
}
