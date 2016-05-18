import java.util.Scanner;

public class Pairs {
  public static void main(String[] args) {

    int NUMBERS_TO_TEST = 1000;

    int number = 3;

    int count = 0;

    System.out.println("The prime pairs under 1,000 are: \n");

    
    while(number <= NUMBERS_TO_TEST)
    {
      if(isPrime(number))
      {
        int first_of_pair = number;

        int second_of_pair = number + 2;

        if(isPrime(second_of_pair))
        {
          System.out.println(first_of_pair + " " + second_of_pair + "\n");
        }
      }

      number += 2;
    }



}

  /** is number prime */
  public static boolean isPrime(int number) {
        if (number == 2) return true;
    for (int divisor = 3; divisor <= Math.sqrt(number) + 1; divisor+= 2)
      if (number % divisor == 0) return false; // not a prime
    return true; // number is prime
  }
}