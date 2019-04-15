// Copyright 2018 Brezeanu Dan-Eugen
#include "draw_functions.h"

int introGame(cardT* deck, int selection){
  int x = WINDOW_X / 3;
  int y = WINDOW_Y / 2;
  int input;
  int returnValue = 0;

  CLR;

  buildDeck(deck);

  if(selection == MULTIPLAYER){
    mvprintw(x,y,"HOW MANY PLAYERS? (2-5)");
    refresh();

    while(input < '2' || input > '5')
      input = getch();

      returnValue = input - '0';
  }
  else
    returnValue = 1;

  CLR;

  if(selection == NEW_GAME)
    mvprintw(x,y,"HOW MANY A.I. PLAYERS? (1-5)");
  else if(selection == MULTIPLAYER)
          mvprintw(x,y,"HOW MANY A.I. PLAYERS? (0-5)");
  refresh();

  input = 6;

  while(input < ((selection == MULTIPLAYER) ? ('0') : ('1')) || input > '5')
    input = getch();

  returnValue = returnValue * 10 + input - '0';

  return returnValue;
}

void printCard(int whereToPrint, cardT card, const int shown){
  int x = 0, y = 0;

  if(whereToPrint == PRINT_ON_PILE){
    x = PILE_X;
    y = PILE_Y;
    mvprintw(PILE_X, PILE_Y+1, "%c", 32);
  }

  if(whereToPrint == PRINT_ON_DECK){
    x = DECK_X;
    y = DECK_Y;

    mvaddch(x,y,ACS_CKBOARD);
    return;
  }

  if(whereToPrint == PRINT_ON_DRAW_PLAY){
    x = DRAW_PLAY_X;
    y = DRAW_PLAY_Y;
  }

  if(x == 0 && y == 0){
    x = HAND_X + 3 * (whereToPrint / 18);
    y = HAND_Y + (5 * (whereToPrint - 1)  % 85);
  }

  if(shown == NO_SHOW)
    mvaddch(x,y,ACS_CKBOARD);
  else{
      switch(card.colour){
        case YELLOW: ON_YELLOW;
                     break;

        case RED: ON_RED;
                  break;

        case GREEN: ON_GREEN;
                    break;

        case BLUE: ON_BLUE;
                   break;
      }

      if(card.number > 9){
        switch(card.number){
          case SKIP: mvprintw(x,y,SKIP_CH);
                     break;

          case REVERSE: mvaddch(x,y,REVERSE_CH);
                        break;

          case PLUS_2: mvprintw(x,y,PLUS2_CH);
                       break;

          case WILD: mvprintw(x,y, WILD_CH);
                     break;

          case PLUS_4: mvprintw(x,y,PLUS4_CH);
                       break;

          default: mvprintw(x,y,"ILLEGAL CN %d", card.number);
                   break;
        }
      }
      else
        mvprintw(x,y,"%d", card.number);
  }
  OFF_ALL;
}

void drawBorders(int whereToDraw, const int isHighlighted){
  int x = 0,y = 0;

  if(whereToDraw == PRINT_ON_PILE){
      x = PILE_X;
      y = PILE_Y;
  }

  if(whereToDraw == PRINT_ON_DECK){
     x = DECK_X;
     y = DECK_Y;
  }

  if(whereToDraw == PRINT_ON_DRAW_PLAY){
    x = DRAW_PLAY_X;
    y = DRAW_PLAY_Y;
  }

  if(whereToDraw == PRINT_ON_LOG){
      x = LOG_X;
      y = LOG_Y;

      mvaddch(x,y,ACS_ULCORNER);

      for(int i = 1; i <= 47; ++i)
        mvaddch(x,++y, ACS_HLINE);

      mvaddch(x,++y,ACS_URCORNER);

      for(int i = 1; i <= 22; ++i)
        mvaddch(++x,y, ACS_VLINE);

      mvaddch(++x,y, ACS_LRCORNER);

      for(int i = 1; i <= 47; ++i)
        mvaddch(x,--y,ACS_HLINE);

      mvaddch(x,--y,ACS_LLCORNER);

      for(int i = 1; i <= 22; ++i)
        mvaddch(--x,y,ACS_VLINE);

      return;
  }

  if(x == 0 && y == 0){
    x = HAND_X + 3 * (whereToDraw / 18);
    y = HAND_Y + (5 * (whereToDraw - 1)  % 85);
  }

  x--; y-=2;
  if(isHighlighted)
    ON_RED;

  mvaddch(x,y,ACS_ULCORNER);
  mvaddch(++x,y,ACS_VLINE);
  mvaddch(++x,y,ACS_LLCORNER);

  mvaddch(x,++y,ACS_HLINE);
  mvaddch(x,++y,ACS_HLINE);
  mvaddch(x,++y,ACS_HLINE);

  mvaddch(x,++y, ACS_LRCORNER);
  mvaddch(--x,y,ACS_VLINE);
  mvaddch(--x,y,ACS_URCORNER);

  mvaddch(x,--y,ACS_HLINE);
  mvaddch(x,--y,ACS_HLINE);
  mvaddch(x,--y,ACS_HLINE);

  OFF_RED;

}

void printHand(int playerNumber, playerHand* hands, const int shown){
  for(int i = 1; i <= hands[playerNumber].handCapacity; ++i){
      printCard(i,hands[playerNumber].handCards[i], shown);
      drawBorders(i, NO_HIGHLIGHT);
  }

}

void printMenu(int selection){
	int height, width;

	getmaxyx(stdscr, height, width);
	clear_screen();
  drawLogo();

	switch(selection)
	{
		case NEW_GAME:
			mvprintw(height/2 -5 ,width/2 - 5,">  New game");

			mvprintw(height/2 ,width/2 - 5,"   Multiplayer");

			mvprintw(height/2 + 5,width/2 - 5,"   Controls");

			mvprintw(height/2 + 10,width/2 - 5,"   Quit");
			break;

		case MULTIPLAYER:
			mvprintw(height/2 -5,width/2 - 5,"   New game");

			mvprintw(height/2 ,width/2 - 5,">  Multiplayer");

			mvprintw(height/2 + 5,width/2 - 5,"   Controls");

			mvprintw(height/2 + 10,width/2 - 5,"   Quit");
			break;

		case CONTROLS:
			mvprintw(height/2 -5,width/2 - 5,"   New game");

			mvprintw(height/2 ,width/2 - 5,"   Multiplayer");

			mvprintw(height/2 + 5,width/2 - 5,">  Controls");

			mvprintw(height/2 + 10,width/2 - 5,"   Quit");
			break;

		case QUIT:
			mvprintw(height/2 -5,width/2 - 5,"   New game");

			mvprintw(height/2 ,width/2 - 5,"   Multiplayer");

			mvprintw(height/2 + 5,width/2 - 5,"   Controls");

			mvprintw(height/2 + 10,width/2 - 5,">  Quit");
			break;

	}

}

int navigateMenu(){
	int input;
	int selection = NEW_GAME, quit = 0;

  drawLogo();
	printMenu(selection);

	while(!quit)
	{
		input = getch();

		switch(input)
		{
			case KEY_UP :

				if(selection == NEW_GAME)
					selection = QUIT;
				else
					selection--;

				printMenu(selection);
				break;

			case KEY_DOWN :

				if(selection == QUIT)
					selection = NEW_GAME;
				else
					selection++;
				printMenu(selection);
				break;

      case KEY_RIGHT:
			case ENTER_KEY :

				return selection;
				break;
		}
	}
	return 0;
}

void displayControls(){
  int x = MAIN_MENU_X, y = MAIN_MENU_Y;

  clear_screen();

  mvaddch(x,y,ACS_UARROW); y+=3; mvprintw(x,y,"Select deck"); y-=3; x+=2;
  mvaddch(x,y,ACS_LARROW); y+=3; mvprintw(x,y,"Previous card"); y-=3; x+=2;
  mvaddch(x,y,ACS_RARROW); y+=3; mvprintw(x,y,"Next card"); y-=3; x+=2;
  mvaddch(x,y,ACS_DARROW); y+=3; mvprintw(x,y,"Select first card"); y-=3; x+=2;
  y-=3; mvprintw(x,y,"ENTER Play/Draw card"); x+=2; y+=3;
  mvprintw(x,y,"S   Show/Hide cards");  ++x;

  getch();

}

int chooseNewColour(){
    int currentColour = RED;
    int input, choseColour = 0;
    int x = NEW_COLOUR_X, y = NEW_COLOUR_Y;
    int redStar_x = 16, redStar_y = 51, blueStar_x = 16, blueStar_y = 48 ;
    int yellowStar_x = 14, yellowStar_y = 48, greenStar_x = 14, greenStar_y = 51;

    ON_RED_BK;

    PRINT_SPACE; y++; PRINT_SPACE; y++; PRINT_SPACE; x++; PRINT_SPACE;  y--; PRINT_SPACE; y--; PRINT_SPACE;

    OFF_RED_BK;
    refresh(); napms(100);

    x--; y-=3;
    ON_BLUE_BK;

    PRINT_SPACE; y++; PRINT_SPACE; y++; PRINT_SPACE; x++; PRINT_SPACE;  y--; PRINT_SPACE;  y--; PRINT_SPACE;

    OFF_BLUE_BK;
    refresh(); napms(100);

    x-=3;
    ON_YELLOW_BK;

    PRINT_SPACE; y++; PRINT_SPACE; y++; PRINT_SPACE; x++; PRINT_SPACE;  y--; PRINT_SPACE;  y--; PRINT_SPACE;

    OFF_YELLOW_BK;
    refresh(); napms(100);

    x--;
    y+=3;
    ON_GREEN_BK;

    PRINT_SPACE; y++; PRINT_SPACE; y++; PRINT_SPACE; x++; PRINT_SPACE;  y--; PRINT_SPACE;  y--; PRINT_SPACE;

    OFF_GREEN_BK;
    refresh(); napms(100);

    ON_RED_BK; mvprintw(redStar_x, redStar_y, "*"); OFF_RED_BK;

    while(!choseColour){
      input = getch();
      refresh();

      switch(input){
        case KEY_UP:
                     switch(currentColour){
                       case RED:
                                ON_GREEN_BK; mvprintw(greenStar_x, greenStar_y, "*"); OFF_GREEN_BK;
                                ON_RED_BK; mvprintw(redStar_x, redStar_y, " "); OFF_RED_BK;
                                currentColour = GREEN;
                                break;
                       case BLUE:
                                ON_YELLOW_BK; mvprintw(yellowStar_x, yellowStar_y, "*"); OFF_YELLOW_BK;
                                ON_BLUE_BK; mvprintw(blueStar_x, blueStar_y, " "); OFF_BLUE_BK;
                                currentColour = YELLOW;
                                break;
                     }
                     break;

        case KEY_DOWN:
                      switch(currentColour){
                        case GREEN:
                                 ON_RED_BK; mvprintw(redStar_x, redStar_y, "*"); OFF_RED_BK;
                                 ON_GREEN_BK; mvprintw(greenStar_x, greenStar_y, " "); OFF_GREEN_BK;
                                 currentColour = RED;
                                 break;
                        case YELLOW:
                                 ON_BLUE_BK; mvprintw(blueStar_x, blueStar_y, "*"); OFF_BLUE_BK;
                                 ON_YELLOW_BK; mvprintw(yellowStar_x, yellowStar_y, " "); OFF_YELLOW_BK;
                                 currentColour = BLUE;
                                 break;
                      }
                      break;

        case KEY_LEFT:
                      switch(currentColour){
                        case GREEN:
                                 ON_YELLOW_BK; mvprintw(yellowStar_x, yellowStar_y, "*"); OFF_YELLOW_BK;
                                 ON_GREEN_BK; mvprintw(greenStar_x, greenStar_y, " "); OFF_GREEN_BK;
                                 currentColour = YELLOW;
                                 break;
                        case RED:
                                 ON_BLUE_BK; mvprintw(blueStar_x, blueStar_y, "*"); OFF_BLUE_BK;
                                 ON_RED_BK; mvprintw(redStar_x, redStar_y, " "); OFF_RED_BK;
                                 currentColour = BLUE;
                                 break;
                      }
                      break;

        case KEY_RIGHT:
                      switch(currentColour){
                        case BLUE:
                                 ON_RED_BK; mvprintw(redStar_x, redStar_y, "*"); OFF_RED_BK;
                                 ON_BLUE_BK; mvprintw(blueStar_x, blueStar_y, " "); OFF_BLUE_BK;
                                 currentColour = RED;
                                 break;
                        case YELLOW:
                                 ON_GREEN_BK; mvprintw(greenStar_x, greenStar_y, "*"); OFF_GREEN_BK;
                                 ON_YELLOW_BK; mvprintw(yellowStar_x, yellowStar_y, " "); OFF_YELLOW_BK;
                                 currentColour = GREEN;
                                 break;
                      }
                      break;

        case ENTER_KEY:
                        choseColour = 1;
                        break;
      }

    }


    for(int i = 13; i <= 16; ++i)
      for(int j = 47; j <= 53; ++j)
        mvprintw(i,j," ");
    refresh();

    return currentColour;
}

void drawLogo(){

  // --- U --- //
  for(int i = LOGO_X; i < LOGO_X + 10; ++i){
    mvaddch(i,LOGO_Y,ACS_VLINE);
    mvaddch(i,LOGO_Y+2,ACS_VLINE);
  }

  mvaddch(LOGO_X + 10, LOGO_Y, ACS_VLINE);
  mvaddch(LOGO_X + 11, LOGO_Y, ACS_LLCORNER);
  mvaddch(LOGO_X + 10, LOGO_Y + 2, ACS_LLCORNER);

  for(int i = LOGO_Y + 1; i < LOGO_Y + 11; ++i){
    mvaddch(LOGO_X + 10, i+2, ACS_HLINE);
    mvaddch(LOGO_X + 11, i, ACS_HLINE);
  }

  mvaddch(LOGO_X + 11, LOGO_Y + 11, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 12, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 13, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 14, ACS_HLINE);

  mvaddch(LOGO_X + 11, LOGO_Y + 15, ACS_LRCORNER);
  mvaddch(LOGO_X + 10, LOGO_Y + 13, ACS_LRCORNER);
  mvaddch(LOGO_X + 10, LOGO_Y + 15, ACS_VLINE);

  for(int i = LOGO_X + 9; i >= LOGO_X; --i){
    mvaddch(i, LOGO_Y + 15, ACS_VLINE);
    mvaddch(i, LOGO_Y + 13, ACS_VLINE);
  }

  mvaddch(LOGO_X - 1, LOGO_Y, ACS_ULCORNER);
  mvaddch(LOGO_X - 1, LOGO_Y + 1, ACS_HLINE);
  mvaddch(LOGO_X - 1, LOGO_Y + 2, ACS_URCORNER);

  mvaddch(LOGO_X - 1, LOGO_Y + 13, ACS_ULCORNER);
  mvaddch(LOGO_X - 1, LOGO_Y + 14, ACS_HLINE);
  mvaddch(LOGO_X - 1, LOGO_Y + 15, ACS_URCORNER);

  // --- N --- //

  for(int i = LOGO_X + 1; i < LOGO_X + 11; ++i){
    mvaddch(i, LOGO_Y + 25, ACS_VLINE);
    mvaddch(i, LOGO_Y + 27, ACS_VLINE);
  }

  mvaddch(LOGO_X + 11, LOGO_Y + 25, ACS_LLCORNER);
  mvaddch(LOGO_X + 11, LOGO_Y + 26, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 27, ACS_LRCORNER);

  mvaddch(LOGO_X, LOGO_Y + 25, ACS_VLINE);
  mvaddch(LOGO_X - 1, LOGO_Y + 25, ACS_ULCORNER);
  mvaddch(LOGO_X - 1, LOGO_Y + 26, ACS_HLINE);

  for(int i = LOGO_X + 1, j = LOGO_Y + 28; i < LOGO_X + 10; ++i, ++j){
    mvprintw(i, j, "\\");
    mvprintw(i, j + 2, "\\");
  }

  mvprintw(LOGO_X, LOGO_Y + 29, "\\");
  mvaddch(LOGO_X - 1, LOGO_Y + 28, ACS_HLINE);
  mvaddch(LOGO_X - 1, LOGO_Y + 27, ACS_HLINE);


  for(int i = LOGO_X + 9; i >= LOGO_X; i--){
    mvaddch(i, LOGO_Y + 39, ACS_VLINE);
    mvaddch(i, LOGO_Y + 41, ACS_VLINE);
  }

  mvprintw(LOGO_X + 10, LOGO_Y + 37, "\\");
  mvaddch(LOGO_X + 11, LOGO_Y + 38, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 39, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 40, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 41, ACS_LRCORNER);
  mvaddch(LOGO_X + 10, LOGO_Y + 41, ACS_VLINE);

  mvaddch(LOGO_X - 1, LOGO_Y + 41, ACS_URCORNER);
  mvaddch(LOGO_X - 1, LOGO_Y + 40, ACS_HLINE);
  mvaddch(LOGO_X - 1, LOGO_Y + 39, ACS_ULCORNER);

  // --- O --- //

  mvaddch(LOGO_X - 1, LOGO_Y + 51, ACS_ULCORNER);
  mvaddch(LOGO_X , LOGO_Y + 53, ACS_ULCORNER);
  mvaddch(LOGO_X - 1, LOGO_Y + 52, ACS_HLINE);
  mvaddch(LOGO_X - 1, LOGO_Y + 53, ACS_HLINE);

  for(int i = LOGO_Y + 54; i < LOGO_Y + 67; ++i){
    mvaddch(LOGO_X - 1, i, ACS_HLINE);
    mvaddch(LOGO_X , i, ACS_HLINE);
    mvaddch(LOGO_X + 11, i, ACS_HLINE);
    mvaddch(LOGO_X + 10, i, ACS_HLINE);
  }

  mvaddch(LOGO_X, LOGO_Y + 51, ACS_VLINE);

  for(int i = LOGO_X + 1; i < LOGO_X + 10; ++i){
    mvaddch(i, LOGO_Y + 51, ACS_VLINE);
    mvaddch(i, LOGO_Y + 53, ACS_VLINE);
    mvaddch(i, LOGO_Y + 67, ACS_VLINE);
    mvaddch(i, LOGO_Y + 69, ACS_VLINE);
  }

  mvaddch(LOGO_X + 10, LOGO_Y + 53, ACS_LLCORNER);
  mvaddch(LOGO_X + 10, LOGO_Y + 67, ACS_LRCORNER);
  mvaddch(LOGO_X, LOGO_Y + 67, ACS_URCORNER);
  mvaddch(LOGO_X - 1, LOGO_Y + 67, ACS_HLINE);
  mvaddch(LOGO_X - 1, LOGO_Y + 68, ACS_HLINE);
  mvaddch(LOGO_X - 1, LOGO_Y + 69, ACS_URCORNER);
  mvaddch(LOGO_X, LOGO_Y + 69, ACS_VLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 69, ACS_LRCORNER);
  mvaddch(LOGO_X + 10, LOGO_Y + 69, ACS_VLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 68, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 67, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 53, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 52, ACS_HLINE);
  mvaddch(LOGO_X + 11, LOGO_Y + 51, ACS_LLCORNER);
  mvaddch(LOGO_X + 10, LOGO_Y + 51, ACS_VLINE);

  refresh();
}

void showInfo(int currentPlayer, int* cardsInDeck, int currentPlayerOrder){
    int x = INFO_X, y = INFO_Y;
    int countCardsInDeck = 0;

    for(int i = y; i < y + WINDOW_Y; ++i)
      for(int j = x; j < x + 8; ++j)
        mvprintw(j,i,"%c",32);

    mvprintw(x,y,"CURRENT PLAYER: %d", currentPlayer);
    x += 2;

    for(int i = 0; i < DECK_CAPACITY; ++i)
      if(cardsInDeck[i] == IN_DECK)
        countCardsInDeck++;

    mvprintw(x,y,"CARDS IN DECK: %d", countCardsInDeck);

    x += 2;

    mvprintw(x,y,"PLAYER ORDER: %s", (currentPlayerOrder == NORMAL_ORDER) ? ("NORMAL") : ("REVERSED"));

}

void printLogContent(char** logContent){
  int x = LOG_X, y = LOG_Y + 1;

  for(int i = x + 1; i <= x + 22; ++i)
    for(int j = y; j < y + 47; ++j)
      mvprintw(i,j," ");

  for(int i = 0; i <= LOG_CAPACITY; ++i)
   if(logContent[i] != NULL)
    mvprintw(++x,y,"%s", logContent[i]);

}
