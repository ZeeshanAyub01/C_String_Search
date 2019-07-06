#ifndef A3_H
#define A3_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//Struct and functions written for Question 1

typedef struct string{
    char string[50];
    long signature;
}String;

int* mergeSort(int *arrayToSort, int arraySize);
int merge(int **array, int **array1, int **array2, int arraySize, int size1, int size2);
void printArray(int *array, int size);
int *generateSignature(char *string);
long findSignature(char *string);
long createSignature(int *sA);
int *generateSignature(char *string);
void deleteStringArray(char **array,int arraySize);
char **readArrayFile(char *fileName,int *size);
int findAnagramsBF(char **array, int arraySize, char *string,double *timeTaken);
void printString( String toPrint );
String *createStringArray(char **strings,int stringsNumber);
String *mergeSortStrings(String *arrayToSort, int arraySize);
int mergeStringsArray(String  **array, String  **array1, String  **array2, int arraySize, int size1, int size2);
int findAnagramsSorted(char *inputString, String *strings, int arraySize,double *timeTaken);


//Functions written for Question 2

int findSubStringBM(char *toFindIn, char *toFind,int *shifts,double *timeTaken);
int findSubStringHP(char *toFind, char *toFindIn,int *shifts,double *timeTaken);
int findSubStringBF(char *toFind, char *toFindIn,double *timeTaken);
int getShiftHP(char *subString, char matchedCharacter);
int max(int a, int b);
void printTable(int *shiftTable, int tableSize);
int *generateTable(char *subString, int *tableSize);
int returnShiftValue(int *shiftTable,int tableSize, char *subString, char character);
int detectPattern(char *string);
int getBMShift(char *bigString, char *string, int suffixLength,int *match);
char *fileRead(char *fileName);
int detectSuffixRep(char *string,int matchedLength);
int verifyUserChoice(char *userChoice);


#endif