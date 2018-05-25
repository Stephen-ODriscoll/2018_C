#include "useful.h"

void startGame(int initialNumber);

int* initialiseArray(int initialNumber, int size);

void displayState(int* pListOfNumbers,  int  positionOfCursor, int size, int numberOfGoes);

void moveCursorRight(int* positionOfCursor, int* pNumberOfGoes, int max);

void moveCursorLeft(int* positionOfCursor, int* pNumberOfGoes);

void incrementDigitInListAtPos(int* pListOfNumbers,  int  positionOfCursor, int* numberOfGoes);

void decrementDigitInListAtPos(int* pListOfNumbers,  int  positionOfCursor, int* numberOfGoes);

boolean isPalindrome(int* plistOfNumbers, int size);

char get_command();

void processCommand(int* pList, int size, int* pNumberOfGoes, int* pPositionOfCursor, char command);
