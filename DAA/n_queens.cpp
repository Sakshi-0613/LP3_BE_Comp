//-------------------------------------------------------------
// N-Queens Problem using Backtracking
// (with first Queen placed in a fixed column)
//-------------------------------------------------------------

#include <iostream>
using namespace std;

int n, fixedCol; 
int col[20] = {0}, d1[40] = {0}, d2[40] = {0}, board[20][20] = {0};

bool solve(int r) {
    // Base condition: all queens placed
    if (r == n)
        return true;

    // Place the first queen in the fixed column
    if (r == 0) {
        col[fixedCol] = d1[r + fixedCol] = d2[r - fixedCol + n] = 1;
        board[r][fixedCol] = 1;
        return solve(r + 1);
    }

    // Try placing queen in each column for this row
    for (int c = 0; c < n; c++) {
        if (!col[c] && !d1[r + c] && !d2[r - c + n]) 
        {
            // Place queen
            col[c] = d1[r + c] = d2[r - c + n] = 1;
            
            board[r][c] = 1;

            // Recur for next row
            if (solve(r + 1))
                return true;

            // Backtrack
            col[c] = d1[r + c] = d2[r - c + n] = 0;
            board[r][c] = 0;
        }
    }
    return false;
}

int main() {
    cout << "Enter N: ";
    cin >> n;

    cout << "Enter the column (0 to n-1) for first queen: ";
    cin >> fixedCol;

    if (solve(0)) {
        cout << "\nN-Queens Solution:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << "\n";
        }
    } else {
        cout << "\nNo solution possible!\n";
    }

    return 0;
}
