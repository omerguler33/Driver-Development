

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f407xx.h"



/*
 *  @def_group SSM_Values
 *
 */


#define SPI_SSM_ENABLE              ( (uint32_t)(0x00000300) )
#define SPI_SSM_DISABLE             ( (uint32_t)(0x00000000) )


typedef enum
{
	SPI_FLAG_RESET = 0x0U ,
	SPI_FLAG_SET = !SPI_FLAG_RESET

}SPI_FlagStatus_t;


typedef enum
{
	SPI_BUS_FREE = 0x1U,
	SPI_BUS_BUSY_TX = 0x2U,
	SPI_BUS_BUSY_RX = 0x3U

}SPI_busStatus_t ;


/*
 * @def_group SPI_Baudrate
 *
 */

#define SPI_BAUDRATE_DIV2                 ( (uint32_t)(0x00000000) )
#define SPI_BAUDRATE_DIV4                 ( (uint32_t)(0x00000008) )
#define SPI_BAUDRATE_DIV8                 ( (uint32_t)(0x00000010) )
#define SPI_BAUDRATE_DIV16                ( (uint32_t)(0x00000018) )
#define SPI_BAUDRATE_DIV32                ( (uint32_t)(0x00000020) )
#define SPI_BAUDRATE_DIV64                ( (uint32_t)(0x00000028) )
#define SPI_BAUDRATE_DIV128               ( (uint32_t)(0x00000030) )
#define SPI_BAUDRATE_DIV2256              ( (uint32_t)(0x00000038) )



/*
 * @def_group CPHA_Values
 *
 */

#define SPI_CPHA_FIRST                   ( (uint32_t)(0x00000000) )
#define SPI_CPHA_SECOND                  ( (uint32_t)(0x00000001) )


/*
 * @def_group CPOL_Values
 *
 */

#define SPI_CPOL_LOW                   ( (uint32_t)(0x00000000) )
#define SPI_CPOL_HIGH                  ( (uint32_t)(0x00000002) )


/*
 * @def_group DFF_Values
 *
 */

#define SPI_DFF_8BITS                  ( (uint32_t)(0x00000000) )
#define SPI_DFF_16BITS                 ( (uint32_t)(0x00000800) )


/*
 * @def_group MODE_Values
 *
 */

#define SPI_MODE_SLAVE                 ( (uint32_t)(0x00000000) )
#define SPI_MODE_MASTER                ( (uint32_t)(0x00000004) )                        // 0000 0000 0000 0000 0000 0000 0000 0100


/*
 * @def_group FF_Values
 *
 */

#define SPI_FRAMEFORMAT_MSB           ( (uint32_t)(0x00000000) )
#define SPI_FRAMEFORMAT_LSB           ( (uint32_t)(0x00000080) )



/*
 *
 *  @def_group BUS_Values
 */

#define SPI_BUS_FullDuplex            ( (uint32_t)(0x00000000) )
#define SPI_BUS_ReceiveOnly           ( (uint32_t)(0x00000400) )
#define SPI_BUS_HalfDuplex_Trans      ( (uint32_t)(0x0000C000) )
#define SPI_BUS_HalfDuplex_receive    ( (uint32_t)(0x00008000) )






typedef struct{

	uint32_t Mode ;                      /* !< MODE values for SPI                      @def_group MODE_Values                  */
	uint32_t CPHA ;                      /* !< CPHA values for SPI                      @def_group CPHA_Values                  */
	uint32_t CPOL ;                      /* !< CPOL values for SPI                      @def_group CPOL_Values                  */
	uint32_t BaudRate ;                  /* !< BAUDRATE Selection                       @def_group SPI_Baudrate                 */
	uint32_t SSM_Cmd ;                   /* !< SSM values for SPI                       @def_group SSM_Values                   */
	uint32_t DFF_Format ;                /* !< DFF values for SPI                       @def_group DFF_Values                   */
	uint32_t BusConfig ;                 /* !< BUS_Config values for SPI                @def_group BUS_Values                   */
    uint32_t FrameFormat ;               /* !< Frame Format values for SPI              @def_group FF_Values                    */

}SPI_InitTypedef_t;



typedef struct __SPI_HandleTypedef_t
{
    SPI_TypeDef_t *Instance ;
	SPI_InitTypedef_t Init ;
    uint8_t *pTxDataAddr ;
    uint16_t TxDataSize;
    uint8_t busStateTx ;
    void(*TxISRFunction)(struct __SPI_HandleTypedef_t *SPI_Handle);
    uint8_t *pRxDataAddr ;
    uint16_t RxDatasize ;
    uint8_t busStateRx ;
    void(*RxISRFunction)(struct __SPI_HandleTypedef_t *SPI_Handle) ;

}SPI_HandleTypedef_t;


void SPI_Init( SPI_HandleTypedef_t *SPI_Handle) ;

void SPI_PeriphCmd(SPI_HandleTypedef_t* SPI_Handle , FunctionalState_t StateOfSPI );

void SPI_TransmitData(SPI_HandleTypedef_t* SPI_Handle , uint8_t *pData , uint16_t sizeOfData);
void SPI_ReceiveData(SPI_HandleTypedef_t* SPI_Handle, uint8_t *pBuffer , uint16_t sizeOfData);
SPI_FlagStatus_t SPI_Get_FlagStatus(SPI_HandleTypedef_t* SPI_Handle , uint16_t SPI_Flag) ;
void SPI_TransmitData_IT(SPI_HandleTypedef_t* SPI_Handle , uint8_t *pData , uint16_t sizeOfData);
void SPI_ReceiveData_IT(SPI_HandleTypedef_t* SPI_Handle, uint8_t *pBuffer , uint16_t sizeOfData);

void SPI_InterruptHandler(SPI_HandleTypedef_t* SPI_Handle) ;








#endif /* INC_SPI_H_ */
