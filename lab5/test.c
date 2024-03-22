#include <stdio.h>
#include <stdlib.h>

typedef struct Node_struct {
	int key;
	struct Node_struct *left;
	struct Node_struct *right;
} Node;

// A utility function to create a new BST node
Node* createNode(int item)
{
	Node* newNode = (Node*) malloc (sizeof(Node));
	newNode->key = item;
	newNode->left = newNode->right = NULL;
	return newNode;
}

// A utility function to do inorder traversal of BST
void inorder(Node* node)
{
	if (node != NULL) 
	{
		inorder(node->left);
		printf("%d ", node->key);
		inorder(node->right);
	}
}

// A utility function to check if the node is an External node
int isExternal(Node* node)
{
	return node == NULL;
}

// Utility function to search a key in a BST
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

// A utility function to insert a new node with given key in BST
Node* Insert(Node* node, int key)
{
	// Base case, Node is empty so create a new node with NULL left and right child
	if (isExternal(node))
	{
		return createNode(key);
	}

	// Otherwise, recur down the tree
	if (key <= node->key) // If Key is less than node, move to the left Child
	{
		node->left = Insert(node->left, key);
	}
	else if (key > node->key) // // If Key is more than node, move to the right Child. Add '>=' if u want equal key to move on the right tree instead of left tree
	{
		node->right = Insert(node->right, key);
	}
}

// // Insertion Method based on the slide, doesnt work, waste 1.5 hours tryinh to figure out why, the TreeSearch doesnt move the fucking Node
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

// /* Given a binary search tree and a key, this function deletes the key and returns the new node */
// struct Node* deleteNode(struct Node* node, int k)
// {
// 	// Base case
// 	if (node == NULL)
// 		return node;

// 	// Recursive calls for ancestors of
// 	// node to be deleted
// 	if (node->key > k) {
// 		node->left = deleteNode(node->left, k);
// 		return node;
// 	}
// 	else if (node->key < k) {
// 		node->right = deleteNode(node->right, k);
// 		return node;
// 	}

// 	// We reach here when node is the node
// 	// to be deleted.

// 	// If one of the children is empty
// 	if (node->left == NULL) {
// 		struct Node* temp = node->right;
// 		free(node);
// 		return temp;
// 	}
// 	else if (node->right == NULL) {
// 		struct Node* temp = node->left;
// 		free(node);
// 		return temp;
// 	}

// 	// If both children exist
// 	else {

// 		struct Node* succParent = node;

// 		// Find successor
// 		struct Node* succ = node->right;
// 		while (succ->left != NULL) {
// 			succParent = succ;
// 			succ = succ->left;
// 		}

// 		// Delete successor. Since successor
// 		// is always left child of its parent
// 		// we can safely make successor's right
// 		// right child as left of its parent.
// 		// If there is no succ, then assign
// 		// succ->right to succParent->right
// 		if (succParent != node)
// 			succParent->left = succ->right;
// 		else
// 			succParent->right = succ->right;

// 		// Copy Successor Data to node
// 		node->key = succ->key;

// 		// Delete Successor and return node
// 		free(succ);
// 		return node;
// 	}
// }

// Driver Code
int main()
{
	/* Let us create following BST
			50
		/	 \
		30	 70
		/ \ / \
	20 40 60 80 */
	Node* root = NULL;
	root = Insert(root, 50);
	Insert(root, 30);
	Insert(root, 20);
	Insert(root, 40);
	Insert(root, 40);
	Insert(root, 70);
	Insert(root, 60);
	Insert(root, 60);
	Insert(root, 80);
	Insert(root, 45);
	Insert(root, 67);

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

    // // Delete
	// printf("Original BST: ");
	// inorder(root);

	// printf("\n\nDelete a Leaf Node: 20\n");
	// root = deleteNode(root, 20);
	// printf("Modified BST tree after deleting Leaf Node:\n");
	// inorder(root);

	// printf("\n\nDelete Node with single child: 70\n");
	// root = deleteNode(root, 70);
	// printf("Modified BST tree after deleting single child Node:\n");
	// inorder(root);

	// printf("\n\nDelete Node with both child: 50\n");
	// root = deleteNode(root, 50);
	// printf("Modified BST tree after deleting both child Node:\n");
	// inorder(root);    
	return 0;
}
