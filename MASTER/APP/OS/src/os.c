  /******************************************************************************
 *
 * [FILE NAME]: <os.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <01/01/2022>
 *
 * [DESCRIPTION]: <Source file for OS Scheduler>
 *
 *******************************************************************************/

#include "os.h"
#include "AppTask.h"
#include "Button.h"
#include "SysTick.h"
#include "can.h"   

 
/* Macro Used to Enable Interrupts  */
#define Enable_Interrupts()    __asm("CPSIE I")

/* Global variable store the Os Time */
static volatile uint32 Timer_Tick_Count = 0;

/* Global variable to indicate the the timer has a new tick */
static volatile  uint8 Timer_Tick_Flag = 0;

/* Global variable to increment the Number of  ticks  */
static volatile uint8 Counter1=0;

/* Global variable to increment the Number of  ticks  */
static volatile  uint8 Counter2=0;

/* A flag to indicate that some transmission error occurred.*/
volatile bool g_bErrFlag = 0;

/*A flag for the interrupt handler to indicate that a message was received.*/
volatile bool g_bRXFlag = 0;

/************************************************************************************
* Service Name: Os_start
* Reentrancy: Non-Reentrant 
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Intialize the System .
************************************************************************************/
void Os_start(void)
{
    /* Global Interrupts Enabled */
    Enable_Interrupts();
    
    /*  Makes callback function to call OS_Timer_Reschedule Every Timer Tick*/
    SysTick_SetCallBack(OS_Timer_Reschedule);
    
        /*  Makes callback function to call OS_Can_Refresh Every Time Can Interruput  happens*/
    Can_SetCallBack(OS_Can_Refresh);
    
    /* To make timer tick every 20 MS */
    SysTick_Start(TIMER_BASE);

   /* To initalize the system*/
    Init_Task();

    /* Start the Scheduler */
    Os_Scheduler();
}

/************************************************************************************
* Service Name: OS_Can_Refresh
* Reentrancy: Reentrant 
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Can Callback Function.
************************************************************************************/
void OS_Can_Refresh(void){
  
uint32 ui32Status;
  
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

    
    else if(ui32Status == TXOBJECT)
    {
        /*
        Getting to this point means that the TX interrupt occurred on
        message object TXOBJECT, and the message reception is complete.
        Clear the message object interrupt.
        */
        CANIntClear(CAN0_BASE, TXOBJECT);

        /*
        Since a message was transmitted, clear any error flags.
        This is done because before the message is transmitted it triggers
        a Status Interrupt for TX complete. by clearing the flag here we
        prevent unnecessary error handling from happeneing
        */
        g_bErrFlag  = 0;
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



/************************************************************************************
* Service Name: OS_Timer_Reschedule
* Reentrancy: Reentrant 
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: This function is a timer tick handler for a software timer in an operating system.
************************************************************************************/
void OS_Timer_Reschedule(void)
{
     /*increment both counter to indicate the number Of Timer Ticks*/
   Timer_Tick_Count   = TIMER_BASE;

  
    Counter1++;
    Counter2++;
    
    if(Counter1==25)
    {
      Timer_Tick_Count=500;
      Counter1=0;
    }
    
    if(Counter2==3)
    {
      Timer_Tick_Count=60;
      Counter2=0;
    }
    /* Raising the timer flag to indicate the timr tick */
    Timer_Tick_Flag = 1;
}

/************************************************************************************
* Service Name: Os_Scheduler
* Reentrancy: Reentrant 
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Scheduler Task.
************************************************************************************/
void Os_Scheduler(void)
{
    while(1)
    {
	/* Code is only executed in case there is a new timer tick */
	if(Timer_Tick_Flag == 1)
	{
          /* Switch Case will run based on Timer Count*/
	    switch(Timer_Tick_Count)
            {
            case EVERY_20:
                          /*checks  SW1 & SW2 State*/
			    Button_Task(); 
                            
                            /*Clear Timer interrupt Flag*/
			    Timer_Tick_Flag = 0;
			    break;
                            
		case EVERY_60:
                            
                            /*checks  SW1 & SW2 State*/
			    Button_Task(); 
                            /*State Machine Function to change the color based on Sw1 & Sw2 State*/
			    App_Task();
                            
                            /*Clear Timer interrupt Flag*/
			    Timer_Tick_Flag = 0;
			    break;
		
                            
              case EVERY_500:
                            
                            /*Transmits Can Message every 500MS*/
			    Transmit_MSG();
                            
                            /*Clear Timer interrupt Flag*/
			    Timer_Tick_Flag = 0;
                            
                            /*Clears Timer Count tick to Start again*/
			    Timer_Tick_Count = 0;
                            
			    break;
            }
	}
    }

}