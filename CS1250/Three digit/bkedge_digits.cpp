#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	int number;

	int count = 0;

	cout << "Running program \n" << "Writing numbers to file \"digits.txt\" \n" << "Done \n";

	ifstream infile;

	ofstream outfile;

	infile.open("random.txt");

	outfile.open("digits.txt");

	while (infile >> number)
	{
		if (number > 99 && number < 1000)
		{
			outfile << number << endl;

			count++;

		}
	}

	outfile << endl << "There are " << count <<" three digit numbers in the file";

	outfile.close();

	infile.close();

	return 0;	
}