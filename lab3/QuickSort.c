// C program for Quick sort
#include <stdio.h>

// function to swap elements
void swap (int *a, int *b) 
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

// function to print array elements
void printArray(int array[], int size) 
{
    for (int i = 0; i < size; ++i) 
    {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

void quickSortTest (int array[], int low, int high) 
{
    if (low < high) 
    {
        int pivot = array[high];
        int leftIndex = low;
        int rightIndex = high - 1;
        
        while (leftIndex <= rightIndex)
        {
            while ( (leftIndex <= rightIndex) && (array[leftIndex] <= pivot) )
            {
                leftIndex += 1;
            }
            while ( (leftIndex <= rightIndex) && (array[rightIndex] >= pivot) )
            {
                rightIndex -= 1;
            }
            if (leftIndex < rightIndex)
            {
                swap (&array[leftIndex], &array[rightIndex]);
            }
        }
        swap (&array[leftIndex], &array[high]);

        // recursive call on the left of pivot
        quickSortTest (array, low, leftIndex - 1);

        // recursive call on the right of pivot
        quickSortTest (array, leftIndex + 1, high);
    }
}

// main function
int main() {
    int data[] = {8, 7, 2, 1, 0, 9, 6};

    int n = sizeof(data) / sizeof(data[0]);
    printf("Unsorted Array\n");
    printArray(data, n);

    // perform quicksort on data
    quickSortTest (data, 0, n - 1);

    printf ("Sorted array in ascending order: \n");
    printArray (data, n);
}