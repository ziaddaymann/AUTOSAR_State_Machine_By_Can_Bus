 /******************************************************************************
 *
 * Module: Button
 *
 * File Name: Button.h
 *
 * Description: Header file to Initilaze Buttons.
 *
 * Author: Ziad Ayman
 *
 *******************************************************************************/


#ifndef BUTTON_H
#define BUTTON_H

#include "StandardTypes.h"

/* Button State according to its configuration PULL UP/Down */
#define BUTTON_PRESSED  STD_LOW
#define BUTTON_RELEASED STD_HIGH

/*************************************************
*           API  Functions Prototype
**************************************************/

/************************************************************************************
* Service Name: BUTTON_getState1
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (out): Switch 1 State
* Return value: None
* Description: Returns the current state of switch 1
*********************************************************************************************************/
uint8 BUTTON_getState1(void);

/************************************************************************************
* Service Name: BUTTON_getState2
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (out): Switch 2 State
* Return value: None
* Description: Returns the current state of switch 2
*********************************************************************************************************/
uint8 BUTTON_getState2(void);


/************************************************************************************
* Service Name: Button1_Current_State
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Updates the state of switch 1 using debouncing to ensure reliable button presses
*********************************************************************************************************/
void Button1_Current_State(void);


/************************************************************************************
* Service Name: Button2_Current_State
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Updates the state of switch 2 using debouncing to ensure reliable button presses
*********************************************************************************************************/
void Button2_Current_State(void);
/******************************************************************************/
#endif /* BUTTON_H */