/*
Student Name: Muhammad Zeeshan Ayub,
Student Id: 0994442,
Assignment # 3
Date: 03/11/2019
Brute Force String Search
*/


#include "A3.h"

//The function called by main to find the entered pattern using the brute force method
int findSubStringBF(char *toFindIn, char *toFind,double *timeTaken){

    int m = 0;
    int occ = 0;
    int l = 0;
    clock_t end;
    double clocks = CLOCKS_PER_SEC;
    double time = 0;
    clock_t start = clock();
    

    for(int i=0; i<strlen(toFindIn); i++){
        l = i;
        while(toFindIn[l] == toFind[m]){
            
            m++;
            l++;

            if(m == strlen(toFind) ){
                occ++;
            }
        }
        m = 0;

    }

    end = clock();

    time = (end - start)/clocks;
    *timeTaken = time;

    return occ;
}

//The function that reads in the text from a file into a string and returns that string
char *fileRead(char *fileName){

  FILE *fptr = NULL;
  fptr = fopen(fileName, "r");
  char *buffer;
  char c;
  int i = 0;
  c = ' ';
  int j = 1;

  if( fptr == NULL){
    printf("Unable to open %s!\n", fileName);
    return NULL;
  }
  else{
    buffer = calloc(1, sizeof(char));
    
    while( !feof(fptr) ){
      fscanf(fptr, "%c", &c);
      buffer[i] = c;
      buffer = realloc( buffer, (j+1 )*(sizeof(char)) );
      j++;
      i++;
        }
    }

    buffer[i-1] = '\0';
    fclose(fptr);

  return buffer;
}
