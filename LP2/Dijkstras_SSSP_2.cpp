#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
    int n;
    vector<vector<pair<int, int>>> adjacencyMatrix;
    vector<int> distance;
    vector<int> parent;

public:
    Graph(int);
    void addEdge(int, int, int);
    void dijkstra(int);
    void printShortestPaths();
};

Graph::Graph(int n) : n(n), adjacencyMatrix(n), distance(n, INT_MAX), parent(n, -1) {}

void Graph::addEdge(int u, int v, int w)
{
    adjacencyMatrix[u].push_back({v, w});
    adjacencyMatrix[v].push_back({u, w});
}

void Graph::dijkstra(int src)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distance[src] = 0;
    pq.push({0, src});
    int node, child, weight;
    while (!pq.empty())
    {
        int dist = pq.top().first;
        node = pq.top().second;
        pq.pop();
        for (auto i : adjacencyMatrix[node])
        {
            child = i.first;
            weight = i.second;
            if (dist + weight < distance[child])
            {
                distance[child] = dist + weight;
                parent[child] = node;
                pq.push({dist + weight, child});
            }
        }
    }
}

void Graph::printShortestPaths()
{
    for (int i = 0; i < n; i++)
    {
        vector<int> path;
        int dst = i;
        while (dst != -1)
        {
            path.push_back(dst);
            dst = parent[dst];
        }
        reverse(path.begin(), path.end());
        cout << "Shortest Distance for node " << i << " from node 0 is with distance : " << distance[i] << endl;
        cout << "Shortest Path for node " << i << " from node 0 is : [ ";
        for (int j = 0; j < path.size(); j++)
        {
            cout << path[j] << " -> ";
        }
        cout << "]" << endl;
    }
}

int main()
{
    int n, e;
    cout << "Enter the Number of Vertex :-> ";
    cin >> n;
    Graph g(n);
    cout << "Enter the Number of edges :-> ";
    cin >> e;
    int u, v, w;
    for (int i = 0; i < e; i++)
    {
        cout << "Enter Edge as source, destination and weight :-> " << endl;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    int src;
    cout << "Enter source vertex :-> ";
    cin >> src;
    g.dijkstra(src);
    g.printShortestPaths();
    return 0;
}
