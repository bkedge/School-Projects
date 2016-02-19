// Brady Kedge
// 02-08-16
//Project 1 - Part B
//Recursive function for Fibonacci
	#include <iostream>
	using namespace std;

	int FibonacciIteration(int n);

	int main()
	{
		int n;
        
        //Enter n
        cout << "Enter Nth term of Fibonnaci: ";
        cin >> n;
        //Gets n
        cout << FibonacciIteration(n) << endl;
        
        //Pause
        cin.get();

		return 0;
	}

    //Iterative Method
	int FibonacciIteration(int n)
    {
        if (n == 1)
            return 1;
        if (n == 0)
            return 0;
        
        int n1 = 0;
        int n2 = 1;
        int addition = 0;
        
        for (int i=0; i < n-1; i++)
        {
            addition = n2 + n1;
            n1 = n2;
            n2 = addition;
        }
        
        return addition;
    }
