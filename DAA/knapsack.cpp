//-------------------------------------------------------------
// Fractional Knapsack Problem using Greedy Method
// (No Built-in Sort, Functions Used)
//-------------------------------------------------------------

#include <iostream>
using namespace std;

//-------------------------------------------------------------
// Structure for Item (weight, value, and value/weight ratio)
//-------------------------------------------------------------
struct Item 
{
    float wt;
    float val;
    float ratio;
};

//-------------------------------------------------------------
// Function to input all items and compute ratio
//-------------------------------------------------------------
void inputItems(Item a[], int n) 
{
    cout << "Enter weight and value of each item:\n";
    for (int i = 0; i < n; i++) 
    {
        cin >> a[i].wt >> a[i].val;
        a[i].ratio = a[i].val / a[i].wt; // compute value/weight ratio
    }
}

//-------------------------------------------------------------
// Function to manually sort items by ratio in descending order
//-------------------------------------------------------------
void sortItemsByRatio(Item a[], int n) 
{
    // simple bubble sort (no built-in sort)
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (a[i].ratio < a[j].ratio) 
            {
                Item temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

//-------------------------------------------------------------
// Function to display items (for verification)
//-------------------------------------------------------------
void displayItems(Item a[], int n) 
{
    cout << "\nItems sorted by value/weight ratio:\n";
    cout << "Weight\tValue\tRatio\n";
    for (int i = 0; i < n; i++) 
    {
        cout << a[i].wt << "\t" << a[i].val << "\t" << a[i].ratio << endl;
    }
}

//-------------------------------------------------------------
// Function to apply Fractional Knapsack Greedy Method
//-------------------------------------------------------------
float fractionalKnapsack(Item a[], int n, float capacity) 
{
    float profit = 0.0;
    float W = capacity;

    cout << "\nItems taken:\n";

    for (int i = 0; i < n; i++) 
    {
        if (W == 0)
            break;

        if (a[i].wt <= W) 
        {
            // take the full item
            W -= a[i].wt;
            profit += a[i].val;
            cout << "Took full item (w=" << a[i].wt << ", v=" << a[i].val << ")\n";
        } else 
        {
            // take a fractional part
            float fraction = W / a[i].wt;
            profit += (a[i].val * fraction);
            cout << "Took " << fraction * 100 << "% of item (w=" 
                 << a[i].wt << ", v=" << a[i].val << ")\n";
            W = 0; // knapsack is full
        }
    }

    return profit;
}

//-------------------------------------------------------------
// Main Function
//-------------------------------------------------------------
int main() 
{
    int n;
    float capacity;
    Item a[20]; // assuming max 20 items for simplicity

    cout << "Enter number of items: ";
    cin >> n;

    inputItems(a, n);

    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    sortItemsByRatio(a, n);
    displayItems(a, n);

    float maxProfit = fractionalKnapsack(a, n, capacity);

    cout << "\nMaximum Profit = " << maxProfit << endl;

    return 0;
}
