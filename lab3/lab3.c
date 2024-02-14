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

// Function to do Insertion sort (Like how u sort a poker card on your handm left to right, put lowest on the left and continue right)
void insertionSort (int arr[], int size)
{
	int i, key, j;
	for (i = 1; i < size; i++) 
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

// Function to find the partition position in the Quick Sort. If the pivot is the biggest or the smallest, it will take O(n^2) time complexity
void quickSort (int array[], int low, int high) 
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

        // relocate the pivot, after the line below, the left side has # less than pivot, and the right side has # larger than pivot
        swap (&array[leftIndex], &array[high]);

        // recursive call on the left of pivot
        quickSort (array, low, leftIndex - 1);

        // recursive call on the right of pivot
        quickSort (array, leftIndex + 1, high);
    }
}

// Create a Linked List for the integer type data
typedef struct Int_Node_struct{
    int data;
    struct Int_Node_struct* nextNodePtr;
    struct Int_Node_struct* head;
    struct Int_Node_struct* tail;
    int size;
} Int_Node;

// Function to create a new Node Int
Int_Node* createNodeInt () 
{
    Int_Node* newNode = (Int_Node*) malloc (sizeof(Int_Node));
    newNode->head = NULL;
    newNode->tail = NULL;
    newNode->size = 0;
    return newNode;
}

// removeHead() function: Remove at the head
int removeHeadInt (Int_Node* node) //add Node
{
    if (node->head == NULL)
    {
        printf("Error: The list is empty\n");
    }

    Int_Node* tempNode = node->head;
    int removedData = tempNode->data;

    if (node->head == node->tail)
    {
        // Only one node in the list
        node->head = node->tail = NULL;
    }
    else
    {
        node->head = node->head->nextNodePtr;
        tempNode->nextNodePtr = NULL;
    }
    
    free (tempNode);
    node->size--;
    return removedData;
}

// addTail() function: Insert at the tail
void addTailInt (Int_Node* node, int data) //add Node
{
    Int_Node* newNodeTail = (Int_Node*) malloc (sizeof(Int_Node));
    newNodeTail->data = data;
    newNodeTail->nextNodePtr = NULL;
    if (node->tail == NULL) //if no node has been added yet
    {
        node->head = node->tail = newNodeTail;
    }
    else
    {
        node->tail->nextNodePtr = newNodeTail;
        node->tail = newNodeTail;
    }
    node->size++;
}

// Check if the stack is empty
int isEmptyInt (Int_Node* node) //add Node
{
    return node->size == 0;
}

// Print the stack from head to tail using recursive
void printStackRecursiveInt (Int_Node* node) //must put head node in the argument when using this function or else infinite loop. Time complexity: O(n^2)
{
    if (node == NULL) 
    {
        return; // Base case: if node is NULL, return
    }
    printf("\n| %d |", node->data); // Print current node's data, put this after the function to print in reverse
    printStackRecursiveInt (node->nextNodePtr); // Recursive function for the next node
    //printf("\n| %c |", node->data); // Print current node's data, put this before the function to print in order
}

// Make the Linked List Empty
void emptyListInt (Int_Node* node) 
{
   Int_Node* currentNode = node->head;
   Int_Node* nextNode;

   //Assign next to current-> nextNode then delete the current node, repeat until over
   while (currentNode != NULL) 
   {
      nextNode = currentNode->nextNodePtr;
      free (currentNode);
      currentNode = nextNode;
   }
   //Delete the start node
   node->head = NULL;
}

// Merged 2 Sorted Queue A and Queue B into Queue S
Int_Node* mergeSortedQueues (Int_Node* queueA, Int_Node* queueB, Int_Node* queueS) 
{
    while (!isEmptyInt(queueA) && !isEmptyInt(queueB)) 
    {
        //If Front Content of Queue A >= than Queue B, then Enqueue Queue A item to Queue S and Dequeue item from queue A. Vice versa if Queue B > Queue A
        if (queueA->head->data <= queueB->head->data) 
        {
            addTailInt (queueS, queueA->head->data);
            removeHeadInt (queueA);
        } 
        else 
        {
            addTailInt (queueS, queueB->head->data);
            removeHeadInt (queueB);
        }
    }

    // Enqueue remaining elements of queue A
    while (!isEmptyInt(queueA)) 
    {
        addTailInt (queueS, queueA->head->data);
        removeHeadInt (queueA);
    }

    // Enqueue remaining elements of queue B
    while (!isEmptyInt(queueB)) 
    {
        addTailInt (queueS, queueB->head->data);
        removeHeadInt (queueB);
    }
    return queueS;
}

// Display the menu options.
void menu(void) 
{
    puts("\nEnter your choice:\n"
    " 1. Insertion-Sort.\n"
    " 2. Quick Sort.\n"
    " 3. Merged Sort.\n"
    " 4. Performance test for Language recognizer.\n"
    " 5. Print in Reverse\n"
    " 0. Exit.\n");
}

int main() {
    int choice;
    // int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int arr1[] = {10, 8, 9, 7, 2, 5, 3, 1, 6, 4};
    int arr2[] = {1, 2, 4, 5, 3, 7, 8, 10, 11, 9, 6};
    int listS[] = {1, 10, 4, 5, 3, 7, 8, 2, 11, 9, 6};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(listS) / sizeof(listS[0]);

    Int_Node* queueS = NULL;
    
    while (1) 
    {
        menu ();
        scanf("%d", &choice);

        switch (choice) 
        {
            //Press 1 to use Insertion Sort Algorithm
            case 1:
                printf("Unsorted Array\n");
                printArray(arr1, size1);

                // Perform Insertion Sort 
                insertionSort(arr1, size1);

                printf ("Sorted array in ascending order using Insertion Sort: \n");
                printArray(arr1, size1);
                break;
            
            //Press 2 to use Quick Sort Algorithm
            case 2:
                printf("Unsorted Array\n");
                printArray(arr2, size2);

                // Perform Quick Sort 
                quickSort (arr2, 0, size2 - 1);

                printf ("Sorted array in ascending order using Quick Sort: \n");
                printArray (arr2, size2);
                break;

            //Press 3 to use Merged Sort Algorithm
            case 3:
                queueS = createNodeInt();

                //Sample data for lists A and B
                

                //Enqueue elements from lists A and B into their respective queues
                for (int i = 0; i < sizeof(listS) / sizeof(listS[0]) ; i++)
                {
                    addTailInt (queueS, listS[i]);
                }

                printStackRecursiveInt (queueS->head);

                // Perform Quick Sort 
                // mergeSort (arr, 0, size - 1);

                break;    

            case 0:
                exit(0);

            default:
                printf("Invalid choice! Please choose from 0 to 9\n");
        }
    }
    return 0;
}