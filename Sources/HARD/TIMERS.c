/**
  ******************************************************************************************************************
  * @file    TIMERS.c 
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   configuration des timers
  ******************************************************************************************************************/
	
	#include "stm32f10x.h"                  /* STM32F10x.h definitions            */
	#include "Registers.h"
	#include "TIMERS.h"
	
	#include "game.h"
	#include "GPIO.h"
	

void initTIMERS()
{
	configTimer1();
	configTimer2();
	configTimer8();
}

//Controle la vitesse de déplacement du pacman
void configTimer1()
{
	RCC->APB2ENR |= (1<<11);
	TIM1->PSC = 3;					 //Pour une dur?e de 3,6ms
	TIM1->ARR = 64800;
	TIM1->DIER |= (1<<0);		// Permet de dire que l'on va utiliser une routine d'interruption
	stopTimer1();
	SETENA0 |= (1<<25);
}

void startTimer1()
{
	TIM1->CR1 |= (1<<0); //Activation du timer1
}

void stopTimer1()
{
	TIM1->CR1 &= ~(1<<0); //Arret du timer1
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	if(TIM1->SR & UIF)
	{
		gameLoop();
		TIM1->SR &= ~UIF;	
	}
}


//Controle la vitesse de d?placement du missile
void configTimer2()
{
	RCC->APB1ENR |= (1<<0);
	TIM2->PSC = 3; //Pour une dur?e de 1.8ms
  TIM2->ARR = 32400; 
	
  TIM2->DIER |= UIE; // autorisation des interruptions sur Timer2
 	SETENA0 = (1<<28); // bit 28 pour activation IRQ Timer2
}

void startTimer2()
{ 
	TIM2->CR1 |= (1<<0); 
}

void stopTimer2()
{
	TIM2->CR1 &= ~(1<<0); //Arret du timer2
}

void TIM2_IRQHandler (void){
    if ( TIM2->SR & UIF )
		{ 
      TIM2->SR  &= ~UIF; // abaissement drapeau			
    }
}


//Controle la vitesse de d?placement des ennemis
void configTimer8()
{
	RCC->APB2ENR |= (1<<13);
	setSpeedTimer8(NORMAL);			
	TIM8->ARR = 36000;
	TIM8->DIER |= (1<<0);
	stopTimer8();
	SETENA1 |= (1<<12);
}

void setSpeedTimer8(Speed speed)
{
	if(speed==NORMAL) TIM8->PSC = 31; 					// 16ms
	else if	(speed==SPEED) TIM8->PSC = 25; 			// 13ms
	else if	(speed==HARDCORE) TIM8->PSC = 19; 	// 10ms
	else if	(speed==IMPOSSIBLE) TIM8->PSC = 13; 	// 7ms
}

void startTimer8()
{ 
	TIM8->CR1 |= (1<<0);   //Activation du timer8
}

void stopTimer8()
{
	TIM8->CR1 &= ~(1<<0); //Arret du timer8
}


//routine d'interruption pour l'actualisation des coordonn?es du missile
void TIM8_UP_TIM13_IRQHandler(void)
{	
	if(TIM8->SR & UIF)
	{
				
		TIM8->SR &= ~UIF;//on remet le bit SR ? 0 pour la prochaine interruption
	}
}

//Timer pour la gestion de l'aléatoire
void initTimer3()
{
	RCC->APB1ENR |= (1<<1);
	TIM3->PSC = 0;
  TIM3->ARR = 0xFFFF; 
	TIM3->CR1 |= (1<<0);   //Activation du timer3
}

int getTimer3Value()
{
	return TIM3->CNT;
}

