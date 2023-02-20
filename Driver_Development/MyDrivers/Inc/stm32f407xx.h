

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_



#define  __IO     volatile
#include <stdint.h>                                                                            /* used for uint32_t                        */
#include <string.h>
#include <stddef.h>

#define SET_BIT(REG,BIT)                   ( (REG) |= (BIT)  )
#define CLEAR_BIT(REG,BIT)                 ( (REG) &= ~(BIT) )
#define READ_BIT(REG,BIT)                  ( (REG) & (BIT)   )


#define UNUSED(x)       (void)x

typedef enum
{
	DISABLE = 0x0U,
	ENABLE = !DISABLE

}FunctionalState_t;


/*
 *   Microprosesor Defines
 *
 */

#define NVIC_ISER0                       (( uint32_t*) 0xE000E100 )

/*
 *   IRQ NUMBERS = VECTOR LIST   @def_group IRQ_Numbers
 *
 */

typedef enum{
	EXTI0_IRQnummber = 6 ,
	EXTI1_IRQnummber = 7 ,
	EXTI2_IRQnummber = 8 ,
	EXTI3_IRQnummber = 9 ,
    SPI1_IRQnumber = 35
}IRQnumber_TypeDef_t;


/*
 *   Memory Base Address
 *
 */

#define RAM_BASE_ADDR                                (0x08000000UL)                            /*  RAM Basse Address                          */
#define SRAM1_BASE_ADDR                              (0x20000000UL)                            /*  SRAM1 Base Address 112KB                   */
#define SRAM2_BASE_ADDR                              (0x200C1000UL)                            /*  SRAM2 Base Address 112KB                   */


/*
 * Peripheral Base Addresses
 *
 */

#define PERIBH_BASE_ADDR                            (0x40000000UL)                             /*  All Peripherals base Addresses             */
#define APB1_BASE_ADDR                              (PERIBH_BASE_ADDR)                         /*  APB1 Bus Domain Base Address               */
#define APB2_BASE_ADDR                              (PERIBH_BASE_ADDR + 0x00010000UL)          /*  APB2 Bus Domain Base Address               */
#define AHB1_BASE_ADDR                              (PERIBH_BASE_ADDR + 0x00020000UL)          /*  AHB1 Bus Domain Base Address               */
#define AHB2_BASE_ADDR                              (PERIBH_BASE_ADDR + 0x10000000UL)          /*  AHB2 Bus Domain Base Address               */


/*
 *   APB1 Peripharel Base Addresses
*/

#define TIM2_BASE_ADDR                             (APB1_BASE_ADDR + 0x0000UL)                  /*  TIM 2 Base Address     */
#define TIM3_BASE_ADDR                             (APB1_BASE_ADDR + 0x0400UL)                  /*  TIM 3 Base Address     */
#define TIM4_BASE_ADDR                             (APB1_BASE_ADDR + 0x0800UL)                  /*  TIM 4 Base Address     */
#define TIM5_BASE_ADDR                             (APB1_BASE_ADDR + 0x0C00UL)                  /*  TIM 5 Base Address     */
#define TIM6_BASE_ADDR                             (APB1_BASE_ADDR + 0x1000UL)                  /*  TIM 6 Base Address     */
#define TIM7_BASE_ADDR                             (APB1_BASE_ADDR + 0x1400UL)                  /*  TIM 7 Base Address     */

#define SPI2_BASE_ADDR                             (APB1_BASE_ADDR + 0x3800UL)                  /*  SPI 2 Base Address     */
#define SPI3_BASE_ADDR                             (APB1_BASE_ADDR + 0x3C00UL)                  /*  SPI 3 Base Address     */

#define USART2_BASE_ADDR                           (APB1_BASE_ADDR + 0x4400UL)                  /*  USART 2 Base Address   */
#define USART3_BASE_ADDR                           (APB1_BASE_ADDR + 0x4800UL)                  /*  USART 3 Base Address   */

#define UART4_BASE_ADDR                            (APB1_BASE_ADDR + 0x4C00UL)                  /*  UART 4 Base Address    */
#define UART5_BASE_ADDR                            (APB1_BASE_ADDR + 0x5000UL)                  /*  UART 5 Base Address    */

#define I2C1_BASE_ADDR                             (APB1_BASE_ADDR + 0x5400UL)                  /*  I2C 1 Base Address     */
#define I2C2_BASE_ADDR                             (APB1_BASE_ADDR + 0x5800UL)                  /*  I2C 2 Base Address     */
#define I2C3_BASE_ADDR                             (APB1_BASE_ADDR + 0x5C00UL)                  /*  I2C 3 Base Address     */


/*
 *   APB2 Peripharel Base Addresses
*/

#define TIM1_BASE_ADDR                            (APB2_BASE_ADDR + 0x0000UL)                   /*  TIM 1 Base Address   */
#define TIM8_BASE_ADDR                            (APB2_BASE_ADDR + 0x0400UL)                   /*  TIM 8 Base Address   */

#define USART1_BASE_ADDR                          (APB2_BASE_ADDR + 0x1000UL)                   /*  USART 1 Base Address */
#define USART6_BASE_ADDR                          (APB2_BASE_ADDR + 0x1400UL)                   /*  USART 6 Base Address */

#define ADC1_BASE_ADDR                            (APB2_BASE_ADDR + 0x2000UL)                   /*  ADC 1 Base Address   */
#define ADC2_BASE_ADDR                            (APB2_BASE_ADDR + 0x2100UL)                   /*  ADC 2 Base Address   */
#define ADC3_BASE_ADDR                            (APB2_BASE_ADDR + 0x2200UL)                   /*  ADC 3 Base Address   */

#define SDIO_BASE_ADDR                            (APB2_BASE_ADDR + 0x2C00UL)                   /*  SDIO Base Address    */

#define SPI1_BASE_ADDR                            (APB2_BASE_ADDR + 0x3000UL)                   /*  SPI 1 Base Address   */
#define SPI4_BASE_ADDR                            (APB2_BASE_ADDR + 0x3400UL)                   /*  SPI 4 Base Address   */

#define EXTI_BASE_ADDR                            (APB2_BASE_ADDR + 0x3C00UL)                   /*  EXTI Base Address    */
#define SYSCFG_BASE_ADDR                          (APB2_BASE_ADDR + 0x3800UL)                   /*  SYSCFG Base Address  */


/*
 *   AHB1 Peripharel Base Addresses
 */

#define GPIOA_BASE_ADDR                           (AHB1_BASE_ADDR + 0x0000UL)                   /*  GPIO A Base Address   */
#define GPIOB_BASE_ADDR                           (AHB1_BASE_ADDR + 0x0400UL)                   /*  GPIO B Base Address   */
#define GPIOC_BASE_ADDR                           (AHB1_BASE_ADDR + 0x0800UL)                   /*  GPIO C Base Address   */
#define GPIOD_BASE_ADDR                           (AHB1_BASE_ADDR + 0x0C00UL)                   /*  GPIO D Base Address   */
#define GPIOE_BASE_ADDR                           (AHB1_BASE_ADDR + 0x1000UL)                   /*  GPIO E Base Address   */
#define GPIOF_BASE_ADDR                           (AHB1_BASE_ADDR + 0x1400UL)                   /*  GPIO F Base Address   */
#define GPIOG_BASE_ADDR                           (AHB1_BASE_ADDR + 0x1800UL)                   /*  GPIO G Base Address   */
#define GPIOH_BASE_ADDR                           (AHB1_BASE_ADDR + 0x1C00UL)                   /*  GPIO H Base Address   */
#define GPIOI_BASE_ADDR                           (AHB1_BASE_ADDR + 0x2000UL)                   /*  GPIO I Base Address   */
#define GPIOJ_BASE_ADDR                           (AHB1_BASE_ADDR + 0x2400UL)                   /*  GPIO J Base Address   */
#define GPIOK_BASE_ADDR                           (AHB1_BASE_ADDR + 0x2800UL)                   /*  GPIO K Base Address   */

#define RCC_BASE_ADDR                             (AHB1_BASE_ADDR + 0x3800UL)                   /*  RCC Base Address      */

#define DMA1_BASE_ADDR                            (AHB1_BASE_ADDR + 0x6000UL)                   /*  DMA 1 Base Address    */
#define DMA2_BASE_ADDR                            (AHB1_BASE_ADDR + 0x6400UL)                   /*  DMA 2 Base Address    */




/*
 *  PERIPHERAL STRUCTURE DEFINITIONS
 *
 */

typedef struct {

__IO uint32_t MODER ;                     /* !< GGPIO port mode register                                    address offset = 0x0000             */
__IO uint32_t OTYPER ;                    /* !< GPIO port output type register                              Address offset = 0x0004             */
__IO uint32_t OSPEEDR ;                   /* !< GPIO port output SPEED register                             address offset = 0x0008             */
__IO uint32_t PUPDR ;                     /* !< GPIO port PULL-UP / PULL-DOWN register                      address offset = 0x000C             */
__IO uint32_t IDR ;                       /* !< GPIO port INPUT data register                               address offset = 0x0010             */
__IO uint32_t ODR ;                       /* !< GPIO port OUTPUT data register                              address offset = 0x0014             */
__IO uint32_t BSRR ;                      /* !< GPIO port bit set / reset register                          address offset = 0x0018             */
__IO uint32_t LCKR ;
__IO uint32_t AFR[2] ;                    /* !< GPIO alternate functionLOW/HİGH register                    Address offset = 0x0020             */


}GPIO_TypeDef_t;

typedef struct{

 __IO uint32_t CR ;                       /* !< clock control register                                        address offset = 0x0000            */
 __IO uint32_t PLLCFGR ;                  /* !< PLL configuration register                                    address offset = 0x0004            */
 __IO uint32_t CFGR ;                     /* !< clock configuration register                                  address offset = 0x0008            */
 __IO uint32_t CIR ;                      /* !< clock interrupt register                                      address offset = 0x000C            */
 __IO uint32_t AHB1RSTR ;                 /* !< AHB1 peripheral reset register                                address offset = 0x0010            */
 __IO uint32_t AHB2RSTR ;                 /* !< AHB2 peripheral reset register                                address offset = 0x0014            */
 __IO uint32_t AHB3RSTR ;                 /* !< AHB3 peripheral reset register                                address offset = 0x0018            */
 __IO uint32_t RESERVED0 ;                /* !< RESERVED                                                      address offset = 0x001C            */
 __IO uint32_t APB1RSTR ;                 /* !< APB1 peripheral reset register                                address offset = 0x0020            */
 __IO uint32_t APB2RSTR ;                 /* !< APB2 peripheral reset register                                address offset = 0x0024            */
 __IO uint32_t RESERVED1 ;                /* !< RESERVED                                                      address offset = 0x0028            */
 __IO uint32_t RESERVED2 ;                /* !< RESERVED                                                      address offset = 0x002C            */
 __IO uint32_t AHB1ENR  ;                 /* !< AHB1 peripheral clock enable register                         address offset = 0x0030            */
 __IO uint32_t AHB2ENR  ;                 /* !< AHB2 peripheral clock enable register                         address offset = 0x0034            */
 __IO uint32_t AHB3ENR  ;                 /* !< AHB3 peripheral clock enable register                         address offset = 0x0038            */
 __IO uint32_t RESERVED3 ;                /* !< RESERVED                                                      address offset = 0x003C            */
 __IO uint32_t APB1ENR  ;                 /* !< APB1 peripheral clock enable register                         address offset = 0x0040            */
 __IO uint32_t APB2ENR  ;                 /* !< APB2 peripheral clock enable register                         address offset = 0x0044            */
 __IO uint32_t RESERVED4 ;                /* !< RESERVED                                                      address offset = 0x0048            */
 __IO uint32_t RESERVED5 ;                /* !< RESERVED                                                      address offset = 0x004C            */
 __IO uint32_t AHB1LPENR ;                /* !< AHB1 peripheral clock enable in low power mode register       address offset = 0x0050            */
 __IO uint32_t AHB2LPENR ;                /* !< AHB1 peripheral clock enable in low power mode register       address offset = 0x0054            */
 __IO uint32_t AHB3LPENR ;                /* !< AHB1 peripheral clock enable in low power mode register       address offset = 0x0058            */
 __IO uint32_t RESERVED6 ;                /* !< RESERVED                                                      address offset = 0x005C            */
 __IO uint32_t APB1LPENR ;                /* !< APB1 peripheral clock enable in low power mode register       address offset = 0x0060            */
 __IO uint32_t APB2LPENR ;                /* !< APB2 peripheral clock enable in low power mode register       address offset = 0x0064            */
 __IO uint32_t RESERVED7[2] ;             /* !< RESERVED                                                      address offset = 0x006C            */
 __IO uint32_t BDCR ;                     /* !< Backup domain control register                                address offset = 0x0070            */
 __IO uint32_t CSR ;                      /* !< clock control & status register                               address offset = 0x0074            */
 __IO uint32_t RESERVED8 ;                /* !< RESERVED                                                      address offset = 0x0078            */
 __IO uint32_t RESERVED9 ;                /* !< RESERVED                                                      address offset = 0x007C            */
 __IO uint32_t SSCGR ;                    /* !< spread spectrum clock generation register                     address offset = 0x0080            */
 __IO uint32_t PLLI2SCFGR ;               /* !< PLLI2S configuration register                                 address offset = 0x0084            */

}RCC_TypeDef_t;



typedef struct{

	__IO uint32_t MEMRMP ;               /* !<  SYSCFG memory remap register                                  address offset = 0x00             */
	__IO uint32_t PMC ;                  /* !<  SYSCFG peripheral mode configuration register                 address offset = 0x04             */
	__IO uint32_t EXTI_CR[4];            /* !<  SYSCFG external interrupt configuration register              address offset = 0x08             */
	__IO uint32_t CMPCR ;                /* !<  SYSCFG Compensation cell control register                     address offset = 0x20             */

}SYSCFG_TypeDef_t;


typedef struct{
	__IO uint32_t IMR ;                  /* !<  Interrupt mask register                                       address offset = 0x00             */
	__IO uint32_t EMR ;                  /* !<  Event mask register                                           address offset = 0x04             */
	__IO uint32_t RTSR ;                 /* !<  Rising trigger selection register                             address offset = 0x08             */
	__IO uint32_t FTSR ;                 /* !<  Falling trigger selection register                            address offset = 0x0C             */
	__IO uint32_t SWIER ;                /* !<  Software interrupt event register                             address offset = 0x10             */
	__IO uint32_t PR ;                   /* !<  Pending register                                              address offset = 0x14             */

}EXTI_TypeDef_t;




typedef struct{
	__IO uint32_t CR1 ;                  /* !< SPI control register  1                                        address offset = 0x00             */
	__IO uint32_t CR2 ;                  /* !< SPI control register  2                                        address offset = 0x04             */
	__IO uint32_t SR ;                   /* !< SPI status register                                            address offset = 0x08             */
	__IO uint32_t DR ;                   /* !< SPI data register                                              address offset = 0x0C             */
	__IO uint32_t CRCPR ;                /* !< CRC polynomial register                                        address offset = 0x10             */
	__IO uint32_t RXCRCR ;               /* !< RX CRC register                                                address offset = 0x14             */
	__IO uint32_t TXCRCR ;               /* !< TX CRC register                                                address offset = 0x18             */
	__IO uint32_t I2SCFGR ;              /* !< SPI_I2S configuration register                                 address offset = 0x1C             */
	__IO uint32_t I2SPR ;                /* !< SPI_I2S prescaler register                                     address offset = 0x20             */

}SPI_TypeDef_t;


typedef struct
{
	__IO uint32_t SR ;
	__IO uint32_t DR ;
	__IO uint32_t BRR ;
	__IO uint32_t CR1;
	__IO uint32_t CR2 ;
	__IO uint32_t CR3 ;
	__IO uint32_t GTPR ;

}USART_TypeDef_t;

#define GPIOA                                ( (GPIO_TypeDef_t*)(GPIOA_BASE_ADDR)   )
#define GPIOB                                ( (GPIO_TypeDef_t*)(GPIOB_BASE_ADDR)   )
#define GPIOC                                ( (GPIO_TypeDef_t*)(GPIOC_BASE_ADDR)   )
#define GPIOD                                ( (GPIO_TypeDef_t*)(GPIOD_BASE_ADDR)   )
#define GPIOE                                ( (GPIO_TypeDef_t*)(GPIOE_BASE_ADDR)   )
#define GPIOF                                ( (GPIO_TypeDef_t*)(GPIOF_BASE_ADDR)   )
#define GPIOG                                ( (GPIO_TypeDef_t*)(GPIOG_BASE_ADDR)   )
#define GPIOH                                ( (GPIO_TypeDef_t*)(GPIOH_BASE_ADDR)   )
#define GPIOI                                ( (GPIO_TypeDef_t*)(GPIOI_BASE_ADDR)   )
#define GPIOJ                                ( (GPIO_TypeDef_t*)(GPIOJ_BASE_ADDR)   )
#define GPIOK                                ( (GPIO_TypeDef_t*)(GPIOK_BASE_ADDR)   )

#define RCC                                  ( (RCC_TypeDef_t*)(RCC_BASE_ADDR)      )

#define SYSCFG                               ( (SYSCFG_TypeDef_t*)(SYSCFG_BASE_ADDR))
#define EXTI                                 ( (EXTI_TypeDef_t*)(EXTI_BASE_ADDR)    )

#define SPI1                                 ( (SPI_TypeDef_t*)(SPI1_BASE_ADDR)     )
#define SPI2                                 ( (SPI_TypeDef_t*)(SPI2_BASE_ADDR)     )
#define SPI3                                 ( (SPI_TypeDef_t*)(SPI3_BASE_ADDR)     )
#define SPI4                                 ( (SPI_TypeDef_t*)(SPI4_BASE_ADDR)     )
#define SPI5                                 ( (SPI_TypeDef_t*)(SPI5_BASE_ADDR)     )

#define USART1                                ( (USART_TypeDef_t*)(USART1_BASE_ADDR)  )
#define USART2                                ( (USART_TypeDef_t*)(USART2_BASE_ADDR)  )
#define USART3                                ( (USART_TypeDef_t*)(USART3_BASE_ADDR)  )
#define USART6                                ( (USART_TypeDef_t*)(USART6_BASE_ADDR)  )

/*
 *  AHB1ENR
 *
 */

#define RCC_AHB1ENR_GPIOAEN_pos                ( 0U                                )           // RCC AHB1ENR Register GPIOAEN Bit Position
#define RCC_AHB1ENR_GPIOAEN_mask               ( (0x1) << RCC_AHB1ENR_GPIOAEN_pos  )           // RCC AHB1ENR Register GPIOAEN Bit Mask
#define RCC_AHB1ENR_GPIOAEN                    ( RCC_AHB1ENR_GPIOAEN_mask          )           // RCC AHB1ENR Register GPIOAEN Bit Macro

#define RCC_AHB1ENR_GPIOBEN_pos                ( 1U                                )           // RCC AHB1ENR Register GPIOBEN Bit Position
#define RCC_AHB1ENR_GPIOBEN_mask               ( (0x1) << RCC_AHB1ENR_GPIOBEN_pos  )           // RCC AHB1ENR Register GPIOBEN Bit Mask
#define RCC_AHB1ENR_GPIOBEN                    ( RCC_AHB1ENR_GPIOBEN_mask          )           // RCC AHB1ENR Register GPIOBEN Bit Macro

#define RCC_AHB1ENR_GPIOCEN_pos                ( 2U                                )           // RCC AHB1ENR Register GPIOCEN Bit Position
#define RCC_AHB1ENR_GPIOCEN_mask               ( (0x1) << RCC_AHB1ENR_GPIOCEN_pos  )           // RCC AHB1ENR Register GPIOCEN Bit Mask
#define RCC_AHB1ENR_GPIOCEN                    ( RCC_AHB1ENR_GPIOCEN_mask          )           // RCC AHB1ENR Register GPIOCEN Bit Macro

#define RCC_AHB1ENR_GPIODEN_pos                ( 3U                                )           // RCC AHB1ENR Register GPIODEN Bit Position
#define RCC_AHB1ENR_GPIODEN_mask               ( (0x1) << RCC_AHB1ENR_GPIODEN_pos  )           // RCC AHB1ENR Register GPIODEN Bit Mask
#define RCC_AHB1ENR_GPIODEN                    ( RCC_AHB1ENR_GPIODEN_mask          )           // RCC AHB1ENR Register GPIODEN Bit Macro

#define RCC_AHB1ENR_GPIOEEN_pos                ( 4U                                )           // RCC AHB1ENR Register GPIOEEN Bit Position
#define RCC_AHB1ENR_GPIOEEN_mask               ( (0x1) << RCC_AHB1ENR_GPIOEEN_pos  )           // RCC AHB1ENR Register GPIOEEN Bit Mask
#define RCC_AHB1ENR_GPIOEEN                    ( RCC_AHB1ENR_GPIOEEN_mask          )           // RCC AHB1ENR Register GPIOEEN Bit Macro



/*
 *  APB2ENR
 *
 */

#define RCC_APB2ENR_SYSCFG_pos                 ( 14U                               )           // RCC APB2ENR Register SYSCFG Bit Position
#define RCC_APB2ENR_SYSCFG_mask                ( (0x1) << RCC_APB2ENR_SYSCFG_pos   )           // RCC APB2ENR Register SYSCFG Bit Mask
#define RCC_APB2ENR_SYSCFGEN                   ( RCC_APB2ENR_SYSCFG_mask           )           // RCC APB2ENR Register SYSCFG Bit Macro

#define RCC_APB2ENR_SPI1_pos                   ( 12U                               )           // RCC APB2ENR Register SPI1 Bit Position
#define RCC_APB2ENR_SPI1_mask                  ( (0x1) << RCC_APB2ENR_SPI1_pos     )           // RCC APB2ENR Register SPI1 Bit Mask
#define RCC_APB2ENR_SPI1EN                     ( RCC_APB2ENR_SPI1_mask             )           // RCC APB2ENR Register SPI1 Bit Macro

#define RCC_APB2ENR_USART1_pos                ( 4U                                 )           // RCC APB2ENR Register UART1 Bit Position
#define RCC_APB2ENR_USART1_mask               ( (0x1) << RCC_APB2ENR_USART1_pos    )           // RCC APB2ENR Register UART1 Bit Mask
#define RCC_APB2ENR_USART1EN                  ( RCC_APB2ENR_USART1_mask            )
/*
 *  APB1ENR
 *
 */



#define RCC_APB1ENR_SPI2_pos                   ( 14U                               )           // RCC APB1ENR Register SPI2 Bit Position
#define RCC_APB1ENR_SPI2_mask                  ( (0x1) << RCC_APB1ENR_SPI2_pos     )           // RCC APB1ENR Register SPI2 Bit Mask
#define RCC_APB1ENR_SPI2EN                     ( RCC_APB1ENR_SPI2_mask             )           // RCC APB1ENR Register SPI2 Bit Macro

#define RCC_APB1ENR_SPI3_pos                   ( 15U                               )           // RCC APB1ENR Register SPI3 Bit Position
#define RCC_APB1ENR_SPI3_mask                  ( (0x1) << RCC_APB1ENR_SPI3_pos     )           // RCC APB1ENR Register SPI3 Bit Mask
#define RCC_APB1ENR_SPI3EN                     ( RCC_APB1ENR_SPI3_mask             )           // RCC APB1ENR Register SPI3 Bit Macro

#define RCC_APB1ENR_USART2_pos                  (17U                               )           // RCC APB2ENR Register UART2 Bit Position
#define RCC_APB1ENR_USART2_mask                 (0x1 << RCC_APB1ENR_USART2_pos     )           // RCC APB2ENR Register UART2 Bit Mask
#define RCC_APB1ENR_USART2EN                    (RCC_APB1ENR_USART2_mask           )           // RCC APB2ENR Register UART2 Bit Macro

#define SPI_CR2_TXEIE                          ( 7U                                )
#define SPI_CR1_SPE                            ( 6U                                )
#define SPI_SR_BUSY                            ( 7U                                )
#define SPI_SR_TxE                             ( 1U                                )
#define SPI_SR_RxNE                            ( 0U                                )
#define SPI_CR1_DFF                            ( 11U                               )
#define SPI_CR2_RXNEIE                         ( 6U                                )

#define USART_CR2_STOP                         ( 12U                               )
#define USART_SR_TXE                           ( 7U                                )
#define USART_SR_TC                            ( 6U                                )
#define USART_CR1_UE                           ( 13U                               )
#define USART_SR_RXE                           ( 5u                                )


/*
 *  FLAG Definition
 *
 */


#define SPI_TxE_FLAG                           ( (0x1U) << SPI_SR_TxE             )
#define SPI_BUSY_FLAG                          ( (0x1U) << SPI_SR_BUSY            )
#define SPI_RxNE_FLAG                          ( (0x1U) << SPI_SR_TxE             )

#define USART_TxE_FLAG                         ( (0x1U) << USART_SR_TXE           )
#define USART_TC_FLAG                          ( (0x1U) << USART_SR_TC            )
#define USART_RxNE_FLAG                        ( (0x1U) << USART_SR_RXE           )


#include "GPIO.h"
#include "RCC.h"
#include "EXTI.h"
#include "SPI.h"
#include <UART.h>

#endif /* INC_STM32F407XX_H_ */

