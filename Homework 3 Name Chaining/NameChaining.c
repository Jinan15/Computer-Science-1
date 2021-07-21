#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function checks if permutation is pretty
int check(char arr[][21], int perm[], int MAX) {
    int temp = 0;
    for(int i = 0; i < MAX-1; i++) {
        if( arr[perm[i]][strlen(arr[perm[i]])-1] == arr[perm[i+1]][0] ) {
            temp = 1;
        } else {
            return 0;
        }
    }
    return 1;
}

//function creates all possible permutations
int chain(char arr[][21], int used[], int perm[], int MAX, int N) {
    //base case if N == 0 it means a permutation has been created
    if (N == 0) {
        //calls check function
        int temp = check(arr, perm, MAX);
        if(temp == 1) {
            return 1;
        }
        return 0;
    }

    //recursive part - creates permutations (also backtracks)
    for (int i = 0; i < MAX; i++) {
        if (used[i] == 0) {
            used[i] = 1;
            perm[N-1] = i;
            int tryPerm = chain(arr, used, perm, MAX, N-1);
            if(tryPerm == 1) {
                return 1;
            }
            used[i] = 0;
        }
    }
    return 0;
}

int main()
{
    int n; //number of words being inputted
    scanf("%d", &n);

    //Declaring 3 arrays
    char words[n][21];
    int used[n];
    int perm[n];

    //Initializing 3 arrays
    for(int i = 0; i < n; i++) {
        scanf("%s", words[i]);
        used[i] = 0;
        perm[i] = 0;
    }

    //calls recursive chain function
    int ans = chain(words, used, perm, n, n);

    //prints the answer (correct permutation)
    for(int i = 0; i < n; i++) {
        printf("%s ", words[perm[i]]);
    }

    return 0;
}
