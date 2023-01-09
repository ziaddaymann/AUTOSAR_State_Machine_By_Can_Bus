 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: Led.h
 *
 * Description: Header file to Initilaze Leds.
 *
 * Author: Ziad Ayman
 *
 *******************************************************************************/

#ifndef _H_LED_H
#define _H_LED_H

#include "StandardTypes.h"

/************************************************************************************
* Service Name: RED_On
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Red on.
************************************************************************************/
void RED_On(void);


/************************************************************************************
* Service Name: BLUE_On
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to BLUE on.
************************************************************************************/
void BLUE_On(void);


/************************************************************************************
* Service Name: GREEN_On
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to GREEN on.
************************************************************************************/
void GREEN_On(void);


/************************************************************************************
* Service Name: WHITE_On
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to WHITE on.
************************************************************************************/
void WHITE_On(void);

#endif