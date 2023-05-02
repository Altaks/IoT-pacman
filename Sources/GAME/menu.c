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
#include "ImagesBMP.h"
#include "ExtGlobales.h"

#include "stdio.h"

//affichage de l'?cran d'accueil
void displayMenu(MenuSelected menuSelected)
{	
	clearScreenGLCD();	
	displayLogo();
	
	if(menuSelected==JOUER)
	{ 
		GLCD_SetForegroundColor(GLCD_COLOR_RED);
		GLCD_DrawString  (100, 100,"Jouer");
		GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
		GLCD_DrawString (100, 140, "Quitter");
	}
	else if(menuSelected==QUITTER)
	{ 
		GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
		GLCD_DrawString (100, 100,"Jouer");
		GLCD_SetForegroundColor(GLCD_COLOR_RED);
		GLCD_DrawString (100, 140,"Quitter");
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
	
void displayGameLosed()
{
	char chaine[20];
	clearScreenGLCD();
	displayLogo();
	
	GLCD_SetForegroundColor(GLCD_COLOR_RED);
	GLCD_DrawString  (100, 100,"Perdu !!!");
	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
	sprintf(chaine,"Votre score : %d",score);
	GLCD_DrawString (20, 140, chaine);
	
	while(!userButtonPressed());
}

void displayGameWon()
{
	displayLogo();
	
	GLCD_SetForegroundColor(GLCD_COLOR_RED);
	GLCD_DrawString  (100, 100,"GAGNE !!!");
	
	while(!userButtonPressed());
}

void displayLogo()
{
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
	GLCD_SetFont(&GLCD_Font_16x24);
	GLCD_DrawString  (3, 0,"   SPACE-DEFENDER");
	
	GLCD_DrawBitmap (100,40,WIDTH_ENNEMI1,HEIGHT_ENNEMI1,(unsigned char *) bmpEnnemi1);
	GLCD_DrawBitmap (145,40,WIDTH_ENNEMI2,HEIGHT_ENNEMI2,(unsigned char *) bmpEnnemi2Red);
	GLCD_DrawBitmap (190,40,WIDTH_ENNEMI3,HEIGHT_ENNEMI3,(unsigned char *) bmpEnnemi3Green);
}

