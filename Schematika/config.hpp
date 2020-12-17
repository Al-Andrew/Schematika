#pragma once


///Window
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Schematika"
#define ACTION_COOLDOWN 0.1f


///Theme
#define BACKGROUND_COLOR          Color({   0,   0,   0, 0.f })
#define CONSOLE_WARNING_COLOR	  Color({ 255,   0,   0, 1.F })

#define BLOCK_BACKGROUND_COLOR    Color({ 236, 240, 241, 1.f })
#define BLOCK_BORDER_COLOR        Color({ 149, 165, 166, 1.f })
#define BLOCK_FILL_COLOR          Color({   0, 153, 153, 1.f })
#define BLOCK_TEXT_COLOR          Color({  51,   0, 102, 1.f })
#define BLOCK_DECIZIE_DA_COLOR    Color({ 102, 255, 102, 1.f })
#define BLOCK_DECIZIE_NU_COLOR    Color({ 255, 102, 102, 1.f })
#define BLOCK_DECIZIE_TEXT_COLOR  Color({  51,   0, 102, 1.f })

#define NODE_COLOR				  Color({  39, 174,  96, 1.f })
#define NODE_HOVER_COLOR	      Color({ 255, 102, 102, 1.f })
#define NODE_LINE_COLOR		      Color({ 142,  68, 173, 1.f })
#define NODE_SELECT_COLOR		  Color({ 140,  40, 150, 1.f })

#define MENU_BACKGROUND_COLOR     Color({ 189, 195, 199, 1.f })
#define MENU_BORDER_COLOR         Color({ 127, 140, 141, 1.f })
#define MENU_HOVER_COLOR          Color({ 140,  34, 140, .3f })

///Menu
#define MENU_BORDER_WIDTH 5.f
#define SELECT_BLOCK_MENU_SPACER 75.f
#define SELECT_BLOCK_MENU_WIDTH 200.f
#define SELECT_BLOCK_MENU_HEIGHT WINDOW_HEIGHT
#define BLOCK_TITLE_HEIGHT SELECT_MENU_HEIGHT/2.f
#define TITLE_UP_SPACE 5.f
#define SELECT_MENU_HEIGHT 35 
#define SELECT_TRASH_POSX 1040.f
#define SELECT_TRASH_POSY 30.f

///Bocks
#define DEFAULT_X WINDOW_WIDTH/2
#define DEFAULT_Y WINDOW_HEIGHT/2
#define BLOCK_LIMITS_RIGHT 1012
#define BLOCK_LIMITS_LEFT 68
#define BLOCK_LIMITS_DOWN 34
#define BLOCK_LIMITS_UP 647
#define DECIZIE_WIDTH 120
#define DECIZIE_HEIGHT 50
#define CALCUL_WIDTH 110
#define CALCUL_HEIGHT 50
#define START_WIDTH 110
#define START_HEIGHT 50
#define STOP_WIDTH 110
#define STOP_HEIGHT 50
#define OUT_WIDTH 100
#define OUT_HEIGHT 40
#define IN_WIDTH 100
#define IN_HEIGHT 40
#define NODE_RADIUS 8.f

///Text
#define TEXT_MENU_SIZE 16
#define TEXT_BLOCK_SIZE 20