/**
  ******************************************************************************************************************
  * @file    menu.h 
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   Gestion du menu
  ******************************************************************************************************************/
	
#ifndef __MENU_H
#define __MENU_H

typedef enum {JOUER, QUITTER} MenuSelected;

//Affiche le menu du jeu
void displayMenu(MenuSelected menuSelected);
//Raffraichi l'écran du menu
int refreshMenu(void);
//Affiche l'éran de fin, indique que le joueur a perdu ainsi que son score final
void displayGameLost(void);
//Affiche l'éran de fin, indique que le joueur a gagné
void displayGameWon(void);
//Affiche une illustration sur le menu
void displayLogo(void);

#endif
