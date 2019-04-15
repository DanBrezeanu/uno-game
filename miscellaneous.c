// Copyright 2018 Brezeanu Dan-Eugen
#include "miscellaneous.h"


void init(){
  initscr();  // porneste stdscr
  keypad(stdscr,TRUE);
  start_color();

  init_pair(PAIR_RED,COLOR_RED,COLOR_BLACK);
  init_pair(PAIR_GREEN,COLOR_GREEN,COLOR_BLACK);
  init_pair(PAIR_BLUE,COLOR_BLUE,COLOR_BLACK);
  init_pair(PAIR_YELLOW,COLOR_YELLOW,COLOR_BLACK);

  init_pair(PAIR_RED_BK,COLOR_WHITE,COLOR_RED);
  init_pair(PAIR_GREEN_BK,COLOR_WHITE,COLOR_GREEN);
  init_pair(PAIR_BLUE_BK,COLOR_WHITE,COLOR_BLUE);
  init_pair(PAIR_YELLOW_BK,COLOR_WHITE,COLOR_YELLOW);

  noecho(); // nu afiseaza tastele scrise
  curs_set(0); // ascunde cursorul
  attron(A_BOLD);
  refresh();
}

void clear_screen(){
	for(int i = 0; i < WINDOW_Y; ++i)
		for(int j = 0; j < WINDOW_X ; ++j)
				mvprintw(j,i,"%c",32); // afiseaza spatii pe tot ecranul
}

void clear_hand(){
  for(int i = HAND_Y - 10; i < HAND_Y + 85; ++i)
    for(int j = HAND_X - 1; j < WINDOW_X; ++j)
      mvprintw(j,i,"%c",32);
}

char* toString(int number){
  char* returnValue = calloc(100, sizeof(char));

  switch(number){
    case 0:
            returnValue = "0 ";
            break;
    case 1:
            returnValue = "1 ";
            break;
    case 2:
            returnValue = "2 ";
            break;
    case 3:
            returnValue = "3 ";
            break;
    case 4:
            returnValue = "4 ";
            break;
    case 5:
            returnValue = "5 ";
            break;
    case 6:
            returnValue = "6 ";
            break;
    case 7:
            returnValue = "7 ";
            break;
    case 8:
            returnValue = "8 ";
            break;
    case 9:
            returnValue = "9 ";
            break;


  }

  return returnValue;
}

int getRandom(int *cardsInDeck){
  int randomOutput;

  srand(time(NULL));

  do{
    randomOutput = rand() % DECK_CAPACITY;

  }while(cardsInDeck[randomOutput] != IN_DECK);

  return randomOutput;
}

void addLogContent(char** logContent, const int action, int currentPlayer, cardT topPileCard){
  char* contentToAdd = calloc(100, sizeof(char));


  for(int i = LOG_CAPACITY - 1; i > 0; --i)
    strcpy(logContent[i], logContent[i-1]);

  strcpy(contentToAdd, " Player "); strcat(contentToAdd, toString(currentPlayer));

  if(action == ACTION_DRAW){
    strcat(contentToAdd, "has drawn a card");
    strcpy(logContent[0], contentToAdd);
    return;
  }

  if(action == ACTION_PLAY){
    strcat(contentToAdd, "has played a ");

    switch(topPileCard.colour){
      case RED:
                strcat(contentToAdd, "RED ");
                break;

      case GREEN:
                 strcat(contentToAdd, "GREEN ");
                 break;

      case YELLOW:
                  strcat(contentToAdd, "YELLOW ");
                  break;

      case BLUE:
                 strcat(contentToAdd, "BLUE ");
                 break;
    }

    if(topPileCard.number >= 0 && topPileCard.number <= 9)
      strcat(contentToAdd, toString(topPileCard.number));
    else
      switch(topPileCard.number){
        case SKIP:
                   strcat(contentToAdd, "SKIP");
                   break;

        case PLUS_2:
                     strcat(contentToAdd, "+2");
                     break;

        case PLUS_4:
                     strcat(contentToAdd, "+4");
                     break;

        case REVERSE:
                      strcat(contentToAdd, "REVERSE");
                      break;

        case WILD:
                  strcat(contentToAdd, "WILD");
                  break;

      }

    strcpy(logContent[0], contentToAdd);
    return;
  }

  if(action == ACTION_SKIP){
    strcat(contentToAdd, "has skipped his turn");

    strcpy(logContent[0], contentToAdd);
    return;
  }

  if(action == ACTION_DRAW_PLAY){
    strcat(contentToAdd, "drawn and played a ");

    switch(topPileCard.colour){
      case RED:
                strcat(contentToAdd, "RED ");
                break;

      case GREEN:
                 strcat(contentToAdd, "GREEN ");
                 break;

      case YELLOW:
                  strcat(contentToAdd, "YELLOW ");
                  break;

      case BLUE:
                 strcat(contentToAdd, "BLUE ");
                 break;
    }

    if(topPileCard.number >= 0 && topPileCard.number <= 9)
      strcat(contentToAdd, toString(topPileCard.number));
    else
      switch(topPileCard.number){
        case SKIP:
                   strcat(contentToAdd, "SKIP");
                   break;

        case PLUS_2:
                     strcat(contentToAdd, "+2");
                     break;

        case PLUS_4:
                     strcat(contentToAdd, "+4");
                     break;

        case REVERSE:
                      strcat(contentToAdd, "REVERSE");
                      break;

        case WILD:
                  strcat(contentToAdd, "WILD");
                  break;

      }

    strcpy(logContent[0], contentToAdd);
    return;

  }

  if(action == ACTION_CONTESTED){
    strcat(contentToAdd, "contested with a ");

    switch(topPileCard.colour){
      case RED:
                strcat(contentToAdd, "RED ");
                break;

      case GREEN:
                 strcat(contentToAdd, "GREEN ");
                 break;

      case YELLOW:
                  strcat(contentToAdd, "YELLOW ");
                  break;

      case BLUE:
                 strcat(contentToAdd, "BLUE ");
                 break;
    }

    if(topPileCard.number >= 0 && topPileCard.number <= 9)
      strcat(contentToAdd, toString(topPileCard.number));
    else
      switch(topPileCard.number){
        case SKIP:
                   strcat(contentToAdd, "SKIP");
                   break;

        case PLUS_2:
                     strcat(contentToAdd, "+2");
                     break;

        case PLUS_4:
                     strcat(contentToAdd, "+4");
                     break;

        case REVERSE:
                      strcat(contentToAdd, "REVERSE");
                      break;

        case WILD:
                  strcat(contentToAdd, "WILD");
                  break;

      }

    strcpy(logContent[0], contentToAdd);
    return;
  }

  if(action == ACTION_WON){
     strcat(contentToAdd, "has won the game!");
     strcpy(logContent[0], contentToAdd);
     return;
  }

}
