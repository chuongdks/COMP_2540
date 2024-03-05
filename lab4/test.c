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

// Used after the Insertion of the new key k. Restore the MinHeap order by swapping 'k' along the upward path
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

// Insert a key at the last node (Last node of a binary tree is last index of Array)
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

// Used after replacing the root's element (key) 
void DownHeap (int index) 
{
    int smallest = index;
    int left = LeftChild(index);
    int right = RightChild(index);

    if (left < size && heap[left] < heap[smallest])
        smallest = left;
    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != index) {
        Swap(&heap[index], &heap[smallest]);
        DownHeap(smallest);
    }
}

int RemoveMin() 
{
    if (size <= 0) 
    {
        printf("Heap is empty, cannot remove minimum element.\n");
        return -1;
    }

    int min = heap[0];
    heap[0] = heap[size - 1];
    size--;
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
    Insert(6);
    Insert(2);
    Insert(7);
    Insert(9);
    Insert(5);

    DisplayHeap();

    printf("Min element: %d\n", Min());
    printf("Removing min element...\n");
    // RemoveMin();
    DisplayHeap();

    printf("Heap size: %d\n", HeapSize());
    printf("Is heap empty? %s\n", isEmpty() ? "Yes" : "No");

    // int arr[] = {10, 5, 15, 30, 20};
    // int n = sizeof(arr) / sizeof(arr[0]);

    // HeapSort(arr, n);
    // DisplayHeap(arr, n);


    return 0;
}
