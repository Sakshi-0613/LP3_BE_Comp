#include<iostream>
using namespace std;

long long call_count = 0;   // counts recursive calls

// Recursive Fibonacci (exponential complexity)
long long fib(int n)
{
    call_count++;   // count each function call
    
    if(n <= 1)
        return n;
    return fib(n-1) + fib(n-2);
}

// Iterative Fibonacci (linear complexity)
long long fib_iter(int n, long long &steps)
{
    steps = 0;           // count loop operations
    int a = 0, b = 1, c;
    
    if(n == 0) return a;
    if(n == 1) return b;

    for(int i = 2; i <= n; i++)
    {
        steps++;         // count each step
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;

    cout << "\nRecursive Fibonacci Series:\n";
    for(int i = 0; i < n; i++)
    {
        call_count = 0;
        long long result = fib(i);
        cout << "fib(" << i << ") = " << result 
             << " | Calls = " << call_count 
             << " | Approx Complexity ~ 2^" << i << endl;
    }

    cout << "\nIterative Fibonacci Series:\n";
    long long steps;
    for(int i = 0; i < n; i++)
    {
        long long result = fib_iter(i, steps);
        cout << "fib(" << i << ") = " << result 
             << " | Steps = " << steps 
             << " | Complexity = O(n)" << endl;
    }

    return 0;
}
