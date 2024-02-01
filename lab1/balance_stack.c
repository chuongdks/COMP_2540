#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Struct declaration for the Stack
typedef struct Stack_struct {
    int top; //top, keep track of the array
    int maxStack; //added maxStack for the bonus question, change the size of array easily
    char* stack; //data
} Stack;

// Initialize a newStack fromt the struct Stack
Stack* Create_Stack (int maxStack) 
{
    Stack* newStack = (Stack*) malloc (sizeof(Stack));
    newStack->top = -1; //initialize the top as '-1' because the first item in the stack is index as '0', so an empty stack is '-1'
    newStack->maxStack = maxStack; //adjustable maximum number of stack
    newStack->stack = (char*)malloc(newStack->maxStack * sizeof(char)); 

    return newStack;
}

//Check if the stack is empty
int isEmpty (Stack* stack)
{
    return stack->top == -1;
}

//Push items into the stack, check if stack is full
void push (Stack* stack, char items) 
{
    if (stack->top == stack->maxStack - 1) //if the maximum value of the stack reaches in the array
    {
        printf("Warning: Full stack reached.\n");
        return;
    }
    stack->top++;
    stack->stack[stack->top] = items;
}

//Pop the last item out of the stack
char pop (Stack* stack) 
{
    if (isEmpty(stack)) 
    {
        printf("Warning: No item to pop out of the stack.\n");
        return -1;
    }
    return stack->stack[stack->top--];
}

//Return the size of the items in the stack
int Stack_Size (Stack* stack)
{
    return (stack->top) + 1;
}

//Content of the top stack
char top (Stack* stack)
{
    if (isEmpty(stack)) 
    {
        printf("Warning: No item inside the stack.\n");
        return -1;
    }
    return stack->stack[stack->top];
}

//Print the stack like it was viusalize in a push popm way
void printStack (Stack* stack)
{
    for (int i = stack->top; i >= 0; i--)
    {
        printf ("\n| %c |", stack->stack[i]);
    }
}

//Bracket Matching function [({})] is good; }{[], ({}] is wrong
int BracketMatch (char* string, int size)
{
    int flag = 0; //use flag instead of return 1, -1 cuz need to free the stack before returning
    Stack* stack = Create_Stack(50); // Create a new stack

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
            push (stack, string[i]);
        }
        //if string[i] is a closing grouping symbol then
        else if (string[i] == ')' ||
                 string[i] == '}' || 
                 string[i] == ']')
        {
            //if the stack is empty return false
            if (isEmpty(stack)) 
            {
                printf("Warning: No items in the stack to match with.\n");
                flag = -1;
                break;
            }

            //If the item of the pop stack does not match the type of string[i] then return false
            char pop_character = pop(stack); 
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
    if (isEmpty(stack) && flag == 0)
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
    free(stack->stack);
    free(stack);    

    return flag;
}

//Language Recognizer, detect strings contain # of 0 then a # of 1 (00001111, 0011, 01 good; 10, 00111, 0101 bad)
int LanguageRecognizer (char* string, int size)
{
    int zero_counter = 0, one_counter = 0; //not sure what to do with them, prof said secret trick is to count # of 0 and 1
    int flag = 0; //use flag instead of return 1, -1 cuz need to free the stack before returning
    
    Stack* stack = Create_Stack(50); // Create a new stack

    // Start measuring time
    clock_t start_time = clock();

    //Scan the string
    for (int i = 0; i < size; i++)
    {
        //If the items is '0', push it to the stack
        if (string[i] == '0')
        {
            push (stack, string[i]);
            zero_counter++;
        }
        //if the items is '1' then
        else if (string[i] == '1')
        {
            //if the stack is empty return false
            if (isEmpty(stack)) 
            {
                printf("Warning: Detect case where # of '1' > '0' case.\n");
                flag = -1;
                break;
            }
            //if the next item after '1' is '0' (0101) then return false
            if (i + 1 < size && string[i + 1] == '0')
            {
                printf("Warning: Detect a 0101 case.\n");
                flag = -1; 
                break;              
            }
            pop(stack);
            one_counter++;
        }
    }

    //if at the end the stack is empty then return true, else the Bracket is not match
    if (isEmpty(stack) && flag == 0)
    {
        printf("Every number is balance.\n");
        flag = 1;
    }
    else if (flag == 0)
    {
        printf("Warning: Unbalanced number.\n");
        flag = -1;       
    }

    // Stop measuring time
    clock_t end_time = clock();
    // Calculate elapsed time in nanoseconds
    double elapsed_time_ns = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1e9;
    // Print the elapsed time
    printf("Elapsed Time: %.2f nanoseconds\n", elapsed_time_ns);
    
    // Free the memory allocated for the stack
    free(stack->stack);
    free(stack);    

    return flag;
}

// Display the menu options.
void menu(void) 
{
    puts("\nEnter your choice:\n"
    " 1. Push.\n"
    " 2. Pop.\n"
    " 3. Check Empty.\n"
    " 4. Check Size.\n"
    " 5. Content of Top Stack.\n"
    " 6. Print Stack .\n"
    " 7. Bracket Matching.\n"
    " 8. Language recognizer.\n"
    " 9. Performance test for Language recognizer.\n"
    " 0. Exit.\n");
}

int main() {
    int choice;
    char items, string[100];
    char* stringBig = NULL;
    Stack* stack = Create_Stack (50);
    
    while (1) 
    {
        menu ();
        scanf("%d", &choice);

        switch (choice) 
        {
            //Press 1 to let user enter new item and push it in the stack, you can press 1 *string here* to push a bunch of char at the same time
            case 1:
                printf("Enter any word to push in the stack: ");
                scanf(" %c", &items);
                push(stack, items);
                printStack (stack);
                printf("\n");
                break;
            
            //Press 2 to Pop item out of the stack
            case 2:
                items = pop (stack);
                printf("Item Popped out of the stack: %c\n", items);
                printStack (stack);
                printf("\n");
                break;

            //Press 3 to check if stack is empty
            case 3:
                if (isEmpty (stack))
                {
                    printf("The Stack is empty\n");
                }
                else 
                {
                    printf("The Stack is not empty\n");
                }
                break;

            //Press 4 to see the current stack size
            case 4:
                printf("Current size of the Stack is: %d\n", Stack_Size (stack));
                break;

            //Press 5 to see the content of the tops stack
            case 5:
                items = top (stack);
                if (items != -1) 
                {
                    printf("Content of the Top Stack: %c\n", items);
                }
                break;
            
            //Press 6 to print the whole stack
            case 6:
                printStack (stack);
                printf("\n");
                break;

            //Press 7 to use the Bracket Matching function for a string
            case 7:
                printf("Enter the string with parenthesis: ");
                
                //User enter the string, added getchar() to help with the input buffer
                getchar();
                fgets(string, sizeof(string), stdin);
                string[strlen(string)-1] = '\0';

                BracketMatch (string ,strlen(string));
                break;

            //Press 8 to use the Language Recognizer function for a string
            case 8:
                printf("Enter the string with 0n1n: ");

                //User enter the string, added getchar() to help with the input buffer
                getchar();
                fgets(string, sizeof(string), stdin);
                string[strlen(string)-1] = '\0';

                LanguageRecognizer (string ,strlen(string));
                break;
            
            //Test to see the running time for the function LanguageRecognizer()
            case 9:
                // Loop for different string lengths
                for (int n = 2; n <= 512*2; n *= 2) //1048576
                {
                    char* stringBig = (char*)malloc((n + 1) * sizeof(char)); // Allocate memory for the string
                    Stack* stack = Create_Stack (n);

                    // Fill the 1st half with '0'
                    for (int i = 0; i < n/2; ++i) 
                    {
                        stringBig[i] = '0';
                    }
                    // Fill the 2nd half with '1'
                    for (int i = n/2; i < n; ++i) 
                    {
                        stringBig[i] = '1';
                    }
                    stringBig[n] = '\0'; // Null-terminate the last array of the string

                    printf("\nRunning Language Recognizer function with n = %d\n", n);
                    printf("%s\n", stringBig); //remove comment to see the string

                    // Run the LanguageRecognizer function and measure the time
                    LanguageRecognizer(stringBig, n);

                    // Free the memory allocated for the stringBig
                    free(stringBig);
                }
                break;

            //Press 9 to exit the program
            case 0:
                exit(0);

            default:
                printf("Invalid choice! Please choose from 0 to 9\n");
        }
    }
    return 0;
}