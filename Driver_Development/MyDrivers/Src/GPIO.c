

#ifndef SRC_GPIO_C_
#define SRC_GPIO_C_

#include "GPIO.h"

/*
 * @brief   GPIO_Init , configures ports and pins
 * @param   GPIOx = GPIO port base address
 * @param   GPIO_InitTypeDef_t = User config structurs
 *
 * @retval void
 */

void GPIO_Init(GPIO_TypeDef_t *GPIOx , GPIO_InitTypeDef_t *GPIO_conFigStruct)
{

	uint32_t position ;
	uint32_t fakePosition = 0;
	uint32_t lastPosition = 0 ;

	for(position = 0 ; position < 16 ; position++ )
	{

		/*    MODE CONFİG         */

		fakePosition = (0x1U << position );
		lastPosition = (uint32_t)(GPIO_conFigStruct->PinNumber) & fakePosition ;           // 0 x 0000 0000 00010 0000 pin5

		if(lastPosition == fakePosition)
		{
			uint32_t tempValue = GPIOx->MODER ;
			tempValue &= ~(0x3U << (position * 2)) ;
			tempValue |= ( (GPIO_conFigStruct-> Mode) << (position * 2) ) ;
			GPIOx->MODER = tempValue ;

			if(GPIO_conFigStruct->Mode == (GPIO_MODER_AF | GPIO_MODER_OUTPUT))
			{
				/*  OTYPER  CONGİG    */
				tempValue = GPIOx->OTYPER ;
				tempValue &= ~(0x1U << position );
				tempValue |= ( GPIO_conFigStruct->OTYPE) <<( position) ;
				GPIOx->OTYPER = tempValue ;

				/*  OSPEED CONFİG   */
				tempValue = GPIOx->OSPEEDR ;
				tempValue &= ~(0x1U << position * 2 );
				tempValue |= ( GPIO_conFigStruct->Speed) <<( position * 2) ;
				GPIOx->OSPEEDR = tempValue ;
			}

		    /*  PUSH PULL CONFİG   */
			tempValue = GPIOx->PUPDR ;
			tempValue &= ~(0x3U << (position * 2)) ;
			tempValue |= ( (GPIO_conFigStruct-> PUPD) << (position * 2) ) ;
			GPIOx->PUPDR = tempValue ;


			if(GPIO_conFigStruct->Mode == GPIO_MODER_AF)
				{
					tempValue = GPIOx->AFR[position >> 3U];
					tempValue &= ~((0xFU) << (position & 7U)*4 );
					tempValue |= ( (GPIO_conFigStruct->Alternate) << (position & 7U)*4 )  ;
					GPIOx->AFR[position >> 3U] = tempValue ;
				}


		}

	}



}



/*
 * @brief   GPIO_Write_Pin , makes pin hıgh or low
 * @param   GPIOx = GPIO port base address
 * @param   PinNumber = GPIO pin number
 * @param   PinState = GPIO_PIN_Set or GPIO_PIN_Reset
 *
 * @retval void
 */

void GPIO_Write_Pin( GPIO_TypeDef_t *GPIOx, uint16_t PinNumber , GPIO_PinState_t PinState)
{

	if(PinState == GPIO_PIN_Set) {

		GPIOx->BSRR = PinNumber ;
	}
	else{

		GPIOx->BSRR = (PinNumber << 16U) ;
	}
}



/*
 * @brief   GPIO_Read_Pin , read pins of GPIOx port
 * @param   GPIOx = GPIO port base address
 * @param   PinNumber = GPIO pin numbers 0-15
 *
 * @retval GPIO_PinState_t
 */

GPIO_PinState_t GPIO_Read_Pin(GPIO_TypeDef_t *GPIOx , uint16_t PinNumber)
{

	GPIO_PinState_t bitstatus = GPIO_PIN_Reset ;

	if((GPIOx->IDR & PinNumber ) != GPIO_PIN_Reset)
	{
		bitstatus = GPIO_PIN_Set ;
	}

	return bitstatus ;
}



/*
 * @brief   GPIO_TogglePin , toogle pins of GPIOx port
 * @param   GPIOx = GPIO port base address
 * @param   PinNumber = GPIO pin numbers 0-15
 *
 * @retval  void
 */

void GPIO_TogglePin( GPIO_TypeDef_t *GPIOx, uint16_t PinNumber )
{
	uint32_t tempODRvalue = GPIOx->ODR ;
	GPIOx->BSRR = (tempODRvalue & PinNumber) << 16U  |  (~tempODRvalue & PinNumber) ;

}






#endif /* SRC_GPIO_C_ */
