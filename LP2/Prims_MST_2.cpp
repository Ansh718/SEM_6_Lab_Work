#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
    int nV;
    int nE;
    vector<vector<int>> adjMatrix;

public:
    Graph();
    Graph(int, int);
    void create();
    void display();
    void prim();
};

Graph::Graph() {}

Graph::Graph(int nV, int nE) : nV(nV), nE(nE), adjMatrix(nV, vector<int>(nV, 0)) {}

void Graph::create()
{
    int src = 0;
    int dst = 0;
    int weight = 0;
    for (int i = 0; i < nE; i++)
    {
        cout << "\n Enter the edge between :-> " << endl;
        cin >> src >> dst;
        cout << "\n Enter the weight of the edge between " << src << " & " << dst << " :->" << endl;
        cin >> weight;
        adjMatrix[src][dst] = weight;
    }
}

void Graph::display()
{
    for (int i = 0; i < nV; i++)
    {
        for (int j = 0; j < nV; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void Graph::prim()
{
    vector<int> key(nV, 9999);
    vector<int> parent(nV, 1);
    vector<bool> MST(nV, false);
    int cost = 0;
    vector<vector<int>> mst(nV, vector<int>(nV, 0));
    int src = 0;
    cout << "\nEnter source vertex :-> " << endl;
    cin >> src;
    key[src] = 0;
    for (int i = 0; i < nE; i++)
    {
        int min = 0;
        min = 9999;
        int k = 0;
        for (int j = 0; j < nV; j++)
        {
            if (!(MST[j]) && key[j] < min)
            {
                min = key[j];
                k = j;
            }
        }
        MST[k] = true;
        for (int i = 0; i < nV; i++)
        {
            if (adjMatrix[k][i])
            {
                int temp = 0;
                temp = adjMatrix[k][i];
                if (temp < key[i] && !(MST[i]))
                {
                    key[i] = temp;
                    parent[i] = k;
                }
            }
        }
    }
    for (int i = 1; i < nV; i++)
    {
        int p = 0;
        p = parent[i];
        mst[p][i] = key[i];
    }
    cout << "\n Minimum Spanning Tree :-> " << endl;
    for (int i = 0; i < nV; i++)
    {
        for (int j = 0; j < nV; j++)
        {
            cost += mst[i][j];
            cout << mst[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "\nThe minimum cost is:-> " << cost << endl;
}

int main()
{
    int v = 0;
    int e = 0;
    cout << "Enter the no of vertex :" << endl;
    cin >> v;
    cout << "Enter the no of edges :" << endl;
    cin >> e;
    int start;
    Graph g(v, e);
    int chc;
    while (true)
    {
        cout << endl;
        cout << " ------------------Menu------------------ " << endl;
        cout << " 1. Create Graph " << endl;
        cout << " 2. Display Graph " << endl;
        cout << " 3. Prim " << endl;
        cout << " 4. Exit " << endl;
        cout << "Enter the option :-> " << endl;
        cin >> chc;
        if (chc == 1)
        {
            g.create();
        }
        else if (chc == 2)
        {
            g.display();
        }
        else if (chc == 3)
        {
            g.prim();
        }
        else if (chc == 4)
        {
            break;
        }
    }
    return 0;
}
