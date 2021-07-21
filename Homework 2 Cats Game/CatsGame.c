#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TOP_BOUND 1000000000
#define BOT_BOUND -1000000000

//The readLine function reads a line and returns a integer
//the integer corresponds to the word (phrase) entered
int readLine() {
    char * temp = (char *)calloc(20, sizeof(char));

    //while loop reads in line and stores string in temp char array
    char letter = 0;
    int pos = 0;
    while (letter != '\n') {
        scanf("%c", &letter);
        temp[pos] = letter;
        pos++;
    }

    strlwr(temp); //makes string lower case

    //if any form of "cold" is inputted then the function returns -1
    if(strstr(temp, "cold")) {//No. Colder.
        return -1;
    }
    //if any form of "change" is inputted then the function returns 0
    if(strstr(temp, "change")) {//No. No. Change
        return 0;
    }
    //if any form of "warm" is inputted then the function returns 1
    if(strstr(temp, "warm")) {//No. Warmer.
        return 1;
    }
    //if any form of "no" but not "no change" is inputted
    //then the function returns -2
    if(strstr(temp, "no")) {//No
        return -2;
    }
    //if any form of "yes" is inputted then the function returns 2
    if(strstr(temp, "yes")) {//Yes!!!
        return 2;
    }
    //if any form of "game over" is inputted then the function returns 2
    if(strstr(temp, "game over")) {//Game Over
        return 2;
    }
    return 2;//if incorrect input is detected the program ends by returning 2
}

//uses input to decrease min and max and then outputs the min or max depending
//on the previous guess and current guess
int nextGuessCalc(int *min, int *max, int *prevGuess, int curGuess, int numGuesses, int input) {
    if(numGuesses == 0) { //first guess will always be the min (0)
        return *min;
    }
    if(numGuesses == 1) { //second guess will always be the max
        prevGuess = curGuess;
        return *max;
    }
    if(input == 0) { //if "no change" is entered than the midpoint is guessed/outputted
        int midpoint = (*prevGuess + curGuess) / 2;
        *prevGuess = curGuess;
        return midpoint;
    }
    //runs if colder is entered
    if(input == -1) {
        //runs if the previous guess is less than the current guess
        if(*prevGuess < curGuess) {
            //range is cut in half by making max the midpoint - 1 of the range
            *max = ceil((double)(*min+*max) / 2.0) - 1;
            //if min = previous guess its not a solution and therefore one is added to min
            if(*min == *prevGuess) {
                *min = *min + 1;
            }
            *prevGuess = curGuess;
            return *min;
        //runs if previous guess is greater than the current guess
        } else if(*prevGuess > curGuess) {
            //range is cut in half by making min the midpoint + 1 of the range
            *min = floor((double)(*min+*max) / 2.0) + 1;
            //if max = previous guess its not a solution and therefore 1 is subtracted from max
            if(*max == *prevGuess) {
                *max = *max - 1;
            }
            *prevGuess = curGuess;//if this is hit then there was some error in the calculation
            return *max;
        }
    }
    //Runs if warmer is entered
    if(input == 1) {
        //Runs if previous guess is lower than current guess
        if(*prevGuess < curGuess) {
            //if the current guess = max then min is cut in half
            //if the current guess is not max then min stays the same
            if(curGuess == (*max)){
                *min = floor((double)(*prevGuess+*max) / 2.0) + 1;
                *max = *max - 1;
            }
            *prevGuess = curGuess;
            return *min;
        //Runs if previous guess is greater than current guess
        } else if(*prevGuess > curGuess) {
            //if previous guess was the max before +/- 1 then max is cut in half
            if((*prevGuess == (*max+1)) || (*prevGuess == (*max-1))){
                *max = ceil((double)(*min+*max) / 2.0);
            }
            //if current guess is min then min - 1
            if(*min == curGuess) {
                *min = *min + 1;
            }
            *prevGuess = curGuess;
            return *max;
        }
    }
    //if this return statement is hit then there was a input error and min is returned as the guess
    return *min;
}


int main()
{
    //Top bound value entered by user
    int range;
    scanf("%d", &range);

    //Catches the next line character from input
    char test = 0;
    while (test != '\n'){
        scanf("%c", &test);
    }

    int min = 1;//Minimum number will always start at 0
    int max = range; //Maximum number will be range given by user

    int input = 0;
    int prevGuess = min; //Previous guess is initialized at min number
    int curGuess = min; //Current guess is also initialized at min number
    int numGuesses = 0; //Tracks the number of guesses given

    //loops until a "yes" or "game over" is entered
    //the while loop also ends if a word is misspelled or not entered
    while (input != 2) {
        curGuess = nextGuessCalc(&min, &max, &prevGuess, curGuess, numGuesses, input);
        numGuesses++;
        printf("%d\n", curGuess);
        fflush(stdout);
        input = readLine();//reads in string input and returns a number corresponding to the string
    }


    return 0;
}
