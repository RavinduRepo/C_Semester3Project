#include <stdio.h>
#include <string.h>

int fibNo(int x);                               // calculate x th fibonachi number
char* matchFib(int f, int a, int b);            // function to check if the fibonachinumber was given

int main() {
    int f, a, b;
    scanf(" %d %d %d", &f, &a, &b); // getting inputs

    printf("%s", matchFib(f, a , b)); // prints the output

    return 0;
}

char* matchFib(int f, int a, int b){
    static char out[6];         //string to hold TRUE or FALSE
    int x = fibNo(f);
    if (x == a || x == b){      // checking if true 
        strcpy(out, "TRUE");
    }
    else{
        strcpy(out, "FALSE");
    }
    return out;
}
int fibNo(int x){
    int ans = 0;
    int  a, b;
    for (int i = 1; i <= x; i++){
        ans = (i == 1 || i == 2)? 1 : a + b;
        b = a;                          // i - 2 th fibonachi number
        a = ans;                        // i - 1 th fibonachi number
    }
    return ans;
}


