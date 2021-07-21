#include <stdio.h>
#include <stdlib.h>

// typedefs
typedef struct Node Node;

// struct
struct Node {
    Node * Left;
    Node * Right;
    int actNum;
    int victor;
};

// Prototypes
Node * createNode(int n);

Node * insertNode(Node * root, int n);

void findVictor(Node * root, int * p);

// excitement is global because its easier
long long int excitement = 0;

int main()
{
    // gets and stores total number of players
    int numPlayers;
    scanf("%d", &numPlayers);

    // root is parent node of the BST
    Node * root = NULL;

    // creating 2 arrays and allocating memory
    int * activation = calloc(numPlayers - 1, sizeof(int));
    int * skill = calloc(numPlayers, sizeof(int));

    // gets the activation order
    for(int i = 0; i < numPlayers - 1; i++) {
        scanf("%d", &activation[i]);
    }

    // creates BST by inserting nodes (reverse order of activation array)
    for(int i = numPlayers - 2; i >= 0; i--) {
        root = insertNode(root , activation[i]);
    }

    // gets all the players skills and stores it in array
    for(int i = 0; i < numPlayers; i++) {
        scanf("%d", &skill[i]);
    }

    findVictor(root, skill);

    printf("%lld", excitement);

    return 0;
}

// allocates memory for node, n is the activation order of node
Node * createNode(int n) {
    Node * ret = calloc(1, sizeof(Node));
    ret->actNum = n;
    ret->Left = NULL;
    ret->Right = NULL;
    ret->victor = -1;
    return ret;
}

// inserts node into BST
Node * insertNode(Node * root, int n) {
    // When empty spot is found, new node is created and inserted (base case)
    if(root == NULL) {
        root = createNode(n);
        return root;
    }
    // If the root is bigger than n (activation number)
    // Then we go left
    if (n < root->actNum) {
        root->Left = insertNode(root->Left, n);
    }
    // If the root is smaller than n (activation number)
    // Then we go right
    if (n > root->actNum) {
        root->Right = insertNode(root->Right, n);
    }
    return root;
}

// Finds the excitement of the tournament
// takes the root node and player array as inputs
void findVictor(Node * root, int * p) {
    // Part 1 - traverse BST in post order
    // base case for when a empty node is found
    if (root == NULL) {
        return;
    }
    // find left children first the right children until leaf is found
    findVictor(root->Left, p);
    findVictor(root->Right, p);

    // index is found by using the nodes activation number and subtracting 1
    // Because arrays are 0 based
    int index = root->actNum - 1;

    // If both left and right child nodes of root are empty
    // Then take 2 players from they player array and calculate excitement
    // Then set the root victor with whoever had the higher skill rating
    if(root->Left == NULL && root->Right == NULL) {
        if(p[index] > p[index + 1]) {
            excitement += p[index] - p[index + 1];
            root->victor = p[index];
        } else {
            excitement += p[index + 1] - p[index];
            root->victor = p[index + 1];
        }
    }

    // If the right child of root is empty and left side has a node
    // Then take right side player from they player array
    // and the victor from the left sub tree and calculate excitement
    // Then set the root victor with whoever had the higher skill rating
    if(root->Left != NULL && root->Right == NULL) {
        if(root->Left->victor > p[index + 1]) {
            excitement += root->Left->victor - p[index + 1];
            root->victor = root->Left->victor;
        } else {
            excitement += p[index + 1] - root->Left->victor;
            root->victor = p[index + 1];
        }
    }

    // If the left child of root is empty and right side has a node
    // Then take left side player from they player array
    // and the victor from the right sub tree and calculate excitement
    // Then set the root victor with whoever had the higher skill rating
    if(root->Left == NULL && root->Right != NULL) {
        if(p[index] > root->Right->victor) {
            excitement += p[index] - root->Right->victor;
            root->victor = p[index];
        } else {
            excitement += root->Right->victor - p[index];
            root->victor = root->Right->victor;
        }
    }

    // If both the left and right side has a node
    // Then take victor from the left and right sub tree and calculate excitement
    // Then set the root victor with whoever had the higher skill rating
    if(root->Left != NULL && root->Right != NULL) {
        if(root->Left->victor > root->Right->victor) {
            excitement += root->Left->victor - root->Right->victor;
            root->victor = root->Left->victor;
        } else {
            excitement += root->Right->victor - root->Left->victor;
            root->victor = root->Right->victor;
        }
    }
}




