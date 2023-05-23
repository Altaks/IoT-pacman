/**
  ******************************************************************************************************************
  * @file    random.h
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   Gestion de l'al�atoire
  ******************************************************************************************************************/
	
#ifndef __RANDOM_H
#define __RANDOM_H

void initRandom(void); //Lance le timer 3
void setRandom(void); //R�cup�re une valeur al�atoire � partir d'une seed bas�e sur le temps du timer 3
int getRandom(int min, int max); //Renvoie la vlaeur al�atoire g�n�r�e

#endif

