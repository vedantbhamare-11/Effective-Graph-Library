#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int src, dest, weight;
};

class Graph
{
    list<int> *adj;
    bool isCyclicUtil(int v, bool visited[], bool *rs);
    bool isundirCyclicUtil(int v, bool visited[], int parent);

public:
    int V;
    int E;
    Edge *edge;
    Graph(int V);
    void addEdge(int v, int w);
    void BFS(int s);
    bool isCyclic();
    bool isundirCyclic();
    bool ShorBFS(int source, int destination, int parent[]);
    void shortest_path(int source, int destination);
};

class Graph1
{
public:
    int V, E;
    Edge *edge;
};

//BFS
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::BFS(int s)
{
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    list<int> queue;
    visited[s] = true;
    queue.push_back(s);

    list<int>::iterator i;

    while (!queue.empty())
    {
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

//CYCLIC DIRECTED GRAPH
bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
    if (visited[v] == false)
    {
        visited[v] = true;
        recStack[v] = true;

        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
                return true;
            else if (recStack[*i])
                return true;
        }
    }
    recStack[v] = false;
    return false;
}

bool Graph::isCyclic()
{
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;

    return false;
}

//CYCLIC UNDIRECTED GRAPH
bool Graph::isundirCyclicUtil(int v, bool visited[], int parent)
{
    visited[v] = true;

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {

        {
            if (isundirCyclicUtil(*i, visited, v))
                return true;
            else if (*i != parent)
                return true;
        }
    }
    return false;
}

bool Graph::isundirCyclic()
{

    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int u = 0; u < V; u++)
    {

        if (!visited[u])
            if (isundirCyclicUtil(u, visited, -1))
                return true;
    }
    return false;
}

//KRUSKAL
Graph1 *createGraph(int V, int E)
{
    Graph1 *graph = new Graph1;
    graph->V = V;
    graph->E = E;

    graph->edge = new Edge[E];

    return graph;
}

class subset
{
public:
    int parent;
    int rank;
};

int find(subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int myComp(const void *a, const void *b)
{
    Edge *a1 = (Edge *)a;
    Edge *b1 = (Edge *)b;
    return a1->weight > b1->weight;
}

void KruskalMST(Graph1 *graph)
{
    int V = graph->V;
    Edge result[V]; // Tnis will store the resultant MST
    int e = 0;      // An index variable, used for result[]
    int i = 0;      // An index variable, used for sorted edges

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]),
          myComp);

    subset *subsets = new subset[(V * sizeof(subset))];

    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E)
    {
        Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    cout << "Following are the edges in the constructed "
            "MST\n";
    int minimumCost = 0;
    for (i = 0; i < e; ++i)
    {
        cout << result[i].src << " -- " << result[i].dest
             << " == " << result[i].weight << endl;
        minimumCost = minimumCost + result[i].weight;
    }
    cout << "Minimum Cost Spanning Tree: " << minimumCost
         << endl;
}

//SHORTEST PATH UNDIRECTED(BFS)
bool Graph::ShorBFS(int source, int destination, int parent[])
{
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
        parent[i] = -1;
    }
    list<int> queue;
    visited[source] = true;
    queue.push_back(source);

    list<int>::iterator i;

    while (!queue.empty())
    {
        source = queue.front();
        queue.pop_front();

        for (i = adj[source].begin(); i != adj[source].end(); ++i)
        {
            if (visited[*i] == false)
            {
                visited[*i] = true;
                parent[*i] = source;
                queue.push_back(*i);
                if (*i == destination)
                    return true;
            }
        }
    }
    return false;
}

void Graph::shortest_path(int source, int destination)
{

    int parent[V];

    if (ShorBFS(source, destination, parent) == false)
    {
        cout << "Destination is not reachable from this source.\n";
        return;
    }

    stack<int> st;

    while (parent[destination] != -1)
    {
        st.push(destination);
        destination = parent[destination];
    }

    cout << source;
    while (!st.empty())
    {
        cout << " -> " << st.top();
        st.pop();
    }
    return;
}

int main()
{
    int V = 4;
    int E = 5;
    Graph1 *graph = createGraph(V, E);

    // add edge 0-1
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

    KruskalMST(graph);
    return 0;
}
