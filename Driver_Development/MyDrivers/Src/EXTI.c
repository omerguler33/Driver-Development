#include "EXTI.h"


/*
 * @brief   EXTI_Init , EXTI init for valid GPIO port and line number
 * @param   EXTI_InitStruct = User config structure
 * @retval void
 */


void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStruct )
{

	uint32_t tempValue = 0 ;
	tempValue = (uint32_t)EXTI_BASE_ADDR ;

	EXTI->IMR &=  ~((0x1U)<< EXTI_InitStruct->EXTI_LineNumber);
	EXTI->EMR &=  ~((0x1U)<< EXTI_InitStruct->EXTI_LineNumber);

	if(EXTI_InitStruct->EXTI_LineCmd != DISABLE)
	{

		tempValue += EXTI_InitStruct->EXTI_Mode ;

		*(( __IO  uint32_t*)tempValue) |= (0x1U)<< EXTI_InitStruct->EXTI_LineNumber;


		tempValue = (uint32_t)EXTI_BASE_ADDR ;
		EXTI->RTSR &= ~((0x1U)<< EXTI_InitStruct->EXTI_LineNumber);
		EXTI->FTSR &= ~((0x1U)<< EXTI_InitStruct->EXTI_LineNumber);

     if(EXTI_InitStruct->TriggerSelection == EXTI_TRIGGER_RF )
     {
    	EXTI->RTSR |= ((0x1U)<< EXTI_InitStruct->EXTI_LineNumber) ;
    	EXTI->FTSR |= ((0x1U)<< EXTI_InitStruct->EXTI_LineNumber) ;


     }
     else
     {
    	 tempValue += EXTI_InitStruct->TriggerSelection ;
    	 *(( __IO uint32_t*)tempValue) |= ((0x1U)<< EXTI_InitStruct->EXTI_LineNumber) ;

     }


	}
	else
	{
		tempValue = (uint32_t)EXTI_BASE_ADDR ;
		tempValue += EXTI_InitStruct->EXTI_Mode ;
		*(( __IO  uint32_t*)tempValue) &= ~(0x1U)<< EXTI_InitStruct->EXTI_LineNumber;
	}


}



/*
 * @brief   EXTI_lineConfig , configures pins and port for SYSCFG
 * @param   PortSource = Port value A-I                  @def_group PORT_Values
 * @param   EXTI_LineSource = Pin number & line number   @def_group EXTI_Line_values
 *
 * @retval void
 */



void EXTI_LineConfig( uint8_t PortSource , uint8_t EXTI_LineSource)
{
	uint32_t tempValue =0 ;
	tempValue = SYSCFG->EXTI_CR[EXTI_LineSource >> 2U];
	tempValue &= ~( 0xF << (EXTI_LineSource & 0x3U)*4 ) ;
	tempValue = ( PortSource << (EXTI_LineSource & 0x3U)*4 );
	SYSCFG->EXTI_CR[EXTI_LineSource >> 2U]= tempValue;
}




/*
 * @brief   NVIC_EnableInterrupt , configures NVIC
 * @param   IRQnumber = IRQ number of lines               @def_group IRQ_Numbers
 * @retval void
 */



void NVIC_EnableInterrupt( IRQnumber_TypeDef_t IRQnumber)
{
	uint32_t tempValue = 0 ;
	tempValue = *((IRQnumber >> 5U) + NVIC_ISER0) ;
	tempValue &= ~(0x1U << (IRQnumber & 0x1FU)) ;
	tempValue = (0x1U << (IRQnumber & 5U)) ;

	*((IRQnumber >> 5U) + NVIC_ISER0  ) = tempValue ;
}








