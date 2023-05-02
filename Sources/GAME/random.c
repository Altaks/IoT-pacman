/**
  ******************************************************************************************************************
  * @file    random.c
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   Gestion de l'aléatoire
  ******************************************************************************************************************/
	
#include "random.h"
#include "TIMERS.h"

#include <stdlib.h>											//fonction rand()


void initRandom(void)
{
	initTimer3();
}

void setRandom(void)
{
	srand(getTimer3Value());
}

int getRandom(int min, int max)
{
	return rand()%(max-min) + min;
}
