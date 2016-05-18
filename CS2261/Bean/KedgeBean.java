import java.util.Scanner;

public class KedgeBean{

  public static void main(String[] args) {

  Scanner input = new Scanner(System.in);

  System.out.print("Enter the number of balls you want to drop: ");

  int ball_number = input.nextInt();

  while(ball_number < 0)
  {
    System.out.print("Please enter a positive number: ");

    ball_number = input.nextInt();
  }



  System.out.print("Enter the number of slots you want: ");

  int slot_number = input.nextInt();

  while(slot_number < 0)
  {
    System.out.print("Please enter a positive number: ");

    slot_number = input.nextInt();
  }

  System.out.println();

  int[] slots_array = new int[slot_number];

  for (int i = 0; i < ball_number; i++) 
  {
    slots_array[ball_path(slot_number)]++; //Fills the slots
  }

  System.out.println();

  display(slots_array); //Prints the slot lineup

}

//Store the slot position of the ball and print its path
public static int ball_path(int slot_number) 
{

int ball_position = 0;

ball_position = slot_number/2;

for(int k=0; k < slot_number; k++)
{  
  if(Math.random()<=.5)
         { 
            ball_position--;
            
            if(ball_position < 0)
            {
                 ball_position++;
            } 
            
              System.out.print("L");
            
          }
       else
          {
             ball_position++;
             
             if(ball_position >= slot_number)
                {
                  ball_position--;
                }
             
             System.out.print("R");
          }

}

System.out.println();

return ball_position;
}

//Gets the slot with the most balls
public static int max(int[] slots_array) 
{

  int results = slots_array[0];



  for(int i = 1; i < slots_array.length; i++)
  {
     if(slots_array[i] > results)
     {
      results = slots_array[i];
     }  
  }

  return results;

  }

//Print the histogram of the slot lineup
public static void display(int[] slots_array) 
{

int slotHeight = max(slots_array);
    
for(int i = slotHeight; i > 0; i--)
  {
    for(int j = 0; j < slots_array.length; j++)
      if(slots_array[j]>=i)
         System.out.print("o");
      else
         System.out.print(" ");
     
    System.out.println();
  }
        

}



}

