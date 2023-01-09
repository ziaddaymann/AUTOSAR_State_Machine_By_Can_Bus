  /******************************************************************************
 *
 * [FILE NAME]: <TransmissionState.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <30/12/2022>
 *
 * [DESCRIPTION]: <Source file for Transmission State>
 *
 *******************************************************************************/

#include "TransmissionState.h"
#include "tm4c123gh6pm_registers.h"


/************************************************************************************
* Service Name: Transmission State
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Responsible for changing the current state machine to Transmission State
************************************************************************************/
void TransmissionState(uint8 Variable)
{
  cantransmit(Variable);
}