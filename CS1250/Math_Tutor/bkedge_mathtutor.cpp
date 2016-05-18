//Brady Kedge
//Intro to Computing 1250 : 001
//Math Tutor Program
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;


int main()
{
	srand(time(0));//Seed for time
	
	int num1,//1st Number
		num2,//Second Number
		total,//Final result
		choice,//User selection
		Add = 1,//Addition choice
		Subtract= 2,//Subtraction choice
		QUIT = 3;//Quits program
	char ch;//Pause holder
	
do{
	cout << endl;
	cout << "Please choose a choice from below" << endl;//Menu
	cout << "---------------------------------\n";
	cout << "1 = Addition\n";
	cout << "2 = Subtraction\n";
	cout << "3 = QUIT\n\n";
	cin >> choice;


	while(choice < Add || choice > QUIT)//Validates
	{
		cout << "Please enter a valid choice" << endl;
		cin >> choice;
	}

	num1 = 100 + rand() % 900;//Gets numbers for the problems
	num2 = 100 + rand() % 900;
	
	if (choice == Add)//Addition
	{
		cout << "You have chosen Addition\n\n";
		cout << "Your problem is: \n";
		cout <<"  " << num1 << "\n" << "+ " << num2 << endl << "------\n";
		cout << "Hit ENTER to see answer" << endl;
		
		cin.ignore();
		cin.get(ch);
		
		total = num1 + num2;
		cout << "Answer is: " << total << endl;
	}

	else if (choice == Subtract)//Subraction
	{
		cout << "You have chosen Subtraction\n\n";
		cout << "Your problem is: \n";
		cout <<"  " << num1 << "\n" << "- " << num2 << endl << "------\n";
		cout << "Hit ENTER to see answer " << endl;

		cin.ignore();
		cin.get(ch);
	
		total = num1 - num2;
		cout << "Answer is: " << total << endl;
	}

} while(choice != QUIT);//Quits


return 0;
}