#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RED 'R'
#define BLACK 'B'

// Structure for a BST node
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Red-black tree node
struct RBNode {
    int key;
    char color; // 'R' for red, 'B' for black
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
};

// Function to create a new BST node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a new Red-black tree node
struct RBNode* createRBNode(int key) {
    struct RBNode* newNode = (struct RBNode*)malloc(sizeof(struct RBNode));
    newNode->key = key;
    newNode->color = 'R'; // New nodes are always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Function to insert a key into BST
struct Node* insertBST(struct Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insertBST(root->left, key);
    } else if (key > root->key) {
        root->right = insertBST(root->right, key);
    }

    return root;
}
// Function to perform left rotation
void leftRotate(struct RBNode* root, struct RBNode* x) {
    struct RBNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(struct RBNode* root, struct RBNode* y) {
    struct RBNode* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

// Function to perform fix-up after Red-black tree insertion
void insertFixup(struct RBNode* root, struct RBNode* node) {
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            struct RBNode* uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                // Case 1: Uncle is red
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    // Case 2: Node is right child
                    node = node->parent;
                    leftRotate(root, node);
                }
                // Case 3: Node is left child
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(root, node->parent->parent);
            }
        } else {
            // Symmetric cases for right child of parent
            struct RBNode* uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                // Case 1: Uncle is red
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    // Case 2: Node is left child
                    node = node->parent;
                    rightRotate(root, node);
                }
                // Case 3: Node is right child
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(root, node->parent->parent);
            }
        }
    }
    root->color = BLACK; // Root must be black
}
// Function to insert a key into Red-black tree
struct RBNode* insertRBT(struct RBNode* root, int key) {
    // Create a new node with the given key
    struct RBNode* newNode = createRBNode(key);

    // Perform BST insertion (similar to BST insertion)
    struct RBNode* parent = NULL;
    struct RBNode* current = root;
    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            free(newNode); // Key already exists, free the new node and return root
            return root;
        }
    }

    // Set the parent of the new node
    newNode->parent = parent;

    // Adjust pointers based on BST insertion
    if (parent == NULL) {
        root = newNode; // If tree is empty, new node becomes root
    } else if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    insertFixup(root, newNode);

    return root;
}

// Function to get the height of a BST
int getHeightBST(struct Node* node) {
    if (node == NULL) {
        return 0;
    }

    int leftHeight = getHeightBST(node->left);
    int rightHeight = getHeightBST(node->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to get the height of a Red-black tree
int getHeightRBT(struct RBNode* node) {
    if (node == NULL) {
        return 0;
    }

    int leftHeight = getHeightRBT(node->left);
    int rightHeight = getHeightRBT(node->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + (node->color == 'B' ? 1 : 0);
}

// Compare function for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Function to generate a random array of size n
int* generateRandomArray(int n) {
    int* array = (int*)malloc(n * sizeof(int));
    srand(time(NULL)); // Seed for random number generation
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 1000; // Generating random numbers between 0 and 999
    }
    return array;
}

int main() {
    // Array sizes to test
    int sizes[] = {8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};

    // Iterate over array sizes
    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int size = sizes[i];
        int* arrayA = generateRandomArray(size);
        int* arrayB = (int*)malloc(size * sizeof(int));
        memcpy(arrayB, arrayA, size * sizeof(int));

        struct Node* bstRoot = NULL;
        struct RBNode* rbtRoot = NULL;

        // Insert keys into BST and RBT
        for (int j = 0; j < size; j++) {
            bstRoot = insertBST(bstRoot, arrayA[j]);
            rbtRoot = insertRBT(rbtRoot, arrayA[j]);
        }

        // Calculate heights
        int bstHeightA = getHeightBST(bstRoot);
        int rbtHeightA = getHeightRBT(rbtRoot);

        // Sort array B
        qsort(arrayB, size, sizeof(int), compare);

        struct Node* bstRootSorted = NULL;
        struct RBNode* rbtRootSorted = NULL;

        // Insert keys from sorted array B into BST and RBT
        for (int j = 0; j < size; j++) {
            bstRootSorted = insertBST(bstRootSorted, arrayB[j]);
            rbtRootSorted = insertRBT(rbtRootSorted, arrayB[j]);
        }

        // Calculate heights for sorted arrays
        int bstHeightB = getHeightBST(bstRootSorted);
        int rbtHeightB = getHeightRBT(rbtRootSorted);

        // Display results
        printf("Array Size: %d\n", size);
        printf("BST Height (Random): %d\n", bstHeightA);
        printf("RBT Height (Random): %d\n", rbtHeightA);
        printf("BST Height (Sorted): %d\n", bstHeightB);
        printf("RBT Height (Sorted): %d\n", rbtHeightB);
        printf("\n");

        // Free memory
        free(arrayA);
        free(arrayB);
    }

    return 0;
}
