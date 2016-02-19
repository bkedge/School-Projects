// Brady Kedge
// 02-09-16
//Project 1 - Part C
//Time comparing program

    #include <iostream>
    #include <sys/time.h>

    using namespace std;
    
    int FibonacciRecursive(int n);
    int FibonacciIteration(int n);
    
    int main()
    {
        int n;
        hrtime_t start, end, total;
        
        cout << "Enter the Nth number of Fibonacci you want to find: ";
        cin >> n;
        
        //Recursive method
        start = gethrtime();
        FibonacciRecursive(n);
        end = gethrtime();
        total = end - start;
        //Time Calculation
        cout << "Time for Recursive method: " << endl;
        //Start
        cout << "    Start: " << start << endl;
        //End
        cout << "    End: " << end << endl;
        //Total
        cout << "    Total Time: " << total << endl;
        
        
        //Iterative method
        start = gethrtime();
        FibonacciIteration(n);
        end = gethrtime();
        //Time Calculation
        total = end - start;
        cout << "Time for Iterative method: " << endl;
        //Start
        cout << "    Start: " << start << endl;
        //End
        cout << "    End: " << end << endl;
        //Total
        cout << "    Total Time: " << total << endl;
        
        return 0;
        
        
        
        
    }
    
    int FibonacciRecursive(int n)
    {
        //Base cases
        if (n == 1)
            return 1;
        if (n == 0)
            return 0;
        //Recursive function
        return FibonacciRecursive(n - 1) + FibonacciRecursive(n - 2);
    }
    
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
