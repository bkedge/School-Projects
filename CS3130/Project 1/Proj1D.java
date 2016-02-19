// Brady Kedge
// 02-10-16
//Project 1 - Part D
//Fibonacci in Arrays

    import java.util.Scanner;

    public class Proj1D {
        public static void main(String[] args)
        {
            int n;
            int size = 100; //Array smaller than 100 digits
            
            
            Scanner input = new Scanner(System.in);
            System.out.println("Enter the Nth number you want: ");
            
            n = input.nextInt();
            
            //Runs the Array and does not trim
            int[] FnArray = IterationArray(n, size);
            
            //Check most significant digit, if 0 then number is less than 100 digits.
            if(FnArray[0] == 0)
            {
                //Trim
                int[] FnArrayTrimmed = TrimZeros(FnArray);
                
                System.out.print("The Nth Fibonacci Number is: ");
                
                //Print
                for(int i = 0; i < FnArrayTrimmed.length; i++)
                {
                    System.out.print(FnArrayTrimmed[i]);
                }
                System.out.println();
            }
            
            //Check most significant digit, if not 0 then run while loop while decrementing n until most significant digit is 0
            if(FnArray[0] != 0)
            {
                //Error message
                System.out.println("The Nth Fibonacci Number has 100 digits or more");
                
                //Find the biggest n < 100 digits
                while(FnArray[0] != 0)
                {
                    n--;
                    FnArray = IterationArray(n, size);
                }
                
                //Trim and iterate 
                int[] FnArrayBig = TrimZeros(IterationArray(n, size));
                
                //Print
                System.out.print("The biggest Fibonacci number less than 100 digits is: ");
                
                for(int i = 0; i < FnArrayBig.length; i++)
                {
                    System.out.print(FnArrayBig[i]);
                }
                System.out.println();
                //Test to see if really 99 digits
                //System.out.println("Length: " + FnArrayBig.length);
                System.out.print("The biggest Fn that is not 100 digits is: " + n);
                System.out.println();
                
            }
            
            //System.out.println(FnArray.length);
            
            /*System.out.print("The Nth Fibonacci Number is: ");
            
            for(int i = 0; i < FnArray.length; i++)
            {
                System.out.print(FnArray[i]);
            }*/
        }
        
        //Add both arrays to return for the Iteration method
        public static int[] addArrays(int[] num1, int[] num2)
        {
            int size = 100;
            int[] numResult = new int[size];
            int carry = 0;
            
            for(int i = size - 1; i >= 0; i--)
            {
                int temp = num1[i] + num2[i] + carry;
                numResult[i] = temp % 10;
                carry = temp / 10;
            }
            
            return numResult;
        }
        
        //Iteration method to find Fn
        public static int[] IterationArray(int n, int size)
        {
            //Standard declarations of Fn-1,Fn-2
            int[] Array1 = new int[size];
            int[] Array2 = new int[size];
            int[] FinalArray = new int[size];
            Array1[size - 1] = 0;//F(0)
            Array2[size - 1] = 1;//F(1)
            
            for(int i = 0; i < n - 1; i++)
            {
                FinalArray = addArrays(Array1, Array2);
                Array1 = Array2;
                Array2 = FinalArray;
                
                //SECONDARY METHOD - BACKUP
                /*int[] TempArray2 = new int[Array2.length];
                for(int j = 0; j < Array2.length; j++)
                {
                    TempArray2[j] = FinalArray[j];
                }
                Array2 = TempArray2;*/
                
            }
            
            return FinalArray;
        }
        
        //Removes all leading zeros
        public static int[] TrimZeros(int[] ZeroArray)
        {
            int offset = 0;
            
            for(int i = 0; i < ZeroArray.length; i++)
            {
                if(ZeroArray[i] != 0)
                {
                    break;
                }
                
                offset++;
                
            }
            
            int[] TrimmedArray = new int[ZeroArray.length - offset];
            
            for(int i = 0; i < TrimmedArray.length; i++)
            {
                TrimmedArray[i] = ZeroArray[i + offset];
            }
            
            //Returns trimmed array
            return TrimmedArray;
        }
        
    }
