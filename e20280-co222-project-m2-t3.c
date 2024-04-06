#include<stdio.h>
#include <stdlib.h>
#include <string.h>

// Initalizing variables
char **Map;
int **Road;
int mapH, mapW;
int StartRow, StartCol;
int EndRow, EndCol;
char *mapdetails;

void makeArray();                                                           // Make map using the input array
int minDistance(int EndRow, int EndCol, int StartRow, int StartCol);        // fill the Road matrix with numbers
int isValidMove(int nextR, int nextC);                                      // Check if the move is in the map
int isTravlePossible(char C, char N);                                       // Check if possible to travel

int fibNo(int x);                                                           //calculates the xth fibonachi number
int checkDoors(int r, int c, int k1, int k2);                               //check if there are telepotation doors
int minDistanceWithP(int TR1, int TC1, int TR2, int TC2);                   //calculate minimum distence concidering telepotation doors

int main(){

    // getting inputs
    scanf(" %d %d", &mapH, &mapW);//hight width inputs

    scanf(" %d %d", &StartRow, &StartCol);//startpoints

    scanf(" %d %d", &EndRow, &EndCol);//endpoints

    mapdetails = (char *)malloc((mapH * mapW) + 1);// create input string

    scanf(" %s", mapdetails);// getting map details input

    int k1, k2, num; //getting three numbers in the map 
    scanf(" %d %d", &k1, &k2);
    scanf(" %d", &num);

    int nd[2][num]; //store all cell values that are to check for telepotation
    for (int i = 0; i < num; i++){
        scanf(" %d %d", &nd[0][i], &nd[1][i]);
    }

    int sd[2][2]; //to store telephotation doors if any
    for (int r = 0; r < 2; r++){
        for (int c = 0; c < 2; c++){
            sd[r][c] = -1; // set defalt values to -1
        }
    }
    for (int i = 0, k = 0; i < num && k <= 1; i++){ //store telephotation doors if any
        int isDoor = checkDoors(nd[0][i], nd[1][i], k1, k2);
        if (isDoor){
            sd[0][k] = nd[0][i];
            sd[1][k] = nd[1][i];
            k++;
        }
    }

    // creating 2d array
    makeArray();
    int min = minDistanceWithP(sd[0][0], sd[1][0], sd[0][1], sd[1][1]); // finding shortest path with portals

    //prints the output
    if (min >= 0){
        printf("The minimum distance from %c to %c is %d", Map[StartRow][StartCol], Map[EndRow][EndCol], min);
    }
    else {
        printf("There is no possible path from %c to %c", Map[StartRow][StartCol], Map[EndRow][EndCol]);
    }

    return 0;
}

int checkDoors(int r, int c, int k1, int k2){
    int calculated = r * mapW + c; //calculate the number for given cell
    int x = fibNo(calculated);
    if (x == k1 || x == k2){
        return 1;
    } else {
        return 0;
    }
}

int fibNo(int x){
    int ans = 0;
    int  a, b;
    for (int i = 1; i <= x; i++){ //return fib number of given number x
        ans = (i == 1 || i == 2)? 1 : a + b;
        b = a;
        a = ans;
    }
    return ans;
}

int minDistance(int EndRow, int EndCol, int StartRow, int StartCol){

    // make a Road 2D array
    for (int r = 0; r < mapH; r++){
        for (int c = 0; c < mapW; c++){
            Road[r][c] = -1;                    // set all other place -1
            if (r == EndRow && c == EndCol){
                Road[r][c] = 0;                 //set end to 0
            }
        }
    }

    //searching for best path
    int Q[mapH * mapW][2];  // making a Q
    Q[0][0] = EndRow;       //setting the starting place
    Q[0][1] = EndCol;
    int countTo = 1;        //end of the Q    
    int initialR, initialC; 

    for (int counted = 0; counted < countTo; counted++){        //runs untill all the posible cells are ended
        initialR = Q[counted][0];                               //setting checking cell cordinates
        initialC = Q[counted][1];
    
        // check above
        if (isValidMove(initialR - 1, initialC) && isTravlePossible(Map[initialR][initialC], Map[initialR - 1][initialC]) && Road[initialR - 1][initialC] == -1){
            Road[initialR - 1][initialC] = Road[initialR][initialC] + 1;
            Q[countTo][0] = initialR - 1;
            Q[countTo][1] = initialC;
            countTo++;
        }
        // check below
        if (isValidMove(initialR + 1, initialC) && isTravlePossible(Map[initialR][initialC], Map[initialR + 1][initialC]) && Road[initialR + 1][initialC] == -1){
            Road[initialR + 1][initialC] = Road[initialR][initialC] + 1;
            Q[countTo][0] = initialR + 1;
            Q[countTo][1] = initialC;
            countTo++;
        }
        // check left
        if (isValidMove(initialR, initialC - 1) && isTravlePossible(Map[initialR][initialC], Map[initialR][initialC - 1]) && Road[initialR][initialC - 1] == -1){
            Road[initialR][initialC - 1] = Road[initialR][initialC] + 1;
            Q[countTo][0] = initialR;
            Q[countTo][1] = initialC - 1;
            countTo++;
        }                
        // check right
        if (isValidMove(initialR, initialC + 1) && isTravlePossible(Map[initialR][initialC], Map[initialR][initialC + 1]) && Road[initialR][initialC + 1] == -1){
            Road[initialR][initialC + 1] = Road[initialR][initialC] + 1;
            Q[countTo][0] = initialR;
            Q[countTo][1] = initialC + 1;
            countTo++;
        }            
    }   
    return Road[StartRow][StartCol];
}

int minDistanceWithP(int TR1, int TC1, int TR2, int TC2){
    int StoD = minDistance(EndRow, EndCol, StartRow, StartCol); // returns the value in starting  location(started from the end and ending from the start)
    int StoT1 = -1, StoT2 = -1, T1toE = -1, T2toE = -1;// set defalt values to -1
    if (TR1 != -1 && TC1 != -1 && TR2 != -1 && TC2 != -1){ // setting up each variable of distences. start to dest(StoD), start to T1(StoT1), start to T2(StoT2),
        StoT1 = minDistance(TR1, TC1, StartRow, StartCol); // start to T1
        StoT2 = minDistance(TR2, TC2, StartRow, StartCol); // start to T2
        T1toE = minDistance(EndRow, EndCol, TR1, TC1);// T1 to end
        T2toE = minDistance(EndRow, EndCol, TR2, TC2);// T2 to end
    }
    //calculates min distence
    int minimumDistence = -1;
    int teleM1 = (StoT1 != -1 && T2toE != -1) ? StoT1 + T2toE : -1; // possible disctence 1 with teleport
    int teleM2 = (StoT2 != -1 && T1toE != -1) ? StoT2 + T1toE : -1; // possible disctence 2 with teleport

    if (StoD == -1 && teleM1 == -1 && teleM2 == -1){ // if not possible
        return -1;
    }
    if (StoD != -1){ // change minimumdistence if able to go without telepotation
        minimumDistence = StoD;
    }
    if (teleM1 != -1 && (minimumDistence == -1 || teleM1 < minimumDistence)){ // check if current min distence is longer than new value or -1 and update
        minimumDistence = teleM1;
    }
    if (teleM2 != -1 && (minimumDistence == -1 || teleM2 < minimumDistence)){ // check if current min distence is longer than new value or -1 and update
        minimumDistence = teleM2;
    }
    return minimumDistence; //return minimum distence
}

int isValidMove(int nextR, int nextC){ // checks if new cordinates are in the map
    return (nextR >= 0 && nextR < mapH && nextC >= 0 && nextC < mapW);
}

int isTravlePossible(char C, char N){
    // Check down(since walking back checks for only 2 stepsdown)   //Check up(since walking back checks 3 steps up)
    return (C - N <= 2 && N - C <= 3);
}

void makeArray(){ 
    // allocate memory
    Map = (char **)malloc(mapH * sizeof(char *));
    Road = (int **)malloc(mapH * sizeof(int *));
    for(int i = 0; i < mapH; i++) {
        Map[i] = (char *)malloc(mapW * sizeof(char));
        Road[i] = (int *)malloc(mapW * sizeof(int)); 
    }
    // make map details
    int index = 0;
    for (int r = 0; r < mapH; r++){
        for (int c = 0; c < mapW; c++){
            Map[r][c] = mapdetails[index];
            index++;
        }
    }
}