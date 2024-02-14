#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to swap elements
void swap (int *a, int *b) 
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Function to print array elements
void printArray (int array[], int size) 
{
    for (int i = 0; i < size; ++i) 
    {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

// Function to sort an array using insertion sort
void insertionSort (int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++) 
    {
		key = arr[i]; // Store the next element to be compared to a temporary variable named key
		j = i - 1; // Check the element to the left of the key element index

		// Move elements of arr[0..i-1] from index: (key_index - 1) to index: 0. If that element is greater than key, move one position ahead of its current position 
		while (j >= 0 && arr[j] > key) 
        {
			arr[j + 1] = arr[j]; // Move element 1 position ahead of its current position
			j--; // Reduce the index to move to index 0
		}
		arr[j + 1] = key; // Insert the key back to the array. Use j + 1 cuz at the index j, its element is smaller than the key element, so insert at the j + 1
	}
}

// function to find the partition position in the Quick Sort
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

// Display the menu options.
void menu(void) 
{
    puts("\nEnter your choice:\n"
    " 1. Insertion-Sort.\n"
    " 2. Quick Sort.\n"
    " 3. Merged Sort.\n"
    " 4. Check Size.\n"
    " 9. Performance test for Language recognizer.\n"
    " 0. Exit.\n");
}

int main() {
    int choice;
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    while (1) 
    {
        menu ();
        scanf("%d", &choice);

        switch (choice) 
        {
            //Press 1 to 
            case 1:
                printf("Unsorted Array\n");
                printArray(arr, n);

                // Perform Insertion Sort 
                insertionSort(arr, n);

                printf ("Sorted array in ascending order using Insertion Sort: \n");
                printArray(arr, n);
                break;
            
            //Press 2 to 
            case 2:
                printf("Unsorted Array\n");
                printArray(arr, n);

                // Perform Quick Sort 
                quickSortTest (arr, 0, n - 1);

                printf ("Sorted array in ascending order using Quick Sort: \n");
                printArray (arr, n);
                break;

            case 0:
                exit(0);

            default:
                printf("Invalid choice! Please choose from 0 to 9\n");
        }
    }
    return 0;
}