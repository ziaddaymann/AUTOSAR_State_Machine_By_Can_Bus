  /******************************************************************************
 *
 * [FILE NAME]: <Port.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <03/11/2022>
 *
 * [DESCRIPTION]: <Source file for PORT>
 *
 *******************************************************************************/
 
 

#include "Port.h"
#include "tm4c123gh6pm_registers.h"

uint8 Port_Status = PORT_NOT_INITIALIZED; 
 
/************************************************************************************
* Service Name: Port_Init
* Service ID: 0x00
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Setup the port pin
*              - Setup the direction of the GPIO pin
*              - Setup pin as Digital or Analog 
*              - Setup pin as changeable or unchangeable
*              - Setup pin mode
*              - Setup the internal resistor for i/p pin
*              - Provide initial value for o/p pin
************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr )
{
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    
    
   
    for(int PinIndex=0;PinIndex<PORT_CONFIGURED_CHANNLES;PinIndex++)
    {

      
    switch(ConfigPtr[PinIndex].port_num)
    {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
    
    /* Enable clock for PORT and allow time for clock to start*/
    SYSCTL_REGCGC2_REG |= (1<<ConfigPtr[PinIndex].port_num);
    delay = SYSCTL_REGCGC2_REG;
    
    if( ((ConfigPtr[PinIndex].port_num == 3) && (ConfigPtr[PinIndex].pin_num == 7)) || ((ConfigPtr[PinIndex].port_num == 5) && (ConfigPtr[PinIndex].pin_num == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (ConfigPtr[PinIndex].port_num == 2) && (ConfigPtr[PinIndex].pin_num <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
        continue;
    }
    else
    {
        /* Do Nothing ... No need to unlock the commit register for this pin */
    }
    
    
  switch(ConfigPtr[PinIndex].Mode)
{
       case DIO :    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[PinIndex].pin_num); 
                           *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr[PinIndex].pin_num * 4));      
                           break;
         
       case UART :        
       case ADC :
       case SSI :
       case I2C :
       case M0PWM :
       case M1PWM :
       case M2PWM :
       case CAN :   SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);                   /* Enable Alternative function for this pin by seting the corresponding bit in GPIOAFSEL register */
                              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (ConfigPtr[PinIndex].Mode << (ConfigPtr[PinIndex].pin_num * 4));     /* Set the PMCx bits for this pin */   
                              break;
       
}


  if(ConfigPtr[PinIndex].DigitalMode == PORT_PIN_DIGITAL)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);          /* Set the corresponding bit in the GPIOAMSEL register to enable digital functionality on this pin */

    }
  else
  {
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable digital functionality on this pin */
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);          /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
  }


  
  
    if(ConfigPtr[PinIndex].direction == PORT_PIN_OUT)
    {
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
        if(ConfigPtr[PinIndex].initial_value == STD_HIGH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
    }
    else if(ConfigPtr[PinIndex].direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
        if(ConfigPtr[PinIndex].resistor == PULL_UP)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if(ConfigPtr[PinIndex].resistor == PULL_DOWN)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr[PinIndex].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
    }
    else
    {
        /* Do Nothing */
    }
    
    if(ConfigPtr[PinIndex].Open_Drain == OPEN_DRAIN_ENABLE)
    {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OPENDRAIN_OFFSET) , ConfigPtr[PinIndex].pin_num);     /* Set the corresponding bit in the GPIOODR register to enable the open drain function */
    }
    else
    {
    }
    Port_Status       = PORT_INITIALIZED;
        }
        }



/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x10
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): 
    -Pin       --> Port Pin ID number
    -Direction --> Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
{
        
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    
    switch(Port_PortChannels[Pin].port_number)
    {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
  if(Direction == PORT_PIN_OUT)
  {
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[Pin].channel_number);    /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
  }
  else
  {
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[Pin].channel_number);   /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
  }
}
#endif /* (PORT_SET_PIN_DIRECTION_API == STD_ON) */






/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x40
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): 
    -Pin   --> Port Pin ID number
    -Mode  --> New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode. 
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode)
{
        
        if((Pin > 15) && (Pin < 20))
        {
          /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {
        
          volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
          volatile uint32 delay = 0;
    
          switch(Port_PortChannels[Pin].port_number)
          {
             case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	     case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	     case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	     case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
             case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
             case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
         }
         if(Mode == PORT_PIN_MODE_DIO)
         {
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
           *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));     /* Clear the PMCx bits for this pin */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
         }
         else if(Mode == PORT_PIN_MODE_ADC)
         {
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);      /* Set the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
           *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));     /* Clear the PMCx bits for this pin */
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
         }
         else if(Mode == PORT_PIN_MODE_UART)
         {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));     /* Clear the PMCx bits for this pin */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);     /* Set the PMCx bits for this pin depending on the mode */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
         }
         else if(Mode == PORT_PIN_MODE_SSI)
         {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));     /* Clear the PMCx bits for this pin */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);     /* Set the PMCx bits for this pin depending on the mode */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
         }
         else if(Mode == PORT_PIN_MODE_I2C)
         {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));     /* Clear the PMCx bits for this pin */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);     /* Set the PMCx bits for this pin depending on the mode */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
         }
         else if(Mode == PORT_PIN_MODE_M0PWM)
         {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));     /* Clear the PMCx bits for this pin */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);     /* Set the PMCx bits for this pin depending on the mode */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
         }
         else if(Mode == PORT_PIN_MODE_M1PWM)
         {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));     /* Clear the PMCx bits for this pin */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);     /* Set the PMCx bits for this pin depending on the mode */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
         }
         else if(Mode == PORT_PIN_MODE_CAN)
         {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));     /* Clear the PMCx bits for this pin */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);     /* Set the PMCx bits for this pin depending on the mode */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
         }
         else
         {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));     /* Clear the PMCx bits for this pin */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
         }
         
         
       }
    
  
}
#endif /* (PORT_SET_PIN_MODE_API == STD_ON) */





