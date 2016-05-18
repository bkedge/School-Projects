//Brady Kedge
//Intro to Computing: 001

//This program simulates a craps game
#include <iostream>
#include <string>
#include <cstdlib> //For Random Function
#include <ctime>//For time
using namespace std;

int Rolltotal = 0, //to hold the roll total
		die1 = 0, //Die 1
		die2 = 0; //Die 2
	

float   CompWin = 1, //Value for a win for the computer
		UsrWin = 1, //Value for a win for the user
		Tie = 0.5, //Value for a tie
		CompScore = 0, //Score computer starts at
		UsrScore= 0; //Score user starts at


void DiceRoll() //Simulates two dice being rolled
{
	string holder;
	getline(cin, holder);

	unsigned seed = time(0);
	srand(seed);
	die1 = 1 + rand() % 6;
	die2 = 1 + rand() % 6;
	Rolltotal = die1 + die2;

	cout << "Your dice rolled a sum of: " << Rolltotal << endl;
}

int main()

{
	//Roll 1
	cout << "Type \"Roll\" to roll the dice \n";
	DiceRoll();

	if (Rolltotal == 7 || Rolltotal == 11) //User Wins
	{	UsrScore += UsrWin;
		cout << "You have earned a point. The score is:\n";
		cout << "Computer: " << CompScore << endl;
		cout << "User: " << UsrScore << endl;
	}
	else if (Rolltotal == 2 || Rolltotal == 3 || Rolltotal == 12) //Computer wins
	{	CompScore += CompWin;
		cout << "The computer has earned a point. The score is:\n"; 
		cout << "Computer: " << CompScore << endl;
		cout << "User: " << UsrScore << endl;
	}
	else if (Rolltotal == 4 || Rolltotal == 5 || Rolltotal == 6 || Rolltotal == 8 || Rolltotal == 9 || Rolltotal == 10)
	{	CompScore += Tie;
		UsrScore += Tie;
		cout << "You have tied the computer. The score is:\n";
		cout << "Computer: " << CompScore << endl;
		cout << "User: " << UsrScore << endl;
	} //Tie

	//Roll 2
	cout << "Type \"Roll\" to roll the dice \n ";
	DiceRoll();

	if (Rolltotal == 7 || Rolltotal == 11) //User Wins
	{	UsrScore += UsrWin;
		cout << "You have earned a point. The score is:\n";
		cout << "Computer: " << CompScore << endl;
		cout << "User: " << UsrScore << endl;
	}
	else if (Rolltotal == 2 || Rolltotal == 3 || Rolltotal == 12) //Computer wins
	{	CompScore += CompWin;
		cout << "The computer has earned a point. The score is:\n"; 
		cout << "Computer: " << CompScore << endl;
		cout << "User: " << UsrScore << endl;
	}
	else if (Rolltotal == 4 || Rolltotal == 5 || Rolltotal == 6 || Rolltotal == 8 || Rolltotal == 9 || Rolltotal == 10)
	{	CompScore += Tie;
		UsrScore += Tie;
		cout << "You have tied the computer. The score is:\n";
		cout << "Computer: " << CompScore << endl;
		cout << "User: " << UsrScore << endl;
	} //Tie

	//Roll 3
	cout << "Type \"Roll\" to roll the dice \n ";
	DiceRoll();

	if (Rolltotal == 7 || Rolltotal == 11) //User Wins
	{	UsrScore += UsrWin;
		cout << "You have earned a point. The score is:\n";
		cout << "Computer: " << CompScore << endl;
		cout << "User: " << UsrScore << endl;
	}
	else if (Rolltotal == 2 || Rolltotal == 3 || Rolltotal == 12) //Computer wins
	{	CompScore += CompWin;
		cout << "The computer has earned a point. The score is:\n"; 
		cout << "Computer: " << CompScore << endl;
		cout << "User: " << UsrScore << endl;
	}
	else if (Rolltotal == 4 || Rolltotal == 5 || Rolltotal == 6 || Rolltotal == 8 || Rolltotal == 9 || Rolltotal == 10)
	{	CompScore += Tie;
		UsrScore += Tie;
		cout << "You have tied the computer. The score is:\n";
		cout << "Computer: " << CompScore << endl;
		cout << "User: " << UsrScore << endl;
	} //Tie



	//Totals
	cout << "The game is over. The totals are: \n";
	cout << "User: " << UsrScore << endl;
	cout << "Computer: " << CompScore << endl;

	//Winner Declared
	if (UsrScore > CompScore)
		{cout << "User Wins!" << endl;}
	else if (CompScore > UsrScore)
		{cout << "Computer Wins!" << endl;}
	else if (UsrScore == CompScore)
		{cout << "Game is a tie!" << endl;}

	return 0;

}