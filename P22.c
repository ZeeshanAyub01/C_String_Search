/*
Student Name: Muhammad Zeeshan Ayub,
Student Id: 0994442,
Assignment # 3
Date: 03/11/2019
Horspool String Searching Algorithm
*/


#include "A3.h"

//Function called by the main to search for the entered pattern
int findSubStringHP(char *toFindIn, char *toFind, int *shifts,double *timeTaken){
    
    
    int d = strlen(toFind);
    int lastCharIndex = d - 1;
    int l = lastCharIndex;
    int occ = 0;
    int matchFound = 0;
    int tableSize = 0;
    int *shiftTable = generateTable(toFind,&tableSize);
    int noOfShifts = 0;
    double clocks = CLOCKS_PER_SEC;
    clock_t end;
    double time = 0;
    clock_t start = clock();

    while( lastCharIndex < strlen(toFindIn) ){
        matchFound = 0;
        if( toFind[d - 1] == toFindIn[lastCharIndex]){
            l = lastCharIndex;
            
            while(  ( toFindIn[l] == toFind[d - 1] ) && (l >= 0) && (d-1 >= 0) ){
                d--;
                l--;
                if(d <= 0){
                    occ++;
                    matchFound = 1;
                    break;
            }
            }
            
        }


        d = strlen(toFind) ;
        
        int shift = returnShiftValue(shiftTable,tableSize,toFind,toFindIn[lastCharIndex]);
        lastCharIndex = lastCharIndex + shift;
        l = lastCharIndex;
        noOfShifts++;
        *shifts = noOfShifts;
    }

    end = clock();
    time = (end - start)/clocks;

    *timeTaken = time;
    return occ;
}

//This function returns the value a particular symbol will have in a symbol table for a string pattern
//and is called by the function that is actually constructing the bad symbol table
int getShiftHP(char *subString, char matchedCharacter){

    int shift = (int)strlen(subString);

    for(int i=0; i < strlen(subString); i++){
        if(subString[i] == matchedCharacter){
            shift = max(1,strlen(subString) - i - 1);
        }
    }

    return shift;
}

//Returns the maximum of two numbers
int max(int a, int b){
    if(a > b) return a;
    else return b;
}

//Returns an array that acts as a bad symbol table
int *generateTable(char *subString, int *tableSize){

    if(subString == NULL){
        return NULL;
    }

    int i = 0;
    int t = 0;
    char c;
    int *shiftTable = calloc( strlen(subString) + 1, sizeof(int) );

    for( i = 0; i < strlen(subString); i++){
        shiftTable[i] = getShiftHP(subString,subString[i]);//gets shift value for each symbol
    }

    for(int k = strlen(subString)-2; k >= 0; k--){ //this loops checks to see if the last symbol occurs previously in the pattern
        t++;
        if( subString[k] == subString[strlen(subString) - 1] ){
            c = subString[k];
            break;
        }
    }


    for(int j=0; j < strlen(subString) - 1; j++){ //makes sure that each shift value corresponding to the last character in the pattern is the same
        if(subString[j] == c){
            shiftTable[j] = t;
        }
    }

    shiftTable[i] = (int)strlen(subString); //assigns the shift value for symbols that don't occur in the pattern the length of the pattern
    i++;
    *tableSize = i;

    return shiftTable;
}

//Function that prints out the bad symbol table, used for testing purposes
void printTable(int *shiftTable, int tableSize){
    for(int i=0; i < tableSize; i++){
        printf("%d ",shiftTable[i]);
    }
    printf("\n");
}

//Returns the shift value from the shift table corresponding to the symbol
int returnShiftValue(int *shiftTable,int tableSize, char *subString, char character){
    
    for(int i = 0; i < tableSize - 1; i++){
        if( subString[i] == character){
            return shiftTable[i];
        }
    }

    return shiftTable[strlen(subString)];
}
