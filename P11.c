/*
Student Name: Muhammad Zeeshan Ayub,
Student Id: 0994442,
Course: CIS*3490
Assignment # 3
Date: 03/11/2019
Brute Force method to find anagrams of a string
*/

#include "A3.h"

//The function called by main to find all the anagrams using the brute force method
int findAnagramsBF(char **array, int arraySize, char *string,double *timeTaken){
    long sign = 0;
    long s = 0;
    int anagrams = 0;
    clock_t end;
    double time = 0;
    clock_t start = clock();
    double clocks = CLOCKS_PER_SEC;

    for(int i=0; i<arraySize; i++){
            sign = findSignature(string);
            s = findSignature(array[i]);
            if( (s == sign) && ( strcmp(array[i],string) != 0) && (strlen(array[i]) == strlen(string)) ){
                printf("Anagram found: %s\n",array[i]);
                anagrams++;
            }
        
    }

    end = clock();

    time = (end - start)/clocks;

    *timeTaken = time;

    return anagrams;
}


void printArray(int *array, int size){

    for(int i=0; i<size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

//This function reads in the strings from a file into an array
char **readArrayFile(char *fileName,int *size){
    
    char **array = calloc(40000,50*sizeof(char));
    int i = 0;
    char string[20];
    FILE *fptr = NULL;
    fptr = fopen(fileName,"r+");

    if(fptr == NULL){
        printf("Unable to open %s, exiting program now\n", fileName);
        free(array);
        exit(0);
    }

    while(!feof(fptr)){
        fscanf(fptr,"%s",string);
        array[i] = calloc(strlen(string)+1,sizeof(char));
        strcpy(array[i],string);
        i++;

    }
    i--;
    *size = i;

    fclose(fptr);
    return array;

}


//Frees the array of strings
void deleteStringArray(char **array,int arraySize){

    for(int i=0; i < arraySize; i++){
        free(array[i]);
    }

    free(array);
}






