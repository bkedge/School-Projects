//Brady Kedge
//Intro To Computing
//Parallelogram Project

#include <iostream>
#include <string>

using namespace std;

//Parallelogram Prototype
void picture(int);

void starsfunc(int);

//Main Function
int main()
{
	int RowNum;

	cout << "Please enter a number between 1 and 20 for the amount of rows you want \n";
	cin >> RowNum;

	while(RowNum < 1 || RowNum > 20)
	{
		cout << "Please enter a valid number";
		cin >> RowNum;
	}

	int stars;

	stars = RowNum;

	picture(stars);

	return 0;
}

void picture(int paraStars)
{
	for (int v = paraStars; v >= 1; v--)
	{
		for (int h = 1; h <= v; h++)
		{
			cout << " ";
		}
		
		starsfunc(paraStars);
		cout << endl;
	}

}

void starsfunc(int starRow)
{
	for (int a = 1; a <= starRow; a++)
		{
			cout << "*";
		}
}