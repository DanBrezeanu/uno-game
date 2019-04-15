// Copyright 2018 Brezeanu Dan-Eugen
#include "game_logic.h"


void buildDeck(cardT* deck){
    int cardIt = -1;
    for(int i = RED; i <= YELLOW; ++i){
      for(int j = 0; j <= 12; ++j){

        if(j == 0){
          deck[++cardIt].number = 0;
          deck[cardIt].colour   = i;
        }

        if(j > 0 && j <= 9){
          deck[++cardIt].number = j;
          deck[cardIt].colour   = i;

          deck[++cardIt].number = j;
          deck[cardIt].colour   = i;
        }

        if(j == 10){ //skip
          deck[++cardIt].number = SKIP;
          deck[cardIt].colour   = i;

          deck[++cardIt].number = SKIP;
          deck[cardIt].colour   = i;
        }

        if(j == 11){ //reverse
          deck[++cardIt].number = REVERSE;
          deck[cardIt].colour   = i;

          deck[++cardIt].number = REVERSE;
          deck[cardIt].colour   = i;
        }

        if(j == 12){ //+2
          deck[++cardIt].number = PLUS_2;
          deck[cardIt].colour   = i;

          deck[++cardIt].number = PLUS_2;
          deck[cardIt].colour   = i;
        }


      }

    }

   for(int i = 1; i <= 4; ++i){
    deck[++cardIt].number = WILD;
    deck[cardIt].colour   = NEUTRAL;

    deck[++cardIt].number = PLUS_4;
    deck[cardIt].colour   = NEUTRAL;
   }

}

cardT startGame(playerHand* hands, int numberPlayers, cardT* deck, int* cardsInDeck){
  int randomOutput;

  for(int i = 1; i <= numberPlayers; ++i){
    hands[i].handCapacity = 7;

    for(int j = 1; j <= 7; ++j){
      randomOutput = getRandom(cardsInDeck);
      hands[i].handCards[j] = deck[randomOutput];
      cardsInDeck[randomOutput] = IN_HAND;
    }
  }

  do{
    randomOutput = getRandom(cardsInDeck);
  }while(deck[randomOutput].number > 9);

  cardsInDeck[randomOutput] = IN_PILE;
  printCard(PRINT_ON_PILE, deck[randomOutput], SHOW);
  drawBorders(PRINT_ON_PILE, NO_HIGHLIGHT);

  printHand(1, hands, NO_SHOW);

  printCard(PRINT_ON_DECK, CARD_BACK, SHOW);
  drawBorders(PRINT_ON_DECK, NO_HIGHLIGHT);
  refresh();

  return deck[randomOutput];
}

int checkIfMoveAvailable(cardT topPileCard, cardT testCard){
  if(topPileCard.colour == testCard.colour)
    return 1;

  if(topPileCard.number == testCard.number)
    return 1;

  if(testCard.colour == NEUTRAL)
    return 1;

  if(topPileCard.colour == NEUTRAL)
    return 1;

  return 0;
}

void eraseCardFromHand(playerHand* hands, int currentPlayer, int currentCard){
  for(int i = currentCard + 1; i <= hands[currentPlayer].handCapacity; ++i)
    hands[currentPlayer].handCards[i-1] = hands[currentPlayer].handCards[i];

  hands[currentPlayer].handCapacity--;
}

void addCardToHand(playerHand* hands, int currentPlayer, cardT* deck, int* cardsInDeck){
  int randomOutput = getRandom(cardsInDeck);

  cardsInDeck[randomOutput] = IN_HAND;
  ++hands[currentPlayer].handCapacity;
  hands[currentPlayer].handCards[hands[currentPlayer].handCapacity] = deck[randomOutput];
}

void searchAndMarkCard(cardT* deck, cardT cardToSearch, int* cardsInDeck, const int mark){
  for(int i = 0; i < DECK_CAPACITY; ++i)
    if(cardToSearch.colour == deck[i].colour && cardToSearch.number == deck[i].number
       && cardsInDeck[i] == IN_HAND){
        cardsInDeck[i] = mark;
        break;
      }
}

int deckIsEmpty(int *cardsInDeck){
  for(int i = 0; i < DECK_CAPACITY; ++i)
    if(cardsInDeck[i] == IN_DECK)
      return 0;

  return 1;
}

int shuffleDeck(int *cardsInDeck, cardT* deck, cardT topPileCard){
  int availableCardsInDeck = 0;

  for(int i = 0; i < DECK_CAPACITY; ++i){
    if(deck[i].colour == topPileCard.colour && deck[i].number == topPileCard.number
       && cardsInDeck[i] == IN_PILE)
        continue;
    else if(cardsInDeck[i] == IN_PILE){
           cardsInDeck[i] = IN_DECK;
           availableCardsInDeck = 1;
    }
  }

  return availableCardsInDeck;
}

void modifyAttributes(cardT* currentCard, int* currentPlayerOrder, int currentPlayer, int numberPlayers,
                      int* skipCount, int* drawCount){
  if(currentCard->number == REVERSE)
      ((*currentPlayerOrder) == NORMAL_ORDER)
      ? ((*currentPlayerOrder) = REVERSED_ORDER)
      : ((*currentPlayerOrder) = NORMAL_ORDER);

  if(currentCard->number == WILD)
    currentCard->colour = chooseNewColour();

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
      drawCount[(currentPlayer % numberPlayers) + 1] += 2 + drawCount[currentPlayer];
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

    currentCard->colour = chooseNewColour();
  }

}

void modifyAttributesContested(cardT* currentCard, int* currentPlayerOrder, int currentPlayer, int numberPlayers,
                      int* skipCount, int* drawCount){

  if(currentCard->number == SKIP){
    if((*currentPlayerOrder) == NORMAL_ORDER)
      skipCount[(currentPlayer % numberPlayers) + 1] = skipCount[currentPlayer] + 1;
    else{
      if(currentPlayer - 1 == 0)
        skipCount[numberPlayers] = skipCount[currentPlayer] + 1;
      else
        skipCount[currentPlayer - 1] = skipCount[currentPlayer] + 1;
    }
  }

  if(currentCard->number == PLUS_2){
    if((*currentPlayerOrder) == NORMAL_ORDER){
      skipCount[(currentPlayer % numberPlayers) + 1]++;
      drawCount[(currentPlayer % numberPlayers) + 1] += 2 + drawCount[currentPlayer];
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

    currentCard->colour = chooseNewColour();
  }

}

int drawAndPlay(playerHand* hands, int currentPlayer, int currentShow){
    cardT currentCard = hands[currentPlayer].handCards[hands[currentPlayer].handCapacity];
    int x = DRAW_PLAY_X + 2, y = DRAW_PLAY_Y - 5;
    int input, choseMove = 0, isPlayed;

    printCard(PRINT_ON_DRAW_PLAY, currentCard, SHOW);
    drawBorders(PRINT_ON_DRAW_PLAY, HIGHLIGHT);

    mvprintw(x,y,"PLAY THIS CARD? (Y/N)");

    while(!choseMove){
      input = getch();

      switch(input){
        case 's':
        case 'S':
                  clear_hand();
                  currentShow = ~currentShow;
                  printHand(currentPlayer, hands, currentShow);
                  refresh();
                  break;

        case ENTER_KEY:
        case 'y':
        case 'Y':
                  choseMove = 1;
                  isPlayed = 1;
                  break;

        case 'n':
        case 'N':
                  choseMove = 1;
                  isPlayed = 0;
                  break;
      }
    }

    for(int i = DRAW_PLAY_X - 1; i <= DRAW_PLAY_X + 2; ++i)
      for(int j = DRAW_PLAY_Y - 5; j <= DRAW_PLAY_Y + 15; ++j)
        mvprintw(i,j," ");

    return isPlayed;
}

int searchForCardInHand(playerHand* hands, int currentPlayer, int numberToFind, int currentCard){
  for(int i = currentCard + 1; i <= hands[currentPlayer].handCapacity; ++i)
    if(hands[currentPlayer].handCards[i].number == numberToFind)
      return i;

  for(int i = 1; i <= currentCard; ++i)
    if(hands[currentPlayer].handCards[i].number == numberToFind)
      return i;

  return CARD_NOT_AVAILABLE;
}

int checkIfContests(playerHand* hands, int* skipCount, int* drawCount, int currentPlayer, cardT* topPileCard,
                     int currentPlayerOrder, int numberPlayers, cardT* deck, int* cardsInDeck, int* currentShow){
    int x = DRAW_PLAY_X + 2, y = DRAW_PLAY_Y - 5;
    int contests, choseMove = 0;
    int currentCard = 0;
    int availableContestCards = 1;
    int input, moveAvailable;


    mvprintw(x,y,"DO YOU CONTEST? (Y/N)");
    refresh();

    while(!choseMove){
      input = getch();

      switch(input){
        case ENTER_KEY:
        case 'y':
        case 'Y':
                  contests = 1;
                  choseMove = 1;
                  break;
        case 'n':
        case 'N':
                  contests = 0;
                  choseMove = 1;
                  break;
        case 's':
        case 'S':
                  clear_hand();
                  (*currentShow) = ~(*currentShow);
                  printHand(currentPlayer, hands, (*currentShow));
                  refresh();
                  break;
      }
    }

    for(int i = DRAW_PLAY_Y - 6; i < DRAW_PLAY_Y + 15; ++i)
      mvprintw(x,i," ");

    choseMove = 0;

    if(contests){
      mvprintw(x,y,"PRESS ESC TO CANCEL CONTEST");
      refresh();

      currentCard = searchForCardInHand(hands, currentPlayer, topPileCard->number, currentCard);

      if(currentCard == CARD_NOT_AVAILABLE)
        availableContestCards = 0;
      else
        drawBorders(currentCard, HIGHLIGHT);

      while(!choseMove){
          input = getch();
          refresh();

          switch(input){
            case KEY_ESCAPE:
                      choseMove = 1;
                      contests = 0;
                      break;

            case 's':
            case 'S':
                            clear_hand();
                            (*currentShow) = ~(*currentShow);
                            printHand(currentPlayer, hands, (*currentShow));
                            refresh();
                            break;

            case KEY_RIGHT:
                            if(availableContestCards)
                              if(currentCard < hands[currentPlayer].handCapacity){
                                drawBorders(currentCard, NO_HIGHLIGHT);
                                currentCard = searchForCardInHand(hands, currentPlayer, topPileCard->number, currentCard);
                                if(currentCard != CARD_NOT_AVAILABLE)
                                  drawBorders(currentCard, HIGHLIGHT);
                              }
                            break;

            case KEY_LEFT:
                            if(availableContestCards)
                              if(currentCard > 1){
                                drawBorders(currentCard, NO_HIGHLIGHT);
                                currentCard = searchForCardInHand(hands, currentPlayer, topPileCard->number, currentCard);
                                if(currentCard != CARD_NOT_AVAILABLE)
                                  drawBorders(currentCard, HIGHLIGHT);
                              }
                            break;

            case ENTER_KEY:

                              moveAvailable = checkIfMoveAvailable((*topPileCard), hands[currentPlayer].handCards[currentCard]);
                              if(moveAvailable){
                                  searchAndMarkCard(deck, hands[currentPlayer].handCards[currentCard], cardsInDeck, IN_PILE);

                                  modifyAttributesContested(&hands[currentPlayer].handCards[currentCard], &currentPlayerOrder,
                                                   currentPlayer, numberPlayers, skipCount, drawCount);

                                  printCard(PRINT_ON_PILE, hands[currentPlayer].handCards[currentCard], SHOW);

                                  (*topPileCard) = hands[currentPlayer].handCards[currentCard];

                                  eraseCardFromHand(hands, currentPlayer, currentCard);

                                  currentCard = 1;
                                  choseMove = 1;
                                }
                              break;

          }


      }
    }

  for(int i = DRAW_PLAY_Y - 6; i < DRAW_PLAY_Y + 25; ++i)
    mvprintw(x,i," ");

  return contests;
}

void runGame(playerHand* hands, int numberPlayers, cardT* deck, int* cardsInDeck, cardT topPileCard, int* isRealPlayer){
  int input, moveAvailable, isPlayed;
  int currentCard = 1;
  int turnOver = 0;
  int currentPlayer = 0;
  int currentShow = NO_SHOW;
  int availableCardsInDeck = 1;
  int isContested = 0;
  int quitted = 0;
  int currentPlayerOrder = NORMAL_ORDER;
  int *skipCount = calloc(numberPlayers + 1, sizeof(int));
  int *drawCount = calloc(numberPlayers + 1, sizeof(int));
  int *lockContest = calloc(numberPlayers + 1, sizeof(int));
  char **logContent = calloc(30, sizeof(char*));

  drawBorders(PRINT_ON_LOG, NO_HIGHLIGHT);
  for(int i = 0; i < 30; ++i)
    logContent[i] = calloc(100, sizeof(char));

  printLogContent(logContent);

  while(1){ //game
    turnOver = 0;
    currentCard = 1;
    currentShow = (hasAI(isRealPlayer, numberPlayers) == ALL_AI)
                  ? (SHOW)
                  : (NO_SHOW);

    if(hands[currentPlayer].handCapacity == 0 && currentPlayer){
      if(!quitted)
        addLogContent(logContent, ACTION_WON, currentPlayer, topPileCard);
      break;
    }

    if(deckIsEmpty(cardsInDeck))
      availableCardsInDeck = shuffleDeck(cardsInDeck, deck, topPileCard);

    if(currentPlayerOrder == NORMAL_ORDER)
      currentPlayer = (currentPlayer % numberPlayers) + 1;
    else{
      currentPlayer--;
      if(0 == currentPlayer)
        currentPlayer = numberPlayers;
    }

    if(!isRealPlayer[currentPlayer])
      currentShow = NO_SHOW;

    showInfo(currentPlayer, cardsInDeck, currentPlayerOrder /*TODO: other stats*/);
    printLogContent(logContent);
    refresh();


    while(!turnOver){ //turn

        isContested = 0;
        clear_hand();

        printHand(currentPlayer, hands, currentShow);
        refresh();

        // ---CONTEST--- //
        if((drawCount[currentPlayer] || skipCount[currentPlayer]) && lockContest[currentPlayer] == UNLOCKED){
          if(isRealPlayer[currentPlayer])
            isContested = checkIfContests(hands, skipCount, drawCount, currentPlayer, &topPileCard, currentPlayerOrder,
                                        numberPlayers, deck, cardsInDeck, &currentShow);
          else{ // ---AI CONTEST--- //
            currentCard = AIcanContest(hands, topPileCard, currentPlayer);
            if(currentCard != CARD_NOT_AVAILABLE){ // has card to contest
              searchAndMarkCard(deck, hands[currentPlayer].handCards[currentCard], cardsInDeck, IN_PILE);

              // modifyAttributes(&hands[currentPlayer].handCards[currentCard], &currentPlayerOrder,
              //                  currentPlayer, numberPlayers, skipCount, drawCount);

              printCard(PRINT_ON_PILE, hands[currentPlayer].handCards[currentCard], SHOW);

              topPileCard = hands[currentPlayer].handCards[currentCard];
              modifyAttributesAI(hands, &hands[currentPlayer].handCards[currentCard], &currentPlayerOrder,
                               currentPlayer, numberPlayers, skipCount, drawCount);
              eraseCardFromHand(hands, currentPlayer, currentCard);
              isContested = 1;
            }
            else
              isContested = 0;
          }
        }

        if(!isContested){
          if(drawCount[currentPlayer] || skipCount[currentPlayer])
            lockContest[currentPlayer] = LOCKED;

          while(drawCount[currentPlayer]){
            addCardToHand(hands, currentPlayer, deck, cardsInDeck);
            printHand(currentPlayer, hands, currentShow);
            addLogContent(logContent, ACTION_DRAW, currentPlayer, topPileCard);
            refresh();
            napms(200);
            drawCount[currentPlayer]--;
          }

          if(skipCount[currentPlayer]){
            skipCount[currentPlayer]--;
            addLogContent(logContent, ACTION_SKIP, currentPlayer, topPileCard);
            if(skipCount[currentPlayer] == 0)
              lockContest[currentPlayer] = UNLOCKED;
            break;
          }


        }
        else{
          lockContest[currentPlayer] = UNLOCKED;
          addLogContent(logContent, ACTION_CONTESTED, currentPlayer, topPileCard);
          skipCount[currentPlayer] = 0;
          drawCount[currentPlayer] = 0;
          turnOver = 1;
          continue;
        }


        if(isRealPlayer[currentPlayer]){
          drawBorders(currentCard, HIGHLIGHT);
          input = getch();
          switch(input){

            case 'q':
            case 'Q':
                      hands[currentPlayer].handCapacity = 0;
                      quitted = 1;
                      turnOver = 1;
                      break;

            case 's':
            case 'S':
                            clear_hand();
                            currentShow = ~currentShow;
                            printHand(currentPlayer, hands, currentShow);
                            refresh();
                            break;

            case KEY_UP:
                            drawBorders(PRINT_ON_DECK, HIGHLIGHT);
                            drawBorders(currentCard, NO_HIGHLIGHT);
                            currentCard = PRINT_ON_DECK;
                            break;

            case KEY_DOWN:
                            drawBorders(1, HIGHLIGHT);
                            drawBorders(currentCard, NO_HIGHLIGHT);
                            currentCard = 1;
                            break;

            case KEY_RIGHT:
                            if(currentCard < hands[currentPlayer].handCapacity && currentCard >= 1){
                              drawBorders(currentCard+1, HIGHLIGHT);
                              drawBorders(currentCard, NO_HIGHLIGHT);
                              currentCard++;
                            }
                            break;

            case KEY_LEFT:
                            if(currentCard > 1){
                              drawBorders(currentCard-1, HIGHLIGHT);
                              drawBorders(currentCard, NO_HIGHLIGHT);
                              currentCard--;
                            }
                            break;

            case ENTER_KEY:
                            // ---DRAW CARD--- //
                            if(currentCard == PRINT_ON_DECK){
                              if(availableCardsInDeck == 0) // Deck empty
                                break;

                              addCardToHand(hands, currentPlayer, deck, cardsInDeck);

                              currentCard = hands[currentPlayer].handCapacity;

                              moveAvailable = checkIfMoveAvailable(topPileCard, hands[currentPlayer].handCards[currentCard]);
                              if(moveAvailable){ // ---DRAW AND PLAY--- //
                                isPlayed = drawAndPlay(hands, currentPlayer, currentShow);

                                if(isPlayed){
                                  searchAndMarkCard(deck, hands[currentPlayer].handCards[currentCard], cardsInDeck, IN_PILE);

                                  modifyAttributes(&hands[currentPlayer].handCards[currentCard], &currentPlayerOrder,
                                                   currentPlayer, numberPlayers, skipCount, drawCount);

                                  printCard(PRINT_ON_PILE, hands[currentPlayer].handCards[currentCard], SHOW);

                                  topPileCard = hands[currentPlayer].handCards[currentCard];
                                  addLogContent(logContent, ACTION_DRAW_PLAY, currentPlayer, topPileCard);
                                  eraseCardFromHand(hands, currentPlayer, currentCard);
                                }
                                else{
                                  addLogContent(logContent, ACTION_DRAW, currentPlayer, topPileCard);
                                  printHand(currentPlayer, hands, currentShow);
                                  refresh();
                                  napms(500);
                                }
                              }
                              else{ // ---JUST DRAW--- //
                                addLogContent(logContent, ACTION_DRAW, currentPlayer, topPileCard);
                                printHand(currentPlayer, hands, currentShow);
                                refresh();
                                napms(500);
                              }

                              drawBorders(PRINT_ON_DECK, NO_HIGHLIGHT);

                              currentCard = 1;
                              turnOver = 1;
                            }
                            // ---PLAY CARD--- //
                            else{
                              moveAvailable = checkIfMoveAvailable(topPileCard, hands[currentPlayer].handCards[currentCard]);
                              if(moveAvailable){
                                searchAndMarkCard(deck, hands[currentPlayer].handCards[currentCard], cardsInDeck, IN_PILE);

                                modifyAttributes(&hands[currentPlayer].handCards[currentCard], &currentPlayerOrder,
                                                 currentPlayer, numberPlayers, skipCount, drawCount);

                                printCard(PRINT_ON_PILE, hands[currentPlayer].handCards[currentCard], SHOW);

                                topPileCard = hands[currentPlayer].handCards[currentCard];
                                addLogContent(logContent, ACTION_PLAY, currentPlayer, topPileCard);
                                eraseCardFromHand(hands, currentPlayer, currentCard);

                                currentCard = 1;
                                turnOver = 1;
                              }
                            }

          }
          refresh();
        }//is real player
        else{ //play card for AI
         AImove(hands, currentPlayer, deck, cardsInDeck, &topPileCard, logContent, skipCount, drawCount, &currentPlayerOrder, numberPlayers);
         clear_hand();
         printHand(currentPlayer, hands, NO_SHOW);
         refresh();
         napms(500);
         turnOver = 1;
       }

     }//turn
  }//game

  clear_hand();
  printLogContent(logContent);
  refresh();
}
