#pragma once


///Window
#define WINDOW_WIDTH				1280
#define WINDOW_HEIGHT				720
#define WINDOW_TITLE				"Schematika"
#define ACTION_COOLDOWN				0.1f


///Theme 
#define DARK_THEME
#ifndef DARK_THEME
#define BACKGROUND_COLOR          Color({ 190, 190, 190, 0.f })
#define CONSOLE_WARNING_COLOR	  Color({ 255,   0,   0, 1.F })

#define BLOCK_FILL_COLOR          Color({  54,   0, 179, 1.f })
#define BLOCK_TEXT_COLOR          Color({ 255, 255, 255, 1.f })
#define BLOCK_DECIZIE_DA_COLOR    Color({ 102, 255, 102, 1.f })
#define BLOCK_DECIZIE_NU_COLOR    Color({ 255, 102, 102, 1.f })
#define BLOCK_DECIZIE_TEXT_COLOR  Color({  51,   0, 102, 1.f })

#define NODE_COLOR				  Color({   1, 135, 134, 1.f })
#define NODE_HOVER_COLOR	      Color({   3, 218, 198, 1.f })
#define NODE_LINE_COLOR		      Color({ 245,  42, 211, 1.f })
#define NODE_SELECT_COLOR		  Color({   3, 218, 198, 1.f })

#define MENU_BACKGROUND_COLOR     Color({ 240, 240, 240, 1.f })
#define MENU_BORDER_COLOR         Color({  92,  33, 176, 1.f })
#define MENU_HOVER_COLOR          Color({ 140,  34, 140, .3f })
#define MENU_TEXT_HOVER_COLOR     Color({ 140,  34, 140, .3f })
#define MENU_TEXT_COLOR			  Color({ 150, 150, 150, 1.f })

#define BACK_HOVER_COLOR		 Color({  92,  33, 176, 1.f })
#else
#define BACKGROUND_COLOR          Color({  45,  45,  45, 0.f })
#define CONSOLE_WARNING_COLOR	  Color({ 255,   0,   0, 1.F })

#define BLOCK_FILL_COLOR          Color({  54,   0, 179, 1.f })
#define BLOCK_TEXT_COLOR          Color({ 255, 255, 255, 1.f })
#define BLOCK_DECIZIE_DA_COLOR    Color({ 102, 255, 102, 1.f })
#define BLOCK_DECIZIE_NU_COLOR    Color({ 255, 102, 102, 1.f })
#define BLOCK_DECIZIE_TEXT_COLOR  Color({  51,   0, 102, 1.f })

#define NODE_COLOR				  Color({   1, 135, 134, 1.f })
#define NODE_HOVER_COLOR	      Color({   3, 218, 198, 1.f })
#define NODE_LINE_COLOR		      Color({ 142,  68, 173, 1.f })
#define NODE_SELECT_COLOR		  Color({   3, 218, 198, 1.f })

#define MENU_BACKGROUND_COLOR     Color({  50,  50,  50, 1.f })
#define MENU_BORDER_COLOR         Color({ 100, 100, 100, 1.f })
#define MENU_HOVER_COLOR          Color({ 190,  34, 140, .3f })
#define MENU_TEXT_HOVER_COLOR     Color({ 190,  34, 140, 1.f })
#define MENU_TEXT_COLOR			  Color({ 255, 255, 255, 1.f })

#define BACK_HOVER_COLOR		  Color({ 100, 100, 100, 1.f })

#endif


///Menu
#define MENU_BORDER_WIDTH			5.f
#define SELECT_BLOCK_MENU_SPACER	75.f
#define SELECT_BLOCK_MENU_WIDTH		200.f
#define SELECT_BLOCK_MENU_HEIGHT	WINDOW_HEIGHT
#define BLOCK_TITLE_HEIGHT			SELECT_MENU_HEIGHT/2.f
#define SELECT_QUESTION_SPACER		40.f
#define SELECT_SUBMENU_TEXT_SPACER	35.f
#define TITLE_UP_SPACE				5.f
#define SELECT_MENU_HEIGHT			35.f 
#define SELECT_TRASH_WIDTH			40.f
#define SELECT_TRASH_HEIGHT			40.f
#define CLOSE_BUTTON_WIDTH			50.f
#define BACK_BUTTON_WIDTH			50.f
#define CODE_WIDTH					400.f
#define CODE_HEIGHT					150.f
#define HELP_WIDTH					475.f
#define HELP_HEIGHT					static_cast<double>(WINDOW_HEIGHT)
#define ABOUT_WIDTH					400.f
#define ABOUT_HEIGHT				static_cast<double>(WINDOW_HEIGHT)

///Bocks
#define DEFAULT_X					WINDOW_WIDTH/2
#define DEFAULT_Y					WINDOW_HEIGHT/2
#define DECIZIE_WIDTH				120
#define DECIZIE_HEIGHT				50
#define CALCUL_WIDTH				110
#define CALCUL_HEIGHT				50
#define START_WIDTH					110
#define START_HEIGHT				50
#define STOP_WIDTH					110
#define STOP_HEIGHT					50
#define OUT_WIDTH					100
#define OUT_HEIGHT					40
#define IN_WIDTH					100
#define IN_HEIGHT					40
#define NODE_RADIUS					8.f

///Text
#define TEXT_MENU_SIZE				16
#define TEXT_BLOCK_SIZE				20
#define TEXT_SUBMENU_SIZE			20