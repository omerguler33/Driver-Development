

#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f407xx.h"


/*
 * @def_group USART_Modes
 *
 */

#define USART_MODE_TX                (uint32_t)(0x00000008)
#define USART_MODE_RX                (uint32_t)(0x00000004)
#define USART_MODE_TX_RX             (uint32_t)(0x0000000C)


/*
 * @def_group WORDLWNGTH_TYPES
 *
 */

#define USART_WORDLENGTH_8BITS       (uint32_t)(0x00000000)
#define USART_WORDLENGTH_9BITS       (uint32_t)(0x00001000)


/*
 * @def_group parity_selection
 *
 */

#define USART_PARITY_NONE           (uint32_t)(0x00000000)
#define USART_PARITY_EVEN           (uint32_t)(0x00000400)
#define USART_PARITY_ODD            (uint32_t)(0x00000600)


/*
 * @def_group Stop_Bits
 *
 */

#define USART_STOP_1BITS            (uint32_t)(0x00000000)
#define USART_STOP_HALF             (uint32_t)(0x00001000)
#define USART_STOP_2BITS            (uint32_t)(0x00002000)
#define USART_STOP_1_5BITS          (uint32_t)(0x00003000)

/*
 * @def_group OverSampling_Modes
 *
 */

#define USART_OVERSAMPLE_16         (uint32_t)(0x00000000)
#define USART_OVERSAMPLE_8          (uint32_t)(0x00008000)


/*
 * @def_group HardWareFlowControl_Modes
 *
 */

#define USART_HW_NONE                (uint32_t)(0x00000000)
#define USART_HW_RTS                 (uint32_t)(0x00000100)
#define USART_HW_CTS                 (uint32_t)(0x00000200)
#define USART_HW_CTS_RTS             (uint32_t)(0x00000300)


#define __USART_DIV_VALUE_16(__CLOCK__, __BAUDRATE__)                         (25U * (uint32_t)(__CLOCK__)) / (4U * (uint32_t)(__BAUDRATE__))
#define __USART_DIV_VALUE_8(__CLOCK__, __BAUDRATE__)                          (25U * (uint32_t)(__CLOCK__)) / (2U * (uint32_t)(__BAUDRATE__))

typedef enum
{
	USART_FLAG_RESET = 0x0U ,
	USART_FLAG_SET = !USART_FLAG_RESET

}USART_FlagStatus_t;


typedef struct
{
  uint32_t Mode ;                          /*   !< USART transmition and reception mode @def_group USART_Modes              */
  uint32_t BaudRate;                       /*   !< BAUDRATE value for user                                                  */
  uint32_t WordLength ;                    /*   !< WORDLENGTH selection  @def_group WORDLWNGTH_TYPES                        */
  uint32_t Parity ;                        /*   !< Parity selection  @def_group parity_selection                            */
  uint32_t OverSampling ;                  /*   !< oversampling modes  @def_group OverSampling_Modes                        */
  uint32_t StopBits ;                      /*   !< stop bit  selection  @def_group Stop_Bits                                */
  uint32_t HardWareFlowControl ;           /*   !< HardWareFlowControl  @def_group HardWareFlowControl_Modes                */


}USART_InitTypedef_t;


typedef struct
{

  USART_TypeDef_t *Instance ;
  USART_InitTypedef_t Init ;


}USART_HandleTypeDef_t;



void USART_Init( USART_HandleTypeDef_t *USART_Handle );

void USART_TransmitData( USART_HandleTypeDef_t *USART_Handle , uint8_t *pData , uint16_t sizeofData) ;
void USART_ReceiveData( USART_HandleTypeDef_t *USART_Handle , uint8_t *pBuffer , uint16_t sizeofData) ;

USART_FlagStatus_t USART_GetFlagStatus( USART_HandleTypeDef_t *USART_Handle , uint16_t USART_Flag );

void USART_PeriphCmd( USART_HandleTypeDef_t *USART_Handle , FunctionalState_t stateOfUSART);















#endif /* INC_UART_H_ */
