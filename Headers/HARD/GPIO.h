/**
  ******************************************************************************************************************
  * @file    GPIO.h
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   configuration des ports GPIO
  ******************************************************************************************************************/
	
#ifndef __GPIO_H
#define __GPIO_H

extern const int GO_UP[2];
extern const int GO_DOWN[2];
extern const int GO_LEFT[2];
extern const int GO_RIGHT[2];
extern const int IDLE[2];

void initGPIO(void);//Initialisation des ports

int joytickUpPressed(void); //Vérifie l'appui sur le joystick vers le haut
int joytickDownPressed(void); //Vérifie l'appui sur le joystick vers le bas
int joytickSelectPressed(void); //Vérifie l'appui sur le joystick
int joytickLeftPressed(void); //Vérifie l'appui sur le joystick vers la gauche
int joytickRightPressed(void); //Vérifie l'appui sur le joystick vers la droite
int userButtonPressed(void); //Vérifie l'appui sur le bouton user

void startInterruptBP_USER(void); //Lance l'interruption sur le bouton user
void startInterruptJoystick(void); //Lance les interruptions sur le joystick

void stopInterruptBP_USER(void); //stoppe l'interruption sur le bouton user
void stopInterruptJoystick(void); //stoppe les interruptions sur le joystick

#endif
