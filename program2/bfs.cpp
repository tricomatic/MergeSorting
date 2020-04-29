//Name........Yafet Kubrom
//EUID........11334602
//Date........3/3/2020
//Course......CSCE3110.002

#include <iostream>
#include <fstream>      //To open and write to a file
#include <string>
#include <sstream>
#include <list>
using namespace std;
// A structure to represent an adjacency list node
struct Node
{
	int dest;
	struct Node* next;
};

// A structure to represent an adjacency list
struct AdjList
{
	struct Node *head;
};

// A structure to represent a graph.
struct Graph
{
	int V;
	struct AdjList* array;
};

// A utility function to create a new adjacency list node
struct Node* newAdjListNode(int dest)
{
	struct Node* newNode =
	(struct Node*) malloc(sizeof(struct Node));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
	struct Graph* graph =
		(struct Graph*) malloc(sizeof(struct Graph));
	graph->V = V;

	// Create an array of adjacency lists. Size of
	// array will be V
	graph->array =
	(struct AdjList*) malloc(V * sizeof(struct AdjList));

	// Initialize each adjacency list as empty by
	// making head as NULL
	int i;
	for (i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
	// Add an edge from src to dest. A new node is
	// added to the adjacency list of src. The node
	// is added at the begining
	struct Node* newNode = newAdjListNode(dest);
	newNode->next = graph->array[src-1].head;
	graph->array[src-1].head = newNode;

	// Since graph is undirected, add an edge from
	// dest to src also
	newNode = newAdjListNode(src);
	newNode->next = graph->array[dest-1].head;
	graph->array[dest-1].head = newNode;

}

void freeAll(Graph* graph)
{
    Node* tmp;
    int i;
    for(i=0; i < graph->V; i++)
    {
        Node* p = graph->array[i].head;
        while(p)
        {
            tmp = p;
            p = p->next;
            free(tmp);
        }
        free(p);
    }
    graph = NULL;
}

string bfs(Graph* graph, int V, int s)
{
    int i;
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(i = 0; i < V; i++)
        visited[i] = false;

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[s-1] = true;
    queue.push_back(s);


    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        //cout << s << " ";
        queue.pop_front();

        Node *tmp = graph->array[s-1].head;
        while(tmp)
        {
            if(!visited[tmp->dest - 1])
            {
                visited[tmp->dest - 1] = true;
                queue.push_back(tmp->dest);
            }
            tmp = tmp->next;
        }
    }
    for(i = 0; i < V; i++)
    {
        if(visited[i] == false)
        {
            free(visited);
            return "Graph is not connected.";
        }
    }
    free(visited);
    return "Graph is connected.";
}

// Driver program to test above functions
int main()
{
	int num, k;     // tmp variable to hold digits from file
	int count = 0;
    string line;

    ifstream read("data2.txt");
    ofstream write("out2.txt");
    if(!read)
    {
        cout << "data2.txt does not exist" << endl;
    }

    while(getline(read,line))
    {
        if(!line.empty()) count++;
    }

    struct Graph* graph = createGraph(count);   // create a graph with count vertices

    read.clear();
    read.seekg(0, read.beg);                    // restart the pointer to beggining of file
    while(getline(read,line))
    {
        if(!line.empty())
        {
            stringstream tmp (line);            // break line into words
            tmp >> k;                           // grap the beginning as the vertice
            num = k;
            while(tmp >> k) addEdge(graph, num, k); 
        }
    }
    read.close();

    write << bfs(graph, count, 2);
    write.close();

	freeAll(graph);

	return 0;
}
