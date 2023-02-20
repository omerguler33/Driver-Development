/*
 * GPIO.h
 *
 *  Created on: 4 Mar 2022
 *      Author: LENOVOO
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stm32f407xx.h"
#include <stdint.h>

/*
 * @def_group GPIO_MODER_modes
 */

#define GPIO_MODER_INPUT             (0x0U)
#define GPIO_MODER_OUTPUT            (0X1U)
#define GPIO_MODER_AF                (0x2U)
#define GPIO_MODER_ANALOG            (0x3U)



/*
 * @def_group GPIO_OTYPER_modes
 */

#define GPIO_OTYPER_PP               (0x0U)
#define GPIO_OTYPER_OD               (0x1U)





/*
 * @def_group GPIO_PUPD_modes
 */

#define GPIO_PUPD_NOPULL             (0x0U)
#define GPIO_PUPD_PULLUP             (0x1U)
#define GPIO_PUPD_PULLDOWN           (0x2U)
#define GPIO_PUPD_RESERVED           (0x3U)

/*
 * @def_group GPIO_Speed_Modes
 */

#define GPIO_SPEED_LOW               (0x0U)
#define GPIO_SPEED_MEDIUM            (0x1U)
#define GPIO_SPEED_HIGH              (0x2U)
#define GPIO_SPEED_VERY_HIGH         (0x3U)

/*
 * @d_group GPIO_ALTERNATE_modes
 *
 */

#define GPIO_AF0                     (0x0U)
#define GPIO_AF1                     (0x1U)
#define GPIO_AF2                     (0x2U)
#define GPIO_AF3                     (0x3U)
#define GPIO_AF4                     (0x4U)
#define GPIO_AF5                     (0x5U)
#define GPIO_AF6                     (0x6U)
#define GPIO_AF7                     (0x7U)
#define GPIO_AF8                     (0x8U)
#define GPIO_AF9                     (0x9U)
#define GPIO_AF10                    (0xAU)
#define GPIO_AF11                    (0xBU)
#define GPIO_AF12                    (0xCU)
#define GPIO_AF13                    (0xDU)
#define GPIO_AF14                    (0xEU)
#define GPIO_AF15                    (0xFU)



/*
 * @def_group GPIO_pins
 *
 */

#define GPIO_PIN_0          (uint16_t)(0x0001)                   // GPIO PIN 0 SELECTED
#define GPIO_PIN_1          (uint16_t)(0x0002)                   // GPIO PIN 1 SELECTED
#define GPIO_PIN_2          (uint16_t)(0x0004)                   // GPIO PIN 2 SELECTED
#define GPIO_PIN_3          (uint16_t)(0x0008)                   // GPIO PIN 3 SELECTED
#define GPIO_PIN_4          (uint16_t)(0x0010)                   // GPIO PIN 4 SELECTED
#define GPIO_PIN_5          (uint16_t)(0x0020)                   // GPIO PIN 5 SELECTED
#define GPIO_PIN_6          (uint16_t)(0x0040)                   // GPIO PIN 6 SELECTED
#define GPIO_PIN_7          (uint16_t)(0x0080)                   // GPIO PIN 7 SELECTED
#define GPIO_PIN_8          (uint16_t)(0x0100)                   // GPIO PIN 8 SELECTED
#define GPIO_PIN_9          (uint16_t)(0x0200)                   // GPIO PIN 9 SELECTED
#define GPIO_PIN_10         (uint16_t)(0x0400)                   // GPIO PIN 10 SELECTED
#define GPIO_PIN_11         (uint16_t)(0x0800)                   // GPIO PIN 11 SELECTED
#define GPIO_PIN_12         (uint16_t)(0x1000)                   // GPIO PIN 12 SELECTED
#define GPIO_PIN_13         (uint16_t)(0x2000)                   // GPIO PIN 13 SELECTED
#define GPIO_PIN_14         (uint16_t)(0x4000)                   // GPIO PIN 14 SELECTED
#define GPIO_PIN_15         (uint16_t)(0x8000)                   // GPIO PIN 15 SELECTED
#define GPIO_PIN_ALL        (uint16_t)(0xFFFF)                   // GPIO ALL PIN SELECTED



typedef enum
{
	GPIO_PIN_Reset = 0x0U,
	GPIO_PIN_Set = (!GPIO_PIN_Reset)


}GPIO_PinState_t;


typedef struct{

	uint32_t PinNumber ;              /* !<  GPIO pin numbers @def_group GPIO_pins         */
	uint32_t Mode ;                   /* !<  GPIO MODER reg @def_group GPIO_MODER_Modes    */
	uint32_t OTYPE ;                  /* !<  GPIO OTYPER  @def_group GPIO_OTYPER_modes     */
	uint32_t PUPD ;                   /* !<  GPIO PUPD  @def_group GPIO_PUPD_modes         */
	uint32_t Speed ;                  /* !<  GPIO PUPD  @def_group GPIO_Speed_modes        */
	uint32_t Alternate ;              /* !<  GPIO PUPDef  @d_group GPIO_ALTERNATE_modes    */

}GPIO_InitTypeDef_t;




void GPIO_Init(GPIO_TypeDef_t *GPIOx , GPIO_InitTypeDef_t *GPIO_conFigStruct);

void GPIO_Write_Pin( GPIO_TypeDef_t *GPIOx, uint16_t PinNumber , GPIO_PinState_t PinState) ;

GPIO_PinState_t GPIO_Read_Pin(GPIO_TypeDef_t *GPIOx , uint16_t PinNumber);

void GPIO_LockPin( GPIO_TypeDef_t *GPIOx , uint16_t PinNumber );
void GPIO_TogglePin( GPIO_TypeDef_t *GPIOx, uint16_t PinNumber ) ;




#endif /* INC_GPIO_H_ */
