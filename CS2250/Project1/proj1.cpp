//Brady Kedge
//Comp. Sci. 2250 Sec-1
//September 15, 2013

#include <iostream>
#include <string>

using namespace std;

string infin;  //Declaration of input

string are = "are", ire = "ire" , ere = "ere"; //Conjugate ends

int x; //Holds value where "are" starts

int main()
{

	cout << endl; //Skips line
	
	while(cin >> infin) //Reads input
	{
		if(infin.find(are) != -1) //Npos. If no "are" found, skips.
		{
			x = infin.find(are); //Finds location of "are"
		
			infin.erase(x, 3); //Erases "are"

			cout << infin + "o" << "     " << infin + "amus\n"; //First conjugation

			cout << infin + "as" << "    " << infin + "atis\n"; //Second

			cout << infin + "at" << "    " << infin + "ant\n"; //Third

			cout << endl;
		}

		else if(infin.find(ere) != -1) //Same as "are" but with "ere"
		{
			x = infin.find(ere);

			infin.erase(x, 3);

			cout << infin + "eo" <<"    " << infin + "emus\n";

			cout << infin + "es" << "    " << infin + "etis\n";

			cout << infin + "et" << "    " << infin + "ent\n";

		}

		else if(infin.find(ire) != -1) //Same
		{
			x = infin.find(ire);

			infin.erase(x, 3);

			cout << infin + "io" << "    " << infin + "imus\n";

			cout << infin + "is" << "    " << infin + "itis\n";

			cout << infin + "it" << "    " << infin + "iunt\n";

		}

	}
		
	

return 0;

}