/**
  ******************************************************************************************************************
  * @file    GPIO.c 
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   configuration des ports GPIO
  ******************************************************************************************************************/
	
	#include "stm32f10x.h"                  /* STM32F10x.h definitions            */
	#include "Registers.h"
	#include "GPIO.h"
	
	#include "game.h"

void initGPIO(void)
{
	//variable servant à gagner du temps lors de l'attribution des masques aux registres
	unsigned long temp;
	
	//Init Joystick Gauche
	temp = GPIOG->CRH & ~ 0xF000000;
	GPIOG->CRH = temp | 0x4000000;
	
	//Init Joystick Droite
	temp = GPIOG->CRH & ~ 0xF00000;
	GPIOG->CRH = temp | 0x400000;		
	
	//Init Joystick Haut
	temp = GPIOG->CRH & ~ 0xF0000000;
	GPIOG->CRH = temp | 0x40000000;
	
	//Init Joystick Bas
	temp = GPIOD->CRL & ~ 0xF000;
	GPIOD->CRL = temp | 0x4000;
	
	//Init BP_User
	temp = GPIOG->CRH & 0xFFFFFFF0;
	GPIOG->CRH = temp | 0x00000004;
	
	//Init Joystick Select
	temp = GPIOG->CRL & ~ 0xF0000000;
	GPIOG->CRL = temp | 0x40000000;
		
	//Enable GPIO
	RCC->APB2ENR |= (1<<5); // GPIODEN
	RCC->APB2ENR |= (1<<8); // GPIOGEN	
		
	/*---- Mise en service des registres AFIO pour la configuration d'interruptions externes ----*/
  RCC->APB2ENR |= (1 << 0); // Enable AFIO clock
	RCC->APB2ENR |= (1<<1); // AFIOEN  pour l'utilisation en EXTI des GPIO		
}

int joytickUpPressed(void)
{
	return (GPIOG->IDR & 0x8000) == APPUYE;
}

int joytickDownPressed(void)
{
	return (GPIOD->IDR & 0x0008) == APPUYE;
}

int joytickSelectPressed(void)
{
	return (GPIOG->IDR & 0x0080) == APPUYE;
}

int joytickLeftPressed(void)
{
	return (GPIOG->IDR & 0x4000) == APPUYE;
}

int joytickRightPressed(void)
{
	return (GPIOG->IDR & 0x2000) == APPUYE;
}

int userButtonPressed(void)
{
	return (GPIOG->IDR & 0x0100) == APPUYE;
}

void startInterruptBP_USER()
{
	unsigned long temp;

	SETENA0 |= (1<<23); //choix de la routine ? lancer lors de l'interruption
	temp = AFIO_EXTICR3 & 0xFFF0;
	AFIO_EXTICR3 = temp | 0x0006;
	EXTI->IMR |= (1<<8);
	
	EXTI->RTSR |= (1<<8); //on d?clenche lors de l'appui sur le bouton (donc front montant)
}

void startInterruptJoystick(){
	unsigned long temp;
	
	// configuration joystick haut gauche droite
	SETENA1 |= (1 << 8); // activer les lignes d'interruptions externes 10 à 15 pour les inputs du joystick 40e bit donc 32+8
	temp = AFIO_EXTICR4 & 0x000F;
	AFIO_EXTICR4 = temp | 0x6660;
	
	EXTI->IMR |= 0xE000; // on configure le masque sur les interruptions 15 14 13
	EXTI->RTSR |= (1 << 15) + (1 << 14) + (1 << 13); // on les configure en front montant
	
	// config joystick bas
	SETENA0 |= (1 << 9);
	temp = AFIO_EXTICR1 & 0x0FFF;
	AFIO_EXTICR1 = temp | 0x3000;
	
	EXTI->IMR |= (1 << 3);
	EXTI->RTSR |= (1 << 3);
}

void stopInterruptBP_USER()
{
	EXTI->IMR &= ~(1<<8);
}

void stopInterruptJoystick(){
	EXTI->IMR &= ~(0xE000);
	EXTI->IMR &= ~(1 << 3);
}

//routine d'interruption du bouton BP_USER
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & (1<<8)) //on rentre que si il n'y a pas d?ja un missile
	{
		EXTI->PR |= (1<<8); //on remet ? z?ro pour la prochaine interruption
	}	
}
