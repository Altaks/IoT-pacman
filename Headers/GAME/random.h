/**
  ******************************************************************************************************************
  * @file    random.h
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   Gestion de l'aléatoire
  ******************************************************************************************************************/
	
#ifndef __RANDOM_H
#define __RANDOM_H

void initRandom(void); //Lance le timer 3
void setRandom(void); //Récupère une valeur aléatoire à partir d'une seed basée sur le temps du timer 3
int getRandom(int min, int max); //Renvoie la vlaeur aléatoire générée

#endif

