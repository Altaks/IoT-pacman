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

static int xSpaceShip; //position x du vaisseau
static int rocketShooted;
static int xRocket; //position x du vaisseau
static int yRocket; //position y du vaisseau
int	nbEnnemis; //nb ennemis
Ennemi ennemis[30]; //tableau permettant de stocker les ennemis
int nbDeadEnnemis;

void displayLevelName()
{
	char chaine[20];	//Chaine de caractère
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
	GLCD_SetForegroundColor(GLCD_COLOR_YELLOW);
	GLCD_SetFont(&GLCD_Font_6x8);
	
	if(level<=6)
	{
		sprintf(chaine,"Niveau %d",level);
		GLCD_DrawString(0,0,chaine);
	}
	
	else if(level==7)
		GLCD_DrawString(0,0,"Boss");
	
	else if(level==8)
		GLCD_DrawString(0,0,"Boss - Le retour..");	
}

void displayScore()
{
	char chaine[5];	//Chaine de caractère
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
	GLCD_SetForegroundColor(GLCD_COLOR_BLUE);
	GLCD_SetFont(&GLCD_Font_16x24);
	sprintf(chaine,"%d",score);
	GLCD_DrawString((GLCD_WIDTH/2)-30,0,chaine);
}
void setupLevel()
{

}

void startLevel()
{

}

void stopLevel()
{
	stopTimer1();
	stopTimer2();
	stopTimer8();
	stopInterruptBP_USER();
}

void updateSpaceShip()
{	
	
}

void updateRocket()
{
	if (rocketShooted)
	{
		clearZone(xRocket, yRocket+HEIGHT_ROCKET-1, WIDTH_ROCKET, 1); //Permet d'effacer les traces du missile
		
		yRocket --;
		
		GLCD_SetForegroundColor(GLCD_COLOR_RED);
		GLCD_DrawBargraph(xRocket, yRocket	, WIDTH_ROCKET, HEIGHT_ROCKET, 1024);
		
		if(yRocket+HEIGHT_ROCKET<0) //si le missile sort de l'ecran alors on l'enl?ve
		{
			rocketShooted = false;
			displayLevelName();
			displayScore();
		}
	}
}

void shoot()
{
	
}

void updateEnnemis()
{
	int i;
	for(i=0;i<nbEnnemis;i++)
	{
		if(!ennemis[i].dead)	//si l'ennemi n'est pas dead il se déplace
		{	
			//si un ennemi arrive completement a gauche ou a droite on le fait descendre puis on le fait partir dans l'autre direction
			if(ennemis[i].x<=0 || ennemis[i].x>=GLCD_SIZE_Y-ennemis[i].width)
			{
				clearZone(ennemis[i].x, ennemis[i].y, ennemis[i].width, ennemis[i].height); //on efface l'ennemi avant de le décaler d'une ligne
				ennemis[i].direction*=-1;
				ennemis[i].y+=20;
			}
			else if(ennemis[i].direction == 1)
			{
				clearZone(ennemis[i].x, ennemis[i].y, 1, ennemis[i].height); //on efface la trace à gauche
			}
			else
			{
				clearZone(ennemis[i].x + ennemis[i].width-1, ennemis[i].y, 1, ennemis[i].height); //on effacela trace à droite
			}
			
			//increment la coordonn?e x de l'ennemi
			ennemis[i].x += ennemis[i].direction;
			
			// Test pour savoir si l'ennemi est touché
			if(rocketShooted && xRocket >= ennemis[i].x-WIDTH_ROCKET/2 && xRocket <= ennemis[i].x+ennemis[i].width+WIDTH_ROCKET/2 && yRocket <= ennemis[i].y+ennemis[i].height && yRocket >= ennemis[i].y)
			{
				ennemis[i].nbLives--;
				
				if(ennemis[i].type == BOSS)
				{
					score+=10;
				}
				if(ennemis[i].nbLives==0)
				{
					ennemis[i].dead=true;
					//attribution des points en fonction du type de l'ennemi
					switch(ennemis[i].type)
					{
						case ENNEMI_1: score+=5;break;
						case ENNEMI_2: score+=10;break;
						case ENNEMI_3: score+=20;break;
						case BOSS: score+=50;break;
					}
					nbDeadEnnemis++;
				}
				displayScore();
				rocketShooted = false;
				//on efface le missile
				clearZone(xRocket, yRocket, WIDTH_ROCKET, HEIGHT_ROCKET);
				
				//On efface l'ennemi
				clearZone(ennemis[i].x, ennemis[i].y, ennemis[i].width, ennemis[i].height);
			}
			
			
			//affichage de l'ennemi
			
			
			/*Test pour savoir si l'ennemi est arriver a la height du vaisseau*/
			
			//Test pour savoir si le niveau est terminé
			if(nbDeadEnnemis == nbEnnemis)
				levelPassed=true;
		}
	}		
}




