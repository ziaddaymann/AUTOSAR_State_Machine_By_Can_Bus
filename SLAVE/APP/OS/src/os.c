  /******************************************************************************
 *
 * [FILE NAME]: <os.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <02/01/2022>
 *
 * [DESCRIPTION]: <Source file for OS Scheduler>
 *
 *******************************************************************************/

#include "os.h"
#include "AppTask.h"
#include "SysTick.h"
#include "Led.h"
#include "can.h"
#include "ReceptionState.h"



/* Enable IRQ Interrupts ... This Macro enables IRQ interrupts by clearing the I-bit in the PRIMASK. */
#define Enable_Interrupts()    __asm("CPSIE I")

/* Disable IRQ Interrupts ... This Macro disables IRQ interrupts by setting the I-bit in the PRIMASK. */
#define Disable_Interrupts()   __asm("CPSID I")

/* Global variable store the Os Time */
static uint8 g_Time_Tick_Count = 0;

/* Global variable to indicate the the timer has a new tick */
static uint8 g_New_Time_Tick_Flag = 0;

/* A flag to indicate that some transmission error occurred.*/

volatile bool g_bErrFlag = 0;

/*A flag for the interrupt handler to indicate that a message was received.*/

volatile bool g_bRXFlag = 0;

/************************************************************************************
* Service Name: Os_start
* Reentrancy: Non-reentrant
* Parameters (in):  None
* Return value: None
* Description: Task executes once to initialize the os
************************************************************************************/
void Os_start(void)
{
  /* Global Interrupts Enable */
  Enable_Interrupts();
  
  /* 
  Set the Call Back function to call Os_NewTimerTick
  this function will be called every SysTick Interrupt (20ms)
  */
  SysTick_SetCallBack(Os_NewTimerTick);
     /* 
     * Set the Call Back function to call OS_Can_Refresh
     * this function will be called every can Interrupt
     */
    Can_SetCallBack(OS_Can_Refresh);
  
  /* Start SysTickTimer to generate interrupt every 20ms */
  SysTick_Start(TIMER_BASE);
  
  /* Execute the Init Task */
  Init_Task();
  
    /* Initialize Can Driver */
    initcan();
  
  /* Start the Os Scheduler */
  Os_Scheduler();
}
/************************************************************************************
* Service Name: OS_Can_Refresh
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Function called by the Can Driver in the MCAL layer using the call back pointer
************************************************************************************/
void OS_Can_Refresh(void){

  
  uint32_t ui32Status;
  
  /*Read the CAN interrupt status to find the cause of the interrupt*/
  ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
  
  
  /*If the cause is a controller status interrupt, then get the status*/
  
  if(ui32Status == CAN_INT_INTID_STATUS)
  {
    /*
    Read the controller status.  This will return a field of status
    error bits that can indicate various errors.  Error processing
    is not done in this example for simplicity.  Refer to the
    API documentation for details about the error status bits.
    The act of reading this status will clear the interrupt.  If the
    CAN peripheral is not connected to a CAN bus with other CAN devices
    present, then errors will occur and will be indicated in the
    controller status.*/
    
    ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
    
    /*
     Set a flag to indicate some errors may have occurred.
   */
    g_bErrFlag = 1;
  }
  
  /*
  Check if the cause is message object 1, which what we are using for
  sending messages.
  */
  else if(ui32Status == RXOBJECT)
  {
    /*
    Getting to this point means that the RX interrupt occurred on
    message object RXOBJECT, and the message reception is complete.
    Clear the message object interrupt.
    */
    CANIntClear(CAN0_BASE, RXOBJECT);
    
    /*
    Set flag to indicate received message is pending.
    */
    g_bRXFlag = 1;
    
    /*
    Since the message was recived, clear any error flags.
    */
    g_bErrFlag = 0;
  }
  
  /*
  Otherwise, something unexpected caused the interrupt.  This should
  never happen.
  */
  else
  {
    /*
    Spurious interrupt handling can go here.
    */
  }





}
/*********************************************************************************************/
/************************************************************************************
* Service Name: Os_NewTimerTick
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Function called by the Timer Driver in the MCAL layer using the call back pointer
************************************************************************************/

void Os_NewTimerTick(void)
{
  /** Static Variable to detect if the timer reach 1 Sec **/
  static uint8 Counter=0;

  /* Increment the Os time by OS_BASE_TIME */
  g_Time_Tick_Count = TIMER_BASE;
  Counter++;
  
  g_New_Time_Tick_Flag = 1;
  
  if(Counter == 100)
  {
    g_Time_Tick_Count =100; 
    Counter=0;
  }
  
  /* Set the flag to 1 to indicate that there is a new timer tick */
}

/*********************************************************************************************/
/************************************************************************************
* Service Name: Os_Scheduler
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: The Engine of the Os Scheduler used for switch between different tasks
************************************************************************************/
void Os_Scheduler(void)
{
  static uint8 Can_Variable;
  
  while(1)
  {
    /* Code is only executed in case there is a new timer tick */
    
    if(g_New_Time_Tick_Flag == 1)
    {
      switch(g_Time_Tick_Count)
      {
      case EVERY_10:
        Can_Variable = ReceptionState(g_bRXFlag);
        g_New_Time_Tick_Flag = 0;
        break;
        
        
        /**** After 1 sec will aact on recieved data from can ****/
      case EVERY_100:
        App_Task(Can_Variable);
        g_New_Time_Tick_Flag = 0;
        g_Time_Tick_Count = 0;
        break;
      }
    }
  }
  
}