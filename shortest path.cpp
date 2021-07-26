#include <iostream>
#include <stdlib.h>
#include <list>
#include <stack>

using namespace std;

class Graph
{
    int V;
    list<int> *adj;

public:
    Graph(int V);
    void addEdge(int v, int w);
    bool BFS(int source, int destination, int parent[]);
    void shortest_path(int source, int destination);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

bool Graph::BFS(int source, int destination, int parent[])
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
    // it stores parent for each vertex to trace the path.
    int parent[V];
    // BFS returns false means destination is not reachable.
    if (BFS(source, destination, parent) == false)
    {
        cout << "Destination is not reachable from this source.\n";
        return;
    }
    // stack to store the shortest path.
    stack<int> st;
    // tracing the path.
    while (parent[destination] != -1)
    {
        st.push(destination);
        destination = parent[destination];
    }
    // printing the path.
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
    int source, edge, vertices, i, v, w, s, d;
    cout << "\n Enter the number of vertices: ";
    cin >> vertices;
    Graph g(vertices);
    cout << "\n Enter the number of edges: ";
    cin >> edge;
    for (i = 1; i <= edge; i++)
    {
        cout << "\n Enter the connection " << i << ": ";
        cin >> v >> w;
        g.addEdge(v, w);
    }
    cout << "\n Enter the source and destination vertex: ";
    cin >> s >> d;
    g.shortest_path(s, d);

    return 0;
}
