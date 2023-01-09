 /******************************************************************************
 *
 * Module: can
 *
 * File Name: can.c
 *
 * Description: Source file to Initilaze can.
 *
 * Author: Ziad Ayman
 *
 *******************************************************************************/ 




#include "can.h"

tCANMsgObject sCANMessage;

uint8_t pui8MsgData;

/* Global pointer to function used to point upper layer functions
 * to be used in Call Back */
static void (*g_Can_Call_Back_Ptr)(void) = NULL_PTR;

/************************************************************************************
* Service Name: initcan
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Responsible for Can Initilazation
************************************************************************************/
void initcan(){

  SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

  /* Initialize the CAN controller*/
  CANInit(CAN0_BASE);

  /*Set up the bit rate for the CAN bus. */
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
  defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
      CANBitRateSet(CAN0_BASE, ui32SysClock, 500000);
#else
  CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
#endif
  
  /* Enable interrupts on the CAN peripheral.  */
  CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
  
  /* Enable the CAN interrupt on the processor (NVIC).
  */
  IntEnable(INT_CAN0);
  
  IntPrioritySet(INT_CAN0,0XE0);
  
  /* Enable the CAN for operation.*/
  CANEnable(CAN0_BASE);
  
  /*Initialize a message object to be used for receiving CAN messages with CAN ID. */
  
  sCANMessage.ui32MsgID = CAN0RXID;
  sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE;
  sCANMessage.ui32MsgLen = sizeof(pui8MsgData);

  CANMessageSet(CAN0_BASE, RXOBJECT, &sCANMessage, MSG_OBJ_TYPE_RX);
  
  
  
}
/************************************************************************************
* Service Name: CAN0IntHandler
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Responsible for Can interrupts
************************************************************************************/
void CAN0IntHandler(void)
{
  
     /* Check if the can_setCallBack is already called */
    if(g_Can_Call_Back_Ptr != NULL_PTR)
    {
        
      
      (*g_Can_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
    }
    
}
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
void Can_SetCallBack(void(*Ptr2Func)(void))
{
    g_Can_Call_Back_Ptr = Ptr2Func;
}
/************************************************************************************
* Service Name: Can_Recieve
* Reentrancy: reentrant
* Parameters (in):  Recieve_Flag
* Return value: pui8MsgData
* Description: Responsible for Can Recieving
************************************************************************************/
uint8 Can_Recieve(uint8 Recieve_Flag){
  if(Recieve_Flag)
  {    
    /*
     Reuse the same message object that was used earlier to configure
    the CAN for receiving messages.  A buffer for storing the
    received data must also be provided, so set the buffer pointer
    within the message object.
    */
    sCANMessage.pui8MsgData = (uint8_t *)&pui8MsgData;
    
    /*
     Read the message from the CAN.  Message object number 1 is used
     (which is not the same thing as CAN ID).  The interrupt clearing
     flag is not set because this interrupt was already cleared in
     the interrupt handler.
    */
    CANMessageGet(CAN0_BASE, RXOBJECT, &sCANMessage, 0);
    
    /*
     Clear the pending message flag so that the interrupt handler can
     set it again when the next message arrives.
    */
    Recieve_Flag = 0;
    
  }
  return pui8MsgData;
  
}
