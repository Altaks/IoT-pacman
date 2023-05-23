/**
  ******************************************************************************************************************
  * @file    game.h 
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   Gestion du jeu
  ******************************************************************************************************************/
	
#ifndef __GAME_H
#define __GAME_H

#include "stdbool.h"

extern int xPlayer, yPlayer;
extern int playerMovement[2];
extern int xFood, yFood;
extern int playerScore;

//Structure d'un ennemi
typedef struct Ennemi Ennemi;
struct Ennemi
{
	int xPos;
	int yPos;
	bool alignXFirst;
	int direction[2];
};

void displayLevelName(void);
void displayScore(void);

void setupLevel(void);
void startLevel(void);
void stopLevel(void);

bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);
void placeFoodAtRandom(void);

bool sameDirection(int a[2], const int b[2]);
void changeDirection(const int array[2]);
void gameLoop(void);
void updateEnnemiesPositionAndRedraw(void);

#endif
