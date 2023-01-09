 /******************************************************************************
 *
 * Module: CAN
 *
 * File Name: can.c
 *
 * Description: Source file for Can.
 *
 * Author: Ziad Ayman
 *
 *******************************************************************************/

#include "can.h"


tCANMsgObject sCANMessage;
uint8 pui8MsgData;

/* Global pointer to function used to point upper layer functions
 * to be used in Call Back */
static void (*g_Can_Call_Back_Ptr)(void) = NULL_PTR;

/************************************************************************************
* Service Name: initcan
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Responsible for Initializing Can
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

    /*Initialize the message object that will be used for sending CAN
    messages.  The message will be 4 bytes that will contain an incrementing
    value.  Initially it will be set to 0.*/
    pui8MsgData = 0;
    sCANMessage.ui32MsgID = CAN0TXID;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = (uint8 *)&pui8MsgData;


}
/************************************************************************************
* Service Name: CAN0IntHandler
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Responsible for Handling can interrupts
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
* Service Name: cantransmit
* Reentrancy: reentrant
* Parameters (in):  index , id
* Return value: None
* Description: Responsible for Transmitting data
************************************************************************************/
void cantransmit(uint32 index){
  pui8MsgData=index; 
  CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);

}