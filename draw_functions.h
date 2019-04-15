// Copyright 2018 Brezeanu Dan-Eugen
#ifndef DRAWFUNCH
#define DRAWFUNCH
#include "AI_functions.h"

int introGame(cardT* deck, int selection);

void printCard(int whereToPrint, cardT card, const int shown);

void drawBorders(int whereToDraw, const int isHighlighted);

void printHand(int playerNumber, playerHand* hands, const int shown);

void printMenu(int selection);

int navigateMenu();

void displayControls();

int chooseNewColour();

void drawLogo();

void showInfo(int currentPlayer, int* cardsInDeck, int currentPlayerOrder);

void printLogContent(char** logContent);

#endif
