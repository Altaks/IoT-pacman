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
	
	typedef enum {ENNEMI_1, ENNEMI_2, ENNEMI_3, BOSS} Type;
	
	//Structure d'un ennemi
	typedef struct Ennemi Ennemi;
	struct Ennemi
	{
			int direction; //indique le direction de l'ennemi (+1 pour droite ou -1 pour gauche)
			bool dead; //indique si l'ennemi est dead 
			int x; //donne la position en x de l'ennemi
			int y; //donne la position en y de l'ennemi
			int width; //donne la width de l'ennemi
			int height; //donne la height de l'ennemi
			Type type; //indique de quel type est l'ennemi
			int nbLives; //donne le nombre de nbLives de l'ennemi
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
	void updateMangeurPosition(void);
	
	

#endif
