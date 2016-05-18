//Brady Kedge
//Intro to Computing 1250
//Interest Rate Program

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{

	int NewLoan = 1, //New Loan option
		MoreComp = 2,//More comparisons
		Quit = 3, //Quits
		Payments,
		choice;//Menu Selection

	double AnnRate,
			MonthRate, 
			MonthlyPay,
			NewAnnRate,
			NewMonthRate,
			NewMonthlyPay,
			compare,
			Loan;


	do
	{
		cout << "Choose an option from below\n"; //Menu
		cout << "---------------------------\n";
		cout << "New Loan = 1\n";
		cout << "More Comparisons = 2\n";
		cout << "Quit = 3\n";
		cin >> choice;
		cout << endl;

		//Validates
		while(choice < 0 || choice > 3)
		{
			cout << "Please choose a valid option\n";
			cin >> choice;
			cout << endl;
		}

		//New Loan
		if(choice == NewLoan)
		{
			cout << "Please enter the following:\n";
			cout << "---------------------------\n";
			cout << "Annual Interest Rate: ";
			cin >> AnnRate;
			cout << endl;

			MonthRate = AnnRate / 12;

			cout <<"Your Monthly interest rate is: " << MonthRate;
			cout << endl;
			cout << "Numer of payments: ";
			cin >> Payments;
			cout <<endl;
			cout << "Amount of the loan: ";
			cin >> Loan;
			cout << endl;

			MonthlyPay = (MonthRate * pow((1 + MonthRate),Payments)) / (pow((1 + MonthRate),Payments) - 1) * Loan;

			cout << "Your monthly payment is: $" << MonthlyPay;
			cout << endl << endl;
		}

		//More Comparisons
		else if(choice == MoreComp)
		{
			cout << "Please enter a new Annual interest rate: ";
			cin >> NewAnnRate;
			cout << endl;

			NewMonthRate = NewAnnRate / 12;

			cout << "Your new monthly interest rate is: " << NewMonthRate;
			cout << endl;

			NewMonthlyPay = (NewMonthRate * pow((1 + NewMonthRate),Payments)) / (pow((1 + NewMonthRate),Payments) - 1) * Loan;

			cout << "Your new monthly payment is: $" << NewMonthlyPay << endl;

			compare = NewMonthlyPay - MonthlyPay;

			//Save Money
			if(compare < 0)
			{
				cout << "You will save: $" << (-1 * compare) << endl << endl;
			}

			//Pay Money
			else if(compare > 0)
			{
				cout << "You will pay: $" << compare <<" more" << endl << endl;
			}
		}
	}while (choice != 3);//Quits






	return 0;
}