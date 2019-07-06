#include "A3.h"


int main(){

    int index = 0;
    char testSmall[30];
    char userChoice[2];
    int tableSize = 0;
    int shifts = 0;
    char *userPrompt = calloc(1,150*sizeof(char));
    double timeTaken = 0;
    int choiceNum = 0;
    char *testBig = NULL; 
    sprintf(userPrompt,"What program would you like to run?\nType 1 for Q1.1,\nType 2 for Q1.2,\nType 3 for Q2.1,\nType 4 for Q2.2,\nType 5 for Q2.3,\n");
    int occ = 0;
    int arraySize = 0;
    String *stringsArray;
    char testString[50];
    int anagrams = 0;
    char **array = NULL;



    printf("%s",userPrompt);
    scanf("%s",userChoice);
    choiceNum = verifyUserChoice(userChoice);

    while( choiceNum == 0 ){
        printf("Invalid input detected, enter choice again\n");
        //printf("%s",userPrompt);
        scanf("%s",userChoice);
        choiceNum = verifyUserChoice(userChoice);
    }


    if (choiceNum == 1){
        array = readArrayFile("data_4.txt",&arraySize);
        printf("Enter a string to find its anagrams: ");
        scanf("%s",testString);
        anagrams = findAnagramsBF(array,arraySize,testString,&timeTaken);
        printf("Total anagrams found with brute force: %d\n",anagrams);
        printf("Total time taken to find anagrams with brute-force: %lf milliseconds\n",timeTaken*1000);

        for(int i=0; i<= arraySize; i++){
        free(array[i]);
        }

        free(array);

    }

    else if(choiceNum == 2){
        array = readArrayFile("data_4.txt",&arraySize);
        stringsArray = createStringArray(array,arraySize);

        printf("Enter a string to find its anagrams: ");
        scanf("%s",testString);
        anagrams = findAnagramsSorted(testString, stringsArray,arraySize,&timeTaken);
        printf("Total anagrams found: %d\n",anagrams);
        printf("Total time taken to find anagrams with pre-sorting: %lf milliseconds\n",timeTaken*1000);

        for(int i=0; i<= arraySize; i++){
        free(array[i]);
        }

    free(array);
    free(stringsArray);


    }


    else if(choiceNum == 3){
        testBig = fileRead("data_5.txt");
        printf("Enter a pattern to find in the file with brute force: ");
        scanf("%s",testSmall);
        occ = findSubStringBF(testBig,testSmall,&timeTaken);
        printf("For Brute force: The occurences for %s are: %d \n",testSmall,occ);
        printf("Total time taken for brute force: %lf milliseconds\n",timeTaken*1000);
        free(testBig);
    }

    else if(choiceNum == 4){
        testBig = fileRead("data_5.txt");
        printf("Enter a pattern to find in the file with Horspool's algorithm: ");
        scanf("%s",testSmall);
        occ = findSubStringHP(testBig,testSmall,&shifts,&timeTaken);
        printf("For Horspool: The occurences for %s are: %d, and total number of pattern shifts: %d\n",testSmall,occ,shifts);
        printf("Total time taken for Horspool: %lf milliseconds\n",timeTaken*1000);
        free(testBig);
    }

    else if(choiceNum == 5){
        testBig = fileRead("data_5.txt");
        printf("Enter a pattern to find in the file with Boyer-Moore: ");
        scanf("%s",testSmall);
        occ = findSubStringBM(testBig,testSmall,&shifts,&timeTaken);
        printf("For Boyer-Moore: The occurences for %s are: %d, and total number of pattern shifts: %d\n",testSmall,occ,shifts);
        printf("Total time taken for Boyer-Moore: %lf milliseconds\n",timeTaken*1000);
        free(testBig);
    }


    
    free(userPrompt);
    return 0;
}




int verifyUserChoice(char *userChoice){
    if( strlen(userChoice) != 1){
        return 0;
    }

    if( strcmp(userChoice,"1") == 0){
        return 1;
    }

    if( strcmp(userChoice,"2") == 0){
        return 2;
    }

    if( strcmp(userChoice,"3") == 0){
        return 3;
    }

    if( strcmp(userChoice,"4") == 0){
        return 4;
    }

    if( strcmp(userChoice,"5") == 0){
        return 5;
    }

    return 0;


}
