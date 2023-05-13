/**
  ******************************************************************************************************************
  * @file    game.c
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   Gestion du jeu
  ******************************************************************************************************************/

#include "TIMERS.h"
#include "GPIO.h"
#include "GLCD.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"

#include "game.h"
#include "ImagesBMP.h"
#include "ExtGlobales.h"
#include "random.h"

#include "stdio.h"

static int xPlayer = GLCD_WIDTH / 2, yPlayer = GLCD_HEIGHT / 2;
static int playerScore = 2;
static int ennemiesScore = 3;
int playerMovement[2] = {0, 0};

void displayScore()
{
	int defaultX = GLCD_WIDTH - 6;
	int defaultY = GLCD_HEIGHT - HEIGHT_PACMAN - 6;
	int i;
	
	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
	GLCD_SetFont(&GLCD_Font_6x8);
	
	// draw player score count
	GLCD_DrawString(defaultX, defaultY, "]");
	defaultX -= 10;
	for(i = 0; i < playerScore; i++){
		GLCD_DrawBitmap(defaultX, defaultY+1, 4, 4, (const unsigned char*)bmpFood);
		defaultX -= 6;
	};
	defaultX -= 6;
	GLCD_DrawString(defaultX, defaultY, "[");
	
	defaultX -= (6 + WIDTH_PACMAN);
	GLCD_DrawBitmap(defaultX, defaultY, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenRight);
	
	defaultX -= 16;
	
	// draw ennemies score count
	GLCD_DrawString(defaultX, defaultY, "]");
	defaultX -= 10;
	for(i = 0; i < ennemiesScore; i++){
		GLCD_DrawBitmap(defaultX, defaultY+1, 4, 4, (const unsigned char*)bmpFood);
		defaultX -= 6;
	};
	defaultX -= 6;
	GLCD_DrawString(defaultX, defaultY, "[");
	
	defaultX -= (6 + WIDTH_PACMAN);
	GLCD_DrawBitmap(defaultX, defaultY, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpEnnemiOpenRight);
	
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
}
void setupLevel()
{
	GLCD_ClearScreen();
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	startTimer1();
	GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenRight);
	startInterruptJoystick();
	
	// startTimer2();
}

void startLevel()
{
	displayScore();
}

void stopLevel()
{
	stopTimer1();
	stopTimer2();
	stopTimer8();
	stopInterruptBP_USER();
}

void changeDirection(const int direction[2]){
	playerMovement[0] = direction[0]; 
	playerMovement[1] = direction[1]; 
}

bool sameDirection(int a[2], const int b[2]){
	return a[0] == b[0] && a[1] == b[1];
}

void updateMangeurPosition(){
	
	xPlayer += playerMovement[0];
	yPlayer += playerMovement[1];
	
	if(xPlayer <= WIDTH_PACMAN) xPlayer = WIDTH_PACMAN + 1;
	if(xPlayer >= GLCD_WIDTH - WIDTH_PACMAN) xPlayer = GLCD_WIDTH - WIDTH_PACMAN - 1;
	
	if(yPlayer <= HEIGHT_PACMAN) yPlayer = HEIGHT_PACMAN + 1;
	if(yPlayer >= GLCD_HEIGHT - HEIGHT_PACMAN - 2*HEIGHT_FOOD) yPlayer = GLCD_HEIGHT - HEIGHT_PACMAN - 2*HEIGHT_FOOD - 1;
	
	if(sameDirection(playerMovement, GO_UP) && yPlayer >= HEIGHT_PACMAN){
		
		GLCD_DrawRectangle(xPlayer, yPlayer + HEIGHT_PACMAN, WIDTH_PACMAN, 1 );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenUp);
		
	}else if(sameDirection(playerMovement, GO_DOWN) && yPlayer <= GLCD_HEIGHT - HEIGHT_PACMAN - 2*HEIGHT_FOOD){
		
		GLCD_DrawRectangle(xPlayer, yPlayer - 1, WIDTH_PACMAN, 1 );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenDown);
		
	} else if(sameDirection(playerMovement, GO_LEFT) && xPlayer >= WIDTH_PACMAN){
		
		GLCD_DrawRectangle(xPlayer + WIDTH_PACMAN, yPlayer, 1, HEIGHT_PACMAN );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenLeft);
		
	} else if(sameDirection(playerMovement, GO_RIGHT) && xPlayer <= GLCD_WIDTH - WIDTH_PACMAN){
		
		GLCD_DrawRectangle(xPlayer -1, yPlayer, 1, HEIGHT_PACMAN );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenRight);
		
	} else return;
}
