// Copyright 2018 Brezeanu Dan-Eugen
#include "AI_functions.h"

void modifyAttributesAI(playerHand* hands, cardT* currentCard, int* currentPlayerOrder, int currentPlayer, int numberPlayers,
                      int* skipCount, int* drawCount){
  int *colourCount = calloc(5, sizeof(int));
  int maxColour, maxColourCount = 0;

  if(currentCard->number == REVERSE)
      ((*currentPlayerOrder) == NORMAL_ORDER)
      ? ((*currentPlayerOrder) = REVERSED_ORDER)
      : ((*currentPlayerOrder) = NORMAL_ORDER);

  if(currentCard->number == WILD){
    for(int i = 1; i <= hands[currentPlayer].handCapacity; ++i)
      switch(hands[currentPlayer].handCards[i].colour){
        case RED:
                  colourCount[1]++;
                  break;

        case BLUE:
                  colourCount[3]++;
                  break;

        case GREEN:
                   colourCount[2]++;
                   break;

        case YELLOW:
                    colourCount[4]++;
                    break;

      }

    for(int i = 0; i < 4; ++i)
      if(colourCount[i] > maxColourCount){
          maxColourCount = colourCount[i];
          maxColour = i + 1000;
      }

    currentCard->colour = maxColour;
  }

  if(currentCard->number == SKIP){
    if((*currentPlayerOrder) == NORMAL_ORDER)
      skipCount[(currentPlayer % numberPlayers) + 1]++;
    else{
      if(currentPlayer - 1 == 0)
        skipCount[numberPlayers]++;
      else
        skipCount[currentPlayer - 1]++;
    }
  }

  if(currentCard->number == PLUS_2){
    if((*currentPlayerOrder) == NORMAL_ORDER){
      skipCount[(currentPlayer % numberPlayers) + 1]++;
      drawCount[(currentPlayer % numberPlayers) + 1] += 2 + drawCount[currentPlayer] ;
    }
    else{
      if(currentPlayer - 1 == 0){
        skipCount[numberPlayers]++;
        drawCount[numberPlayers] += 2 + drawCount[currentPlayer];
      }
      else{
        skipCount[currentPlayer - 1]++;
        drawCount[currentPlayer - 1] += 2 + drawCount[currentPlayer];
      }
    }
  }

  if(currentCard->number == PLUS_4){
    if((*currentPlayerOrder) == NORMAL_ORDER){
      skipCount[(currentPlayer % numberPlayers) + 1]++;
      drawCount[(currentPlayer % numberPlayers) + 1] += 4 + drawCount[currentPlayer];
    }
    else{
      if(currentPlayer - 1 == 0){
        skipCount[numberPlayers]++;
        drawCount[numberPlayers] += 4 + drawCount[currentPlayer];
      }
      else{
        skipCount[currentPlayer - 1]++;
        drawCount[currentPlayer - 1] += 4 + drawCount[currentPlayer];
      }
    }

    for(int i = 1; i <= hands[currentPlayer].handCapacity; ++i)
      switch(hands[currentPlayer].handCards[i].colour){
        case RED:
                  colourCount[1]++;
                  break;

        case BLUE:
                  colourCount[3]++;
                  break;

        case GREEN:
                   colourCount[2]++;
                   break;

        case YELLOW:
                    colourCount[4]++;
                    break;

      }

    for(int i = 0; i < 4; ++i)
      if(colourCount[i] > maxColourCount){
          maxColourCount = colourCount[i];
          maxColour = i + 1000;
      }

    currentCard->colour = maxColour;
  }

}

void AImove(playerHand* hands, int currentPlayer, cardT* deck, int* cardsInDeck, cardT* topPileCard, char** logContent,
             int* skipCount, int* drawCount, int* currentPlayerOrder, int numberPlayers){

    int currentCard, moveAvailable;

    // ---PLAY CARD--- //
    for(int i = 1; i <= hands[currentPlayer].handCapacity; ++i)
      if(checkIfMoveAvailable((*topPileCard),hands[currentPlayer].handCards[i])){

        drawBorders(i, HIGHLIGHT);
        refresh();
        napms(500);

        searchAndMarkCard(deck, hands[currentPlayer].handCards[i], cardsInDeck, IN_PILE);

        modifyAttributesAI(hands, &hands[currentPlayer].handCards[i], currentPlayerOrder,
                         currentPlayer, numberPlayers, skipCount, drawCount);

        printCard(PRINT_ON_PILE, hands[currentPlayer].handCards[i], SHOW);

        (*topPileCard) = hands[currentPlayer].handCards[i];
        addLogContent(logContent, ACTION_PLAY, currentPlayer, (*topPileCard));
        eraseCardFromHand(hands, currentPlayer, i);

        printHand(currentPlayer, hands, NO_SHOW);
        refresh();
        napms(500);
        return;
      }

    // ---DRAW CARD--- //
    addCardToHand(hands, currentPlayer, deck, cardsInDeck);

    currentCard = hands[currentPlayer].handCapacity;

    moveAvailable = checkIfMoveAvailable((*topPileCard), hands[currentPlayer].handCards[currentCard]);
    if(moveAvailable){ // ---DRAW AND PLAY--- //

        searchAndMarkCard(deck, hands[currentPlayer].handCards[currentCard], cardsInDeck, IN_PILE);

        modifyAttributesAI(hands, &hands[currentPlayer].handCards[currentCard], currentPlayerOrder,
                         currentPlayer, numberPlayers, skipCount, drawCount);

        printCard(PRINT_ON_PILE, hands[currentPlayer].handCards[currentCard], SHOW);

        (*topPileCard) = hands[currentPlayer].handCards[currentCard];
        addLogContent(logContent, ACTION_DRAW_PLAY, currentPlayer, (*topPileCard));
        eraseCardFromHand(hands, currentPlayer, currentCard);
    }
    else{ // ---JUST DRAW--- //
      addLogContent(logContent, ACTION_DRAW, currentPlayer, (*topPileCard));
      printHand(currentPlayer, hands, NO_SHOW);
      refresh();
      napms(500);
    }

    drawBorders(PRINT_ON_DECK, NO_HIGHLIGHT);

}

int AIcanContest(playerHand* hands, cardT topPileCard, int currentPlayer){
  for(int i = 1; i <= hands[currentPlayer].handCapacity; ++i)
    if(hands[currentPlayer].handCards[i].number == topPileCard.number)
      return i;

  return CARD_NOT_AVAILABLE;
}

int hasAI(int* isRealPlayer, int numberPlayers){
  int AIcount = 0;

  for(int i = 1; i <= numberPlayers; ++i)
    if(!isRealPlayer[i])
      AIcount++;

  if(AIcount == 0)
    return NO_AI;

  if(AIcount == numberPlayers - 1)
    return ALL_AI;

  return AI_AND_PLAYERS;
}
