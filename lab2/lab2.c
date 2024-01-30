#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node_struct{
    char data;
    struct Node_struct* nextNodePtr;
    struct Node_struct* head;
    struct Node_struct* tail;
    int size;
} Node;

// Function to create a new Node
Node* createNode () 
{
    Node* newNode = (Node*) malloc (sizeof(Node));
    newNode->head = NULL;
    newNode->tail = NULL;
    newNode->size = 0;
    return newNode;
}

//Create a Linked List for the integer type data
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

//addHead() function: Insert at the head
void addHead (Node* node, char data) //add Node
{
    Node* newNodeHead = (Node*) malloc (sizeof(Node));
    newNodeHead->data = data;
    newNodeHead->nextNodePtr = node->head;
    node->head = newNodeHead;
    if (node->tail == NULL) //if no node has been added yet
    {
        node->tail = node->head;
    }
    node->size++;
}

//removeHead() function: Remove at the head
char removeHead (Node* node) 
{
    if (node->head == NULL)
    {
        printf("Error: The list is empty\n");
    }

    Node* tempNode = node->head;
    char removedData = tempNode->data;

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

//removeHead() function: Remove at the head
char removeHeadInt (Int_Node* node) //add Node
{
    if (node->head == NULL)
    {
        printf("Error: The list is empty\n");
    }

    Int_Node* tempNode = node->head;
    char removedData = tempNode->data;

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

//addTail() function: Insert at the tail
void addTail (Node* node, char data) //add Node
{
    Node* newNodeTail = (Node*) malloc (sizeof(Node));
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

//addTail() function: Insert at the tail
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

//removeTail() function: Remove at the tail
char removeTail(Node* node) //add Node
{
    if (node->head == NULL)
    {
        printf("Error: The list is empty\n");
        return -1;
    }

    Node* currentNode = node->head;
    Node* tempNode = node->tail;
    char removedCharacter = tempNode->data;

    if (node->head == node->tail)
    {
        // Only one node in the list
        node->head = node->tail = NULL;
    }
    else
    {
        // Traverse the list to find the second-to-last node
        while (currentNode->nextNodePtr != node->tail)
        {
            currentNode = currentNode->nextNodePtr;
        }
        // Update tail and free the last node
        node->tail = currentNode;
        node->tail->nextNodePtr = NULL;
    }

    free (tempNode);
    node->size--;
    return removedCharacter;
}

//Check if the stack is empty
int isEmpty (Node* node) //add Node
{
    return node->size == 0;
}

//Check if the stack is empty
int isEmptyInt (Int_Node* node) //add Node
{
    return node->size == 0;
}

//Pop the last item out of the stack and return the popped value
char pop (Node* node)
{
    if (isEmpty (node))
    {
        printf("Error: The list is empty\n");
        return -1;
    }
    char poppedData = removeHead (node);
    return poppedData; //return head->data will cause error cuz what if head->data is NULL, it will return a NULL pointer
}

//Remove node at the head
char deQueue (Node* node) 
{
    if (isEmpty (node))
    {
        printf("Error: The list is empty\n"); //why do we need this function, this is the same as pop () lol
        return -1;
    }
    char poppedData = removeHead (node);
    return poppedData; //return head->data will cause error cuz what if head->data is NULL, it will return a NULL pointer
}

//Return the size of the items in the stack
int Size (Node* node) 
{
    return node->size; 
}

//Content of the Head stack
char getFirst (Node* node) 
{
    if (isEmpty (node)) 
    {
        printf("Warning: No item inside the stack.\n");
        return -1;
    }
    return node->head->data; //we can return this even if head->data
}

//Content of the Tail stack
char getLast (Node* node) 
{
    if (isEmpty (node)) 
    {
        printf("Warning: No item inside the stack.\n");
        return -1;
    }
    return node->tail->data; //we can return this even if tail->data
}

//Print the stack like it was viusalize in a push pop way
void printStack (Node* node) 
{
    Node* currentNode = node->head;
    while (currentNode != NULL) 
    {
        printf ("\n| %c |", currentNode->data);
        currentNode = currentNode->nextNodePtr;
    }
}

// Print the stack from head to tail using recursive
void printStackRecursive(Node* node) //must put head node here or else infinite loop
{
    if (node == NULL) 
    {
        return; // Base case: if node is NULL, return
    }
    printf("\n| %c |", node->data); // Print current node's data
    printStackRecursive (node->nextNodePtr); // Recur for the next node
}

//Make the Linked List Empty
void emptyList (Node* node) 
{
   Node* currentNode = node->head;
   Node* nextNode;

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

//Make the Linked List Empty
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

//Bracket Matching function [({})] is good; }{[], ({}] is wrong
int BracketMatch (Node* node, char* string, int size)
{
    int flag = 0; //use flag instead of return 1, -1 cuz need to free the stack before returning

    //Scanning the string each array for the opening/closing group symbol parenthesis
    for (int i = 0; i < size; i++)
    {
        // Check if the current character is valid
        if (strchr ("{}[]()0123456789+-*/", string[i]) == NULL)
        {
            printf("Warning: Invalid character '%c' in the string. Please use the following character: {,},[,],(,),0,1,2,3,4,5,6,7,8,9,+,-,*,/.\n", string[i]);
            flag = -1;
            break;
        }

        //if string[i] is an opening grouping symbol then push to the stack
        if (string[i] == '(' ||
            string[i] == '{' || 
            string[i] == '[')
        {
            addHead (node, string[i]); //add Node and main
        }
        //if string[i] is a closing grouping symbol then
        else if (string[i] == ')' ||
                 string[i] == '}' || 
                 string[i] == ']')
        {
            //if the stack is empty return false
            if (isEmpty (node)) 
            {
                printf("Warning: No items in the stack to match with.\n");
                flag = -1;
                break;
            }

            //If the item of the pop stack does not match the type of string[i] then return false
            char pop_character = pop (node); 

            if ((pop_character == '(' && string[i] != ')') ||
                (pop_character == '{' && string[i] != '}') ||
                (pop_character == '[' && string[i] != ']'))
            {
                printf("Warning: Wrong type/order of parenthesis.\n");
                flag = -1;
                break;
            }
        }
    }

    //if at the end the stack is empty then return true, else the Bracket is not match
    if (isEmpty (node) && flag == 0) //add Node
    {
        printf("Every symbol matched.\n");
        flag = 1;
    }
    else if (flag == 0)
    {
        printf("Warning: Some parenthesis symbol were never matched.\n");
        flag = -1;   
    }

    // Free the memory allocated for the stack
    emptyList (node); //add Node

    return flag;
}

//Merged 2 Sorted Queue A and Queue B into Queue S
void mergeSortedQueues (Int_Node* queueA, Int_Node* queueB, Int_Node* queueS) 
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

    // Free memory for queues A and B
    emptyListInt (queueA);
    emptyListInt (queueB);
}

// Display the menu options.
void menu(void) 
{
    puts("\nEnter your choice:\n"
    " 1. Push.\t3. enQueue.\n"
    " 2. Pop.\t4. deQueue.\n"
    " 5. Remove Bottom.\n"
    " 6. Check Empty.\t7. Check Size.\n"
    " 8. Top Stack Content.\t9. Bottom Stack Content.\n"
    " 10. Print Stack Recursively.\n"
    " 11. Bracket Matching.\n"
    " 12. Merged 2 Sorted List of Integers.\n"
    " 13. Performance test for Merging 2 Sorted List.\n"
    " 0. Exit.\n");
}

int main() {
    int choice = 0;
    Node* node = NULL;
    node = createNode();
    char data, string[100];
    Node* nodeBracket = NULL;
    
    Int_Node* queueA = NULL;
    Int_Node* queueB = NULL;
    Int_Node* queueS = NULL;
    
    while (1) 
    {
        menu ();
        scanf("%d", &choice);

        switch (choice) 
        {
            //Press 1 to let user enter new item and push it in the stack, you can press 1 *string here* to push a bunch of char at the same time
            case 1:
                printf ("Enter any word to push in the stack: ");
                scanf (" %c", &data);
                addHead (node, data);
                printStack (node);
                //printStackRecursive (node->head);
                printf ("\n");
                break;
            
            //Press 2 to Pop item out of the stack
            case 2:
                data = pop (node);
                printf("Item Popped out of the stack: %c\n", data);
                printStack (node);
                //printStackRecursive (node);
                printf("\n");
                break;

            //Press 3 to let user enter new item and push it in the stack, you can press 1 *string here* to push a bunch of char at the same time
            case 3:
                printf ("Enter any word to enQueue in the stack: ");
                scanf (" %c", &data);
                addTail (node, data);
                printStack (node);
                //printStackRecursive (node);
                printf ("\n");
                break;
            
            //Press 4 to deQueue item out of the stack
            case 4:
                data = deQueue (node);
                printf("Item deQueue out of the stack: %c\n", data);
                printStack (node);
                //printStackRecursive (node);
                printf("\n");
                break;     

            //Press 5 to Remove Bottom item out of the stack
            case 5:
                data = removeTail (node);
                printf("Item at the bottom removed out of the stack: %c\n", data);
                printStack (node);
                //printStackRecursive (node);
                printf("\n");
                break;             

            //Press 6 to check if stack is empty
            case 6:
                if (isEmpty (node))
                {
                    printf("The Stack is empty\n");
                }
                else 
                {
                    printf("The Stack is not empty\n");
                }
                break;

            //Press 7 to see the current stack size
            case 7:
                printf("Current size of the Stack is: %d\n", Size (node));
                break;

            //Press 8 to see the content of the tops stack
            case 8:
                data = getFirst (node);
                printf("Content of the Top Stack: %c\n", data);
                break;

            //Press 9 to see the content of the tops stack
            case 9:
                data = getLast (node);
                if (data != -1) 
                {
                    printf("Content of the Bottom Stack: %c\n", data);
                }
                break;
            
            //Press 10 to print the whole stack recursively
            case 10:
                //printStack (node);
                printStackRecursive (node->head);
                printf("\n");
                break;

            //Press 11 to use the Bracket Matching function for a string
            case 11:
                nodeBracket = createNode();
                printf("Enter the string with parenthesis: ");
                
                //User enter the string, added getchar() to help with the input buffer
                getchar();
                fgets(string, sizeof(string), stdin);
                string[strlen(string)-1] = '\0';

                BracketMatch (nodeBracket, string ,strlen (string));
                break;

            //Press 11 to use the Bracket Matching function for a string
            case 12:
                // Initialize queues
                queueA = createNodeInt();
                queueB = createNodeInt();
                queueS = createNodeInt();

                // Sample data for lists A and B
                int listA[] = {10,11,12,13};
                int listB[] = {1,2,3,4};

                // Enqueue elements from lists A and B into their respective queues
                for (int i = 0; i < sizeof(listA) / sizeof(listA[0]) ; i++)
                {
                    addTailInt (queueA, listA[i]);
                }
                
                for (int i = 0; i < sizeof(listB) / sizeof(listB[0]); i++)
                {
                    addTailInt (queueB, listB[i]);
                }
                

                // Merge queues A and B into queue S
                mergeSortedQueues (queueA, queueB, queueS);

                // Print the merged queue S
                printf("Merged Queue S: ");
                while (!isEmptyInt (queueS)) 
                {
                    printf("%d ", removeHeadInt (queueS));
                }
                printf("\n");

                // Free memory allocated to queues
                free(queueA);
                free(queueB);
                free(queueS);

                break;
            
            // //Test to see the running time for the function mergeSortedQueues()
            // case 13:
            //     // Loop for different string lengths
            //     for (int n = 2; n <= 512*2; n *= 2) //1048576
            //     {
            //         char* stringBig = (char*)malloc((n + 1) * sizeof(char)); // Allocate memory for the string
            //         Stack* stack = Create_Stack (n);

            //         // Fill the 1st half with '0'
            //         for (int i = 0; i < n/2; ++i) 
            //         {
            //             stringBig[i] = '0';
            //         }
            //         // Fill the 2nd half with '1'
            //         for (int i = n/2; i < n; ++i) 
            //         {
            //             stringBig[i] = '1';
            //         }
            //         stringBig[n] = '\0'; // Null-terminate the last array of the string

            //         printf("\nRunning Language Recognizer function with n = %d\n", n);
            //         printf("%s\n", stringBig); //remove comment to see the string

            //         // Run the LanguageRecognizer function and measure the time
            //         LanguageRecognizer(stringBig, n);

            //         // Free the memory allocated for the stringBig
            //         free(stringBig);
            //     }
            //     break;

            //Press 0 to exit the program
            case 0:
                exit(0);

            default:
                printf ("Invalid choice! Please choose from 0 to 9\n");
        }
    }
    return 0;
}

// // FUnction to enter a string and return a bunch of integers based on the ',' 
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main () {
//     int a,b,c,d,e;
//     char dtm[100];
    
//     fgets(dtm, sizeof(dtm), stdin);

//    //strcpy(dtm, "1, 2, 3, 4, 5" );
//    sscanf(dtm, "%d, %d, %d, %d, %d\n", &a, &b, &c, &d, &e);

//    printf("%d %d %d %d %d", a, b, c, d, e );
    
//    return(0);
// }