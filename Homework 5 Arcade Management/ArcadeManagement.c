#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 20

// Typedefs
typedef struct Stack Stack;
typedef struct Node Node;

// struct
struct Stack {
    Node * heads;
};
struct Node {
    char names[MAXSIZE + 1];
    int tokens;
    Node * next;
};

// Prototypes for linked list
Node * createNode(char * name, int tok);
Node * addHead(Node * head, char * name, int tok);
Node * removeHead(Node * head);
void   destroyNode(Node * node);

// Prototypes for stacks
Stack * createStack();
void    push(Stack * stack, char * name, int tok);
void    pushMVP(Stack * stack, char * name, int tok);
void    pop(Stack * stack);
void    printStack(Stack * stack);

// Main runs program
int main()
{
    // Int t is type of process inputted by user
    // Int m is number of token inputted by user
    int t, m;

    // People stack holds everyone in the arcade in the order they came in
    // MVP stack holds all the MVPs in the arcade in the order they came in
    Stack * people = createStack();
    Stack * MVP = createStack();

    // Do while loop runs until a 0 is inputted
    do {
        scanf("%d", &t); // Scans t
        if(t == 1) { // Adds new node
            // Gets token and name input from user and stores it
            char name[MAXSIZE + 1];
            scanf("%d %s", &m, name);
            // Adds new person to people stack and MVP stack if criteria met
            push(people, name, m);
            pushMVP(MVP, name, m);
        } else if(t == 2) { // Removes node
            // If the last person to enter is the current MVP
            // They are popped from the MVP stack
            if(!(strcmp(people->heads->names, MVP->heads->names))) {
                pop(MVP);
            }
            // Pops the last person to enter in people stack
            pop(people);
        } else if(t == 3) { // Prints MVP
            printf("%s\n", MVP->heads->names);
        }
    } while ( t != 0); // Stops the program if t = 0
    return 0;
}

// Allocates memory for a node and sets name and token to given values
Node * createNode(char * name, int tok) {
    Node * ret = calloc(1, sizeof(Node));

    strcpy(ret->names, name);
    ret->tokens = tok;
    ret->next = NULL;

    return ret;
}

// Adds a NEW node to head of the given stack
Node * addHead(Node * head, char * name, int tok) {
    Node * newHead = createNode(name, tok);
    newHead->next = head;
    return newHead;
}

// Removes the head node in the given stack
Node * removeHead(Node * head) {
    if(head == NULL) { // If head is NULL then NULL is returned
        return NULL;
    }
    Node * newHead = head->next;
    destroyNode(head);
    return newHead;
}

// Frees node from memory
void destroyNode(Node * node) {
    free(node);
}

// Allocates memory for stack and sets head node to NULL
Stack * createStack() {
    Stack * ret = calloc(1, sizeof(Stack));
    ret->heads = NULL;
    return ret;
}

// Adds a new node to the head of the stack
void push(Stack * stack, char * name, int tok) {
    if(stack->heads == NULL) { // If the stack is empty then create a new node
        stack->heads = createNode(name, tok);
    } else {
        Node * newhead = addHead(stack->heads, name, tok);
        stack->heads = newhead;
    }
}

// Adds a new node to the head of the stack only if
// the node is the MVP, meaning it has greater than or equal to
// amount of tokens
void pushMVP(Stack * stack, char * name, int tok) {
    if(stack->heads == NULL) { // If stack is empty add a new Node
        stack->heads = createNode(name, tok);
    } else if(stack->heads->tokens <= tok) { // Compare if new person is MVP
        // Add new node to stack
        Node * newhead = addHead(stack->heads, name, tok);
        stack->heads = newhead;
    }
}

// Method prints the stack - for testing purposes
void printStack(Stack * stack) {
    Node * cur = stack->heads;
    while(cur->next != NULL) {
        printf("%s %d\n", cur->names, cur->tokens);
        cur = cur->next;
    }
    printf("%s %d\n", cur->names, cur->tokens);
}

// Removes the head of the stack and sets new head of stack
void pop(Stack * stack) {
    Node * oldHead = stack->heads;
    Node * newHead = removeHead(oldHead);
    stack->heads = newHead;
}



