// Copyright 2018 Brezeanu Dan-Eugen
#ifndef AIFUNCH
#define AIFUNCH
#include "miscellaneous.h"
#include "constants.h"

void modifyAttributesAI(playerHand* hands, cardT* currentCard, int* currentPlayerOrder,
                        int currentPlayer, int numberPlayers,int* skipCount, int* drawCount);

void AImove(playerHand* hands, int currentPlayer, cardT* deck, int* cardsInDeck, cardT* topPileCard,
            char** logContent, int* skipCount, int* drawCount, int* currentPlayerOrder, int numberPlayers);

int  AIcanContest(playerHand* hands, cardT topPileCard, int currentPlayer);
int  hasAI(int* isRealPlayer, int numberPlayers);

#endif
