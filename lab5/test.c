#include <stdio.h>
#include <stdlib.h>

typedef struct Node_struct {
	int key;
	struct Node_struct *left, *right;
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
void inorder(Node* root)
{
	if (root != NULL) 
	{
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}

// Utility function to search a key in a BST
Node* search(Node* root, int key)
{
	// Base Cases: root is null or key is present at root
	if (root == NULL || root->key == key)
		return root;

	// Key is greater than root's key
	if (root->key < key)
		return search(root->right, key);

	// Key is smaller than root's key
	return search(root->left, key);
}

// A utility function to insert
// a new node with given key in BST
Node* insert(Node* node, int key)
{
	// If the tree is empty, return a new node
	if (node == NULL)
	{
		return createNode(key);
	}

	// Otherwise, recur down the tree
	if (key < node->key)
	{
		node->left = insert(node->left, key);
	}
	else if (key > node->key)
	{
		node->right = insert(node->right, key);
	}

	// Return the (unchanged) node pointer
	return node;
}

// /* Given a binary search tree and a key, this function
// deletes the key and returns the new root */
// struct Node* deleteNode(struct Node* root, int k)
// {
// 	// Base case
// 	if (root == NULL)
// 		return root;

// 	// Recursive calls for ancestors of
// 	// node to be deleted
// 	if (root->key > k) {
// 		root->left = deleteNode(root->left, k);
// 		return root;
// 	}
// 	else if (root->key < k) {
// 		root->right = deleteNode(root->right, k);
// 		return root;
// 	}

// 	// We reach here when root is the node
// 	// to be deleted.

// 	// If one of the children is empty
// 	if (root->left == NULL) {
// 		struct Node* temp = root->right;
// 		free(root);
// 		return temp;
// 	}
// 	else if (root->right == NULL) {
// 		struct Node* temp = root->left;
// 		free(root);
// 		return temp;
// 	}

// 	// If both children exist
// 	else {

// 		struct Node* succParent = root;

// 		// Find successor
// 		struct Node* succ = root->right;
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
// 		if (succParent != root)
// 			succParent->left = succ->right;
// 		else
// 			succParent->right = succ->right;

// 		// Copy Successor Data to root
// 		root->key = succ->key;

// 		// Delete Successor and return root
// 		free(succ);
// 		return root;
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
	root = insert(root, 50);
	insert(root, 30);
	insert(root, 20);
	insert(root, 40);
	insert(root, 70);
	insert(root, 60);
	insert(root, 60);
	insert(root, 80);

	// Print inorder traversal of the BST
	inorder(root);

	// Key to be found
	int key = 6;

	// Searching in a BST
	if (search(root, key) == NULL)
		printf("%d not found\n", key);
	else
		printf("%d found\n", key);

	key = 60;

	// Searching in a BST
	if (search(root, key) == NULL)
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
