#include <bits/stdc++.h>
using namespace std;
const int N = 3;

class PuzzleState
{
public:
    vector<vector<int>> puzzle;
    int zeroR;
    int zeroC;
    int g;
    int h;

    bool operator<(const PuzzleState &ps) const
    {
        return ((g + h) < (ps.g + ps.h));
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

    bool isEqual(const PuzzleState &ps) const
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (puzzle[i][j] != ps.puzzle[i][j])
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
    int heuristic(const PuzzleState &ps) const
    {
        int distance = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int data = 0;
                data = ps.puzzle[i][j];
                if (data != 0)
                {
                    int targetR = 0;
                    int targetC = 0;
                    targetR = (data - 1) / N;
                    targetC = (data - 1) % N;
                    distance += (abs(i - targetR) + abs(j - targetC));
                }
            }
        }
        return distance;
    }

    bool isValid(int row, int column) const
    {
        return (row >= 0 && row < N && column >= 0 && column < N);
    }

    vector<PuzzleState> generateNextStates(const PuzzleState &ps) const
    {
        vector<PuzzleState> result;
        const int moves[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        for (int k = 0; k < 4; k++)
        {
            int nextZR = 0;
            int nextZC = 0;
            nextZR = ps.zeroR + moves[k][0];
            nextZC = ps.zeroC + moves[k][1];
            if (isValid(nextZR, nextZC))
            {
                PuzzleState nxt = ps;
                swap(nxt.puzzle[ps.zeroR][ps.zeroC], nxt.puzzle[nextZR][nextZC]);
                nxt.zeroR = nextZR;
                nxt.zeroC = nextZC;
                nxt.g = ps.g + 1;
                nxt.h = heuristic(nxt);
                result.push_back(nxt);
            }
        }
        return result;
    }

    void aStarSearch(const PuzzleState &ips, const PuzzleState &fps) const
    {
        priority_queue<PuzzleState> pQ;
        unordered_set<int> visited;
        pQ.push(ips);
        while (!(pQ.empty()))
        {
            PuzzleState current = pQ.top();
            pQ.pop();
            cout << "\nCurrent State :-> " << endl;
            ips.printPuzzle();
            cout << "\nNumber of moves: " << current.g << endl;
            cout << "\nHeuristic cost: " << current.h << endl;
            cout << "-------------------\n";
            if (current.isEqual(fps))
            {
                cout << "\nGoal State Reached!" << endl;
                cout << "\nNumber of moves: " << current.g << endl;
                cout << "\nHeuristic cost: " << current.h << endl;
                break;
            }
            vector<PuzzleState> nextOptions = generateNextStates(current);
            for (const PuzzleState nxt : nextOptions)
            {
                int chc = 0;
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        chc = chc * 10 + nxt.puzzle[i][j];
                    }
                }
                if (visited.find(chc) == visited.end())
                {
                    pQ.push(nxt);
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
                    st.zeroR = i;
                    st.zeroC = j;
                }
            }
        }
        st.g = 0;
        st.h = heuristic(st);
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
// /*
// Enter the initial state of the puzzle (0 represents the empty tile):
// Enter value at position (0, 0): 0
// Enter value at position (0, 1): 1
// Enter value at position (0, 2): 2
// Enter value at position (1, 0): 4
// Enter value at position (1, 1): 6
// Enter value at position (1, 2): 3
// Enter value at position (2, 0): 7
// Enter value at position (2, 1): 5
// Enter value at position (2, 2): 8
// Enter the final state of the puzzle (0 represents the empty tile):
// Enter value at position (0, 0): 1
// Enter value at position (0, 1): 2
// Enter value at position (0, 2): 3
// Enter value at position (1, 0): 4
// Enter value at position (1, 1): 5
// Enter value at position (1, 2): 6
// Enter value at position (2, 0): 7
// Enter value at position (2, 1): 8
// Enter value at position (2, 2): 0
// Initial State:
// 0 1 2
// 4 6 3
// 7 5 8
// -----
// Current State:
// 0 1 2
// 4 6 3
// 7 5 8
// -----
// Number of moves: 0
// Heuristic cost: 6
// -------------------
// Current State:
// 1 0 2
// 4 6 3
// 7 5 8
// -----
// Number of moves: 1
// Heuristic cost: 5
// -------------------
// Current State:
// 1 2 0
// 4 6 3
// 7 5 8
// -----
// Number of moves: 2
// Heuristic cost: 4
// -------------------
// Current State:
// 1 2 3
// 4 6 0
// 7 5 8
// -----
// Number of moves: 3
// Heuristic cost: 3
// -------------------
// Current State:
// 1 2 3
// 4 0 6
// 7 5 8
// -----
// Number of moves: 4
// Heuristic cost: 2
// -------------------
// Current State:
// 1 2 3
// 4 5 6
// 7 0 8
// -----
// Number of moves: 5
// Heuristic cost: 1
// -------------------
// Current State:
// 1 2 3
// 4 5 6
// 7 8 0
// -----
// Number of moves: 6
// Heuristic cost: 0
// -------------------
// Goal State Reached!
// Number of moves: 6
// Heuristic cost: 0
// */
