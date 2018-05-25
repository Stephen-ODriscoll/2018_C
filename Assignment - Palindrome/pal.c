#include <stdio.h>
#include <stdlib.h>
#include "pal.h"
#include "useful.h"
#include <time.h>

void startGame(int initialNumber)
{
    srand(time(NULL));
    int size = 0;

    int num = initialNumber;
    for(; num > 0; size++)
        num /= 10;

    int* pListOfNumbers = initialiseArray(initialNumber, size);

    int positionOfCursor = rand() % size;
    int numberOfGoes = 0;

    boolean palindrome = isPalindrome(pListOfNumbers, size);

    while(palindrome == False) {

        displayState(pListOfNumbers, positionOfCursor, size, numberOfGoes);

        char command = get_command();
        processCommand(pListOfNumbers, size, &numberOfGoes, &positionOfCursor, command);

        palindrome = isPalindrome(pListOfNumbers, size);
    }

    printf("\nCongrats, you won in %d goes!\n", numberOfGoes);
    free(*pListOfNumbers);
}

int* initialiseArray(int initialNumber, int size)
{
    int* pListOfNumbers = malloc(sizeof(int)* size);
    int divider = 1;
    int i;

    for(i = 0; i < size - 1; i++) {

        divider *= 10;
    }

    for(i = 0; i < size; i++) {

            pListOfNumbers[i] = initialNumber / divider;
            initialNumber = initialNumber - divider * pListOfNumbers[i];
            divider /= 10;
    }

    return pListOfNumbers;
}

void displayState(int* pListOfNumbers,  int  positionOfCursor, int size, int numberOfGoes)
{
	printf("\nGame State:\n\t<");

	int i;

    for(i = 0; i < size; i++)
        printf("%d", pListOfNumbers[i]);

    printf(">\tNumber of Goes: %d\n", numberOfGoes);
    printf("\t ");

    for(i = 0; i < positionOfCursor; i++)
        printf(" ");

    printf("^\n");

	// Use  *pListOfNumbers or pListOfNumbers[0] to access the first item
     // in the array
}

void moveCursorRight(int* pPositionOfCursor, int* pNumberOfGoes, int max)
{
  //*pPositionOfCursor
  //*pPositionOfCursor  = 22

   if(*pPositionOfCursor < max-1) {

     (*pPositionOfCursor)++;
     (*pNumberOfGoes)++;
   }

}

void moveCursorLeft(int* pPositionOfCursor, int* pNumberOfGoes)
{
  //*pPositionOfCursor
  //*pPositionOfCursor  = 22

   if(*pPositionOfCursor > 0) {

     (*pPositionOfCursor)--;
     (*pNumberOfGoes)++;
   }

}

void incrementDigitInListAtPos(int* pListOfNumbers,  int  positionOfCursor, int* pNumberOfGoes)
{

    if(pListOfNumbers[positionOfCursor] < 9) {

        pListOfNumbers[positionOfCursor]++;
        (*pNumberOfGoes)++;
    }
}

void decrementDigitInListAtPos(int* pListOfNumbers,  int  positionOfCursor, int* pNumberOfGoes)
{

    if(pListOfNumbers[positionOfCursor] > 0) {

    pListOfNumbers[positionOfCursor]--;
    (*pNumberOfGoes)++;
    }
}

boolean isPalindrome(int* pListOfNumbers, int size)
{
    boolean palindrome = True;

    int i;

    for(i = 0; i < size/2; i++)
        if(pListOfNumbers[i] != pListOfNumbers[size - i - 1])
            palindrome = False;

    return palindrome;
}

char get_command()
{
	 char  validCharacters[] = { 'a', 'd', 'w', 'x'};

	 printf("Enter a valid character(a, d, w, x): ");

    char input = my_get_char();

    int i;
    for(i = 0; i < 4; i++)
        if(input == validCharacters[i])
            return input;

    return 0;
}

void processCommand(int* pListOfNumbers, int size, int* pNumberOfGoes, int* pPositionOfCursor, char command)
{

    if(command == 'a')
        moveCursorLeft(pPositionOfCursor, pNumberOfGoes);

    else if(command == 'd')
        moveCursorRight(pPositionOfCursor, pNumberOfGoes, size);

    else if(command == 'w')
        incrementDigitInListAtPos(pListOfNumbers, *pPositionOfCursor, pNumberOfGoes);

    else if(command == 'x')
        decrementDigitInListAtPos(pListOfNumbers, *pPositionOfCursor, pNumberOfGoes);
}




