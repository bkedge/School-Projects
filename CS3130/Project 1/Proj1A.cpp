// Brady Kedge
// 02-08-16
//Project 1 - Part A
//Recursive function for Fibonacci
    #include <iostream>
    using namespace std;
    
    //Function Declaration
    int FibonacciRecursive(int n);

    int main()
    {
        int n; //Nth number
        cout << "Enter Nth term of Fibonnaci: ";
        cin >> n;//Enter Number
        cout << FibonacciRecursive(n) << endl; //Displays N

        cin.get();//Pause console

        return 0;
    }
    
    //Recursive Functiob for Fibonacci
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
