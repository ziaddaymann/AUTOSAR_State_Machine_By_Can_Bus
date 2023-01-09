  /******************************************************************************
 *
 * [FILE NAME]: <ReceptionState.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <02/01/2022>
 *
 * [DESCRIPTION]: <Source file for Reception State>
 *
 *******************************************************************************/


#include "ReceptionState.h"
#include "tm4c123gh6pm_registers.h"
#include "can.h"

/************************************************************************************
* Service Name: Reception State
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Responsible for changing the current state machine to Reception State
************************************************************************************/
uint8 ReceptionState (uint8 index)
{
  static uint8 DATA;
  DATA = Can_Recieve(index);
  return DATA;
}