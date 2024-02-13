#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to sort an array using insertion sort
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
			j--; // Reduce the index to move to index 0
		}
		arr[j + 1] = key; // Insert the key back to the array. Use j + 1 cuz at the index j, its element is smaller than the key element, so insert at the j + 1
	}
}

// A utility function to print an array of size n
void printArray(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


// Display the menu options.
void menu(void) 
{
    puts("\nEnter your choice:\n"
    " 1. Insertion-Sort.\n"
    " 2. Pop.\n"
    " 3. Check Empty.\n"
    " 4. Check Size.\n"
    " 5. Content of Top Stack.\n"
    " 6. Print Stack .\n"
    " 7. Bracket Matching.\n"
    " 8. Language recognizer.\n"
    " 9. Performance test for Language recognizer.\n"
    " 0. Exit.\n");
}

int main() {
    int choice;
    int arr[] = { 1, 2, 4, 5, 3, 7, 8, 10, 11, 9, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    while (1) 
    {
        menu ();
        scanf("%d", &choice);

        switch (choice) 
        {
            //Press 1 to let user enter new item and push it in the stack, you can press 1 *string here* to push a bunch of char at the same time
            case 1:
                insertionSort(arr, n);
                printArray(arr, n);
                break;
            
            // //Press 2 to Pop item out of the stack
            // case 2:
            //     items = pop (stack);
            //     printf("Item Popped out of the stack: %c\n", items);
            //     printStack (stack);
            //     printf("\n");
            //     break;

            case 0:
                exit(0);

            default:
                printf("Invalid choice! Please choose from 0 to 9\n");
        }
    }
    return 0;
}