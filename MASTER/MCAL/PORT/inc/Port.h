  /******************************************************************************
 *
 * [FILE NAME]: <Port.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <03/11/2022>
 *
 * [DESCRIPTION]: <Header file for Port>
 *
 *******************************************************************************/

#ifndef PORT_H
#define PORT_H


/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)


/* Standard types */
#include "StandardTypes.h"


#include "Port_Cfg.h"


#include "Common_Macros.h"

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C
#define PORT_OPENDRAIN_OFFSET             0x50C   /* GPIOODR */
   
/* Modes */
#define DIO        (uint8)0
#define UART       (uint8)1
#define ADC        (uint8)2
#define SSI        (uint8)3
#define I2C        (uint8)4
#define M0PWM      (uint8)5
#define M1PWM      (uint8)6
#define M2PWM      (uint8)7
#define CAN        (uint8)8
   


  

   

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Description: Number of all available port pins */
typedef uint8 Port_PinType;

/* Description: Number of all available modes */
typedef uint8 Port_PinModeType;


/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT,NOT_IN_OR_OUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    RESISTOR_OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: PIN digital or analog */
typedef enum
{
    PORT_PIN_DIGITAL,PORT_PIN_ANALOG
}Port_DigitalMode;

/* Description: PIN changeable or not*/
typedef enum
{
    PORT_PIN_CHANGEABLE,PORT_PIN_UNCHANGEABLE
}Port_Pin_DirectionChangeable;

/* Description: Mode changeable or not*/
typedef enum
{
    PORT_MODE_CHANGEABLE,PORT_MODE_UNCHANGEABLE
}Port_Pin_ModeChangeable;

typedef enum
{
    OPEN_DRAIN_ENABLE,OPEN_DRAIN_DISABLE
}Port_Pin_OpenDrain;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 *      5. Choose the initial mode (0,1,2,3,4,5,6,7,8,9,14)
 *      6. Choose digital or analog
 *      7. Choose if the pin direction is changeable or not
 *      8. Choose if the pin mode is changeable or not
 *      9. Choose the pin's intial value
 */
typedef struct 
{
    uint8 port_num; 
    Port_PinType pin_num; 
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    Port_PinModeType Mode;
    Port_DigitalMode DigitalMode;
    Port_Pin_DirectionChangeable Direction_Change;
    Port_Pin_ModeChangeable Mode_Change;
    Port_Pin_OpenDrain  Open_Drain;
    uint8 initial_value;
}Port_ConfigType;

/* Data Structure required for initializing the Dio Driver */
typedef struct 
{
	Port_ConfigType Channel[PORT_CONFIGURED_CHANNLES];
}Port_Config;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
void Port_Init(const Port_ConfigType * Config );

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
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);
#endif



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
#if (Port_SetPinMode == STD_ON)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);
#endif


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */

extern const Port_ConfigType Port_ConfigSet[PORT_CONFIGURED_CHANNLES];

#endif
