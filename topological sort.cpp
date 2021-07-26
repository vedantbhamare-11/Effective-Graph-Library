#include <iostream>
#include <vector>
#include <queue>
using namespace std;
/*
TopologicalSort function takes in 2 parameters. 
    First is an Adjacency List (array of vectors).
    Second is Number of Vertices.
TopologicalSort function returns a vector of type int (vector<int>)
*/
const int numVertices = 6;
int source;
vector<bool> visitedVertex(numVertices, false);
vector<int> inDegree(numVertices, 0);
vector<int> T;

void createAndAddEdge(vector<int> adjList[], int u, int v)
{
    adjList[u].push_back(v);
}

vector<int> TopologicalSort(vector<int> adjList[], int numVertices)
{
    queue<int> Q;
    int v;

    for (int i = 0; i < numVertices; i++)
        for (vector<int>::iterator it = adjList[i].begin(); it != adjList[i].end(); it++)
            inDegree.at(*it)++;

    for (int i = 0; i < numVertices; i++)
        if (inDegree.at(i) == 0)
        {
            source = i;
            Q.push(source);
            visitedVertex.at(source) = true;
            break;
        }

    while (!Q.empty())
    {
        v = Q.front();
        Q.pop();
        T.push_back(v);

        for (vector<int>::iterator it = adjList[v].begin(); it != adjList[v].end(); it++)
            if (!visitedVertex.at(*it))
            {
                inDegree.at(*it)--;
                if (inDegree.at(*it) == 0)
                {
                    Q.push(*it);
                    visitedVertex.at(*it) = true;
                }
            }
    }
    return T;
}

int main(void)
{
    vector<int> adjList[numVertices];
    createAndAddEdge(adjList, 0, 1);
    createAndAddEdge(adjList, 0, 3);
    createAndAddEdge(adjList, 1, 2);
    createAndAddEdge(adjList, 1, 3);
    createAndAddEdge(adjList, 2, 3);
    createAndAddEdge(adjList, 2, 4);
    createAndAddEdge(adjList, 2, 5);
    createAndAddEdge(adjList, 3, 4);
    createAndAddEdge(adjList, 3, 5);
    createAndAddEdge(adjList, 4, 5);
    vector<int> a = TopologicalSort(adjList, 6);
    cout << "Topological Sort for the given Directed Acyclic Graph: ";
    for (int i = 0; i < T.size(); i++)
        cout << T.at(i) << " ";
    cout << endl;
}