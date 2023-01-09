 /******************************************************************************
 *
 * Module: can
 *
 * File Name: can.h
 *
 * Description: Header file to Initilaze can.
 *
 * Author: Ziad Ayman
 *
 *******************************************************************************/ 


#ifndef CAN
#define CAN
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom_map.h"
#include "StandardTypes.h"

#define CAN0RXID                1
#define RXOBJECT                1

/************************************************************************************
* Service Name: CAN0IntHandler
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Responsible for Can interrupts
************************************************************************************/
void CAN0IntHandler(void);

/************************************************************************************
* Service Name: initcan
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Responsible for Can Initilazation
************************************************************************************/
void initcan();

/************************************************************************************
* Service Name: Can_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Ptr2Func - Call Back function address
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the Can call back
************************************************************************************/
void Can_SetCallBack(void(*Ptr2Func)(void));

/************************************************************************************
* Service Name: Can_Recieve
* Reentrancy: reentrant
* Parameters (in):  Recieve_Flag
* Return value: pui8MsgData
* Description: Responsible for Can Recieving
************************************************************************************/
uint8 Can_Recieve(uint8 Recieve_Flag);



#endif