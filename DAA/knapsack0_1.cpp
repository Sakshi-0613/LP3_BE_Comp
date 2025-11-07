//-------------------------------------------------------------
// 0-1 Knapsack Problem using Dynamic Programming
// (No Built-in Functions, Simple Structure)
//-------------------------------------------------------------

#include <iostream>
using namespace std;

//-------------------------------------------------------------
// Function to input item weights and values
//-------------------------------------------------------------
void inputItems(int wt[], int val[], int n)
{
    cout << "Enter weight and value of each item:\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "Item " << i << ": ";
        cin >> wt[i] >> val[i];
    }
}

//-------------------------------------------------------------
// Function to solve 0-1 Knapsack using Dynamic Programming
//-------------------------------------------------------------
int knapsackDP(int wt[], int val[], int n, int W)
{
    int dp[25][2000]; // assuming max 20 items and capacity for simplicity

    // Initialize DP table
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i] <= w)
            {
                int take = val[i] + dp[i - 1][w - wt[i]];
                int notake = dp[i - 1][w];
                dp[i][w] = (take > notake) ? take : notake;
            }
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Print the DP Table (for understanding)
    cout << "\nDP Table:\n";
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
            cout << dp[i][w] << "\t";
        cout << endl;
    }

    // Backtracking to find selected items
    cout << "\nItems selected (item_index : weight, value):\n";
    int w = W;
    for (int i = n; i > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            cout << "Item " << i << " : " << wt[i] << ", " << val[i] << endl;
            w -= wt[i];
        }
    }

    return dp[n][W]; // return max profit
}

//-------------------------------------------------------------
// Main Function
//-------------------------------------------------------------
int main()
{
    int n, W;
    int wt[20], val[20]; // limit to 20 items for simplicity

    cout << "Enter number of items: ";
    cin >> n;

    inputItems(wt, val, n);

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    int maxProfit = knapsackDP(wt, val, n, W);

    cout << "\nMaximum Profit = " << maxProfit << endl;

    return 0;
}
