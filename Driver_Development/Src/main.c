

#include <stdint.h>
#include "stm32f407xx.h"


static void ledConfig();
static void GPIO_ButtonInterruptConfig();
static void SPI_Config();
static void SPI_GPIO_Config();

SPI_HandleTypedef_t SPI_Handle  ;

char message2[12] ;
char message[] = " hello are you there " ;

void EXTI0_IRQHandler()
{
	if( EXTI->PR & 0x1U)
	{
		EXTI->PR |= ( 0x1U << 0U ) ;
		SPI_TransmitData_IT( &SPI_Handle , (uint8_t*)message , strlen(message));

	}

}

void SPI1_IRQHandler()
{

	SPI_InterruptHandler(&SPI_Handle) ;
}

int main(void)
{
    ledConfig();

    GPIO_ButtonInterruptConfig();

    SPI_GPIO_Config() ;

    SPI_Config() ;

    SPI_ReceiveData_IT(SPI_Handle, (uint8_t*)message2 , strlen(message2)) ;


	for(;;)
	{





	}
}


static void ledConfig()
{
  GPIO_InitTypeDef_t GPIO_InitStruct = { 0 };
  RCC_GPIOD_CLK_ENABLE();
  RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.PinNumber = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 ;
  GPIO_InitStruct.Mode = GPIO_MODER_OUTPUT ;
  GPIO_InitStruct.PUPD = GPIO_PUPD_NOPULL ;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW ;

  GPIO_Init(GPIOD, &GPIO_InitStruct) ;

  memset(&GPIO_InitStruct, 0 , sizeof(GPIO_InitStruct));

  GPIO_InitStruct.PinNumber = GPIO_PIN_1 ;
  GPIO_InitStruct.Mode = GPIO_MODER_INPUT ;
  GPIO_InitStruct.PUPD = GPIO_PUPD_PULLDOWN;

  GPIO_Init(GPIOA, &GPIO_InitStruct);


}


static void GPIO_ButtonInterruptConfig()
{
	EXTI_InitTypeDef_t EXTI_Struct = { 0 };
	EXTI_LineConfig(EXTI_PortSource_GPIOA, EXTI_LineSource_0) ;
	RCC_SYSCFG_CLK_ENABLE();

	EXTI_Struct.EXTI_LineCmd = ENABLE ;
	EXTI_Struct.EXTI_Mode =  EXTI_MODE_Interrupt ;
	EXTI_Struct.EXTI_LineNumber = EXTI_LineSource_0 ;
	EXTI_Struct.TriggerSelection = EXTI_TRIGGER_Rising ;
	EXTI_Init(&EXTI_Struct);
	NVIC_EnableInterrupt(EXTI0_IRQnummber);

}


static void SPI_Config()
{

	RCC_SPI1_CLK_ENABLE() ;

	SPI_Handle.Instance = SPI1 ;

	SPI_Handle.Init.BaudRate = SPI_BAUDRATE_DIV8;
	SPI_Handle.Init.BusConfig =  SPI_BUS_FullDuplex ;
	SPI_Handle.Init.CPHA = SPI_CPHA_FIRST ;
	SPI_Handle.Init.CPOL = SPI_CPOL_LOW ;
	SPI_Handle.Init.DFF_Format = SPI_DFF_8BITS ;
	SPI_Handle.Init.FrameFormat = SPI_FRAMEFORMAT_MSB ;
	SPI_Handle.Init.Mode = SPI_MODE_MASTER ;
	SPI_Handle.Init.SSM_Cmd = SPI_SSM_ENABLE ;

	SPI_Init(&SPI_Handle);
	NVIC_EnableInterrupt( SPI1_IRQnumber ) ;
    SPI_PeriphCmd(&SPI_Handle, ENABLE) ;

}

static void SPI_GPIO_Config()
{
	GPIO_InitTypeDef_t  GPIO_InitStruct = { 0 };

	GPIO_InitStruct.Mode = GPIO_MODER_AF ;
	GPIO_InitStruct.OTYPE = GPIO_OTYPER_PP ;
	GPIO_InitStruct.PUPD = GPIO_PUPD_NOPULL ;
	GPIO_InitStruct.Speed = GPIO_SPEED_VERY_HIGH ;
	GPIO_InitStruct.PinNumber = GPIO_PIN_5 | GPIO_PIN_7  ;
	GPIO_InitStruct.Alternate = GPIO_AF5 ;

	GPIO_Init(GPIOA, &GPIO_InitStruct) ;

}


