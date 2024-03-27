#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h> 

//Node declaration for the BST
typedef struct Node_struct {
	int key;
	struct Node_struct *left;
	struct Node_struct *right;
} Node;

// Create a new Node from the struct Node
Node* createNode(int item)
{
	Node* newNode = (Node*) malloc (sizeof(Node));
	newNode->key = item;
	newNode->left = newNode->right = NULL;
	return newNode;
}

// Print the BST in Inorder traversal
void inorder(Node* node)
{
	if (node != NULL) 
	{
		inorder(node->left);
		printf("%d ", node->key);
		inorder(node->right);
	}
}

// Check if the node is an External node
int isExternal(Node* node)
{
	return node == NULL;
}

// Function to Search a key in a BST
Node* TreeSearch(Node* node, int key)
{
	// Base Cases: node is null or key is present at node
	if (isExternal(node) || node->key == key)
	{
		return node; // Return the Base case's node
	}

	// General case
	if (key < node->key) // Key is less than node's key
	{
		return TreeSearch(node->left, key);		
	}
	else if (key > node->key) // Key is greater than node's key
	{
		return TreeSearch(node->right, key);
	}
}

// Function to insert a new node with a value (key)
Node* Insert(Node* node, int key)
{
	// Base case, Node is empty so create a new node with NULL left and right child
	if (isExternal(node))
	{
		return createNode(key);
	}

	// Otherwise, do recursive call down the tree to determine which Left or Right child to Insert
	if (key <= node->key) // If Key is less than Node, move to the left Child
	{
		node->left = Insert(node->left, key);
		return node; 
	}
	else if (key > node->key) // If Key is larger than Node, move to the right Child. Add '>=' if u want equal key to move on the right tree instead of left tree
	{
		node->right = Insert(node->right, key);
		return node;
	}
}

// // Insertion Method based on the slide, doesnt work, waste 1.5 hours trying to figure out why, the TreeSearch() doesnt move the fucking Node!
// Node* Insert(Node* node, int key)
// {
// 	Node* keyNode = TreeSearch(node, key);
// 	if (keyNode == NULL)
// 	{
// 		return createNode(key); // No need to InsertAtExternal() cuz the fucking TreeSearch() return the same key or the NULL (External) node
// 	}

// 	if (keyNode->key == key)
// 	{
// 		return Insert(keyNode->left, key); // Or keyNode->right, whatever way is fine
// 	}
// }

/* Given a binary search tree and a key, this function deletes the key and returns the new node */
Node* deleteNode(Node* node, int key)
{
	// Base case
	if (isExternal(node))
	{
		printf("No value of %d in this tree to be deleted\n", key);
		return node; // return the default node
	}

	// Otherwise, do recursive call down the tree of the node to be deleted
	if (key < node->key) 
	{
		node->left = deleteNode(node->left, key);
		return node; // return the default node or the replaced node depends if if reached 
	}
	else if (key > node->key) 
	{
		node->right = deleteNode(node->right, key);
		return node; // return the default node
	}

	/*  The code Reaching here means the key == node->key. Do the Deletion and Replacement  */

	// Case 1: If one of the Delete Node's Children is empty, replace it with the Children if available
	if (node->left == NULL) // If Left Child is empty
	{
		Node* replacementNode = node->right; // Store content of Right Child to be return
		free(node); // Free the node along with its children
		return replacementNode;
	}
	else if (node->right == NULL)  // If Right Child is empty
	{
		Node* replacementNode = node->left; // Store content of Left Child to be return
		free(node); // Free the node along with its children
		return replacementNode;
	}

	// Case 2: If both children exist, then find the Successor Node on the Left or Right Subtree for replacement (Strongest Left Subtree Node vs Weakest Right Subtree Node)
	else 
	{
		// Parent's Node of the Successor Node
		Node* successorParent = node;

		// Find Successor Node on the Right sub tree (Smallest Right Subtree Node)
		Node* successor = node->right;
		while (successor->left != NULL) // The smallest Node in right sub tree is on the left so go to the left Node until reached empty
		{
			successorParent = successor;
			successor = successor->left;
		}

		// After finding the right Successor Node -> Rearranging the Tree order before the Successor Node key will replace in the Deleted Node key
		if (successorParent != node) 
		{
			// If the node move, then Successor Parent Left Child will be Successor Right Child
			successorParent->left = successor->right; 
		}
		else
		{
			// If the node doesnt move (The replacement is the Deleted node Child), then Successor Parent Right Child will be Successor Right Child
			successorParent->right = successor->right; 
		}

		/* Uncomment 2 code block below to Find the successor Node on the left sub tree instead */

		// // Find Successor Node on the Left sub tree (Biggest Left Subtree Node)
		// Node* successor = node->left;
		// while (successor->right != NULL) // The smallest Node in left sub tree is on the right so go to the right Node until reached empty
		// {
		// 	successorParent = successor;
		// 	successor = successor->right;
		// }

		// // After finding the right Successor Node -> Rearranging the Tree order before the Successor Node key will replace in the Deleted Node key
		// if (successorParent != node)
		// {
		// // If the node move, then Successor Parent Right Child will be Successor Left Child
		// 	successorParent->right = successor->left; 
		// }
		// else
		// {
		// // If the node doesnt move (The replacement is the Deleted node Child), then Successor Parent Left Child will be Successor Left Child
		// 	successorParent->left = successor->left; 
		// }

		// Replace Successor key to Delted node key
		node->key = successor->key;

		// Delete Successor Node and return node
		free(successor);
		return node;
	}
}

// Clear the Bonary Search Tree
void clearBST(Node* node) 
{
    if (node == NULL) return;

    // Recursively clear left and right subtrees
    clearBST(node->left);
    clearBST(node->right);

    // Free current node
    free(node);
}

// Function to draw BST following InOrder traversal
void drawBST(Node* node, int depth) 
{
    if (node == NULL) 
	{
        return;
    }

    // Increase indentation for better visualization
    depth++;

    // Draw right child first
    drawBST(node->right, depth);

    // Print the key with appropriate indentation
    for (int i = 0; i < depth; i++) 
	{
        printf("   ");
    }
    printf("%d\n", node->key);

    // Draw left child
    drawBST(node->left, depth);
}

// Function to print BST structure
void printBST(Node* root) 
{
    printf("Binary Search Tree structure:\n");
    drawBST(root, 0);
}

int main()
{   
	Node* root = NULL;
	FILE * fp;

	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	int n = sizeof(arr) / sizeof(arr[0]);

	// Build heap
	for (int i = 0; i < n; i++) 
	{
		root = Insert(root, arr[i]);
	}

	printf("Original BST: ");
	inorder(root);
	printBST(root);

	root = deleteNode(root, 5);
	printf("\nModified BST tree after Deleting Node 5: ");
	inorder(root);

	root = deleteNode(root, 15);
	printf("\nModified BST tree after Deleting Node 15: ");
	inorder(root);	

	root = deleteNode(root, 1);
	printf("\nModified BST tree after Deleting Node 1: ");
	inorder(root);		

	root = Insert(root, 2);
	printf("\nModified BST tree after Inserting Node 2: ");
	inorder(root);		

	printBST(root);
	
	clearBST(root);
	root = NULL; // REMEMBER TO RESET ROOT TO NULL OR ELSE PROGRAM WILL CRASH AFTER USING IT AND INSERT A NODE

//  Question 7 Onward
	int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	int n1 = sizeof(arr) / sizeof(arr[0]);

	int arr2[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

	for (int i = 0; i < n2; i++) 
	{
		root = Insert(root, arr2[i]);
	}
	printf("\nInserting Array 2: ");
	inorder(root); 

	printBST(root);

	clearBST(root);
	root = NULL; // REMEMBER TO RESET ROOT TO NULL OR ELSE PROGRAM WILL CRASH AFTER USING IT AND INSERT A NODE

	

// // Build heap for Array 1
// 	for (int i = 0; i < n; i++) 
// 	{
// 		root = Insert(root, arr1[i]);
// 	}
// 	printf("\nArray 1: ");
// 	inorder(root); // uncomment to see the Heap 

// 	// Open file to read and write
// 	fp = fopen ("CPU_Time_BST_Search.txt", "w");

// 	/* 1. Loop through different sizes using Heap Sort of key 1 */ 
// 	// Start measuring time
// 	clock_t start_time = clock();
// 	for (int i = 0; i < 10000000; i++) 
// 	{                
// 		// Do the Tree Search for key 1  
// 		TreeSearch (root, 1);
// 	}
// 	// Stop measuring time
// 	clock_t end_time = clock();
// 	// Calculate elapsed time in nanoseconds
// 	double elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC); // * 1e9;

// 	// Print the elapsed time to a file
// 	fprintf(fp, "Search time of (1): ");
// 	fprintf(fp, "%f seconds\n", elapsed_time);      

// 	/* 2. Loop through different sizes using Heap Sort of key 15 */ 
// 	// Start measuring time
// 	start_time = clock();
// 	for (int i = 0; i < 10000000; i++) 
// 	{                
// 		// Do the Tree Search for key 1  
// 		TreeSearch (root, 15);
// 	}
// 	// Stop measuring time
// 	end_time = clock();
// 	// Calculate elapsed time in nanoseconds
// 	elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC); // * 1e9;

// 	// Print the elapsed time to a file
// 	fprintf(fp, "Search time of (15): ");
// 	fprintf(fp, "%f seconds\n", elapsed_time);                 

// 	fclose (fp);

// 	clearBST(root);
// 	root = NULL; // REMEMBER TO RESET ROOT TO NULL OR ELSE PROGRAM WILL CRASH AFTER USING IT AND INSERT A NODE

// // Build heap for Array 2
// 	for (int i = 0; i < n2; i++) 
// 	{
// 		root = Insert(root, arr2[i]);
// 	}
// 	printf("\nArray 2: ");
// 	inorder(root); // uncomment to see the Heap 

// 	// Open file to read and write
// 	fp = fopen ("CPU_Time_BST_Search_2.txt", "w");

// 	/* 1. Loop through different sizes using Heap Sort of key 1 */ 
// 	// Start measuring time
// 	start_time = clock();
// 	for (int i = 0; i < 100000; i++) 
// 	{                
// 		// Do the Tree Search for key 1  
// 		TreeSearch (root, 1);
// 	}
// 	// Stop measuring time
// 	end_time = clock();
// 	// Calculate elapsed time in nanoseconds
// 	elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC); // * 1e9;

// 	// Print the elapsed time to a file
// 	fprintf(fp, "Search time of (1): ");
// 	fprintf(fp, "%f seconds\n", elapsed_time);      

// 	/* 2. Loop through different sizes using Heap Sort of key 15 */ 
// 	// Start measuring time
// 	start_time = clock();
// 	for (int i = 0; i < 100000; i++) 
// 	{                
// 		// Do the Tree Search for key 1  
// 		TreeSearch (root, 15);
// 	}
// 	// Stop measuring time
// 	end_time = clock();
// 	// Calculate elapsed time in nanoseconds
// 	elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC); // * 1e9;

// 	// Print the elapsed time to a file
// 	fprintf(fp, "Search time of (15): ");
// 	fprintf(fp, "%f seconds\n", elapsed_time);                 

// 	fclose (fp);
	return 0;
}
