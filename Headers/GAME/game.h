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
	int xPos; //Position horizontale de l'ennemi
	int yPos; //position verticale de l'ennemi
	bool alignXFirst; // Indicateur du premier axe pour lequel l'ennemi s'aligne avec la nourriture
	int direction[2]; //Direction de déplacement de l'ennemi
};

void displayLevelName(void);
void displayScore(void); //Affiche le score de Mangeur et des ennemis, sous la forme des nouritures mangées en bas de l'écran

void setupLevel(void); //Place les ennemis, la nouriture, Mangeur, et les interfaces de de score en bas de l'écran
void startLevel(void); //Démarre le timer gérant le déplacement des ennemis, et affiche le score
void stopLevel(void); //Met fin au niveau

bool checkCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2); //Vérifie la collision entre deux rectangles
void placeFoodAtRandom(void); //Place la nourriture à des positions aléatoires 

bool sameDirection(int a[2], const int b[2]); //Renvoi true si un vecteur de direction a est  égale à un vecteur de direction b
void changeDirection(const int array[2]); //Change la direction de déplacement des ennemis ou de Mangeur
void gameLoop(void); //Boucle de jeu
void updateEnnemiesPositionAndRedraw(void); //Actualise la position des ennemis et les redessine

#endif
