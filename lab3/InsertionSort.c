// C program for Insertion sort
#include <math.h>
#include <stdio.h>

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
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
			j = j - 1; // Reduce the index to move to index 0
		}
		arr[j + 1] = key; // Insert the key back to the array. Use j + 1 cuz at the index j, its element is smaller than the key element, so insert at the j + 1
	}
}

// A utility function to print an array of size n
void printArray(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
	printf("\n");
}

/* Driver program to test insertion sort */
int main()
{
	int arr[] = { 12, 11, 13, 5, 6 };
	int n = sizeof(arr) / sizeof(arr[0]);

	insertionSort(arr, n);
	printArray(arr, n);

	return 0;
}
