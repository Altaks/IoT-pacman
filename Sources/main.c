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
			
	}
	
}






