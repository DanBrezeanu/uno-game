// Copyright 2018 Brezeanu Dan-Eugen
#ifndef LOGICH
#define LOGICH
#include "draw_functions.h"


void  buildDeck(cardT* deck);

int   checkIfMoveAvailable(cardT topPileCard, cardT testCard);
int   checkIfContests(playerHand* hands, int* skipCount, int* drawCount, int currentPlayer, cardT* topPileCard,
                    int currentPlayerOrder, int numberPlayers, cardT* deck, int* cardsInDeck, int* currentShow);

void  modifyAttributes(cardT* currentCard, int* currentPlayerOrder, int currentPlayer, int numberPlayers,
                      int* skipCount, int* drawCount);
void  modifyAttributesContested(cardT* currentCard, int* currentPlayerOrder, int currentPlayer, int numberPlayers,
                      int* skipCount, int* drawCount);

void  eraseCardFromHand(playerHand* hands, int currentPlayer, int currentCard);
void  addCardToHand(playerHand* hands, int currentPlayer, cardT* deck, int* cardsInDeck);


int   deckIsEmpty(int *cardsInDeck);
int   shuffleDeck(int *cardsInDeck, cardT* deck, cardT topPileCard);

int   drawAndPlay(playerHand* hands, int currentPlayer, int currentShow);

int   searchForCardInHand(playerHand* hands, int currentPlayer, int numberToFind, int currentCard);
void  searchAndMarkCard(cardT* deck, cardT cardToSearch, int* cardsInDeck, const int mark);
void  addLogContent(char** logContent, const int action, int currentPlayer, cardT topPileCard);

void  runGame(playerHand* hands, int numberPlayers, cardT* deck, int* cardsInDeck, cardT topPileCard, int* isRealPlayer);
cardT startGame(playerHand* hands, int numberPlayers, cardT* deck, int* cardsInDeck);
#endif
