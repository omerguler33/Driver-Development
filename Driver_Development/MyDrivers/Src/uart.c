#include "uart.h"


/*
 * @brief   USART_Init , configures the PI peripheral
 *
 * @param   USART_Handle =  User config struct
 *
 * @retval void
 */


void USART_Init( USART_HandleTypeDef_t *USART_Handle )
{
	uint32_t periphClock = 0 ;
	uint32_t mantissaPart = 0 ;
	uint32_t fractionPart = 0 ;
	uint32_t USART_DIV_VALUE = 0 ;
	uint32_t tempValue = 0 ;

	/************************************/



	tempValue = USART_Handle->Instance->CR1 ;

	tempValue |= USART_Handle->Init.OverSampling | USART_Handle->Init.WordLength | USART_Handle->Init.Parity |
			USART_Handle->Init.Mode ;

	USART_Handle->Instance->CR1 = tempValue ;


	/************************************/

	tempValue = USART_Handle->Instance->CR2 ;

	tempValue &= ~(0x3U << (USART_CR2_STOP )) ;

	tempValue |= USART_Handle->Init.StopBits ;

	USART_Handle->Instance->CR2 = tempValue ;

	/************************************/

	tempValue = USART_Handle->Instance->CR3 ;

	tempValue |= USART_Handle->Init.HardWareFlowControl ;

	USART_Handle->Instance->CR3 = tempValue ;

	// baudrate configuration

	if( USART_Handle->Instance == USART1 ||  USART_Handle->Instance == USART6 )
	{

		periphClock = RCC_GetPClock2();
	}
	else
	{

		periphClock = RCC_GetPClock1();
	}


	if(USART_Handle->Init.OverSampling == USART_OVERSAMPLE_16 )
	{

		USART_DIV_VALUE = __USART_DIV_VALUE_16( periphClock, USART_Handle->Init.BaudRate ) ;
		mantissaPart = ( USART_DIV_VALUE / 100U );
		fractionPart = (USART_DIV_VALUE) - (mantissaPart * 100U);
		fractionPart = (( (fractionPart * 16 ) + 50U ) / 100U ) & ((0xFU)) ;
	}
	else
	{

		USART_DIV_VALUE = __USART_DIV_VALUE_8( periphClock, USART_Handle->Init.BaudRate ) ;
		mantissaPart = ( USART_DIV_VALUE / 100U );
		fractionPart = (USART_DIV_VALUE) - (mantissaPart * 100U);
		fractionPart = (( (fractionPart * 8 ) + 50U ) / 100U ) & (0x7U) ;

	}

	tempValue |= mantissaPart << 4U ;
	tempValue |= fractionPart << 0U ;


	USART_Handle->Instance->BRR = tempValue ;
}


/*
 * @brief   USART_TransmitData , Transmit data to slave device
 *
 * @param   USART_Handle =  User config struct
 * @param   pData = address of data to send
 * @param   sizeOfData = length of your data in bytes
 *
 * @retval  void
 */

void USART_TransmitData( USART_HandleTypeDef_t *USART_Handle , uint8_t *pData , uint16_t sizeofData)
{

	uint16_t *data16Bits ;

	if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity == USART_PARITY_NONE ))
		data16Bits= (uint16_t*)pData;

	else
		data16Bits = NULL ;

	while (sizeofData > 0 )
	{
		//while( !(SPI_Handle->Instance->SR & USART_TxE_FLAG )) ;
		while( !(USART_GetFlagStatus( USART_Handle , USART_TxE_FLAG ))) ;

		if(data16Bits == NULL)
		{
			USART_Handle->Instance->DR = (uint8_t)(*data16Bits & (0x00FFU)) ;
			data16Bits--;
			sizeofData++ ;
		}
		else
		{
			USART_Handle->Instance->DR = (uint16_t)(*data16Bits & (0x01FFU)) ;
			data16Bits++ ;
			sizeofData-= 2 ;


		}


	}

	while( !(USART_GetFlagStatus(USART_Handle, USART_TC_FLAG ))) ;
}




/*
 * @brief   USART_ReceiveData , receive data to slave device
 *
 * @param   USART_Handle =  User config struct
 * @param   pBuffer = address of data to store the values that ı get
 * @param   sizeOfData = length of your data in bytes
 *
 * @retval  void
 */



void USART_ReceiveData( USART_HandleTypeDef_t *USART_Handle , uint8_t *pBuffer , uint16_t sizeofData)
{

	uint16_t *p16BitsBuffer ;
	uint8_t *p8BitsBuffer ;

	if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity == USART_PARITY_NONE ) )
	{

		p16BitsBuffer = (uint16_t*)pBuffer ;
		p8BitsBuffer = NULL ;

	}
	else
	{
		p8BitsBuffer = (uint8_t*)pBuffer ;
		p16BitsBuffer = NULL ;
	}

	while( sizeofData > 0 )
	{
		while( !(USART_GetFlagStatus(USART_Handle, USART_RxNE_FLAG)) ) ;

		if( p8BitsBuffer == NULL )
		{
			*p16BitsBuffer =  *((uint16_t*)(USART_Handle->Instance->DR & 0x01FFU)) ;  // 9 biti bir olan sayıyla & lenmesinin nedeni, yapmazsak 16 biti komple geçirir
			 p16BitsBuffer ++  ;
			 sizeofData -= 2  ;

		}
		else
		{
			if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity != USART_PARITY_NONE ))
			{
				*p8BitsBuffer = *((uint8_t*)(USART_Handle->Instance->DR & 0x00FFU));
				 p8BitsBuffer ++ ;
				 sizeofData -- ;
			}
			else if((USART_Handle->Init.WordLength == USART_WORDLENGTH_8BITS) && (USART_Handle->Init.Parity == USART_PARITY_NONE ))
			{
			    *p8BitsBuffer = *((uint8_t*)(USART_Handle->Instance->DR & 0x00FFU));
			     p8BitsBuffer ++ ;
			     sizeofData -- ;
			}
			else
			{
			    *p8BitsBuffer = *((uint8_t*)(USART_Handle->Instance->DR & 0x007FU));
				p8BitsBuffer ++ ;
				sizeofData -- ;
			}
		}


	}

}


/*
 * @brief   USART_GetFlagStatus , return the flag of SR register
 *
 * @param   USART_Handle =  User config struct
 * @param   USART_Flag = flag name of SR register
 * @retval  USART_FlagStatus_t
 */


USART_FlagStatus_t USART_GetFlagStatus( USART_HandleTypeDef_t *USART_Handle , uint16_t USART_Flag )
{
	return( (USART_Handle->Instance->SR) & USART_Flag) ? USART_FLAG_SET : USART_FLAG_RESET  ;

}


/*
 * @brief   USART_PeriphCmd , ENABLE OR DISABLE USART
 *
 * @param   USART_Handle =  User config struct
 * @param   stateOfUSART =  it defines state of USART (enable or dısable)
 *
 * @retval void
 */

void USART_PeriphCmd( USART_HandleTypeDef_t *USART_Handle , FunctionalState_t stateOfUSART)
{
	if(stateOfUSART == ENABLE )
	{
		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_UE) ;
	}
	else
	{
		USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_UE) ;
	}
}










