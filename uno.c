// Copyright 2018 Brezeanu Dan-Eugen
#include "game_logic.h"

int main(){
  setlocale(LC_ALL, "en_US.utf8");

  int selection;
  int numberPlayers;
  int numberPlayersAI;
  cardT topPileCard;
  cardT *deck = calloc(150, sizeof(cardT));
  playerHand *hands = calloc(8, sizeof(playerHand));
  int *cardsInDeck = calloc(150, sizeof(int));
  int *isRealPlayer = calloc(8, sizeof(int));

  init();

  while(1){
    selection = navigateMenu();

    if(selection == NEW_GAME || selection == MULTIPLAYER)
      break;

    if(selection == CONTROLS){
      displayControls();
      clear_screen();
      continue;
    }

    if(selection == QUIT){
        endwin();
        return 0;
    }
  }

  numberPlayers = introGame(deck, selection);
  numberPlayersAI = numberPlayers % 10;
  numberPlayers /= 10;

  for(int i = 1; i <= numberPlayers; ++i)
    isRealPlayer[i] = 1;

  numberPlayers += numberPlayersAI;
  CLR;

  topPileCard = startGame(hands, numberPlayers, deck, cardsInDeck);

  runGame(hands, numberPlayers, deck, cardsInDeck, topPileCard, isRealPlayer);

  refresh();
  getch();
  endwin();
  return 0;
}
