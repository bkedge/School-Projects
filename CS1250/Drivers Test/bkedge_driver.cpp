//Brady Kedge
//Intro to Computing 1250
//Driver Liscense Exam

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

void GetAnswers();

int main()
{

	srand(time(0));

	GetAnswers();

	const int AnsNumb = 20;

	char CorrectAnswer[AnsNumb];

	char StudentAnswer[AnsNumb];

	int count = 0, total = 0;

	ifstream infile;

	infile.open("studentanswers.txt");

	int number;

	while (count < AnsNumb && infile >> number)
	{
		infile >> StudentAnswer[count];
		count++;
	}

	infile.close();

	count = 0;

	infile.open("answers.txt");

	while (count < AnsNumb && infile >> number)
	{
		infile >> CorrectAnswer[count];
		count++;
	}

	infile.close();



for(int index = 0; index < AnsNumb; index++)
{
	if (CorrectAnswer[index] != StudentAnswer[index])
		{
			cout << "Wrong: " << StudentAnswer[index] << "  " << "Right: " << CorrectAnswer[index] << endl;

			total++;
		}
}


cout << endl << "Student missed: " << total <<" questions";

	return 0;
}

void GetAnswers()
{
	const int numquestions = 20;

	//char studanswer[numquestions];

	int numb[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

	char studanswer[numquestions];

	ofstream outputfile;

	//Stores the Array
	for (int index = 0; index < numquestions; index++)
	{
		studanswer[index] = 65 + rand() % 4;
	}

	//Opens the file
	outputfile.open("studentanswers.txt");

	//Writes to the file
	for (int index = 0; index < numquestions; index++)
	{
		outputfile << numb[index] << " " << studanswer[index] << endl;
	}

	//Closes file
	outputfile.close();

	cout << "The answers were saved to a file\n";

	return;

}