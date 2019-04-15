// Copyright 2018 Brezeanu Dan-Eugen
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncursesw/ncurses.h>
#include <time.h>
#include <string.h>
#include <locale.h>

// KEYS //

#define ENTER_KEY  10
#define KEY_ESCAPE 27

// COLOUR PAIRS //

#define PAIR_RED    2
#define PAIR_GREEN  3
#define PAIR_BLUE   4
#define PAIR_YELLOW 5

#define PAIR_RED_BK    6
#define PAIR_GREEN_BK  7
#define PAIR_BLUE_BK   8
#define PAIR_YELLOW_BK 9

// SHORTCUTS FOR PAIRS //

#define ON_RED    attron(COLOR_PAIR(PAIR_RED))
#define ON_GREEN  attron(COLOR_PAIR(PAIR_GREEN))
#define ON_BLUE   attron(COLOR_PAIR(PAIR_BLUE))
#define ON_YELLOW attron(COLOR_PAIR(PAIR_YELLOW))

#define ON_RED_BK    attron(COLOR_PAIR(PAIR_RED_BK))
#define ON_GREEN_BK  attron(COLOR_PAIR(PAIR_GREEN_BK))
#define ON_BLUE_BK   attron(COLOR_PAIR(PAIR_BLUE_BK))
#define ON_YELLOW_BK attron(COLOR_PAIR(PAIR_YELLOW_BK))

#define OFF_RED    attroff(COLOR_PAIR(PAIR_RED))
#define OFF_GREEN  attroff(COLOR_PAIR(PAIR_GREEN))
#define OFF_BLUE   attroff(COLOR_PAIR(PAIR_BLUE))
#define OFF_YELLOW attroff(COLOR_PAIR(PAIR_YELLOW))
#define OFF_ALL    OFF_RED; OFF_GREEN; OFF_BLUE; OFF_YELLOW

#define OFF_RED_BK    attroff(COLOR_PAIR(PAIR_RED_BK))
#define OFF_GREEN_BK  attroff(COLOR_PAIR(PAIR_GREEN_BK))
#define OFF_BLUE_BK   attroff(COLOR_PAIR(PAIR_BLUE_BK))
#define OFF_YELLOW_BK attroff(COLOR_PAIR(PAIR_YELLOW_BK))
#define OFF_ALL_BK    OFF_RED_BK; OFF_GREEN_BK; OFF_BLUE_BK; OFF_YELLOW_BK

// MISCELLANEOUS SHORTCUTS //

#define CLR         clear_screen(); refresh()
#define CARD_BACK   deck[0]
#define PRINT_SPACE mvprintw(x,y,"%c",32)

// COORDONATES //

#define WINDOW_X     40
#define WINDOW_Y     150

#define PILE_X       20
#define PILE_Y       50

#define DECK_X       20
#define DECK_Y       60

#define HAND_X       30
#define HAND_Y       30

#define INFO_X       10
#define INFO_Y       120

#define NEW_COLOUR_X 15
#define NEW_COLOUR_Y 50

#define DRAW_PLAY_X  20
#define DRAW_PLAY_Y  80

#define LOG_X        19
#define LOG_Y        115

#define MAIN_MENU_X  17
#define MAIN_MENU_Y  75

#define LOGO_X       3
#define LOGO_Y       52

// COLOUR CODES //

#define RED     1001
#define GREEN   1002
#define BLUE    1003
#define YELLOW  1004
#define NEUTRAL 1005

// CARD CODES //

#define SKIP    10
#define REVERSE 11
#define PLUS_2  12
#define WILD    13
#define PLUS_4  14

// CARD STRINGS //

#define SKIP_CH    "Ø"
#define REVERSE_CH ACS_LARROW
#define PLUS2_CH   "+2"
#define PLUS4_CH   "+4"
#define WILD_CH    "W"

// PRINT CODES //

#define CARD_NOT_AVAILABLE -10
#define PRINT_ON_LOG       -4
#define PRINT_ON_DRAW_PLAY -3
#define PRINT_ON_PILE      -2
#define PRINT_ON_DECK      -1

// ACTION CODES //

#define ACTION_DRAW      2001
#define ACTION_PLAY      2002
#define ACTION_DRAW_PLAY 2003
#define ACTION_CONTESTED 2004
#define ACTION_SKIP      2005
#define ACTION_WON       2006

// MAIN MENU OPTIONS //

#define NEW_GAME    1
#define MULTIPLAYER 2
#define CONTROLS    3
#define QUIT        4

// CAPACITIES //

#define DECK_CAPACITY 108
#define LOG_CAPACITY  22

// BOOLEAN VALUES //

#define HIGHLIGHT    1
#define NO_HIGHLIGHT 0

#define SHOW    1
#define NO_SHOW 0

#define NORMAL_ORDER   1
#define REVERSED_ORDER 0

#define LOCKED   1
#define UNLOCKED 0

#define IN_DECK 0
#define IN_PILE 1
#define IN_HAND 2

#define NO_AI          0
#define ALL_AI         1
#define AI_AND_PLAYERS 2
