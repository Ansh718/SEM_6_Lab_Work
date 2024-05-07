#include <bits/stdc++.h>
using namespace std;

template <class T>
class Stack
{
private:
    int top;
    vector<T> arr;

public:
    Stack();
    bool isFull();
    bool isEmpty();
    void push(T);
    T pop();
};

template <class T>
Stack<T>::Stack() : top(-1), arr(20) {}

template <class T>
bool Stack<T>::isFull()
{
    return top == 19;
}

template <class T>
bool Stack<T>::isEmpty()
{
    return top == -1;
}

template <class T>
void Stack<T>::push(T x)
{
    if (!(isFull()))
    {
        arr[++top] = x;
    }
}

template <class T>
T Stack<T>::pop()
{
    if (!(isEmpty()))
    {
        return arr[top--];
    }
    return T();
}

template <class T>
class Queue
{
private:
    int front;
    int rear;
    vector<T> arr;

public:
    Queue();
    bool isFull();
    bool isEmpty();
    T frontElement();
    void push(T);
    T pop();
};

template <class T>
Queue<T>::Queue() : front(-1), rear(-1), arr(20) {}

template <class T>
bool Queue<T>::isFull()
{
    return rear == 19;
}

template <class T>
bool Queue<T>::isEmpty()
{
    return front == rear && rear == -1;
}

template <class T>
T Queue<T>::frontElement()
{
    return arr[front];
}

template <class T>
void Queue<T>::push(T x)
{
    if (!(isFull()))
    {
        if (isEmpty())
        {
            front++;
        }
        arr[++rear] = x;
    }
}

template <class T>
T Queue<T>::pop()
{
    if (!isEmpty())
    {
        T answer = arr[front];
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front++;
        }
        return answer;
    }
    return T();
}

class Node
{
private:
    Node *next;
    int dst;

public:
    Node();
    Node(int);
    friend class Graph;
};

Node::Node() : next(NULL) {}

Node::Node(int dst) : dst(dst), next(NULL) {}

class Graph
{
private:
    int nV;
    int nE;
    vector<int> visited;
    vector<string> name;
    vector<Node *> adjacencyList;

public:
    Graph();
    Graph(int, int);
    void create();
    void display();
    void reset();
    void dfsR(int, int);
    void dfs(int);
    void bfsR(Queue<pair<int, int>> &);
    void bfs(int);
};

Graph::Graph() {}

Graph::Graph(int nV, int nE) : nV(nV), nE(nE), visited(nV), name(nV), adjacencyList(nV, NULL)
{
    for (int i = 0; i < nV; i++)
    {
        visited[i] = 0;
        name[i] = "default";
    }
}

void Graph::create()
{
    for (int i = 0; i < nV; i++)
    {
        cout << "\n Enter the name of Landmark :-> " << endl;
        cin >> name[i];
    }
    for (int i = 0; i < nE; i++)
    {
        int src = 0;
        int dst = 0;
        cout << "\n Enter the source :-> " << endl;
        cin >> src;
        cout << "\n Enter the destination :-> " << endl;
        cin >> dst;
        Node *dstNode = new Node(dst);
        if (adjacencyList[src] == NULL)
        {
            adjacencyList[src] = dstNode;
        }
        else
        {
            Node *pointerToAdjacencyList = adjacencyList[src];
            while (pointerToAdjacencyList->next != NULL)
            {
                pointerToAdjacencyList = pointerToAdjacencyList->next;
            }
            pointerToAdjacencyList->next = dstNode;
        }
    }
}

void Graph::display()
{
    for (int i = 0; i < nV; i++)
    {
        cout << name[i] << " :-> ";
        Node *pointerToAdjacencyList = adjacencyList[i];
        while (pointerToAdjacencyList != NULL)
        {
            cout << name[pointerToAdjacencyList->dst] << " :-> ";
            pointerToAdjacencyList = pointerToAdjacencyList->next;
        }
        cout << '\n';
    }
}

void Graph::dfsR(int src, int level)
{
    cout << name[src] << "(Level :-> " << level << ")"
         << " :-> "
         << " ";
    visited[src] = 1;
    Node *pointerToAdjacencyList = adjacencyList[src];
    while (pointerToAdjacencyList != NULL)
    {
        int w = pointerToAdjacencyList->dst;
        if (visited[w] == 0)
        {
            dfsR(w, level + 1);
        }
        pointerToAdjacencyList = pointerToAdjacencyList->next;
    }
}

void Graph::dfs(int src)
{
    Stack<int> s;
    s.push(src);
    visited[src] = 1;
    while (!s.isEmpty())
    {
        int chc = 0;
        chc = s.pop();
        cout << name[chc] << " :-> ";
        Node *pointerToAdjacencyList = adjacencyList[chc];
        while (pointerToAdjacencyList != NULL)
        {
            int w = pointerToAdjacencyList->dst;
            if (visited[w] == 0)
            {
                visited[w] = 1;
                s.push(w);
            }
            pointerToAdjacencyList = pointerToAdjacencyList->next;
        }
    }
}

void Graph::bfsR(Queue<pair<int, int>> &q)
{
    if (q.isEmpty())
    {
        return;
    }
    pair<int, int> vertex = q.pop();
    int v1 = 0;
    int v2 = 0;
    v1 = vertex.first;
    v2 = vertex.second;
    cout << name[v1] << "(Level :-> " << v2 << ")"
         << " :-> "
         << " ";
    Node *pointerToAdjacencyList = adjacencyList[v1];
    while (pointerToAdjacencyList != NULL)
    {
        int w = pointerToAdjacencyList->dst;
        if (visited[w] == 0)
        {
            visited[w] = 1;
            q.push({w, v2 + 1});
        }
        pointerToAdjacencyList = pointerToAdjacencyList->next;
    }
    bfsR(q);
}

void Graph::bfs(int src)
{
    Queue<int> q;
    q.push(src);
    visited[src] = 1;
    while (!q.isEmpty())
    {
        int chc = 0;
        chc = q.pop();
        cout << name[chc] << " :-> ";
        Node *pointerToAdjacencyList = adjacencyList[chc];
        while (pointerToAdjacencyList != NULL)
        {
            int w = pointerToAdjacencyList->dst;
            if (visited[w] == 0)
            {
                visited[w] = 1;
                q.push(w);
            }
            pointerToAdjacencyList = pointerToAdjacencyList->next;
        }
    }
}

void Graph::reset()
{
    fill(visited.begin(), visited.end(), 0);
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
        cout << " 3. DFS " << endl;
        cout << " 4. DFS Recursive" << endl;
        cout << " 5. BFS " << endl;
        cout << " 6. BFS Recursive" << endl;
        cout << " 7. Exit" << endl;
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
            g.reset();
            cout << "Enter the vertex which you want to start from :";
            cin >> start;
            g.dfs(start);
        }
        else if (chc == 4)
        {
            g.reset();
            cout << "Enter the vertex which you want to start from :";
            cin >> start;
            g.dfsR(start, 0);
        }
        else if (chc == 5)
        {
            g.reset();
            cout << "Enter the vertex which you want to start from :";
            cin >> start;
            g.bfs(start);
        }
        else if (chc == 6)
        {
            g.reset();
            cout << "Enter the vertex which you want to start from :";
            cin >> start;
            Queue<pair<int, int>> q;
            q.push({start, 0});
            g.bfsR(q);
        }
        else if (chc == 7)
        {
            break;
        }
    }
    return 0;
}
