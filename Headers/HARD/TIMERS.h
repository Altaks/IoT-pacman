/**
  ******************************************************************************************************************
  * @file    TIMERS.h
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   configuration des timers
  ******************************************************************************************************************/
	
#ifndef __TIMERS_H
#define __TIMERS_H

void initTIMERS(void);

void configTimer1(void);
void startTimer1(void); //Permet de lancer l'affichage du vaisseau
void stopTimer1(void);
void TIM1_UP_TIM10_IRQHandler(void);

void configTimer2(void);
void startTimer2(void); //Permet de lancer l'affichage du missile
void stopTimer2(void);
void TIM2_IRQHandler(void);

void configTimer8(void);
typedef enum {NORMAL, SPEED, HARDCORE, IMPOSSIBLE} Speed;
void setSpeedTimer8(Speed speed);
void startTimer8(void); //Permet de lancer l'affichage des ennemis
void stopTimer8(void);
void TIM8_UP_TIM13_IRQHandler(void);

void initTimer3(void);	//Permet de paramétrer la génération aléatoire
int getTimer3Value(void);

#endif
