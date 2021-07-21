#include <stdio.h>
#include <stdlib.h>

#define SOLVABLE 1
#define NOT_SOLVABLE 0

// Stores basic grid and input info
char ** grid; // Stores the grid, initially empty

int ** rowInput; // Stores the row input
int ** colInput; // Stores the column input

int row, col; // Stores total number of rows and columns in grid

// allocates memory for grid
void createGrid() {
    grid = calloc(row, sizeof(char *));
    for(int i = 0; i < row; i++) {
        grid[i] = calloc(col, sizeof(char));
    }
}

// Bad function but allocates memory and stores row and column input
void readInput() {
    // Creating row and col number of 1 dimensional arrays
    rowInput = calloc(row, sizeof(int *));
    colInput = calloc(col, sizeof(int *));

    int num = 0;

    // Gets and stores row input by row
    for(int i = 0; i < row; i++) {
        scanf("%d", &num);
        rowInput[i] = calloc(num + 1 , sizeof(int));
        rowInput[i][0] = num;

        for(int j = 1; j < num + 1; j++) {
            scanf("%d", &rowInput[i][j]);
        }
    }

    // Gets and stores column input by row
    for(int i = 0; i < col; i++) {
        scanf("%d", &num);
        colInput[i] = calloc(num + 1 , sizeof(int));
        colInput[i][0] = num;

        for(int j = 1; j < num + 1; j++) {
            scanf("%d", &colInput[i][j]);
        }
    }
}

// Prints the final grid
void printGrid() {
    for(int i = 0; i < row; i++, printf("\n")) {
        for(int j = 0; j < col; j++) {
            printf("%c", grid[i][j]);
        }
    }
}

// Prints a specified row - testing purposes only
void printRow(int r) {
    for(int i = 0; i < col; i++) {
        printf("%c ", grid[r][i]);
    }
    printf("\n");
}

// checks if data in specified position (row, column) is valid
// returns 0 (NOT_SOLVABLE) if data in position is not valid
// returns 1 (SOLVABLE) if data in position is valid
// 2 parts to function, part 1 checks row, part 2 checks column
int isValid(int r, int c) {
    // Part 1
    int curIndex = 0; // tracks current index of groupRowArray
    int numberOfGroups = 0; // Tracks the number of groups in groupsRowArray
    int * groupRowArray = calloc(rowInput[r][0] + 1, sizeof(int)); // Stores each group in the row
    rowInput[r][rowInput[r][0] + 1] = 0; // allocates memory for an additional index and sets it to 0 - edge case

    char prevChar = 'r'; // Stores previous character in array

    // Iterates through row up to the current position
    for(int i = 0; i <= c; i++) {
        // If the current position is B then add one to the current group of Black flowers
        if(grid[r][i] == 'B') {
            groupRowArray[curIndex]++;
        }
        // If prevChar is B and current char is r then create a knew group of black flowers
        if(prevChar == 'B' && grid[r][i] == 'r') {
            // If the previous group (the one just completed) has less flowers than needed
            // return NOT_SOLVABLE
            if(groupRowArray[curIndex] < rowInput[r][curIndex + 1]) {
                return NOT_SOLVABLE;
            }
            curIndex++;
        }
        // If prevChar is r and current char is B then add 1 to number of groups
        if(prevChar == 'r' && grid[r][i] == 'B') {
            numberOfGroups++;
        }
        // If the number of groups exceed the number of groups given (inputted by user)
        // Then return NOT_SOLVABLE
        if(numberOfGroups > rowInput[r][0]) {
            return NOT_SOLVABLE;
        }
        prevChar = grid[r][i]; // Set previous char to current char
    }
    // Iterates through the groupRowArray and rowInput array
    for(int i = 0; i < numberOfGroups; i++) {
        // If group row array at current group is larger than expected
        // Then return NOT_SOLVABLE
        // RowInput is i + 1 in column because at index 0 the total number of groups is stored
        if(groupRowArray[i] > rowInput[r][i + 1]) {
            return NOT_SOLVABLE;
        }
    }

    // Part 2
    // Reset common variables to 0 and r
    curIndex = 0;
    numberOfGroups = 0;
    prevChar = 'r';

    int * groupColArray = calloc(colInput[c][0] + 1, sizeof(int)); // Stores each group in column
    colInput[c][colInput[c][0] + 1] = 0; // Allocates memory for an additional index and sets it to 0 - edge case

    // Iterates through row up to the current position
    for(int i = 0; i <= r; i++) {
        // If the current position is B then add one to the current group of Black flowers
        if(grid[i][c] == 'B') {
            groupColArray[curIndex]++;
        }
        // If prevChar is B and current char is r then create a knew group of black flowers
        if(prevChar == 'B' && grid[i][c] == 'r') {
            // If the previous group (the one just completed) has less flowers than needed
            // return NOT_SOLVABLE
            if(groupColArray[curIndex] < colInput[c][curIndex + 1]) {
                return NOT_SOLVABLE;
            }
            curIndex++;
        }
        // If prevChar is r and current char is B then add 1 to number of groups
        if(prevChar == 'r' && grid[i][c] == 'B') {
            numberOfGroups++;
        }
        // If the number of groups exceed the number of groups given (inputted by user)
        // Then return NOT_SOLVABLE
        if(numberOfGroups > colInput[c][0]) {
            return NOT_SOLVABLE;
        }
        prevChar = grid[i][c]; // Set previous char to current char
    }

    //If we are at the last row check if each group in the column is greater than or less than expected group value
    if(r == (row - 1)) {
        // Iterates through the groupColArray and colInput array
        for(int i = 0; i < numberOfGroups; i++) {
            // If group column array at current group is smaller or larger than expected
            // Then return NOT_SOLVABLE
            // RowInput is i + 1 in column because at index 0 the total number of groups is stored
            if(groupColArray[i] != colInput[c][i + 1]) {
                return NOT_SOLVABLE;
            }
        }
        if(numberOfGroups < colInput[c][0]) {
            return NOT_SOLVABLE;
        }
    } else {
        // Iterates through the groupColArray and colInput array
        for(int i = 0; i < numberOfGroups; i++) {
            // If group col array at current group is larger than expected
            // Then return NOT_SOLVABLE
            // ColInput is i + 1 in column because at index 0 the total number of groups is stored
            if(groupColArray[i] > colInput[c][i + 1]) {
                return NOT_SOLVABLE;
            }
        }
    }

    return SOLVABLE;
}

// Checks if the entire row is valid
int isRowValid(int r) {
    int numberOfGroups = 0; // Tracks the total groups (and current group) in groupRowArray
    int * groupRowArray = calloc(rowInput[r][0] + 1, sizeof(int)); // Stores all the groups of black flowers
    rowInput[r][rowInput[r][0] + 1] = 0; // edge case

    char prevChar = 'r'; // holds previous flower

    // Iterates through all flowers in row
    for(int i = 0; i < col; i++) {
        // If current flower is black then add 1 to current group (of black flowers)
        if(grid[r][i] == 'B') {
            groupRowArray[numberOfGroups]++;
        }
        // If the previous flower is black and current flower is red then create a new group
        if(prevChar == 'B' && grid[r][i] == 'r') {
            numberOfGroups++;
        }
        prevChar = grid[r][i]; // Sets previous flower to current flower
    }

    // Iterates through all the groups of black flowers
    for(int i = 0; i <= numberOfGroups; i++) {
        // If a group of black flowers does not equal inputted group of black flowers
        // Return NOT_SOLVABLE
        if(groupRowArray[i] != rowInput[r][i + 1]) {
            return NOT_SOLVABLE;
        }
    }
    return SOLVABLE;
}

// Solves the grid using given input
int solve(int r, int c) {
    // If r is bigger than the rows in the grid, we solved the grid
    if(r == row) {
        return SOLVABLE;
    }
    // If column is greater than the columns in the grid
    // Then recursively call solve but start at the beginning of the next row
    if(c == col) {
        // Checks if the row is SOLVABLE
        if(isRowValid(r) == SOLVABLE) {
            return solve(r + 1, 0);
        }
        return NOT_SOLVABLE;
    }

    // Tries a black flower in current position
    grid[r][c] = 'B';
    // If valid, try next position
    if(isValid(r, c) == SOLVABLE) {
        // if last position in grid is valid, return SOLVABLE
        if(solve(r, c + 1) == SOLVABLE) {
            return SOLVABLE;
        }
    }

    // If B is not valid in current position then input r
    grid[r][c] = 'r';
    // If r is valid, try next position
    if(isValid(r, c) == SOLVABLE) {
        // If last position in grid is valid, return SOLVABLE
        if(solve(r, c + 1) == SOLVABLE) {
            return SOLVABLE;
        }
    }
    // If black and red flower does work, empty current position and backtrack
    grid[r][c] = 0;

    return NOT_SOLVABLE;
}

int main()
{
    scanf("%d %d", &row, &col);

    createGrid();

    readInput();

    solve(0, 0);

    printGrid();

    return 0;
}
