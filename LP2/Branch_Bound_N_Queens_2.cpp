#include <bits/stdc++.h>
using namespace std;

void branchAndBound(int column, int n, vector<string> &chessboard, vector<bool> &right_diagonals, vector<bool> &left_diagonals, vector<bool> &rows, vector<vector<string>> &result)
{
    if (column == n)
    {
        result.push_back(chessboard);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (!(rows[i]) && !(right_diagonals[(n - 1) + (column - i)]) && !(left_diagonals[(i + column)]))
        {
            rows[i] = true;
            right_diagonals[(n - 1) + (column - i)] = true;
            left_diagonals[(i + column)] = true;
            chessboard[i][column] = 'Q';
            branchAndBound(column + 1, n, chessboard, right_diagonals, left_diagonals, rows, result);
            rows[i] = false;
            right_diagonals[(n - 1) + (column - i)] = false;
            left_diagonals[(i + column)] = false;
            chessboard[i][column] = '.';
        }
    }
}

int main()
{
    int n = 0;
    cout << "\nEnter the number of queens :-> " << endl;
    cin >> n;
    vector<string> chessboard(n, string(n, '.'));
    vector<vector<string>> result;
    vector<bool> left_diagonals(2 * n - 1, false);
    vector<bool> right_diagonals(2 * n - 1, false);
    vector<bool> rows(n, false);
    branchAndBound(0, n, chessboard, right_diagonals, left_diagonals, rows, result);
    cout << "\nTotal possible chessboards are :-> " << result.size() << endl;
    for (int i = 0; i < result.size(); i++)
    {
        cout << "Chessboard " << i + 1 << endl;
        for (int j = 0; j < result[i].size(); j++)
        {
            for (int k = 0; k < result[i][j].size(); k++)
            {
                cout << result[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}