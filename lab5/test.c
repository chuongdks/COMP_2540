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
	}
	else if (key > node->key) // If Key is larger than Node, move to the right Child. Add '>=' if u want equal key to move on the right tree instead of left tree
	{
		node->right = Insert(node->right, key);
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
		return node;
	}

	// Otherwise, do recursive call down the tree of the node to be deleted
	if (key < node->key) 
	{
		node->left = deleteNode(node->left, key);
		return node;
	}
	else if (key > node->key) 
	{
		node->right = deleteNode(node->right, key);
		return node;
	}

	// We reach here when this is the node to be deleted.

	// Case 1: If one of the children is empty
	if (node->left == NULL) 
	{
		Node* temp = node->right;
		free(node);
		return temp;
	}
	else if (node->right == NULL) 
	{
		Node* temp = node->left;
		free(node);
		return temp;
	}

	// Case 2: If both children exist
	else 
	{
		Node* succParent = node;

		// Find successor
		Node* succ = node->right;
		while (succ->left != NULL) {
			succParent = succ;
			succ = succ->left;
		}

		// Delete successor. Since successor
		// is always left child of its parent
		// we can safely make successor's right
		// right child as left of its parent.
		// If there is no succ, then assign
		// succ->right to succParent->right
		if (succParent != node)
			succParent->left = succ->right;
		else
			succParent->right = succ->right;

		// Copy Successor Data to node
		node->key = succ->key;

		// Delete Successor and return node
		free(succ);
		return node;
	}
}

// Driver Code
int main()
{
    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
	Node* root = NULL;
	root = Insert(root, 50);
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
	root = deleteNode(root, 20);
	printf("Modified BST tree after deleting Leaf Node:\n");
	inorder(root);

	printf("\n\nDelete Node with single child: 70\n");
	root = deleteNode(root, 70);
	printf("Modified BST tree after deleting single child Node:\n");
	inorder(root);

	printf("\n\nDelete Node with both child: 50\n");
	root = deleteNode(root, 50);
	printf("Modified BST tree after deleting both child Node:\n");
	inorder(root);    
	return 0;
}
