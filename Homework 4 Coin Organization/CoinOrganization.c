#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define name_size 20

//typedef for person struct
typedef struct person person;

//person struct
struct person {
    char name[name_size + 1];
    long long int token;
    long long int bill;
    long long int total;
};

//merge sort function
//person p contains all data, person ans is a temp struct
//len is the length of both struct
void merge(person ** p, person ** ans, int len) {
    // Base case
    if (len <= 1) {
        return;
    }

    int mid = len / 2;
    merge(p, ans, mid);
    merge(p+mid, ans, len-mid);

    // merge the array
    int fptr = 0;
    int bptr = mid;

    for (int i = 0; i < len; i++) {

        if (fptr < mid && bptr < len) {

            if (p[fptr]->total > p[bptr]->total) {
                // front has smaller element
                ans[i]->total = p[fptr]->total;
                strcpy(ans[i]->name, p[fptr]->name);
                fptr++;
            } else {
                // back has smaller (or equal) element
                ans[i]->total = p[bptr]->total;
                strcpy(ans[i]->name, p[bptr]->name);
                bptr++;
            }

        } else if (fptr < mid) {
            // front is non-empty, back is not
            ans[i]->total = p[fptr]->total;
            strcpy(ans[i]->name, p[fptr]->name);
            fptr++;
        } else {
            // back is non-empty, front is not
            ans[i]->total = p[bptr]->total;
            strcpy(ans[i]->name, p[bptr]->name);
            bptr++;
        }
    }
    //replaces unsorted list with temp list which is sorted
    for (int i = 0; i < len; i++) {
        p[i]->total = ans[i]->total;
        strcpy(p[i]->name, ans[i]->name);
    }
}

//function prints all names in person array
void printNames(person ** p, int n) {
    printf("\n");
    for(int i = 0; i < n; i++) {
        printf("%s\n", p[i]->name);
    }
}

//free memory from inputted person array
void freePerson(person ** p, int n) {
    for(int i = 0; i < n; i++) {
        free(p[i]->name);
        free(p[i]);
    }
}

int main()
{
    //stores number of paying customers
    int n = 0;
    scanf("%d", &n);

    //creating and allocating space for person arrays
    //person p array holds arr data, person ans is a temp array for merge sort
    person ** p, ** ans;

    p = calloc(n, sizeof(person *));
    ans = calloc(n, sizeof(person *));

    for(int i = 0; i < n; i++) {
        p[i] = calloc(1, sizeof(person));
        ans[i] = calloc(1, sizeof(person));
    }

    //collects and stores all data in person p
    for(int i = 0; i < n; i++) {
        char name[name_size + 1];
        long long int t, b;
        scanf("%s %lld %lld", name, &t, &b);
        strcpy(p[i]->name, name);
        p[i]->token = t;
        p[i]->bill = b;
    }

    long long int tokenWorth, billWorth;
    scanf("%lld %lld", &tokenWorth, &billWorth);

    //computes number of units each person has and stores it in person p
    for(int i = 0; i < n; i++) {
        long long int totalTokenWorth = p[i]->token * billWorth;
        long long int totalBillWorth = p[i]->bill * tokenWorth;
        p[i]->total = totalTokenWorth + totalBillWorth;
    }

    merge(p, ans, n); //merge sort

    printNames(p, n);//prints answer

    freePerson(p, n);
    freePerson(ans, n);

    return 0;
}
