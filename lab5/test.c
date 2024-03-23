#include <stdio.h>
#include <stdlib.h>

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

// Driver Code
int main()
{
    /* 
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 
	*/

	Node* root = NULL;
	root = Insert(root, 50); // Need one Root Node variable

	Insert(root, 30);
	Insert(root, 20);
	Insert(root, 40);
	// Insert(root, 40);
	Insert(root, 70);
	Insert(root, 60);
	// Insert(root, 60);
	Insert(root, 80);
	// Insert(root, 45);
	// Insert(root, 67);

	// Print inorder traversal of the BST
	inorder(root);
	printf("\n");
	// Key to be found
	int key = 6;

	// Searching in a BST
	if (TreeSearch(root, key) == NULL)
		printf("%d not found\n", key);
	else
		printf("%d found\n", key);

	key = 60;

	// Searching in a BST
	if (TreeSearch(root, key) == NULL)
		printf("%d not found\n", key);
	else
		printf("%d found\n", key);

    // Delete
	printf("Original BST: ");
	inorder(root);

	printf("\n\nDelete a Leaf Node: 20\n");
	deleteNode(root, 20);
	printf("Modified BST tree after deleting Leaf Node:\n");
	inorder(root);

	printf("\n\nDelete Node with single child: 70\n");
	deleteNode(root, 70);
	printf("Modified BST tree after deleting single child Node:\n");
	inorder(root);

	printf("\n\nDelete Node with both child: 50\n");
	deleteNode(root, 50);
	printf("Modified BST tree after deleting both child Node:\n");
	inorder(root);    
	return 0;
}
