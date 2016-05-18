//Brady Kedge
//CS2261-001
//February 7, 2014

import java.util.Scanner;

public class Kedgeperfect {
	public static void main(String[] args) 
	{
	
	final int numbers_to_count = 10000;

	int perfect_sum = 0;

	System.out.println("The perfect numbers under 10,000 are: \n");

 

	//number has to be started at 2 otherwise 1 is counted as a perfect number 
 	for(int number = 2; number <= numbers_to_count; number++)
	{

		for(int i = 1; i < number; i++)
		{
			if(number % i == 0)
			{
				perfect_sum += i;
			}	
		}

			if(number == perfect_sum) 
			{
				System.out.println(number + "\n");
			}

		//have to reset sum to 0 or else the program keeps running
		perfect_sum = 0;
	}
	
	}
}