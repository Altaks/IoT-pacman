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
static int playerScore = 0;
static int ennemiesScore = 0;
int playerMovement[2] = {0, 0};

static int xFood = 0, yFood = 0;

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
	for(i = 0; i < 3-playerScore; i++) defaultX -= 6;
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
	for(i = 0; i < 3-ennemiesScore; i++) defaultX -= 6;
	defaultX -= 6;
	GLCD_DrawString(defaultX, defaultY, "[");
	
	defaultX -= (6 + WIDTH_PACMAN);
	GLCD_DrawBitmap(defaultX, defaultY, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpEnnemiOpenRight);
	
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
}
void setupLevel()
{
	// Starting coroutines and interruptions handling
	initRandom();
	startTimer1();
	startInterruptJoystick();
	
	// Setting up the play screen
	GLCD_ClearScreen();
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenRight);
	
	// placing the food at a random position and display it
	placeFoodAtRandom();
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

void placeFoodAtRandom(){
	// remove the lastest ball
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
	GLCD_DrawRectangle(xFood-1, yFood-1, WIDTH_FOOD+1, HEIGHT_FOOD+1);
	
	// randomize the position of the new food
	xFood = getRandom(0, GLCD_WIDTH - WIDTH_PACMAN);
	yFood = getRandom(0, GLCD_HEIGHT - HEIGHT_PACMAN);
	
	// display it
	GLCD_DrawBitmap(xFood, yFood, WIDTH_FOOD, HEIGHT_FOOD, (const unsigned char *)bmpFood);
	
	// reset painter colors
	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
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
	
	if(xPlayer <= 0) xPlayer = 0;
	if(xPlayer >= GLCD_WIDTH - WIDTH_PACMAN) xPlayer = GLCD_WIDTH - WIDTH_PACMAN - 1;
	
	if(yPlayer <= 0) yPlayer = 0;
	if(yPlayer >= GLCD_HEIGHT - HEIGHT_PACMAN - 2*HEIGHT_FOOD -6) yPlayer = GLCD_HEIGHT - HEIGHT_PACMAN - 2*HEIGHT_FOOD - 7;
	
	if(sameDirection(playerMovement, GO_UP)){
		
		GLCD_DrawRectangle(xPlayer, yPlayer + HEIGHT_PACMAN, WIDTH_PACMAN, 1 );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenUp);
		
	} else if(sameDirection(playerMovement, GO_DOWN)){
		
		GLCD_DrawRectangle(xPlayer, yPlayer - 1, WIDTH_PACMAN, 1 );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenDown);
		
	} else if(sameDirection(playerMovement, GO_LEFT)){
		
		GLCD_DrawRectangle(xPlayer + WIDTH_PACMAN, yPlayer, 1, HEIGHT_PACMAN );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenLeft);
		
	} else if(sameDirection(playerMovement, GO_RIGHT)){
		
		GLCD_DrawRectangle(xPlayer -1, yPlayer, 1, HEIGHT_PACMAN );
		GLCD_DrawBitmap(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, (const unsigned char*)bmpPacManOpenRight);
		
	} else return;
}

bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) {
    // Calcul des coordonnées des bords des rectangles
    int left1 = x1;
    int right1 = x1 + width1;
    int top1 = y1;
    int bottom1 = y1 + height1;

    int left2 = x2;
    int right2 = x2 + width2;
    int top2 = y2;
    int bottom2 = y2 + height2;

    // Vérification de la collision
    return (left1 < right2 && right1 > left2 && top1 < bottom2 && bottom1 > top2);
}

void checkMangeurCollisionWithFood(){
	if(checkCollision(xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN, xFood, yFood, WIDTH_FOOD, HEIGHT_FOOD)){
		placeFoodAtRandom();
		playerScore++;
		displayScore();
	}
}

void gameLoop(){
	updateMangeurPosition();
	checkMangeurCollisionWithFood();
}

