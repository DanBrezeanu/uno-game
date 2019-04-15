// Copyright 2018 Brezeanu Dan-Eugen
#ifndef MISCH
#define MISCH
#include "constants.h"

typedef struct cardT{
  int number;
  int colour;
}cardT;

typedef struct playerHand{
  cardT handCards[DECK_CAPACITY];
  int handCapacity;
}playerHand;

void  init();
void  clear_screen();
void  clear_hand();
char* toString(int number);
int   getRandom(int *cardsInDeck);
void  addLogContent(char** logContent, const int action, int currentPlayer, cardT topPileCard);

#endif
