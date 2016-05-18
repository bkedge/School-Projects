//Brady Kedge
//CS2250
//Reverse Polish Project

#include "stack.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>

using namespace std;

//Prototypes


int main()
{

node *stack = new node;

int s1, s2;

int num;

string user_input;

cout << "Enter an input \n";


while(cin >> user_input)
{	
			if(isdigit(user_input[0]))         //If its a number, push
			{
				num = atoi(user_input.c_str());

				push(num, stack);
			}

			else if(user_input == "+")     //if it is this character add by popping s1 and s2
			{
				s1 = pop(stack);

				s2 = pop(stack);

				push((s1 + s2), stack);
			}

			else if(user_input == "-")  //subtracts
			{
				s1 = pop(stack);

				s2 = pop(stack);

				push((s2 - s1), stack);
			}

			else if(user_input == "*")  //multiplys
			{
				s1 = pop(stack);

				s2 = pop(stack);

				push(((s1) * (s2)), stack);
			}

			else if(user_input == "/")  //divides
			{
				s1 = pop(stack);

				s2 = pop(stack);

				push((s2 / s1), stack);
			}

			else if(user_input == "u")  //negates
			{
				s1 = pop(stack);

				push(-s1, stack);


			}

			else if(user_input == "p")  //Outputs
			{
			
				s1 = pop(stack);

				cout << s1 << endl;


			}

			else if(user_input == "\%")  //divides
			{
				s1 = pop(stack);

				s2 = pop(stack);

				push((s2 % s1), stack);
			}

			else if(user_input == "e")
			{
				exit(0);
			}

		
}


showstack(stack);	

return 0;

}
