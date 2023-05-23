/**
  ******************************************************************************************************************
  * @file    ExtGlobales.h 
  * @author  IUT Informatique La Rochelle
  * @version v1.0
  * @date    2023
  * @modification	
  * @brief   d?clarations des variables globales
  ******************************************************************************************************************/

#ifndef __EXT_GLOBALES_H
#define __EXT_GLOBALES_H

#include "Board_GLCD.h"

extern int gameLost;
extern int gameWon;
extern int levelPassed;

extern int level;
extern int score;

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

#endif
