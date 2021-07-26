#include "graph-lib.h"

int main()
{
    int vertices;
    int v, w, edge, s, d, c;
    cout << "\n Enter the number of vertices: ";
    cin >> vertices;
    cout << "\n Enter the number of edges: ";
    cin >> edge;
    Graph g(vertices);
    WeightedGraph *graph = createGraph(vertices, edge); //limitation 1
    int **edges = new int *[vertices];
    x: int choice = 0;
    while (1)
    {
        cout <<"\n\t____GRAPH LIBRARY____\n";
        cout << "\n 1. BFS\n 2. Directed graph cycle detection.\n 3. Undirected graph cycle detection\n 4. MST\n 5. Shortest Path(BFS)\n 6. DFS\n 7. Dijkstra's\n 8. Topological sort\n";
        cout <<"\n\nEnter your choice from the above list please: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            for (int i = 1; i <= edge; i++)
            {
                cout << "\nEnter the connection " << i << ": ";
                cin >> v >> w;
                g.addEdge(v, w);
            }
            cout << "\nEnter the source vertex: ";
            cin >> s;
            cout << "\nBreadth First Traversal is: ";
            g.BFS(s);
            cout << "\n";
            break;
        case 2:
            for (int i = 1; i <= edge; i++)
            {
                cout << "\nEnter the connection " << i << ": ";
                cin >> v >> w;
                g.addDirectedEdge(v, w);
            }
            if (g.isCyclic())
                cout << "\nGraph contains cycle.";
            else
                cout << "\nGraph does not contain cycle.";
            break;
        case 3:
            for (int i = 1; i <= edge; i++)
            {
                cout << "\nEnter the connection" << i << ":";
                cin >> v >> w;
                g.addDirectedEdge(v, w);
            }
            if (g.isundirCyclic())
                cout << "\nGraph contains cycle.";
            else
                cout << "\nGraph does not contain cycle.";
            break;
        case 4:
            graph->V = vertices;
            graph->E = edge;
            for (int i = 1; i <= edge; i++)
            {
                cout <<"\nEnter the connection " << i << " and edge weight: ";
                int s, d, weight;
                cin >> s >> d >> weight;
                graph->edge[i].src = s;
                graph->edge[i].dest = d;
                graph->edge[i].weight = weight;
            }
            MST(graph);
            break;
        case 5:
            for (int i = 1; i <= edge; i++)
            {
                cout << "\nEnter the connection " << i << ": ";
                cin >> v >> w;
                g.addEdge(v, w);
            }
            cout << "\nEnter the source and destination vertex: ";
            cin >> s >> d;
            g.shortest_path(s, d);
            break;
        case 6:
            for (int i = 1; i <= edge; i++)
            {
                cout << "\nEnter the connection " << i << ": ";
                cin >> v >> w;
                g.addEdge(v, w);
            }
            cout << "\nEnter the source to start traversing\n";
            cin >> s;
            cout << "\nDepth First Traversal is:\n";
            g.DFS(s);
            break;
        case 7:
            for (int i = 0; i < vertices; i++)
            {
                edges[i] = new int[vertices];
                for (int j = 0; j < vertices; j++)
                {
                    edges[i][j] = 0;
                }
            }
            for (int i = 1; i <= edge; i++)
            {
                cout <<"Enter the connection " << i << " and edge weight: ";
                int f, s, weight;
                cin >> f >> s >> weight;
                edges[f][s] = weight;
                edges[s][f] = weight;
            }
            cout << endl;
            cout <<"Shortest path from source vertex 0 is:\n";
            g.dijkstra(edges, vertices);
            break;
        case 8:
            for (int i = 1; i <= edge; i++)
            {
                cout << "\nEnter the connection " << i << ": ";
                cin >> v >> w;
                g.addDirectedEdge(v, w);
            }
            cout << "\nTopological Sort is:\n";
            g.topologicalSort();
            break;
        default:
            break;
        }
        cout << "\n\nDo you wish to continue?(Yes - 1/No - 0): ";
        cin >> c ;
        if(c==1)
            goto x;
        else
            exit(0);
    }
    return 0;
}
