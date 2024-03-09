#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];
int size = 0;

// Get the index of the Parent index based on current one
int Parent (int i) 
{
    return (i - 1) / 2;
}

// Get the index of the Left Child index based on current one
int LeftChild (int i) 
{
    return 2 * i + 1;
}

// Get the index of the Right Child index based on current one
int RightChild (int i) 
{
    return 2 * i + 2;
}

// Classic Swap function
void Swap (int *x, int *y) 
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// 1. Used after the Insertion of the new key k. Restore the MinHeap order by swapping 'k' along the upward path
void UpHeap (int index) 
{
    // Upheap is Terminate when the key k reach the root (no parent node), or a node whose parent has element (key) <= current element (key)
    while (index > 0 && heap[Parent(index)] > heap[index]) // while not reach root and current's parent element > current's element
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
    heap[size] = key;
    size++; //increase the size after that for future use
    UpHeap(size - 1);
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
        if (left < size && heap[left] < heap[smallest]) 
        {
            smallest = left; // if the index reach max size or if the current left child's element < current index element
        }
    }
    else 
    {
        // switch index with child if element of the current index > element of the child's current index
        if (right < size && heap[right] < heap[smallest]) 
        {
            smallest = right; // if the index reach max size or if the current left child's element < current index element
        }
    }

    // smallest = (heap[left] < heap[right]) ? ((left < size && heap[left] < heap[smallest]) ? left : smallest) : ((right < size && heap[right] < heap[smallest]) ? right : smallest);

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
    if (size <= 0) 
    {
        printf("Heap is empty, cannot remove minimum element.\n");
        return -1;
    }

    int min = heap[0]; // store element at root with a temporary variable
    heap[0] = heap[size - 1]; // replace element at root with the final element
    size--; // Decrease size
    DownHeap(0);

    return min;
}

int Min() 
{
    if (size <= 0) 
    {
        printf("Heap is empty, no minimum element.\n");
        return -1;
    }
    return heap[0];
}

// int minRecursive(int index) 
// {
//     if (index >= size) {
//         printf("Invalid index.\n");
//         return -1;
//     }

//     if (index == size - 1) {
//         return heap[index];
//     }

//     int min = minRecursive(index + 1);
//     return (heap[index] < min) ? heap[index] : min;
// }

// int minRecursive(int index) 
// {
//     if (index >= size) {
//         printf("Invalid index.\n");
//         return -1;
//     }

//     int left = leftChild(index);
//     int right = rightChild(index);

//     int smallest = index;
//     if (left < size && heap[left] < heap[smallest])
//         smallest = left;
//     if (right < size && heap[right] < heap[smallest])
//         smallest = right;

//     if (smallest != index)
//         return minRecursive(smallest);
//     else
//         return heap[index];
// }

int HeapSize() 
{
    return size;
}

int isEmpty() 
{
    return size == 0;
}

void HeapSort (int arr[], int n) 
{
    // Build heap
    for (int i = 0; i < n; i++) 
    {
        Insert(arr[i]);
    }

    // Extract elements from heap in sorted order
    for (int i = 0; i < n; i++) 
    {
        arr[i] = RemoveMin();
    }
}

void DisplayHeap() 
{
    printf("Heap: ");
    for (int i = 0; i < size; i++) 
    {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main() {
    Insert(3);
    Insert(5);
    Insert(6);
    Insert(15);
    Insert(9);
    Insert(7);
    Insert(20);
    Insert(16);
    Insert(25);
    Insert(14);
    Insert(12);
    Insert(11);
    Insert(19);

    DisplayHeap();

    printf("Min element: %d\n", Min());
    printf("Removing min element...\n");
    RemoveMin();
    DisplayHeap();

    printf("Heap size: %d\n", HeapSize());
    printf("Is heap empty? %s\n", isEmpty() ? "Yes" : "No");

    // int arr[] = {10, 5, 15, 30, 20};
    // int n = sizeof(arr) / sizeof(arr[0]);

    // HeapSort(arr, n);
    // DisplayHeap(arr, n);


    return 0;
}
