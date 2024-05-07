#include <bits/stdc++.h>
using namespace std;
const int N = 3;

class PuzzleState
{
public:
    vector<vector<int>> puzzle;
    int zeroRow;
    int zeroCol;
    int g;
    int h;

    bool operator<(const PuzzleState &other) const
    {
        return (g + h) > (other.g + other.h);
    }

    void printPuzzle() const
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << puzzle[i][j] << " ";
            }
            cout << endl;
        }
        cout << "-----\n";
    }

    bool isEqual(const PuzzleState &state2) const
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (puzzle[i][j] != state2.puzzle[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
};

class PuzzleSolver
{
public:
    int calculateManhattanDistance(const PuzzleState &state)
    {
        int distance = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int val = 0;
                val = state.puzzle[i][j];
                if (val != 0)
                {
                    int targetRow = 0;
                    targetRow = (val - 1) / N;
                    int targetCol = 0;
                    targetCol = (val - 1) % N;
                    distance += (abs(i - targetRow) + abs(j - targetCol));
                }
            }
        }
        return distance;
    }

    bool isValid(int row, int col)
    {
        return (row >= 0 && row < N && col >= 0 && col < N);
    }

    vector<PuzzleState> generateNextState(const PuzzleState &current)
    {
        vector<PuzzleState> nextStates;
        const int moves[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        for (int k = 0; k < 4; k++)
        {
            int nextZeroRow = 0;
            nextZeroRow = current.zeroRow + moves[k][0];
            int nextZeroCol = 0;
            nextZeroCol = current.zeroCol + moves[k][1];
            if (isValid(nextZeroRow, nextZeroCol))
            {
                PuzzleState next = current;
                swap(next.puzzle[current.zeroRow][current.zeroCol], next.puzzle[nextZeroRow][nextZeroCol]);
                next.zeroRow = nextZeroRow;
                next.zeroCol = nextZeroCol;
                next.g = current.g + 1;
                next.h = calculateManhattanDistance(next);
                nextStates.push_back(next);
            }
        }
        return nextStates;
    }

    void aStarSearch(const PuzzleState &initialState, const PuzzleState &finalState)
    {
        priority_queue<PuzzleState> pQ;
        unordered_set<int> visited;
        pQ.push(initialState);
        while (!(pQ.empty()))
        {
            PuzzleState current = pQ.top();
            pQ.pop();
            cout << "Current State:\n";
            current.printPuzzle();
            cout << "Number of moves: " << current.g << endl;
            cout << "Heuristic cost: " << current.h << endl;
            cout << "-------------------\n";
            if (current.isEqual(finalState))
            {
                cout << "Goal State Reached!\n";
                cout << "Number of moves: " << current.g << endl;
                cout << "Heuristic cost: " << current.h << endl;
                break;
            }
            vector<PuzzleState> nextStates = generateNextState(current);
            for (const PuzzleState &next : nextStates)
            {
                int chc = 0;
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        chc = chc * 10 + next.puzzle[i][j];
                    }
                }
                if (visited.find(chc) == visited.end())
                {
                    pQ.push(next);
                    visited.insert(chc);
                }
            }
        }
    }

    PuzzleState getPuzzleState(const string &p)
    {
        PuzzleState st;
        st.puzzle.resize(N, vector<int>(N));
        cout << p << " (0 represents the empty tile):\n";
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << "Enter value at position (" << i << ", " << j << "): ";
                cin >> st.puzzle[i][j];
                if (st.puzzle[i][j] == 0)
                {
                    st.zeroRow = i;
                    st.zeroCol = j;
                }
            }
        }
        st.g = 0;
        st.h = calculateManhattanDistance(st);
        return st;
    }
};

int main()
{
    PuzzleSolver solver;

    PuzzleState initialState = solver.getPuzzleState("Enter the initial state of the puzzle");
    PuzzleState finalState = solver.getPuzzleState("Enter the final state of the puzzle");

    cout << "Initial State:\n";
    initialState.printPuzzle();

    solver.aStarSearch(initialState, finalState);

    return 0;
}
/*
Enter the initial state of the puzzle (0 represents the empty tile):
Enter value at position (0, 0): 0
Enter value at position (0, 1): 1
Enter value at position (0, 2): 2
Enter value at position (1, 0): 4
Enter value at position (1, 1): 6
Enter value at position (1, 2): 3
Enter value at position (2, 0): 7
Enter value at position (2, 1): 5
Enter value at position (2, 2): 8
Enter the final state of the puzzle (0 represents the empty tile):
Enter value at position (0, 0): 1
Enter value at position (0, 1): 2
Enter value at position (0, 2): 3
Enter value at position (1, 0): 4
Enter value at position (1, 1): 5
Enter value at position (1, 2): 6
Enter value at position (2, 0): 7
Enter value at position (2, 1): 8
Enter value at position (2, 2): 0
Initial State:
0 1 2
4 6 3
7 5 8
-----
Current State:
0 1 2
4 6 3
7 5 8
-----
Number of moves: 0
Heuristic cost: 6
-------------------
Current State:
1 0 2
4 6 3
7 5 8
-----
Number of moves: 1
Heuristic cost: 5
-------------------
Current State:
1 2 0
4 6 3
7 5 8
-----
Number of moves: 2
Heuristic cost: 4
-------------------
Current State:
1 2 3
4 6 0
7 5 8
-----
Number of moves: 3
Heuristic cost: 3
-------------------
Current State:
1 2 3
4 0 6
7 5 8
-----
Number of moves: 4
Heuristic cost: 2
-------------------
Current State:
1 2 3
4 5 6
7 0 8
-----
Number of moves: 5
Heuristic cost: 1
-------------------
Current State:
1 2 3
4 5 6
7 8 0
-----
Number of moves: 6
Heuristic cost: 0
-------------------
Goal State Reached!
Number of moves: 6
Heuristic cost: 0
*/