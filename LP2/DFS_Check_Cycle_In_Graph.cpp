#include <bits/stdc++.h>
using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adj;
    bool isCyclicUtil(int v, vector<bool> &visited, int parent)
    {
        visited[v] = true;
        for (int i : adj[v])
        {
            if (!visited[i])
            {
                if (isCyclicUtil(i, visited, v))
                {
                    return true;
                }
            }
            else if (i != parent)
            {
                return true;
            }
        }
        return false;
    }

public:
    Graph(int V) : V(V)
    {
        adj.resize(V);
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u); // Add this line for undirected graph
    }

    bool isCyclic()
    {
        vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i)
        {
            if (!visited[i])
            {
                if (isCyclicUtil(i, visited, -1))
                {
                    return true;
                }
            }
        }
        return false;
    }

    void display()
    {
        cout << "Vertices: " << V << endl;
        cout << "Edges:\n";
        for (int i = 0; i < V; ++i)
        {
            cout << i << " -> ";
            for (int j : adj[i])
            {
                cout << j << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;
    Graph g(V);
    int choice;
    int u, v;
    do
    {
        cout << "\n1. Add Edge\n";
        cout << "2. Check for cycle\n";
        cout << "3. Display Graph\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter edge (u v): ";
            cin >> u >> v;
            g.addEdge(u, v);
            break;
        case 2:
            if (g.isCyclic())
            {
                cout << "Graph contains cycle\n";
            }
            else
            {
                cout << "Graph does not contain cycle\n";
            }
            break;
        case 3:
            g.display();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please enter again.\n";
        }
    } while (choice != 4);
    return 0;
}

// Contains
//  0<->1
//  0<->2
//  1<->2
//  2<->3

// Doesn't Contain
//  0<->1
//  1<->2
//  2<->3