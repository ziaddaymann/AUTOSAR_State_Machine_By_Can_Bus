  /******************************************************************************
 *
 * [FILE NAME]: <TransmissionState.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <30/12/2022>
 *
 * [DESCRIPTION]: <Header file for Transmission State>
 *
 *******************************************************************************/


#ifndef TRANSMISSIONSTATE_H
#define TRANSMISSIONSTATE_H 

#include "StandardTypes.h"
#include "can.h"

/************************************************************************************
* Service Name: Transmission State
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Responsible for changing the current state machine to Transmission State
************************************************************************************/
void TransmissionState(uint8 Variable);

#endif