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

const int GO_UP[2] = {0, -1};
const int GO_DOWN[2] = {0, 1};
const int GO_LEFT[2] = {-1, 0};
const int GO_RIGHT[2] = {1, 0};
const int IDLE[2] = {0, 0};

static int xPlayer = GLCD_WIDTH / 2, yPlayer = GLCD_HEIGHT / 2;
static int playerMovement[2] = {0, 1};
static int playerScore = 3;

void displayScore()
{
	int defaultX = GLCD_WIDTH - 6;
	int defaultY = GLCD_HEIGHT - 6;
	int i;
	for(i = 0; i < playerScore; i++){
		GLCD_DrawBitmap(defaultX, defaultY, 4, 4, (const unsigned char*)bmpFood);
		defaultX -= 6;
	};
}
void setupLevel()
{
	GLCD_ClearScreen();
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	startTimer1();
	GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenRight);
	
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

void changeDirection(int direction[2]){
	playerMovement[0] = direction[0]; 
	playerMovement[1] = direction[1]; 
}

int samePosition(int a[2], const int b[2]){
	return a[0] == b[0] && a[1] == b[1];
}

void updateMangeurPosition(){
	
	if(samePosition(playerMovement, GO_UP) && yPlayer > HEIGHT_PACMAN){
		
		GLCD_DrawRectangle(xPlayer, yPlayer + HEIGHT_PACMAN, WIDTH_PACMAN, 1 );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenUp);
		yPlayer += playerMovement[1];
		
	}else if(samePosition(playerMovement, GO_DOWN) && yPlayer < GLCD_HEIGHT - HEIGHT_PACMAN - 2*HEIGHT_FOOD){
		
		GLCD_DrawRectangle(xPlayer, yPlayer - 1, WIDTH_PACMAN, 1 );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenDown);
		yPlayer += playerMovement[1];
	
	} else if(samePosition(playerMovement, GO_LEFT) && xPlayer > WIDTH_PACMAN){
		
		GLCD_DrawRectangle(xPlayer + WIDTH_PACMAN, yPlayer, 1, HEIGHT_PACMAN );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenLeft);
		xPlayer += playerMovement[0];
		
	} else if(samePosition(playerMovement, GO_RIGHT) && xPlayer < GLCD_WIDTH - WIDTH_PACMAN){
		
		GLCD_DrawRectangle(xPlayer -1, yPlayer, 1, HEIGHT_PACMAN );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenRight);
		xPlayer += playerMovement[0];
		
	}
}
