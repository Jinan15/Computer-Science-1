/*
    Name: Jinan Patel
    Revised my function to account for extra spaces in between names
    Revised function to account for single letters
    Hopefully a 100000 char wont take to long to compile
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define arrSize 100000

void readString() {
    char* name = (char *)calloc(arrSize + 1, sizeof(char)); //stores full input
    char letter = 0;
    int namePos = 0;
    //stores all input into a name array
    while (letter != '\n') {
        scanf("%c", &letter);
        name[namePos] = letter;
        namePos++;
    }

    char* output = (char *)calloc(arrSize + 1, sizeof(char));
    int outputPos = 0;
    //for loop iterates through name char array
    for(int i = 0; i < (arrSize + 1); i++) {

        if((i == 0) && (name[i] != ' ')) { //If first char in array is a letter then it is outputted
            output[outputPos] = name[i];
            outputPos++;
        }
        else if ((name[i] == ' ') && (i > 1)) { //checks for a space in current char
            if (name[i - 1] != ' ') { //if there is no space in the previous char then char is outputted
                output[outputPos] = name[i - 1];
                outputPos++;
            }
        }
        else if ((name[i - 2] == ' ') && (name[i - 1] != ' ')) { //if there was a space 2 iterations before and last iteration was a char (not a space) then the char is outputted
            output[outputPos] = name[i - 1];
            outputPos++;
        }
        else if ((name[i] == '\n') && (name[i - 1] != ' ')) { //if \n is found then last char is recorded unless the last char is a space
            if (i > 1) { //checks edge case - only one letter is inputted then nothing is outputted here
                output[outputPos] = name[i - 1];
            }
        }
    }

    printf("%s\n", output);
}

int main()
{
    int n;
    scanf("%d", &n);

    //makes sure first input (\n) doesn't mess with char inputs in function
    char test = 0;
    while (test != '\n'){
        scanf("%c", &test);
    }

    for(int i = 0; i < n; i++) {
        readString(); // The function reads input and generates a handle then outputs it
    }

    return 0;
}
