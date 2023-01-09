  /******************************************************************************
 *
 * [FILE NAME]: <ReceptionState.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <02/01/2022>
 *
 * [DESCRIPTION]: <Header file for Reception State>
 *
 *******************************************************************************/


#ifndef _H_RECEPTIONSTATE_H
#define _H_RECEPTIONSTATE_H 

#include "StandardTypes.h"
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Reception State
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Responsible for changing the current state machine to Reception State
************************************************************************************/
uint8 ReceptionState (uint8 index);


#endif