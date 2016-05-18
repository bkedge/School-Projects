import java.util.Scanner;
import java.util.Random;

public class Connect{

	public static void main(String[] args){

		String[][] game = fillArray();

		boolean no_winner = true;

		int count = 0;

		printArray(game);

		while(no_winner)
		{
			if(count % 2 == 0)
				redPlayersTurn(game);
			else
				yellowPlayersTurn(game);

			count++;

			printArray(game);

			if(checkForWin(game) != null)
			{
				if(checkForWin(game) == "R")
					System.out.println("Red Player Wins!");
				else if(checkForWin(game) == "Y")
					System.out.println("Yellow Player Wins!");

				no_winner = false;
			}
		}

		
	}


public static String[][] fillArray()
{
	//have to have 7 rows because of bottom row being "-" and 15 columns to make "| | |"
	//pattern
	String[][] game = new String[7][15];

	//loops through array making the pattern
	for(int i =0; i < game.length; i++)
	{
		for(int j = 0; j < game[i].length; j++)
		{
			if(j % 2 == 0)
				game[i][j] = "|";
			

			else
				game[i][j] = " ";

			//makes the last row since array starts at index 0
			if(i == 6)
				game[i][j] = "-";
			
		}
	}

	return game;
}

public static void printArray(String[][] game)
{
	for(int i = 0; i < game.length; i++)
	{
		for(int j = 0; j < game[i].length; j++)
		{
			System.out.print(game[i][j]);
		}

		System.out.println();
	}
}

public static void redPlayersTurn(String[][] game)
{
	System.out.println("Red Player's Turn");

	//gets a random number between 6 and 0 for the slot drop
	Random rand = new Random();

	int red_drop = rand.nextInt((6-0) + 1) + 0;

	//converts from 1 2 3 4 5 6 ... column to 1 3 5 7 9 ... column setup
	int conversion = 2 * red_drop + 1;

	for(int i = 5; i >=0; i--)
	{
		if(game[i][conversion] == " ")
		{
			game[i][conversion] = "R";
			break;
		}
	}
}

//Same method as redPlayer just with yellow
public static void yellowPlayersTurn(String[][] game)
{
	System.out.println("Yellow Player's Turn");

	
	Random rand = new Random();

	int yellow_drop = rand.nextInt((6-0) + 1) + 0;

	int conversion = 2 * yellow_drop + 1;

	for(int i = 5; i >=0; i--)
	{
		if(game[i][conversion] == " ")
		{
			game[i][conversion] = "Y";
			break;
		}
	}
}


public static String checkForWin(String[][] game)
{	
	//checks for horizontal win
	for(int i = 0; i < 6; i++)
	{
		//starts at 0 and increments by two because of odd numbered column setup
		for(int j = 0; j < 7; j += 2)
		{
			if((game[i][j+ 1] != " ") && (game[i][j + 3] != " ") && (game[i][j + 5] != " ")
				&& (game[i][j + 7] != " ") && ((game[i][j + 1] == game[i][j + 3])
				&& (game[i][j+3] == game[i][j+5]) && (game[i][j+5] == game[i][j+7]))
			  )

		  return game[i][j+1];
		}
	}


	//Tests for vertical win but the values of j and i 
	//are reversed since it is checking differently
	for(int i = 1; i < 15; i += 2)
	{
		for(int j = 0; j < 3; j++)
		{
			if((game[j][i] != " ") && (game[j+1][i] != " ") && (game[j+2][i] != " ") && (game[j+3][i] != " ")
				&& ((game[j][i] == game[j+1][i]) && (game[j+1][i] == game[j+2][i]) && (game[j+2][i] == game[j+3][i])))
		  return game[j][i];
		}
	}

	//Tests for Top down diagonal win
	for(int i = 0; i < 3; i++)
	{
		for(int j = 1; j < 9; j += 2)
		{
			if ((game[i][j] != " ") && (game[i+1][j+2] != " ") && (game[i+2][j+4] != " ")
			&& (game[i+3][j+6] != " ") && ((game[i][j] == game[i+1][j+2]) && (game[i+1][j+2] == game[i+2][j+4]) && (game[i+2][j+4] == game[i+3][j+6])))

			return game[i][j];
		}
	}

	//Tests for bottom up diagonal win
	for(int i = 0; i < 3; i++)
	{
		for(int j = 7; j < 15; j += 2)
		{
			if ((game[i][j] != " ") && (game[i+1][j-2] != " ") && (game[i+2][j-4] != " ")
			&& (game[i+3][j-6] != " ") && ((game[i][j] == game[i+1][j-2]) && (game[i+1][j-2] == game[i+2][j-4]) && (game[i+2][j-4] == game[i+3][j-6])))

			return game[i][j];
		}
	}

	//If it finds no winner then return nothing
	return null;	
}


}