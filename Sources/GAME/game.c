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

static Ennemi ennemies[3];

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
	int i = 0;
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
	
	// place and draw all the ennemies
	for(i = 0; i < 3; i++){
		ennemies[i].xPos = getRandom(WIDTH_PACMAN*2, GLCD_WIDTH - (WIDTH_PACMAN*2));
		ennemies[i].yPos = getRandom(HEIGHT_PACMAN*2, GLCD_HEIGHT - (HEIGHT_PACMAN*2));
		ennemies[i].alignXFirst = getRandom(0, 1); // true or false
		GLCD_DrawBitmap(ennemies[i].xPos, ennemies[i].yPos, WIDTH_ENNEMI, HEIGHT_ENNEMI, (const unsigned char*) bmpEnnemiOpenLeft);
	}
}

void startLevel()
{
	displayScore();
	startTimer8();
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
	clearZone(xFood, yFood, WIDTH_FOOD, HEIGHT_FOOD); 
	
	// randomize the position of the new food
	xFood = getRandom(WIDTH_PACMAN*2, GLCD_WIDTH - (WIDTH_PACMAN*2));
	yFood = getRandom(HEIGHT_PACMAN*2, GLCD_HEIGHT - (HEIGHT_PACMAN*2));
	
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

void redrawEnnemies(){
	int i = 0;
	for(; i < 3; i++){
		Ennemi * ennemi = &ennemies[i]; // get the address of the ennemi
		
		if(sameDirection(ennemi->direction, GO_UP)){
		
			GLCD_DrawRectangle(ennemi->xPos, ennemi->yPos + HEIGHT_ENNEMI, WIDTH_ENNEMI, 1 );
			GLCD_DrawBitmap(ennemi->xPos, ennemi->yPos, WIDTH_ENNEMI, HEIGHT_ENNEMI, (const unsigned char*)bmpEnnemiOpenUp);
		
		} else if(sameDirection(ennemi->direction, GO_DOWN)){
			
			GLCD_DrawRectangle(ennemi->xPos, ennemi->yPos - 1, WIDTH_ENNEMI, 1 );
			GLCD_DrawBitmap(ennemi->xPos, ennemi->yPos, WIDTH_ENNEMI, HEIGHT_ENNEMI, (const unsigned char*)bmpEnnemiOpenDown);
			
		} else if(sameDirection(ennemi->direction, GO_LEFT)){
			
			GLCD_DrawRectangle(ennemi->xPos + WIDTH_ENNEMI, ennemi->yPos, 1, HEIGHT_ENNEMI );
			GLCD_DrawBitmap(ennemi->xPos, ennemi->yPos, WIDTH_ENNEMI, HEIGHT_ENNEMI, (const unsigned char*)bmpEnnemiOpenLeft);
			
		} else if(sameDirection(ennemi->direction, GO_RIGHT)){
			
			GLCD_DrawRectangle(ennemi->xPos -1, ennemi->yPos, 1, HEIGHT_ENNEMI );
			GLCD_DrawBitmap(ennemi->xPos, ennemi->yPos, WIDTH_ENNEMI, HEIGHT_ENNEMI, (const unsigned char*)bmpEnnemiOpenRight);
			
		} else return;
	}
}

void updateEnnemiesPositionAndRedraw(){
	int i = 0;
	int newPosition[2];
	int oldPosition[2];
	for(; i < 3; i++){
		Ennemi * ennemi = &ennemies[i]; // get the address of the ennemi
	
		oldPosition[0] = ennemi->xPos;
		oldPosition[1] = ennemi->yPos;
		
		if(ennemi->alignXFirst){
			if(ennemi->xPos != xFood){
				// si le x est pas bon, ajuster le x
				if(ennemi->xPos > xFood) ennemi->xPos--; else ennemi->xPos++;
			} else {
				// sinon ajuster le y
				if(ennemi->yPos > yFood) ennemi->yPos--; else ennemi->yPos++;
			}
		} else {
			// faire l'inverse
			if(ennemi->yPos != yFood){
				// si le y est pas bon, ajuster le y
				if(ennemi->yPos > yFood) ennemi->yPos--; else ennemi->yPos++;
			} else {
				// sinon ajuster le y
				if(ennemi->xPos > xFood) ennemi->xPos--; else ennemi->xPos++;
			}
		}
		
		if(ennemi->xPos <= 0) ennemi->xPos = 0;
		if(ennemi->xPos >= GLCD_WIDTH - WIDTH_PACMAN) ennemi->xPos = GLCD_WIDTH - WIDTH_PACMAN - 1;
		
		if(ennemi->yPos <= 0) ennemi->yPos = 0;
		if(ennemi->yPos >= GLCD_HEIGHT - HEIGHT_PACMAN - 2*HEIGHT_FOOD -6) ennemi->yPos = GLCD_HEIGHT - HEIGHT_PACMAN - 2*HEIGHT_FOOD - 7;
		

		newPosition[0] = ennemi->xPos;
		newPosition[1] = ennemi->yPos;
		
		ennemi->direction[0] = newPosition[0] - oldPosition[0];
		ennemi->direction[1] = newPosition[1] - oldPosition[1]; // define ennemi direction
		
		if(checkCollision(ennemi->xPos, ennemi->yPos, WIDTH_ENNEMI, HEIGHT_ENNEMI, xFood, yFood, WIDTH_FOOD, HEIGHT_FOOD)){
			placeFoodAtRandom();
			ennemiesScore++;
			if(ennemiesScore == 3) {
				gameLosed = true;
				stopLevel();
				return;
			}
			if(ennemiesScore == 2) setSpeedTimer8(SPEED);
			displayScore();
		} else redrawEnnemies();
	}
	
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
		if(playerScore == 3) {
			stopLevel();
			gameWon = true;
		}
	}
}

void checkMangeurCollisionWithEnnemies(){
	int i = 0;
	for(; i < 3; i++) {
		Ennemi * ennemi = &ennemies[i];
		if(checkCollision(ennemi->xPos, ennemi->yPos, WIDTH_ENNEMI, HEIGHT_ENNEMI, xPlayer, yPlayer, WIDTH_PACMAN, HEIGHT_PACMAN)){
			stopLevel();
			gameLosed = true;
		}
	}
}

void gameLoop(){
	updateMangeurPosition();
	checkMangeurCollisionWithEnnemies();
	checkMangeurCollisionWithFood();
}

