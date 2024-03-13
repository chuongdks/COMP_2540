#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
#include <time.h>
#include <string.h>

#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];
int size = 0;

// Get the index of the Parent index based on current one
int Parent (int i) 
{
    return i / 2;
}

// Get the index of the Left Child index based on current one
int LeftChild (int i) 
{
    return 2 * i;
}

// Get the index of the Right Child index based on current one
int RightChild (int i) 
{
    return 2 * i + 1;
}

// Classic Swap function
void Swap (int *x, int *y) 
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// In-order traversal
void inorderTraversal(int index) 
{
    if (index <= size) 
    {
        inorderTraversal(LeftChild(index)); // Traverse left subtree
        printf("%d ", heap[index]);         // Visit current node
        inorderTraversal(RightChild(index)); // Traverse right subtree
    }
}

// Pre-order traversal
void preorderTraversal(int index) 
{
    if (index <= size) 
    {
        printf("%d ", heap[index]);         // Visit current node
        preorderTraversal(LeftChild(index)); // Traverse left subtree
        preorderTraversal(RightChild(index)); // Traverse right subtree
    }
}

// Post-order traversal
void postorderTraversal(int index) 
{
    if (index <= size) 
    {
        postorderTraversal(LeftChild(index)); // Traverse left subtree
        postorderTraversal(RightChild(index)); // Traverse right subtree
        printf("%d ", heap[index]);          // Visit current node
    }
}

int HeapSize() 
{
    return size;
}

int isEmpty() 
{
    return size == 0;
}

int IsExternal(int index)
{
    if (index > size)
    {
        return 1;
    }
    return 0;
}

// 1. Used after the Insertion of the new key k. Restore the MinHeap order by swapping 'k' along the upward path
void UpHeap (int index) 
{
    // Upheap is Terminate when the key k reach the root (no parent node), or a node whose parent has element (key) <= current element (key)
    while (index > 1 && heap[Parent(index)] > heap[index]) // while not reach root and parent element > current's element --> Swap place
    {
        // The index is moved in the Swap() function, continue the action UpHeap until condition is met
        Swap (&heap[Parent(index)], &heap[index]); // Use swap() to switch place btw Parent index and current index
        index = Parent(index); // Remember to change the position to the current's Parent after switching the element     
    }
}

// 2. Insert a key at the last node (Last node of a binary tree is last index of Array)
void Insert (int key) 
{
    // Check if size is larger than the Maximum heap size
    if (size >= MAX_HEAP_SIZE)
    {
        printf("Heap Array is full, cannot insert more elements.\n");
        return;
    }

    // Insert the key element to the index size, which is the larges index (last Node) of the heap
    heap[size+1] = key;
    size++; //increase the size after that for future use
    UpHeap(size);
}

// 3. Used after replacing the root's element (key) 
void DownHeap (int index) 
{
    int smallest = index;
    int left = LeftChild(index);
    int right = RightChild(index);

    // Choose the smaller element of the left or right child
    if (heap[left] < heap[right]) 
    {
        // switch index with child if element of the current index > element of the child's current index
        if (left <= size && heap[left] < heap[smallest]) 
        {
            smallest = left; // if the index reach max size or if the current left child's element < current index element
        }
    }
    else 
    {
        // switch index with child if element of the current index > element of the child's current index
        if (right <= size && heap[right] < heap[smallest]) 
        {
            smallest = right; // if the index reach max size or if the current left child's element < current index element
        }
    }

    // smallest = (heap[left] < heap[right]) ? ((left <= size && heap[left] < heap[smallest]) ? left : smallest) : ((right <= size && heap[right] < heap[smallest]) ? right : smallest);

    // Swapped the element with the child index if satisfy the condition
    if (smallest != index) 
    {
        Swap(&heap[index], &heap[smallest]);
        DownHeap(smallest);
    }
}

// 4. Remove the root of the Node and replace it with the 
int RemoveMin() 
{
    if (size < 1) 
    {
        printf("Heap is empty, cannot remove minimum element.\n");
        return -1;
    }

    int min = heap[1]; // store element at root with a temporary variable
    heap[1] = heap[size]; // replace element at root with the final element
    size--; // Decrease size
    DownHeap(1);

    return min;
}

// The most obvious find min function if use MinHeap
// int Min() 
// {
//     if (size <= 0) 
//     {
//         printf("Heap is empty, no minimum element.\n");
//         return -1;
//     }
//     return heap[0];
// }

int Min (int index) 
{
    int left = LeftChild(index);
    int right = RightChild(index);

    // Base case
    if (IsExternal(index))
      return INT_MAX;
 
    // Return minimum of 3 values:
    // 1) Root's data 
    // 2) Max in Left Subtree
    // 3) Max in right subtree
    int min = heap[index];
    int leftMin = Min(left);
    int rightMax = Min(right);

    if (leftMin < min)
    {
         min = leftMin;
    }
    if (rightMax < min)
    {
        min = rightMax;
    }

    return min;
}

// Find max value of 
int Max (int index) 
{
    int left = LeftChild(index);
    int right = RightChild(index);

    // Base case
    if (IsExternal(index))
        return INT_MIN;
 
    // Return maximum of 3 values:
    // 1) Root's data 
    // 2) Max in Left Subtree
    // 3) Max in right subtree
    int max = heap[index];
    int leftMax = Max(left);
    int rightMax = Max(right);

    if (leftMax > max)
    {
        max = leftMax;
    }
    if (rightMax > max)
    {
        max = rightMax;
    }

    return max;
}

void DisplayHeap() 
{
    printf("Heap: ");
    for (int i = 1; i <= size; i++) 
    {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

void HeapSort (int arr[], int n) 
{
    // Build heap
    for (int i = 0; i < n; i++) 
    {
        Insert(arr[i]);
    }
    
    DisplayHeap();

    // Extract elements from heap in sorted order
    printf("Sorted Heap: ");
    for (int i = 0; i < n; i++) 
    {
        arr[i] = RemoveMin();
        printf("%d ", arr[i]);
    }  
}

void ClearHeap() 
{
    size = 0; // Reset the size to 0, effectively clearing the heap
}

// Display the menu options.
void menu(void) 
{
    puts("\nEnter your choice:\n"
    " 1. Insert a number into the Heap.\n"
    " 2. Remove the Root from the Heap.\n"
    " 3. Find the Max and Min value of the Heap.\n"
    " 4. Check if the Heap is Empty and Check its Size.\n"
    " 5. Display the Heap\n"
    " 6. Emptied the Heap\n"
    " 7. Test the running time for the Heap Sort\n"
    " 0. Exit.\n");
}

int main() {
    int choice;

    char items;

    FILE * fp;

    while (1) 
    {
        menu();
        scanf("%d", &choice);

        switch (choice) 
        {
            //Press 1 to Insert a number into the Heap
            case 1:
                printf("Enter any number to Insert into the Heap: ");
                scanf(" %d", &items);
                Insert(items);
                DisplayHeap();
                printf("\n");
                break;
            
            //Press 2 to Remove the Root from the Heap
            case 2:
                printf("Min element: %d\n", Min(1));
                printf("Removing min element...\n");
                RemoveMin();
                DisplayHeap();            
                break;

            //Press 3 to find the Max and Min value of the Heap
            case 3:
                printf("Max element: %d\n", Max(1));
                printf("Min element: %d\n", Min(1));
                break;    

            //Press 4 to check if the Heap is Empty and to check its Size
            case 4:
                printf("Is heap empty? %s\n", isEmpty() ? "Yes" : "No");
                printf("Heap size: %d\n", HeapSize());
                break;   

            //Press 5 to Display the Heap
            case 5:
                DisplayHeap();
                break;   

            //Press 6 to Emptied the Heap
            case 6:
                ClearHeap();
                break;               

            //Press 7 to Test the running time for the Heap Sort
            case 7:
                // Open file to read and write
                fp = fopen ("CPU_Time_Heap_Sort.txt", "w");

                // Seed the random number generator using the current time
                srand(time(NULL));

                fprintf(fp, "\n");
                fprintf(fp, "Insertion Sort:\n");
                fprintf(fp, "Size | Time\n");
                fprintf(fp, "-----|------\n");

                // Loop through different sizes using Insertion Sort
                for (int i = 8; i < 1048577; i*=2) // 64 --> 1048576 // Memory allocation failed
                {
                    ClearHeap();
                    // Generate sorted lists A and B with random data
                    int *listS = malloc(i * sizeof(int));
                    if (listS == NULL) 
                    {
                        printf ("Memory allocation failed\n");
                        exit(1);
                    }

                    // Fill lists S with random sorted data
                    for (int j = 0; j < i; j++) 
                    {
                        listS[j] = rand() % 1048578; //Range from 0 - 1048578
                    }
                    
                    // Start measuring time
                    clock_t start_time = clock();

                    // Do the Sorting 
                    HeapSort (listS, i);

                    // Stop measuring time
                    clock_t end_time = clock();
                    // Calculate elapsed time in nanoseconds
                    double elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC); // * 1e9;
                    
                    // Print the
                    // printf("\nSorted Arrays using Insertion Sort: ");
                    // printArray (listS, i);

                    // Print the elapsed time
                    // printf("%d |  %.2f seconds\n", i, elapsed_time);

                    // Print the elapsed time to a file
                    fprintf(fp, "%d |  %.2f seconds\n", i, elapsed_time);
                }
                                               
                fclose (fp);
                break;

            case 0:
                exit(0);

            default:
                printf("Invalid choice! Please choose from 0 to 9\n");
        }
    }
    return 0;
}