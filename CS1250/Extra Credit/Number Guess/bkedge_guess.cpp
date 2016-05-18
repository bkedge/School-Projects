//Brady Kedge
//Intro to Computing
//Number Guessing Game

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
	srand(time(0));//Seed of time

	int NewGame = 1,//New Game Choice
		QuitGame = 2,//Quit Game Choice
		RandNum,//Random Number
		count = 0,//Guess counter
		guess,//Users guess
		choice;//Users choice


	//Starts the loop
	do{
		cout << endl;
		cout << "Please choose a choice from below\n";
		cout << "---------------------------------\n";
		cout << "New Game = 1\n";
		cout << "Quit = 2\n";
		cin >> choice;

		//Validates
		while(choice < NewGame || choice > QuitGame)
		{
			cout << "Please enter a valid choice \n";
			cin >> choice;
		}

		RandNum = 1 + rand() % 99; //Random Number

		
		//Starts the game
		if (choice == NewGame)
		{
			cout << "Enter your guess of a number between 1 and 100\n";
			do{
				cin >> guess;
				
				//Out of Range
				if (guess < 1 || guess > 100)
				{
					cout << "You guessed out of range. Please guess a number between 1 and 100\n";
				}

				//Too High
				else if (guess > RandNum)
				{
					cout << "You guessed to high please try again\n";
				}

				//Too low
				else if (guess < RandNum)
				{
					cout << "You guessed to low please try again\n";
				}

				//Counter Variable
				count++;
			} while(guess != RandNum);//User guesses right

		cout << "You guessed the right number\n";
		cout << "It took you " << count << " guesses to get it right\n";
				
		}

	} while(choice != QuitGame);//Quits

	return 0;
}