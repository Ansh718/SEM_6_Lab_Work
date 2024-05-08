#include <bits/stdc++.h>
using namespace std;
bool solution(int x, int y, int z)
{
    if ((x + y) < z)
    {
        return false;
    }
    vector<int> operations = {x, -x, y, -y};
    set<int> visited;
    queue<int> q;
    visited.insert(0);
    q.push(0);
    while (!q.empty())
    {
        int temp = q.front();
        q.pop();
        for (int op : operations)
        {
            int total = temp + op;
            if (total == z)
            {
                return true;
            }
            else if (total < 0 || total > x + y)
            {
                continue;
            }
            else
            {
                if (visited.find(total) == visited.end())
                {
                    visited.insert(total);
                    q.push(total);
                }
            }
        }
    }
    return false;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int jug1_capacity = 0;
    int jug2_capacity = 0;
    int to_be_measured = 0;
    cout << "\nEnter the capacity of Jug 1 :-> " << endl;
    cin >> jug1_capacity;
    cout << "\nEnter the capacity of Jug 2 :-> " << endl;
    cin >> jug2_capacity;
    cout << "\nEnter the quantity of water you wish to measure :-> " << endl;
    cin >> to_be_measured;
    cout << solution(jug1_capacity, jug2_capacity, to_be_measured);
    return 0;
}