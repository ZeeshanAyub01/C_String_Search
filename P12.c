/*
Student Name: Muhammad Zeeshan Ayub,
Student Id: 0994442,
Course: CIS*3490
Assignment # 3
Date: 03/11/2019
Finding anagrams using pre-sorting
*/


#include "A3.h"

//This function is called by the main to find all the anagrams of the given string using pre-sorting
int findAnagramsSorted(char *inputString, String *strings, int arraySize,double *timeTaken){

    long sign = findSignature(inputString); //Generates a signature for the gven string
    String *sortedStrings = mergeSortStrings(strings,arraySize); //Sorts the entered strings based on their signatures using merge-sort
    int anagrams = 0;
    clock_t end;
    double time = 0;
    double clocks = CLOCKS_PER_SEC;
    clock_t start = clock();

    for(int i=0; i<arraySize; i++){
        if( ( sign == sortedStrings[i].signature ) && ( strlen(sortedStrings[i].string) == strlen(inputString) ) && (strcmp(inputString,sortedStrings[i].string) != 0) ){
            printf("Anagram found: %s\n",sortedStrings[i].string);
            anagrams++;
        }
    }

    end = clock();

    time = (end - start)/clocks;
    *timeTaken = time;

    return anagrams;
}

//Sorts the string structs in an array according to their signatures
String *mergeSortStrings(String *arrayToSort, int arraySize){

    if(arraySize <= 1){
        return arrayToSort;
    }

    int s1 = arraySize/2;
    int s2 = arraySize - s1;
    String *subArray1 = calloc(s1,sizeof(String));
    String *subArray2 = calloc(s2,sizeof(String ));

    for(int i=0; i < s1; i++){
        subArray1[i] = arrayToSort[i];
    }

    for(int i=0; i < s2; i++){
        subArray2[i] = arrayToSort[i+s1];
    }

    mergeSortStrings(subArray1,s1);
    mergeSortStrings(subArray2,s2);
    mergeStringsArray(&arrayToSort,&subArray1,&subArray2,arraySize,s1,s2);
    free(subArray1);
    free(subArray2);
    return arrayToSort;
}

//Prints the contents of an individual string struct for testing purposes
void printString( String toPrint ){
   char *print = malloc( 100*sizeof(char) );
   sprintf(print,"{String: %s \n Signature: %ld}",toPrint.string,toPrint.signature); 
   printf("%s\n",print);
   free(print);
}

//Creates the string struct
String createString(char *theString){
    String newString;
    strcpy(newString.string,theString);
    newString.signature = findSignature(theString);
    return newString;

}


//generates a signature as an integer for a string based on the number of times each character occurs in the string
int *generateSignature(char *string){

    int *intArray = calloc(10,sizeof(int));

    for(int i=0 ; i< 10; i++){
        intArray[i] = 0;
    }

    for(int i=0; i<strlen(string);i++){
        if(string[i] == '0'){
            intArray[0] = intArray[0] + 1;
        }
        else if(string[i] == '1'){
            intArray[1] = intArray[1] + 1;
        }
        else if(string[i] == '2'){
            intArray[2] = intArray[2] + 1;
        }
        else if(string[i] == '3'){
            intArray[3] = intArray[3] + 1;
        }
        else if(string[i] == '4'){
            intArray[4] = intArray[4] + 1;
        }
        else if(string[i] == '5'){
            intArray[5] = intArray[5] + 1;
        }
        else if(string[i] == '6'){
            intArray[6] = intArray[6] + 1;
        }
        else if(string[i] == '7'){
            intArray[7] = intArray[7] + 1;
        }
        else if(string[i] == '8'){
            intArray[8] = intArray[8] + 1;
        }
        else if(string[i] == '9'){
            intArray[9] = intArray[9] + 1;
        }

    }

    return intArray;
}

//Converts the signature of a string from an integer array to a single long integer value
long createSignature(int *sA){

    long toReturn = 0;

    toReturn = 1000000000*sA[0] + 100000000*sA[1] + 10000000*sA[2] + 1000000*sA[3] + 100000*sA[4] + 10000*sA[5];
    toReturn = toReturn + 1000*sA[6] + 100*sA[7] + 10*sA[8] + 1*sA[9];

    return toReturn;
}


//Wrapper for the two functions used to create the signature for a string
long findSignature(char *string){

    int *signArray = generateSignature(string);
    long signature = createSignature(signArray);
    free(signArray);
    return signature;
}

//Creates an array for the strings and adds the strings to it
String *createStringArray(char **strings,int stringsNumber){
    String *stringArray = calloc(stringsNumber, sizeof(String));

    for(int i=0; i < stringsNumber; i++){
        stringArray[i] = createString(strings[i]);
    }

    return stringArray;
}


//The merge function used to merge sort the strings array based on their signature value
int mergeStringsArray(String  **array, String  **array1, String  **array2, int arraySize, int size1, int size2){
    //https://www.geeksforgeeks.org/merge-sort/
    String  *Array = *array;
    String  *Array1 = *array1;
    String  *Array2 = *array2;
    int i = 0;
    int j = 0;
    int k = 0;
    int static a = 0;
    int inversions = 0;

    a++;
    
    while( i < size1 && j < size2 ){

        if( Array1[i].signature < Array2[j].signature ){
            Array[k] = Array1[i];
            i++;
            k++;          
        }
        else if(Array1[i].signature >= Array2[j].signature ){
            Array[k] = Array2[j];
            j++;
            k++;       
        }
    }

    while (i < size1) 
    { 
        Array[k] = Array1[i]; 
        i++; 
        k++; 
    } 

    while (j < size2) 
    { 
        Array[k] = Array2[j];
        j++; 
        k++; 
    } 

    return inversions;

}


