// Name......Yafet Kubrom
// EUID......11334602
// Date......4/14/2020
// Course....CSCE3110.002
// ...Prim's Algorithm...

#include <iostream>
#include <fstream>  // open and write to a file
#include <sstream>  // for stringstream()
#include <bits/stdc++.h>
#include <string>

using namespace std;

#define V 50

string prim(int graph[V][V], int a);
int minKey(int key[], bool mstSet[], int a);


int main()
{
  int a = 0, b = 0;    // counter for the array
  string line;      // temporary variable for holding one line a time
  int k, graph[V][V]; // assuming 50 or less vertices
  ifstream read("data4.txt");
  ofstream write("output4.txt");
  if (!read)
  {
    cout << "data1.txt does not exist on current directory" << endl;
    exit(1);
  }

  while (getline(read,line))
  {
    stringstream tmp (line);
    while(tmp >> k) graph[a][b++] = k;
    a++,b=0;
  }
  string output = prim(graph, a);
  write << output << endl;
  read.close();
  write.close();
}

string prim(int graph[V][V], int a)
{
  int u; // for minimum purposes
  // array to store constructed mst
  int parent[a];
  // skey values to pick min weight
  int key[a];
  // true/false if vertices are included on mst
  bool mstSet[a];

  // initialize
  for (int i = 0; i < a; i++)
    key[i] = INT_MAX, mstSet[i] = false;

  key[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < a - 1; count++)
  {
    // pick min connected vertices
    u = minKey(key, mstSet, a);

    // add min to mst set
    mstSet[u] = true;

    for (int v = 0; v < a; v++)
      if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
        parent[v] = u, key[v] = graph[u][v];
  }
  int num = 0;
  string k, b;
  string c = "The edges of the minimum Spanning tree are ";
  for (int i = 1; i < a; i++)
  {
    num += graph[i][parent[i]];
    k = to_string(parent[i] + 1);
    b = to_string(i + 1);
    c.append("(" + k + ","+ b + ")"+", ");
  }
  c.append("and has total cost of " + to_string(num));

  return c;
}

// A utility function to find the vertex
// with minimum key value, from the set
// of vertices not yet included in MST
int minKey(int key[], bool mstSet[], int a)
{
  // initialize min value
  int min = INT_MAX, min_index;
  for (int i = 0; i < a; i++)
  {
    if (mstSet[i] == false && key[i] < min)
      min = key[i], min_index = i;
  }
  return min_index;
}
