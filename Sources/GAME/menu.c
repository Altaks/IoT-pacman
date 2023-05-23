/**
  ******************************************************************************************************************
  * @file    menu.c
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   Gestion du menu
  ******************************************************************************************************************/

#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "GPIO.h"
#include "GLCD.h"

#include "menu.h"
#include "game.h"
#include "ImagesBMP.h"
#include "ExtGlobales.h"

#include "stdio.h"

//affichage de l'?cran d'accueil
void displayMenu(MenuSelected menuSelected)
{	
	displayLogo();
	GLCD_SetFont(&GLCD_Font_16x24);
	
	if(menuSelected==JOUER)
	{ 
		GLCD_SetForegroundColor(GLCD_COLOR_RED);
		GLCD_DrawString  (100, 100,"> Play");
		GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
		GLCD_DrawString (100, 140, "  Quit");
	}
	else if(menuSelected==QUITTER)
	{ 
		GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
		GLCD_DrawString (100, 100,"  Play");
		GLCD_SetForegroundColor(GLCD_COLOR_RED);
		GLCD_DrawString (100, 140,"> Quit");
	}
}

int refreshMenu()
{
	static MenuSelected menuSelected = JOUER;
	
	if(joytickUpPressed() && menuSelected == QUITTER)
	{
		menuSelected = JOUER;
		displayMenu(menuSelected);
	}
	if(joytickDownPressed()&& menuSelected == JOUER) 
	{
		menuSelected = QUITTER;
		displayMenu(menuSelected);
	}
	
	return joytickSelectPressed() && menuSelected==JOUER;
}
	
void displayGameLost()
{
	char chaine[20];
	clearScreenGLCD();
	displayLogo();
	
	GLCD_SetForegroundColor(GLCD_COLOR_RED);
	GLCD_DrawString  (100, 100,"Perdu !!!");
	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
	sprintf(chaine,"Votre score : %d",playerScore);
	GLCD_DrawString (20, 140, chaine);
	
	while(!userButtonPressed());
}

void displayGameWon()
{
	clearScreenGLCD();
	displayLogo();
	
	GLCD_SetForegroundColor(GLCD_COLOR_GREEN);
	GLCD_DrawString  (100, 100,"GAGNE !!!");
	
	while(!userButtonPressed());
}

void displayLogo()
{
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);

	GLCD_SetFont(&GLCD_Font_16x24);
	GLCD_DrawString  (3, 24,"      PAC-MAN");

	GLCD_SetFont(&GLCD_Font_6x8);
	GLCD_DrawString  (3, GLCD_HEIGHT - 8,"Arnaud Mazurier         IUT A2           Hugo Russeil");

	GLCD_DrawBitmap (100,60,WIDTH_PACMAN,HEIGHT_PACMAN,(unsigned char *) bmpEnnemiOpenRight);
	GLCD_DrawBitmap (145,60,WIDTH_PACMAN,HEIGHT_PACMAN,(unsigned char *) bmpPacManOpenRight);
	GLCD_DrawBitmap (190,62,WIDTH_FOOD,HEIGHT_FOOD,(unsigned char *) bmpFood);
}

