//Brady Kedge
//Intro to Computing 1250
//Prime number counter

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	int number, count = 0;

	ifstream infile;

	infile.open("numbers.txt");

	while (infile >> number)
	{
		
		
	if (number == 1 || number == 2 || number == 3 || number == 5 || number == 7 || number == 17)
		{
			count++;
		}

	else if (number % 2 == 0 || number % 3 == 0 || number % 5 == 0 || number % 7 == 0 || number % 17 == 0)
		{}

	else
		{
		
		count++;
		
		}
	
	}

	cout << "There are " << count << " prime numbers in the file" << endl;

	infile.close();

return 0;

}
