#include "SPI.h"


static void SPI_CloseISR_RX(SPI_HandleTypedef_t *SPI_Handle)
{
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_RXNEIE) ;
	SPI_Handle->pRxDataAddr = NULL ;
	SPI_Handle->RxDatasize = 0 ;
	SPI_Handle->busStateRx = SPI_BUS_FREE ;
}

static void SPI_ReceiveHelper_16BITS(SPI_HandleTypedef_t *SPI_Handle)
{

	*((uint16_t*)(SPI_Handle->pRxDataAddr)) = SPI_Handle->Instance->DR ;
	SPI_Handle->pRxDataAddr += sizeof(uint16_t);
	SPI_Handle->RxDatasize -= 2 ;

	if(SPI_Handle->RxDatasize == 0 )
	{
		 SPI_CloseISR_RX(SPI_Handle) ;
	}

}

static void SPI_ReceiveHelper_8BITS(SPI_HandleTypedef_t *SPI_Handle)
{

	*((uint8_t*)(SPI_Handle->pRxDataAddr)) = *((__IO uint8_t*)&SPI_Handle->Instance->DR);
	SPI_Handle->pRxDataAddr += sizeof(uint8_t) ;
	SPI_Handle->RxDatasize -= 1 ;

}



static void SPI_CloseISR_TX( SPI_HandleTypedef_t *SPI_Handle )
{
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_TXEIE) ;
	SPI_Handle->TxDataSize = 0 ;
	SPI_Handle->pTxDataAddr = NULL ;
	SPI_Handle->busStateTx = SPI_BUS_FREE ;
}

static void SPI_TransmitHelper_16BITS (SPI_HandleTypedef_t *SPI_Handle)
{
   SPI_Handle->Instance->DR =  *((uint16_t*)(SPI_Handle->pTxDataAddr)) ;
   SPI_Handle->pTxDataAddr+= sizeof(uint16_t) ;
   SPI_Handle->TxDataSize -= 2 ;

   if(  SPI_Handle->TxDataSize == 0)
   {
  	 SPI_CloseISR_TX( SPI_Handle) ;
   }

}

static void SPI_TransmitHelper_8BITS (SPI_HandleTypedef_t *SPI_Handle)
{
	 SPI_Handle->Instance->DR =  *((uint8_t*)(SPI_Handle->pTxDataAddr)) ;
     SPI_Handle->pTxDataAddr+= sizeof(uint8_t) ;
     SPI_Handle->TxDataSize -- ;

     if(  SPI_Handle->TxDataSize == 0)
     {
    	 SPI_CloseISR_TX( SPI_Handle) ;
     }

}

/*
 * @brief   SPI_Init , configures the PI peripheral
 *
 * @param   SPI_Handle =  User config struct
 *
 * @retval void
 */


void SPI_Init( SPI_HandleTypedef_t *SPI_Handle)
{
	uint32_t tempValue = 0 ;
	tempValue = SPI_Handle->Instance->CR1 ;
	tempValue |= (SPI_Handle->Init.BaudRate) | (SPI_Handle->Init.CPHA) | (SPI_Handle->Init.CPOL) | (SPI_Handle->Init.DFF_Format) | \
			  (SPI_Handle->Init.Mode) | (SPI_Handle->Init.FrameFormat) | (SPI_Handle->Init.BaudRate) | (SPI_Handle->Init.SSM_Cmd)  ;
	SPI_Handle->Instance->CR1 = tempValue;
}


/*
 * @brief   SPI_PeriphCmd , ENABLE OR DISABLE SPI
 *
 * @param   SPI_Handle =  User config struct
 * @param   StateOfSPI =  it defines state of spı (enable or dısable)
 *
 * @retval void
 */


void SPI_PeriphCmd(SPI_HandleTypedef_t* SPI_Handle , FunctionalState_t StateOfSPI )
{
	if(StateOfSPI == ENABLE)
	{
		SPI_Handle->Instance->CR1 |= ( (0x1U) << (SPI_CR1_SPE) );

	}
	else
	{
		SPI_Handle->Instance->CR1 &= ~( (0x1U) << (SPI_CR1_SPE) );

	}
}


/*
 * @brief   SPI_TransmitData , Transmit data to slave device
 *
 * @param   SPI_Handle =  User config struct
 * @param   pData = address of data to send
 * @param   sizeOfData = length of your data in bytes
 *
 * @retval  void
 */


void SPI_TransmitData(SPI_HandleTypedef_t* SPI_Handle , uint8_t *pData , uint16_t sizeOfData)
{

	if(SPI_Handle->Init.DFF_Format == SPI_DFF_16BITS )
	{
		while(sizeOfData > 0 )
		{
			if(SPI_Get_FlagStatus(SPI_Handle, SPI_TxE_FLAG))
			{

				SPI_Handle->Instance->DR =  *((uint16_t*)pData);
				pData += sizeof(uint16_t) ;
				sizeOfData -= 2 ;
			}

		}

	}
	else
	{
		while(sizeOfData > 0 )
		{
			if(SPI_Get_FlagStatus(SPI_Handle, SPI_TxE_FLAG))
			{

				SPI_Handle->Instance->DR = *pData;
				pData += sizeof(uint8_t) ;
				sizeOfData-- ;

			}


		}

	}

	while (SPI_Get_FlagStatus(SPI_Handle, SPI_BUSY_FLAG)) ;  // Wait for BUSY FLAG  (SPI_Handle->Instance->SR >> 7U) & (0x1U)
}



/*
 * @brief   SPI_ReceiveData , receive data to slave device
 *
 * @param   SPI_Handle =  User config struct
 * @param   pData = address of data to store the values that ı get
 * @param   sizeOfData = length of your data in bytes
 *
 * @retval  void
 */


void SPI_ReceiveData(SPI_HandleTypedef_t* SPI_Handle, uint8_t *pBuffer , uint16_t sizeOfData)
{

	if(SPI_Handle->Init.DFF_Format == SPI_DFF_16BITS )
	{
		while(sizeOfData > 0)
		{
			if(SPI_Get_FlagStatus(SPI_Handle, SPI_RxNE_FLAG))
			{
				*((uint16_t*)pBuffer ) = SPI_Handle->Instance->DR;
				pBuffer += sizeof(uint16_t) ;
			    sizeOfData -= 2 ;
			}

		}
	}
	else
	{
		while(sizeOfData > 0)
		{
			if(SPI_Get_FlagStatus(SPI_Handle, SPI_RxNE_FLAG))
			{
				*(pBuffer) = *((__IO uint8_t*)&SPI_Handle->Instance->DR);
				pBuffer += sizeof(uint8_t) ;
			    sizeOfData -= 1 ;
			}
		}


	}

}


/*
 * @brief   SPI_Get_FlagStatus , return the flag of SR register
 *
 * @param   SPI_Handle =  User config struct
 * @param   SPI_Flag = flag name of SR register
 * @retval  SPI_FlagStatus_t
 */

SPI_FlagStatus_t SPI_Get_FlagStatus(SPI_HandleTypedef_t* SPI_Handle , uint16_t SPI_Flag)
{


	return((SPI_Handle->Instance->SR) & (SPI_Flag) ) ? SPI_FLAG_SET : SPI_FLAG_RESET ;

}



void SPI_TransmitData_IT(SPI_HandleTypedef_t* SPI_Handle , uint8_t *pData , uint16_t sizeOfData)
{

	SPI_busStatus_t busState = SPI_Handle-> busStateTx ;

	if(busState != SPI_BUS_BUSY_TX)
	{
		   SPI_Handle->pTxDataAddr = (uint8_t*)pData ;
		   SPI_Handle->TxDataSize = (uint16_t)sizeOfData  ;
		   SPI_Handle->busStateTx = SPI_BUS_BUSY_TX ;

		   if(SPI_Handle->Instance->CR1 & (0x1U << SPI_CR1_DFF))
		   {

             SPI_Handle->TxISRFunction = SPI_TransmitHelper_16BITS ;



		   }
		   else
		   {

			   SPI_Handle->TxISRFunction = SPI_TransmitHelper_8BITS ;
		   }


		   SPI_Handle->Instance->CR2 |= (0x1U) << SPI_CR2_TXEIE ;
	}


}


void SPI_InterruptHandler(SPI_HandleTypedef_t* SPI_Handle)
{

	uint8_t interruptSource = 0 ;
	uint8_t interruptFlag = 0 ;

	interruptSource = ( SPI_Handle->Instance->CR2 ) & ( 0x1U << SPI_CR2_TXEIE)  ;
	interruptFlag  = ( SPI_Handle->Instance->SR ) & ( 0x1U << SPI_SR_TxE ) ;

	if( (interruptSource != 0 ) && ( interruptFlag != 0 ))
	{

		SPI_Handle->TxISRFunction(SPI_Handle);

	}

	interruptSource = ( SPI_Handle->Instance->CR2 ) & ( 0x1U << SPI_CR2_RXNEIE)  ;
	interruptFlag  = ( SPI_Handle->Instance->SR ) & ( 0x1U << SPI_SR_RxNE ) ;

	if( (interruptSource != 0 ) && ( interruptFlag != 0 ))
		{

			SPI_Handle->TxISRFunction(SPI_Handle);

		}



}



void SPI_ReceiveData_IT(SPI_HandleTypedef_t* SPI_Handle, uint8_t *pBuffer , uint16_t sizeOfData)
{
	SPI_busStatus_t busState = SPI_Handle->busStateRx ;

	if(busState != SPI_BUS_BUSY_RX)
	{

	SPI_Handle->pRxDataAddr = (uint8_t*)(pBuffer) ;
	SPI_Handle->RxDatasize = (uint16_t)(sizeOfData) ;
	SPI_Handle->busStateRx = SPI_BUS_BUSY_RX ;

	if(SPI_Handle->Instance->CR1 & (0x1 << SPI_CR1_DFF))
	{

		SPI_Handle->RxISRFunction = SPI_ReceiveHelper_16BITS ;
	}
	else
	{

		SPI_Handle->RxISRFunction = SPI_ReceiveHelper_8BITS ;
	}


	SPI_Handle->Instance->CR1 |= (0x1 << SPI_CR2_RXNEIE) ;

	}

}



















