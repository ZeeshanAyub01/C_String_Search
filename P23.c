/*
Student Name: Muhammad Zeeshan Ayub,
Student Id: 0994442,
Assignment # 3
Date: 03/11/2019
Boyer's Moore String Searching Algorithm
*/


#include "A3.h"

//The function called by main to search for the given pattern using the Boyer's Moore string search algorithm
int findSubStringBM(char *toFindIn, char *toFind, int *shifts,double *timeTaken){

    int occ = 0; //The number of occurences of the pattern to find
    int lastCharIndex = strlen(toFind) - 1; //string searching starts at the last character of the entered pattern
    int shift = 1; //Initializes the number of shifts to make at 1
    int s = strlen(toFind) - 1; //the index of the last character of the entered pattern
    int match = 0; //A flag to check of a match of the entered pattern was found
    int tableSize = 0; //Size of the bad symbol table
    int *shiftTable = generateTable(toFind,&tableSize); //The bad symbol table
    int totalShifts = 0; //The total number of shifts made to find the occurences of the pattern
    double clocks = CLOCKS_PER_SEC; 
    clock_t end;
    double time = 0;
    clock_t start = clock();

    while( lastCharIndex < strlen(toFindIn) ){//This while loop continues until the end of the larger string is reached
        if( toFindIn[lastCharIndex] == toFind[s] ){
            
            shift = getBMShift(toFindIn,toFind,lastCharIndex,&match);//The size of the shift to make is determined by a function according to the Boyer's Moore algorithm
            if( match == 1 ){//if a match is detected the number of occurences is incremented and the flag is reset to 0
                occ++;
                match = 0;
            }
        }
        else{
            shift = returnShiftValue(shiftTable,tableSize,toFind,toFindIn[lastCharIndex]);//
        }
        
        lastCharIndex = lastCharIndex + shift;
        totalShifts++;
    }

    *shifts = totalShifts;
    end = clock();
    time = (end - start)/clocks;
    *timeTaken = time;

    return occ;
}


//Function used during testing to determine if any of the last part in a string occurs previously in the string
int detectPattern(char *string){

    char c = string[strlen(string)-1];
    int sl = strlen(string) - 1;
    int l = 0;
    int match = 0;
    int shift = 0;
    int mark = 0;

    for(int i = strlen(string) - 2; i >= 0; i--){
        l = 0;
        if(string[i] == c){
            
            while( string[i] == string[sl]){ //if the last character of the string occurs before in the string, check to see what length of the suffix matches at that point
                
                sl--; 
                i--;
                l++; 
                
            }
            
            if(l > 0){ //length of the matching suffix
            
                match++;
                mark = i + l; //position where the match was found
            }

        }
        sl = strlen(string) - 1; //restores sL to the very last character of the string
    }

    shift = strlen(string) - mark - match;

    if(match <= 0) printf("No match found!\n");
    else printf("Matches found: %d\n",match);

    return shift;
}


//Calculates and returns shift based on the Boyer-Moore's string search algorithm
int getBMShift(char *bigString, char *string, int suffixLoc, int *match){
    
    if(suffixLoc < 0){
        return 1;
    }

    
    int i = suffixLoc; //the position in the large string where the suffix match was encountered
    int sL = 0; //the length of the repeating pattern
    int shift = 1; //initiliazies the value of the shift to 1
    int indSm = strlen(string) - 1; //index of the last character in the pattern
    int tableSize = 0; 
    int *shiftTable = generateTable(string,&tableSize);//Generates the bad symbol table
    int badCharShift = 1; //the bad symbol shift
    int shiftGS = 0; //good suffix shift

    while( bigString[i] == string[indSm] && indSm >= 0 ){
        
        sL++;
        i--;
        indSm--;
    }

    if(sL <= 1){//if the length of the matched suffix is 1, then corresponding value from the bad symbol table is returned
        shift = returnShiftValue(shiftTable,tableSize,string,bigString[i+1]);
        
    }
    else{
        badCharShift = returnShiftValue(shiftTable,tableSize,string,bigString[i]) - sL; //the shift value from the bad symbol table
        shiftGS = detectSuffixRep(string,sL); //the good suffix shift value
    }

    badCharShift = max(badCharShift,1); //the shift based on the bad symbol table
    shift = max(badCharShift,shiftGS); //the maximum good suffix shift and the bad symbol shift, that is, the value to return
    if(sL == strlen(string)){
        *match = 1; //notifies the calling function that a match has been detected
    }
            
    return shift;
}


//This funciton checks to see if the matched part at the end of the pattern repeats anywhere previously in the pattern.
//If it does, it returns the position where the suffix was found initially
int detectSuffixRep(char *string, int matchedLength){

    int pM = strlen(string)-1;
    int mM = strlen(string)-1;
    int sL = 0;
    int shift = 0;

    for(int i = strlen(string)-2; i >= 0; i--){
        if( string[i] == string[strlen(string) - 1] ){
            pM = i;
            while( string[i] == string[mM] ){
                i--;
                mM--;
                sL++;
            }
        }
        if( (sL > 1) && (sL <= matchedLength) ){
            shift = (int)((strlen(string) -sL) - (i+1) );

            //printf("!!Confirmed suffix rep at %d, returning: %d!!\n",i+1,shift);
            return shift;
        }
    }
    return -1; //Returns -1 if the suffix does not repeat
}
