

#ifndef SRC_RCC_C_
#define SRC_RCC_C_


#include "RCC.h"

const uint8_t AHB_Prescaler[] = { 0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9 } ;

const uint8_t APB_Prescaler[] = { 0,0,0,0,1,2,3,4 } ;

uint32_t RCC_GetSystemClock(void)
{

	uint32_t SystemCoreClock = 0 ;
	uint8_t ClkSource = 0 ;

	ClkSource = (( RCC->CFGR >> 2U ) & ( 0x3U ));

	switch(ClkSource)
	{
	case 0 : SystemCoreClock = 16000000 ; break ;
	case 1 : SystemCoreClock =  8000000 ; break ;


	default : SystemCoreClock = 16000000  ;

	}

	return SystemCoreClock ;

}



uint32_t RCC_GetHClock(void)                       //  AHB1 Sinyal hattının frekansı bulunur.
{
	uint32_t AHB_PeriphClock = 0 ;
	uint32_t SystemCoreClock = 0 ;
	uint8_t HPRE_Value = 0 ;
	uint8_t tempValue = 0 ;

	SystemCoreClock = RCC_GetSystemClock() ;         // gelen osilator frekansı alındı
	HPRE_Value = (RCC->CFGR >> 4U) & ( 0xFU ) ;      // recister 4 bit sağa kaydırııldı ve 0x1111 ile andlendi  ve dönğş değeri olarak 0 den 15 e kadar değer alındı

	tempValue = AHB_Prescaler[ HPRE_Value] ;         // gelen değerler oluşturulan dizide index olarak alındı

	AHB_PeriphClock = SystemCoreClock >> tempValue  ; // gelen osilator frekansı indexten gelen bölüm değerine bölündü

	return AHB_PeriphClock ;
}


uint32_t RCC_GetPClock1(void)                        // APB1 clock hattının prescelar ları bulundu
{
	uint32_t APB1_PeriphClock = 0 ;
	uint32_t Hclock = 0 ;
	uint8_t  APB1PRE_Value = 0 ;
	uint8_t tempValue = 0 ;

	Hclock =  RCC_GetHClock() ;

	APB1PRE_Value = (RCC->CFGR >> 10U ) & (0x7U) ;

    tempValue = APB_Prescaler[APB1PRE_Value] ;

    APB1_PeriphClock = 	Hclock >> tempValue ;

    return APB1_PeriphClock ;

}


uint32_t RCC_GetPClock2(void)                          // APB2 clock hattının prescelar ları bulundu
{
	uint32_t APB2_PeriphClock = 0 ;
	uint32_t Hclock = 0 ;
	uint8_t  APB2PRE_Value = 0 ;
	uint8_t tempValue = 0 ;

	Hclock =  RCC_GetHClock() ;

	APB2PRE_Value = (RCC->CFGR >> 13U ) & (0x7U) ;

    tempValue = APB_Prescaler[APB2PRE_Value] ;

    APB2_PeriphClock = 	Hclock >> tempValue ;

    return APB2_PeriphClock ;

}


#endif /* SRC_RCC_C_ */


