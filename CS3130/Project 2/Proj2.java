//Brady Kedge
//CS3130
//3-5-2016
//Project #2

import java.util.Random;

public class Proj2 {
    public static void main(String[] args) {

        Random r = new Random();
        int insert = 0;
        long start;
        long end;
        long totalTime;

        int FirstSize = 1000;
        int SecondSize = 10000;
        int ThirdSize = 100000;

        //Initialize arrays
        int[] SortedArraySmall = new int[FirstSize];
        int[] SortedArrayMid = new int[SecondSize];
        int[] SortedArrayLarge = new int[ThirdSize];
        int[] SaSCopy = new int[SortedArraySmall.length];
        int[] SaMCopy = new int[SortedArrayMid.length];
        int[] SaLCopy = new int[SortedArrayLarge.length];

        int[] NearSortedArraySmall = new int[FirstSize];
        int[] NearSortedArrayMid = new int[SecondSize];
        int[] NearSortedArrayLarge = new int[ThirdSize];
        int[] NsSCopy = new int[NearSortedArraySmall.length];
        int[] NsMCopy = new int[NearSortedArrayMid.length];
        int[] NsLCopy = new int[NearSortedArrayLarge.length];

        int[] RandomArraySmall = new int[FirstSize];
        int[] RandomArrayMid = new int[SecondSize];
        int[] RandomArrayLarge = new int[ThirdSize];
        int[] RaSCopy = new int[RandomArraySmall.length];
        int[] RaMCopy = new int[RandomArrayMid.length];
        int[] RaLCopy = new int[RandomArrayLarge.length];

        //Fill Arrays
        FillArrays(SortedArraySmall,
                SortedArrayMid,
                SortedArrayLarge,
                NearSortedArraySmall,
                NearSortedArrayMid,
                NearSortedArrayLarge,
                RandomArraySmall,
                RandomArrayMid,
                RandomArrayLarge);

        //TIME CALCULATIONS//
        /////////////////////////////////////////////////////////////////////////////////////////////////////

        System.arraycopy(SortedArraySmall, 0, SaSCopy, 0, SortedArraySmall.length);
        System.arraycopy(SortedArrayMid, 0, SaMCopy, 0, SortedArrayMid.length);
        System.arraycopy(SortedArrayLarge, 0, SaLCopy, 0, SortedArrayLarge.length);
        System.arraycopy(NearSortedArraySmall, 0, NsSCopy, 0, NearSortedArraySmall.length);
        System.arraycopy(NearSortedArrayMid, 0, NsMCopy, 0, NearSortedArrayMid.length);
        System.arraycopy(NearSortedArrayLarge, 0, NsLCopy, 0, NearSortedArrayLarge.length);
        System.arraycopy(RandomArraySmall, 0, RaSCopy, 0, RandomArraySmall.length);
        System.arraycopy(RandomArrayMid, 0, RaMCopy, 0, RandomArrayMid.length);
        System.arraycopy(RandomArrayLarge, 0, RaLCopy, 0, RandomArrayLarge.length);



        /////////////////////////////////
        //SELECTION SORT IMPLEMENTATION//
        ////////////////////////////////

        System.out.println("SELECTION SORT: ");
        //Sorted Small
        start = System.nanoTime();
        SelectionSort(SaSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 1,000 integers: " + totalTime);

        //Sorted Medium
        start = System.nanoTime();
        SelectionSort(SaMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 10,000 integers: " + totalTime);

        //Sorted Large
        start = System.nanoTime();
        SelectionSort(SaLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 100,000 integers: " + totalTime);

        //Near Sorted Small
        start = System.nanoTime();
        SelectionSort(NsSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 1,000 integers: " + totalTime);

        //Near Sorted Medium
        start = System.nanoTime();
        SelectionSort(NsMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 10,000 integers: " + totalTime);

        //Near Sorted Large
        start = System.nanoTime();
        SelectionSort(NsLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 100,000 integers: " + totalTime);

        //Random Small
        start = System.nanoTime();
        SelectionSort(RaSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 1,000 integers: " + totalTime);

        //Random Medium
        start = System.nanoTime();
        SelectionSort(RaMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 10,000 integers: " + totalTime);

        //Random Large
        start = System.nanoTime();
        SelectionSort(RaLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 100,000 integers: " + totalTime);

        System.arraycopy(SortedArraySmall, 0, SaSCopy, 0, SortedArraySmall.length);
        System.arraycopy(SortedArrayMid, 0, SaMCopy, 0, SortedArrayMid.length);
        System.arraycopy(SortedArrayLarge, 0, SaLCopy, 0, SortedArrayLarge.length);
        System.arraycopy(NearSortedArraySmall, 0, NsSCopy, 0, NearSortedArraySmall.length);
        System.arraycopy(NearSortedArrayMid, 0, NsMCopy, 0, NearSortedArrayMid.length);
        System.arraycopy(NearSortedArrayLarge, 0, NsLCopy, 0, NearSortedArrayLarge.length);
        System.arraycopy(RandomArraySmall, 0, RaSCopy, 0, RandomArraySmall.length);
        System.arraycopy(RandomArrayMid, 0, RaMCopy, 0, RandomArrayMid.length);
        System.arraycopy(RandomArrayLarge, 0, RaLCopy, 0, RandomArrayLarge.length);

        //////////////////
        //INSERTION SORT//
        //////////////////

        System.out.println("INSERTION SORT: ");
        //Sorted Small
        start = System.nanoTime();
        InsertionSort(SaSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 1,000 integers: " + totalTime);

        //Sorted Medium
        start = System.nanoTime();
        InsertionSort(SaMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 10,000 integers: " + totalTime);

        //Sorted Large
        start = System.nanoTime();
        InsertionSort(SaLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 100,000 integers: " + totalTime);

        //Near Sorted Small
        start = System.nanoTime();
        InsertionSort(NsSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 1,000 integers: " + totalTime);

        //Near Sorted Medium
        start = System.nanoTime();
        InsertionSort(NsMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 10,000 integers: " + totalTime);

        //Near Sorted Large
        start = System.nanoTime();
        InsertionSort(NsLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 100,000 integers: " + totalTime);

        //Random Small
        start = System.nanoTime();
        InsertionSort(RaSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 1,000 integers: " + totalTime);

        //Random Medium
        start = System.nanoTime();
        InsertionSort(RaMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 10,000 integers: " + totalTime);

        //Random Large
        start = System.nanoTime();
        InsertionSort(RaLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 100,000 integers: " + totalTime);

        System.arraycopy(SortedArraySmall, 0, SaSCopy, 0, SortedArraySmall.length);
        System.arraycopy(SortedArrayMid, 0, SaMCopy, 0, SortedArrayMid.length);
        System.arraycopy(SortedArrayLarge, 0, SaLCopy, 0, SortedArrayLarge.length);
        System.arraycopy(NearSortedArraySmall, 0, NsSCopy, 0, NearSortedArraySmall.length);
        System.arraycopy(NearSortedArrayMid, 0, NsMCopy, 0, NearSortedArrayMid.length);
        System.arraycopy(NearSortedArrayLarge, 0, NsLCopy, 0, NearSortedArrayLarge.length);
        System.arraycopy(RandomArraySmall, 0, RaSCopy, 0, RandomArraySmall.length);
        System.arraycopy(RandomArrayMid, 0, RaMCopy, 0, RandomArrayMid.length);
        System.arraycopy(RandomArrayLarge, 0, RaLCopy, 0, RandomArrayLarge.length);

        //////////////
        //BUBBLESORT//
        /////////////

        System.out.println("BUBBLE SORT: ");
        //Sorted Small
        start = System.nanoTime();
        BubbleSort(SaSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 1,000 integers: " + totalTime);

        //Sorted Medium
        start = System.nanoTime();
        BubbleSort(SaMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 10,000 integers: " + totalTime);

        //Sorted Large
        start = System.nanoTime();
        BubbleSort(SaLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 100,000 integers: " + totalTime);

        //Near Sorted Small
        start = System.nanoTime();
        BubbleSort(NsSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 1,000 integers: " + totalTime);

        //Near Sorted Medium
        start = System.nanoTime();
        BubbleSort(NsMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 10,000 integers: " + totalTime);

        //Near Sorted Large
        start = System.nanoTime();
        BubbleSort(NsLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 100,000 integers: " + totalTime);

        //Random Small
        start = System.nanoTime();
        BubbleSort(RaSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 1,000 integers: " + totalTime);

        //Random Medium
        start = System.nanoTime();
        BubbleSort(RaMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 10,000 integers: " + totalTime);

        //Random Large
        start = System.nanoTime();
        BubbleSort(RaLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 100,000 integers: " + totalTime);

        System.arraycopy(SortedArraySmall, 0, SaSCopy, 0, SortedArraySmall.length);
        System.arraycopy(SortedArrayMid, 0, SaMCopy, 0, SortedArrayMid.length);
        System.arraycopy(SortedArrayLarge, 0, SaLCopy, 0, SortedArrayLarge.length);
        System.arraycopy(NearSortedArraySmall, 0, NsSCopy, 0, NearSortedArraySmall.length);
        System.arraycopy(NearSortedArrayMid, 0, NsMCopy, 0, NearSortedArrayMid.length);
        System.arraycopy(NearSortedArrayLarge, 0, NsLCopy, 0, NearSortedArrayLarge.length);
        System.arraycopy(RandomArraySmall, 0, RaSCopy, 0, RandomArraySmall.length);
        System.arraycopy(RandomArrayMid, 0, RaMCopy, 0, RandomArrayMid.length);
        System.arraycopy(RandomArrayLarge, 0, RaLCopy, 0, RandomArrayLarge.length);

        /////////////////////////
        //BUBBLESORT WITH SWAPS//
        /////////////////////////

        System.out.println("BUBBLE SORT WITH SWAPS: ");
        //Sorted Small
        start = System.nanoTime();
        BubbleSortCount(SaSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 1,000 integers: " + totalTime);

        //Sorted Medium
        start = System.nanoTime();
        BubbleSortCount(SaMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 10,000 integers: " + totalTime);

        //Sorted Large
        start = System.nanoTime();
        BubbleSortCount(SaLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 100,000 integers: " + totalTime);

        //Near Sorted Small
        start = System.nanoTime();
        BubbleSortCount(NsSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 1,000 integers: " + totalTime);

        //Near Sorted Medium
        start = System.nanoTime();
        BubbleSortCount(NsMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 10,000 integers: " + totalTime);

        //Near Sorted Large
        start = System.nanoTime();
        BubbleSortCount(NsLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 100,000 integers: " + totalTime);

        //Random Small
        start = System.nanoTime();
        BubbleSortCount(RaSCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 1,000 integers: " + totalTime);

        //Random Medium
        start = System.nanoTime();
        BubbleSortCount(RaMCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 10,000 integers: " + totalTime);

        //Random Large
        start = System.nanoTime();
        BubbleSortCount(RaLCopy);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 100,000 integers: " + totalTime);

        System.arraycopy(SortedArraySmall, 0, SaSCopy, 0, SortedArraySmall.length);
        System.arraycopy(SortedArrayMid, 0, SaMCopy, 0, SortedArrayMid.length);
        System.arraycopy(SortedArrayLarge, 0, SaLCopy, 0, SortedArrayLarge.length);
        System.arraycopy(NearSortedArraySmall, 0, NsSCopy, 0, NearSortedArraySmall.length);
        System.arraycopy(NearSortedArrayMid, 0, NsMCopy, 0, NearSortedArrayMid.length);
        System.arraycopy(NearSortedArrayLarge, 0, NsLCopy, 0, NearSortedArrayLarge.length);
        System.arraycopy(RandomArraySmall, 0, RaSCopy, 0, RandomArraySmall.length);
        System.arraycopy(RandomArrayMid, 0, RaMCopy, 0, RandomArrayMid.length);
        System.arraycopy(RandomArrayLarge, 0, RaLCopy, 0, RandomArrayLarge.length);

        /////////////
        //QUICKSORT//
        /////////////

        System.out.println("QUICK SORT: ");
        //Sorted Small
        start = System.nanoTime();
        QuickSort(SaSCopy, 0, SaSCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 1,000 integers: " + totalTime);

        //Sorted Medium
        start = System.nanoTime();
        QuickSort(SaMCopy, 0, SaMCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 10,000 integers: " + totalTime);

        //Sorted Large
        start = System.nanoTime();
        QuickSort(SaLCopy, 0, SaLCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 100,000 integers: " + totalTime);

        //Near Sorted Small
        start = System.nanoTime();
        QuickSort(NsSCopy, 0, NsSCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 1,000 integers: " + totalTime);

        //Near Sorted Medium
        start = System.nanoTime();
        QuickSort(NsMCopy, 0, NsMCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 10,000 integers: " + totalTime);

        //Near Sorted Large
        start = System.nanoTime();
        QuickSort(NsLCopy, 0, NsLCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 100,000 integers: " + totalTime);

        //Random Small
        start = System.nanoTime();
        QuickSort(RaSCopy, 0, RaSCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 1,000 integers: " + totalTime);

        //Random Medium
        start = System.nanoTime();
        QuickSort(RaMCopy, 0, RaMCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 10,000 integers: " + totalTime);

        //Random Large
        start = System.nanoTime();
        QuickSort(RaLCopy, 0, RaLCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 100,000 integers: " + totalTime);

        /////////////
        //MERGESORT//
        /////////////

        System.out.println("MERGE SORT: ");
        //Sorted Small
        start = System.nanoTime();
        MergeSort(SaSCopy, 0, SaSCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 1,000 integers: " + totalTime);

        //Sorted Medium
        start = System.nanoTime();
        MergeSort(SaMCopy, 0, SaMCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 10,000 integers: " + totalTime);

        //Sorted Large
        start = System.nanoTime();
        MergeSort(SaLCopy, 0, SaLCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Sorted Array of 100,000 integers: " + totalTime);

        //Near Sorted Small
        start = System.nanoTime();
        MergeSort(NsSCopy, 0, NsSCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 1,000 integers: " + totalTime);

        //Near Sorted Medium
        start = System.nanoTime();
        MergeSort(NsMCopy, 0, NsMCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 10,000 integers: " + totalTime);

        //Near Sorted Large
        start = System.nanoTime();
        MergeSort(NsLCopy, 0, NsLCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Near Sorted Array of 100,000 integers: " + totalTime);

        //Random Small
        start = System.nanoTime();
        MergeSort(RaSCopy, 0, RaSCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 1,000 integers: " + totalTime);

        //Random Medium
        start = System.nanoTime();
        MergeSort(RaMCopy, 0, RaMCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 10,000 integers: " + totalTime);

        //Random Large
        start = System.nanoTime();
        MergeSort(RaLCopy, 0, RaLCopy.length - 1);
        end = System.nanoTime();
        totalTime = end - start;
        System.out.println("Time for Random Sorted Array of 100,000 integers: " + totalTime);

        ///////////////////////////////////////////////////////////////////////////////////////////

        /*for(int i = 0; i < 20; i++)
        {
            System.out.print(RandomArrayLarge[i] + " ");
        }

        System.out.println();

        for(int i = 0; i < 20; i++)
        {
            System.out.print(RaLCopy[i] + " ");
        }*/





    }

    public static int[] SelectionSort(int[] SelectArray)
    {


        for(int i = 0; i < SelectArray.length - 1; i++)
        {
            int key = i;

            for(int j = i + 1; j < SelectArray.length; j++)
            {
                if(SelectArray[j] < SelectArray[key])
                {
                    key = j;
                }
            }

            int small = SelectArray[key];
            SelectArray[key] = SelectArray[i];
            SelectArray[i] = small;
        }

        return SelectArray;
    }

    public static int[] InsertionSort(int[] InsertArray)
    {
        for (int i = 1; i < InsertArray.length; i++)
        {
            int sort = InsertArray[i];
            int j = i;
            while(j > 0 && InsertArray[j - 1] > sort)
            {
                InsertArray[j] = InsertArray[j - 1];
                j--;
            }
            InsertArray[j] = sort;
        }

        return InsertArray;
    }

    public static int[] BubbleSortCount(int[] BubArrayCount)
    {
        int temp;
        int swaps = 0;
        boolean swapped = true;
        while(swapped)
        {
            swapped = false;
            for(int j = 1; j < BubArrayCount.length - 1; j++)
            {
                if(BubArrayCount[j-1] > BubArrayCount[j])
                {
                    temp = BubArrayCount[j - 1];
                    BubArrayCount[j - 1] = BubArrayCount[j];
                    BubArrayCount[j] = temp;
                    swapped = true;
                    swaps++;

                }
            }

        }

        return BubArrayCount;
    }

    public static int[] BubbleSort(int[] BubArray)
    {
        int temp;
        for(int i = 0; i < BubArray.length - 1; i++)
        {
            for(int j = 1; j < BubArray.length - 1; j++)
            {
                if(BubArray[j-1] > BubArray[j])
                {
                    temp = BubArray[j - 1];
                    BubArray[j - 1] = BubArray[j];
                    BubArray[j] = temp;
                }
            }

        }

        return BubArray;
    }

    public static void QuickSort(int[] QuickArray, int low, int high)
    {
        int q = Partition(QuickArray, low, high);
        if(low < q - 1)
            QuickSort(QuickArray, low, q - 1);
        if(q < high)
            QuickSort(QuickArray, q, high);
    }

    public static int Partition(int[] QuickArray, int low, int high)
    {
        int i = low;
        int j = high;
        int temp;
        int pivot = QuickArray[(low + high) / 2];

        while(i <= j)
        {
            while(QuickArray[i] < pivot)
            {
                i++;
            }
            while(QuickArray[j] > pivot)
            {
                j--;
            }

            if(i <= j)
            {
                temp = QuickArray[i];
                QuickArray[i] = QuickArray[j];
                QuickArray[j] = temp;
                i++;
                j--;
            }
        }



        return i;
    }


    public static void MergeSort(int[] MergeArray, int low, int high)
    {
        if(low == high)
            return;
        else
        {
            int middle = (low + high) / 2;
            MergeSort(MergeArray, low, middle);
            MergeSort(MergeArray, middle + 1, high);
            Merge(MergeArray, low, middle, high);
        }
    }

    public static void Merge(int[] MergeArray, int low, int middle, int high)
    {
        int[] Left = new int[middle - low + 2];
        for(int i = low; i <= middle; i++)
        {
            Left[i - low] = MergeArray[i];
        }

        Left[middle - low + 1] = Integer.MAX_VALUE;

        int[] Right = new int[high - middle + 1];

        for(int i = middle + 1; i <= high; i++)
        {
            Right[i - middle - 1] = MergeArray[i];
        }

        Right[high - middle] = Integer.MAX_VALUE;
        int i = 0;
        int j = 0;

        for(int x = low; x <= high; x++)
        {
            if(Left[i] <= Right[j])
            {
                MergeArray[x] = Left[i];
                i++;
            }
            else
            {
                MergeArray[x] = Right[j];
                j++;
            }
        }
    }





    public static void FillArrays(int[] SAS, int[] SAM, int[] SAL, int[] NSS, int[] NSM, int[] NSL, int[] RAS, int[] RAM, int[] RAL )
    {
        Random r = new Random();
        int insert = 0;

        //SORTED ARRAYS//
        //Small
        for(int i = 0; i < SAS.length;  i++)
        {
            SAS[i] = i;
        }
        //Mid
        for(int i = 0; i < SAM.length; i++)
        {
            SAM[i] = i;
        }
        //Large
        for(int i = 0; i < SAL.length; i++)
        {
            SAL[i] = i;
        }

        //NEARSORTED ARRAYS//
        //Small
        for(int i = 0; i < NSS.length;  i++)
        {
            if((i+1) % 10 == 0)
            {
                insert = r.nextInt(10000) + 1;
                NSS[i] = insert;
            }
            else {
                NSS[i] = i;
            }
        }
        //Mid
        for(int i = 0; i < NSM.length; i++)
        {
            if((i+1) % 10 == 0)
            {
                insert = r.nextInt(10000) + 1;
                NSM[i] = insert;
            }
            else {
                NSM[i] = i;
            }
        }
        //Large
        for(int i = 0; i < NSL.length; i++)
        {
            if((i+1) % 10 == 0)
            {
                insert = r.nextInt(10000) + 1;
                NSL[i] = insert;
            }
            else {
                NSL[i] = i;
            }
        }

        //RANDOM ARRAYS//
        //Small
        for (int i = 0; i < RAS.length; i++)
        {
            insert = r.nextInt(10000) + 1;
            RAS[i] = insert;
        }

        //Mid
        for (int i = 0; i < RAM.length; i++)
        {
            insert = r.nextInt(10000) + 1;
            RAM[i] = insert;
        }

        //Large
        for (int i = 0; i < RAL.length; i++)
        {
            insert = r.nextInt(10000) + 1;
            RAL[i] = insert;
        }


    }

}
