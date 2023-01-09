  /******************************************************************************
 *
 * [FILE NAME]: <Dio.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <03/11/2022>
 *
 * [DESCRIPTION]: <Source file for DIO>
 *
 *******************************************************************************/

#include "Dio.h"
#include "Dio_Regs.h"



STATIC const Dio_ConfigChannel * Dio_PortChannels = NULL_PTR;
 uint8 Dio_Status = DIO_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Dio_Init
* Service ID[hex]: 0x10
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Dio module.
************************************************************************************/
void Dio_Init(const Dio_ConfigType * ConfigPtr)
{

		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		Dio_Status       = DIO_INITIALIZED;
		Dio_PortChannels = ConfigPtr->Channels; /* address of the first Channels structure --> Channels[0] */
}

/************************************************************************************
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a level of a channel(pin).
************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
        
	/* In-case there are no errors */
	
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels[ChannelId].Port_Num)
		{
                    case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
		}
		if(Level == STD_HIGH)
		{
			/* Write Logic High */
			SET_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].Ch_Num);
		}
		else if(Level == STD_LOW)
		{
			/* Write Logic Low */
			CLEAR_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].Ch_Num);
		}
	

}

/************************************************************************************
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): 
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to return the value of the specified DIO channel.
************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
	Dio_LevelType output = STD_LOW;

		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels[ChannelId].Port_Num)
		{
                    case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
		}
		/* Read the required channel */
		if(BIT_IS_SET(*Port_Ptr,Dio_PortChannels[ChannelId].Ch_Num))
		{
			output = STD_HIGH;
		}
		else
		{
			output = STD_LOW;
		}
	
        return output;
}


/************************************************************************************
* Service Name: Dio_WritePort
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): port_id - ID of DIO Port.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a Level of a Port.
************************************************************************************/
#if (Dio_WritePort == STD_ON)
void Dio_WritePort(Dio_PortType port_id, Dio_LevelType Level)
{
	volatile uint32 * portPtr = NULL_PTR;
	
	
		/* Point to the correct PORT register according to the Port Id stored in the port_number member */
		switch(Config[port_id].port_number)
		{
                    case 0:    portPtr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    portPtr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    portPtr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    portPtr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    portPtr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    portPtr = &GPIO_PORTF_DATA_REG;
		               break;
		}
		if(Level == LOGIC_HIGH)
		{
			/* Write Logic High */
			SET_BIT(*portPtr,Config[port_id].port_number);
		}
		else if(Level == LOGIC_LOW)
		{
			/* Write Logic Low */
			CLEAR_BIT(*portPtr,Config[port_id].port_number);
		}
	

}

#endif


/************************************************************************************
* Service Name: Dio_ReadPort
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): port_id - ID of DIO Port.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType
* Description: Function to return the value of the specified DIO Port.
************************************************************************************/
#if (Dio_ReadPort == STD_ON)
Dio_PortLevelType  Dio_ReadPort(Dio_PortType port_id)
{
	volatile uint32 * portPtr = NULL_PTR;
	Dio_PortLevelType output = LOGIC_LOW;

	
		/* Point to the correct PORT register according to the Port Id stored in the port_number member */
		switch(Config[port_id].port_number)
		{
                    case 0:    portPtr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    portPtr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    portPtr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    portPtr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    portPtr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    portPtr = &GPIO_PORTF_DATA_REG;
		               break;
		}
		/* Read the required channel */
		if(BIT_IS_SET(*portPtr,Config[port_id].port_number))
		{
			output = LOGIC_HIGH;
		}
		else
		{
			output = LOGIC_LOW;
		}
	
        return output;
}
#endif


/************************************************************************************
* Service Name: Dio_WriteChannelGroup
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Level.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to return the value of the specified DIO channel group.
************************************************************************************/
#if (Dio_WriteChannelGroup == STD_ON)
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level)
{
	volatile uint32 * portPtr = NULL_PTR;
	
	
		/* Point to the correct PORT register according to the Port Id stored in the port_number member */
		switch(ChannelGroupIdPtr->index)
		{
                    case 0:    portPtr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    portPtr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    portPtr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    portPtr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    portPtr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    portPtr = &GPIO_PORTF_DATA_REG;
		               break;
		}
		if(Level == LOGIC_HIGH)
		{
			/* Write Logic High */
			SET_BIT(*portPtr,ChannelGroupIdPtr->mask);
		}
		else if(Level == LOGIC_LOW)
		{
			/* Write Logic Low */
			CLEAR_BIT(*portPtr,ChannelGroupIdPtr->mask);
		}
	

}
#endif
/************************************************************************************
* Service Name: Dio_FlipChannel
* Service ID[hex]: 0x11
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to flip the level of a channel and return the level of the channel after flip.
************************************************************************************/
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
	Dio_LevelType output = STD_LOW;


	/* In-case there are no errors */
	
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels[ChannelId].Port_Num)
		{
                    case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
		}
		/* Read the required channel and write the required level */
		if(BIT_IS_SET(*Port_Ptr,Dio_PortChannels[ChannelId].Ch_Num))
		{
			CLEAR_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].Ch_Num);
			output = STD_LOW;
		}
		else
		{
			SET_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].Ch_Num);
			output = STD_HIGH;
		}
	
	
        return output;
}
#endif
