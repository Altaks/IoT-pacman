/**
  ******************************************************************************************************************
  * @file    main.c 
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   
  ******************************************************************************************************************/

#include "GLCD.h"
#include "GPIO.h"
#include "TIMERS.h"
#include "random.h"

#include "menu.h"
#include "game.h"

//variables globales
int gameLosed, gameWon, levelPassed, level, score;

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main(void){
	
	//initalisation du HARDWARE
	initGLCD();
	initGPIO();
	initTIMERS();
	initRandom();
	
	while(1)
	{		
		//Affichage du menu
		displayMenu(JOUER);
		while(!refreshMenu());
		
		//Lancement de la partie
		setRandom();
		gameLosed = gameWon = false;
		level = 1;
		score = 0;
		while(!gameLosed && !gameWon)			//Boucle de la partie
		{
			//Lancement du niveau
			setupLevel();
			startLevel();
			while(!gameLosed && !levelPassed);		//Boucle du niveau
			stopLevel();	
		}
		
		//Partie Perdue
		if(gameLosed) displayGameLosed();
		
		//Partie Gagnée
		else if(gameWon) displayGameWon();
	}
}






