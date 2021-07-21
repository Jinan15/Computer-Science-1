#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DEFAULT_CAP 10

// typedefs to make life easier (given code)
typedef struct Piece Piece;
typedef struct List List;
typedef struct Board Board;

// piece struct (given code)
struct Piece {
    int rank, file, ind;
};

// list struct (given code)
struct List {
    int identifier;
    Piece ** arr;
    int size, cap;
};

// board struct (given code)
struct Board {
    List ** arr;
    int size, cap;
};

// Prototypes (given code)
Board * createBoard();
List * createRank(int);
Piece * createPiece(int, int, int);
void destroyBoard(Board *);
void destroyRank(List *);
void destroyPiece(Piece *);
void addPieceToRank(List *, Piece *);
void addRankToBoard(Board *, List *);
void expandRank(List *);
void expandBoard(Board *);
List * findRank(Board *, int);

// Prototypes (not given)
List * findID(Board *, int);
void findHits(Board *, Board *, int);

// Main
int main()
{
    Board * rows = createBoard(); //creating board (sorted by rows)
    Board * cols = createBoard(); //creating board (sorted by columns)

    //n is the number of inputs given my user
    int n, rank, file;
    scanf("%d", &n);

    //iterates to each line of input and stores piece in rank
    //if rank does not exist, findRank creates a new rank (row or column)
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &rank, &file);
        Piece * p = createPiece(rank, file, i);
        List * listRow = findRank(rows, rank);
        List * listCol = findRank(cols, file);
        addPieceToRank(listRow, p);
        addPieceToRank(listCol, p);
    }

    printf("\n"); //separates input from output my 1 line

    //for loop iterates through every piece in order
    //and finds all possible attacks
    for(int i = 0; i < n; i++) {
        findHits(rows, cols, i);
        printf("\n");
    }

    destroyBoard(rows);
    destroyBoard(cols);
    return 0;
}

// Creates a board
Board * createBoard() {
    Board * ret;

    ret = (Board *) calloc(1, sizeof(Board));

    ret->size = 0;
    ret->cap = DEFAULT_CAP;
    ret->arr = (List **) calloc(DEFAULT_CAP, sizeof(List *));

    return ret;
}

// Creates a rank which can be either a row or column
List * createRank(int ind) {
    List * ret;

    ret = (List *) calloc(1, sizeof(List));

    ret->identifier = ind;
    ret->size = 0;
    ret->cap = DEFAULT_CAP;
    ret->arr = (Piece **) calloc(DEFAULT_CAP, sizeof(Piece *));

    return ret;
}

// Creates a piece with inputted values
Piece * createPiece(int rank, int file, int ind) {
    Piece * ret;

    ret = (Piece *) calloc(1, sizeof(Piece));

    ret->rank = rank;
    ret->file = file;
    ret->ind = ind;

    return ret;
}

// Adds piece to rank
void addPieceToRank(List * l, Piece * p) {
    if(l->size == l->cap) { //expands rank if size reaches cap
        expandRank(l);
    }

    l->arr[l->size] = p;
    l->size++;
}

// Adds rank to board
void addRankToBoard(Board * b, List * l) {
    if(b->size == b->cap) { //expands board if size reaches cap
        expandBoard(b);
    }

    b->arr[b->size] = l;
    b->size++;
}

// Expands the capacity of rank by doubling it
void expandRank(List * l) {
    int newCap = l->cap * 2;
    l->arr = (Piece **) realloc(l->arr, newCap * sizeof(Piece *));
    l->cap = newCap;
}

// Expands the capacity of board by doubling it
void expandBoard(Board * b) {
    int newCap = b->cap * 2;
    b->arr = (List **) realloc(b->arr, newCap * sizeof(List *));
    b->cap = newCap;
}

// finds or creates then returns a rank
List * findRank(Board * b, int rank) {
    List * ret;
    // If a rank with inputted id exists in the given board
    // Then the rank is returned
    for(int i = 0; i < b->size; i++) {
        if(b->arr[i]->identifier == rank) {
            return b->arr[i];
        }
    }
    // If rank doesn't exist then a new rank is created
    // and new rank is returned
    ret = createRank(rank);
    addRankToBoard(b, ret);
    return ret;
}

// Finds rank with given piece id and returns rank
List * findID(Board * b, int id) {
    List * ret;
    for(int i = 0; i < b->size; i++) {
        for(int j = 0; j < b->arr[i]->size; j++) {
            if(b->arr[i]->arr[j]->ind == id) {
                return b->arr[i];
            }
        }
    }
    return ret; //this return statement will never hit (ideally)
}

// takes in both boards and piece id (r is row board and c is column board)
void findHits(Board * r, Board * c, int id) {
    //if int stays -1 it means there is no rook that it can attack on that side
    int prevRowID = -1; // holds id of rook if before rook given in row
    int nextRowID = -1; // holds id of rook if after rook given in row
    int prevColID = -1; // holds id of rook if before rook given in column
    int nextColID = -1; // holds id of rook if after rook given in column
    int numHits = 0; // total attacks the given rook can do (if none then 0, max is 4)
    int rank, file; //holds current rooks row and column
    int min = -1, max = INT_MAX;

    List * rowList = findID(r, id); //stores current rooks row
    List * colList = findID(c, id); //stores current rooks column

    //finds current rooks rank and file and stores it
    for(int i = 0; i < rowList->size; i++) {
        if(rowList->arr[i]->ind == id) {
            rank = rowList->arr[i]->rank;
            file = rowList->arr[i]->file;
        }
    }

    // Finds if the rook can attack another rook in its row
    for(int i = 0; i < rowList->size; i++) {
        if((rowList->arr[i]->file > file) && (rowList->arr[i]->file < max)) {
            max = rowList->arr[i]->file;
            nextRowID = rowList->arr[i]->ind + 1;
        }
        if((rowList->arr[i]->file < file) && (rowList->arr[i]->file > min)) {
            min = rowList->arr[i]->file;
            prevRowID = rowList->arr[i]->ind + 1;
        }
    }

    min = -1;
    max = INT_MAX;

    // Finds if the rook can attack another rook in its column
    for(int i = 0; i < colList->size; i++) {
        if((colList->arr[i]->rank > rank) && (colList->arr[i]->rank < max)) {
            max = colList->arr[i]->rank;
            nextColID = colList->arr[i]->ind + 1;
        }
        if((colList->arr[i]->rank < rank) && (colList->arr[i]->rank > min)) {
            min = colList->arr[i]->rank;
            prevColID = colList->arr[i]->ind + 1;
        }
    }
    // If the id for the int is not -1 it means the rook can attack another rook
    if (prevRowID != -1) {
        numHits++;
    }
    if (nextRowID != -1) {
        numHits++;
    }
    if (prevColID != -1) {
        numHits++;
    }
    if (nextColID != -1) {
        numHits++;
    }

    printf("%d ", numHits); //prints how many attacks a the given rook can attack

    // prints out the id numbers of rooks the given rook can attack
    if (prevRowID != -1) {
        printf("%d ", prevRowID);
    }
    if (nextRowID != -1) {
        printf("%d ", nextRowID);
    }
    if (prevColID != -1) {
        printf("%d ", prevColID);
    }
    if (nextColID != -1) {
        printf("%d", nextColID);
    }
}

// Frees a board from memory
void destroyBoard(Board * b) {
    for(int i = 0; i < b->size; i++) {
        destroyRank(b->arr[i]); //frees each individual rank
    }
    free(b);
}

// Frees a rank from memory
void destroyRank(List * l) {
    for(int i = 0; i < l->size; i++) {
        destroyPiece(l->arr[i]); //frees each individual piece
    }
    free(l);
}

// Frees a piece from memory
void destroyPiece(Piece * p) {
    free(p);
}
