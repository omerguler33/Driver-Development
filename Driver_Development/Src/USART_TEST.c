#include "stm32f407xx.h"

static void USART_Config(void) ;
static void GPIO_Config(void) ;

USART_HandleTypeDef_t USART_Handle ;

char messageToSend[20] = "" ;

int main()
{


   GPIO_Config() ;
   USART_Config() ;

   USART_ReceiveData(&USART_Handle, (uint8_t*)(messageToSend), 12) ; // strlen kullanılmamasının nedeni tanımladığımız değişken
                                                                     //  ilk başta hiçbir veriiçermiyor ve boyutu 0 dır
   USART_TransmitData(&USART_Handle, (uint8_t*)(messageToSend), strlen(messageToSend)) ;



	while(1);
}



static void USART_Config(void)
{

	RCC_USART2_CLK_ENABLE() ;

	USART_Handle.Instance = USART2 ;
	USART_Handle.Init.BaudRate = 115200 ;
	USART_Handle.Init.HardWareFlowControl = USART_HW_NONE ;
	USART_Handle.Init.Mode = USART_MODE_TX_RX ;
	USART_Handle.Init.OverSampling = USART_OVERSAMPLE_16;
	USART_Handle.Init.Parity = USART_PARITY_NONE ;
	USART_Handle.Init.StopBits = USART_STOP_1BITS ;
	USART_Handle.Init.WordLength = USART_WORDLENGTH_8BITS ;

	USART_Init(&USART_Handle) ;
	USART_PeriphCmd(&USART_Handle, ENABLE);

}

static void GPIO_Config(void)
{

	GPIO_InitTypeDef_t GPIO_initStruct = { 0 };

	GPIO_initStruct.Mode = GPIO_MODER_AF ;
	GPIO_initStruct.OTYPE = GPIO_OTYPER_PP ;
	GPIO_initStruct.PUPD = GPIO_PUPD_NOPULL ;
	GPIO_initStruct.PinNumber = GPIO_PIN_2 | GPIO_PIN_3 ;
	GPIO_initStruct.Speed = GPIO_SPEED_VERY_HIGH ;
	GPIO_initStruct.Alternate = GPIO_AF7 ;

	GPIO_Init(GPIOA, &GPIO_initStruct) ;
}
