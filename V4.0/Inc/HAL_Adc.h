/*
 * HAL_Adc.h
 *
 *  Created on: Jul 18, 2023
 *      Author: Seif pc
 */

#ifndef HAL_ADC_H_
#define HAL_ADC_H_

/*---------Includes Section Start----------*/
#include <stdint.h>
#include "Std_types.h"
#include "HAL_Gpio.h"
/*---------Includes Section End------------*/

/*---------Macro Declarations Start----------*/
#define HAL_ADC_INT_EN EN

#define HAL_ADC_ALLIGNMENT_LEFT  	0
#define HAL_ADC_ALLIGNMENT_RIGHT 	1

#define HAL_WATCHDOG_ENABLE 		0
#define HAL_WATCHDOG_DISABLE 		1

#define HAL_ADC_SCHN_SN_CONV			0/*Single Mode in which conv must be re enabled*/
#define HAL_ADC_SCHN_AUTO_CONV			1/*Automatically Conversion is re-enabled*/
#define HAL_ADC_MCHN_SN_CONV			2
#define HAL_ADC_MCHN_AUTO_CONV			3
#define HAL_ADC_TINJECTED_CONV			4/*ADC is triggered by external Events*/
#define HAL_ADC_AINJECTED_CONV			5/*Automatic Triggering after Regular */

#define HAL_ADC_SCAN_MODE			1
#define HAL_ADC_NSCAN_MODE			0

#define	HAL_ADC_CONT_FLAG 			0U
#define HAL_ADC_SING_FLAG			1U

#define	HAL_ADC_CHANNEL_0 			(1<<0)
#define HAL_ADC_CHANNEL_1			(1<<1)
#define HAL_ADC_CHANNEL_2			(1<<2)
#define HAL_ADC_CHANNEL_3			(1<<3)
#define HAL_ADC_CHANNEL_4			(1<<4)
#define HAL_ADC_CHANNEL_5			(1<<5)
#define HAL_ADC_CHANNEL_6			(1<<6)
#define	HAL_ADC_CHANNEL_7 			(1<<7)
#define HAL_ADC_CHANNEL_8			(1<<8)
#define HAL_ADC_CHANNEL_9			(1<<9)
#define HAL_ADC_CHANNEL_10			(1<<10)
#define HAL_ADC_CHANNEL_11			(1<<11)
#define HAL_ADC_CHANNEL_12			(1<<12)
#define HAL_ADC_CHANNEL_13			(1<<13)
#define HAL_ADC_CHANNEL_14			(1<<14)
#define HAL_ADC_CHANNEL_15			(1<<15)
/*ADC Control Register C1*/
#define AWDEN_POS			 23U
#define AWDEN_EN_MSK		 (1<<AWDEN_POS)
#define AWDEN_DIS_MSK		 (~(1<<AWDEN_POS))
#define JAWDEN_POS			 22U
#define JAWDEN_EN_MSK		 (1<<JAWDEN_POS)
#define JAWDEN_DIS_MSK		 (~(1<<JAWDEN_POS))
#define DUAL_MODE_POS		 16U
#define CMB_REG_INJ_SIM	     (0x00000001U<<DUAL_MODE_POS)
#define CMB_REG_ALT_MODE	 (0x00000002U<<DUAL_MODE_POS)
#define CMB_INJ_FINT_MODE    (0x00000003U<<DUAL_MODE_POS)
#define CMB_INJ_SINT_MODE	 (0x00000004U<<DUAL_MODE_POS)
#define DUALMOD_INJ_SIM		 (0x00000005U<<DUAL_MODE_POS)
#define DUALMOD_REG_SIM		 (0x00000006U<<DUAL_MODE_POS)
#define DUALMOD_FAST_INT	 (0x00000007U<<DUAL_MODE_POS)
#define DUALMOD_SLOW_INT	 (0x00000008U<<DUAL_MODE_POS)
#define DUALMOD_ALT_INT	     (0x00000009U<<DUAL_MODE_POS)
#define DISCNUM_POS			 13U
#define DISCMODE_1_CHN		 (0x00000000U<<DISCNUM_POS)
#define DISCMODE_2_CHN		 (0x00000001U<<DISCNUM_POS)
#define DISCMODE_3_CHN		 (0x00000002U<<DISCNUM_POS)
#define DISCMODE_4_CHN		 (0x00000003U<<DISCNUM_POS)
#define DISCMODE_5_CHN		 (0x00000004U<<DISCNUM_POS)
#define DISCMODE_6_CHN		 (0x00000005U<<DISCNUM_POS)
#define DISCMODE_7_CHN 		 (0x00000006U<<DISCNUM_POS)
#define DISCMODE_8_CHN		 (0x00000007U<<DISCNUM_POS)
#define JDISCEN_POS			 12U
#define JDISCEN_EN_MSK		 (1<<JDISCEN_POS)
#define JDISCEN_DIS_MSK		 (~(1<<JDISCEN_POS))
#define AWDCH_POS			 0U
#define AWDCH_CHN_0		     (0x00000000U<<AWDCH_POS)
#define AWDCH_CHN_1		 	 (0x00000001U<<AWDCH_POS)
#define AWDCH_CHN_2		 	 (0x00000002U<<AWDCH_POS)
#define AWDCH_CHN_3			 (0x00000003U<<AWDCH_POS)
#define AWDCH_CHN_4			 (0x00000004U<<AWDCH_POS)
#define AWDCH_CHN_5			 (0x00000005U<<AWDCH_POS)
#define AWDCH_CHN_6 		 (0x00000006U<<AWDCH_POS)
#define AWDCH_CHN_7			 (0x00000007U<<AWDCH_POS)
#define AWDCH_CHN_8			 (0x00000008U<<AWDCH_POS)
#define AWDCH_CHN_9		 	 (0x00000009U<<AWDCH_POS)
#define AWDCH_CHN_10		 (0x0000000AU<<AWDCH_POS)
#define AWDCH_CHN_11		 (0x0000000BU<<AWDCH_POS)
#define AWDCH_CHN_12		 (0x0000000CU<<AWDCH_POS)
#define AWDCH_CHN_13		 (0x0000000DU<<AWDCH_POS)
#define AWDCH_CHN_14 		 (0x0000000EU<<AWDCH_POS)
#define AWDCH_CHN_15		 (0x0000000FU<<AWDCH_POS)
#define AWDCH_CHN_16		 (0x00000010U<<AWDCH_POS)
#define AWDCH_CHN_17		 (0x00000011U<<AWDCH_POS)

/*ADC Control Register C2*/
#define TSVREFE_POS     23U
#define TSVREFE_EN	    (1<<TSVREFE_POS)
#define TSVREFE_DIS	    (~(1<<TSVREFE_POS))
#define SWSTART_POS     22U
#define SWSTART_START   (1<<SWSTART_POS)
#define JSWSTART_POS    21U
#define JSWSTART_START  (1<<JSWSTART_POS)
#define EXTTRIG_POS		20U
#define EXTTRIG_EN_MSK	(1<<EXTTRIG_POS)
#define EXTTRIG_DIS_MSK (~(1<<EXTTRIG_POS))
#define ALLIGN_POS		11U
#define ALLIGN_LEFT_MSK (1<<ALLIGN_POS)
#define ALLIGN_RIGH_MSK (~(1<<ALLIGN_POS))
#define DMA_POS			8U
#define DMA_EN_MSK		(1<<DMA_POS)
#define DMA_DIS_MSK		(~(1<<DMA_POS))
#define RSTCAL_POS		3U
#define RSTCAL_INIT		(1<<RSTCAL_POS)
#define CAL_POS			2U
#define CAL_EN			(1<<CAL_POS)
#define CONT_CONV_POS	1U
#define SINGLE_CONV		(~(1<<CONT_CONV_POS))
#define CONTINOUS_CONV  (1<<CONT_CONV_POS)
#define ADON_POS		0U
#define ADON_ON			(1<<ADON_POS)
#define ADON_OFF		(~(1<<ADON_POS))

/*ADC SAMPLE TIME REGISTER _CNT */
#define TS_1_5		0x00000000UL
#define TS_7_5		0x00000001UL
#define TS_13_5 	0x00000002UL
#define TS_28_5		0x00000003UL
#define TS_41_5		0x00000004UL
#define TS_55_5		0x00000005UL
#define TS_71_5		0x00000006UL
#define TS_239_5	0x00000007UL

#define HAL_ADC_EOC			 1U
#define RCC_APB2ENR_ADC1_Pos 9U
#define RCC_APB2ENR_ADC2_Pos 10U
/*---------Function Macro Declarations End------------*/
#define HAL_RCC_ADC1_EN() (SET_BIT(RCC->APB2ENR,RCC_APB2ENR_ADC1_Pos))
#define HAL_RCC_ADC2_EN() (SET_BIT(RCC->APB2ENR,RCC_APB2ENR_ADC2_Pos))
/*---------Function Macro Declarations Start---------*/


/*---------Data Types Section Declaration Start------*/

/*Channel Struct*/
typedef struct
{
	ADC_TypeDef *Instance;
	uint32_t Channel_NO;
	uint32_t Alignment;
	uint32_t Watchdog_EN;
	uint32_t Watchog_High;
	uint32_t Watchdog_LOW;
	uint32_t Sample_Time;
}ADC_CH_t;

typedef struct{
	uint32_t ADC_Mode;
	uint32_t NO_channels;
	uint32_t Sample_Time[18];
	uint32_t CHANNEL_POS[18];
#if HAL_ADC_INT_EN == EN
	void (*ADC_Callback)(void);
#endif
	ADC_CH_t Init;
}ADC_init_t;

/*---------Data Types Section Declaration End--------*/

/*---------Software Interfaces Declaration Start-------*/
void HAL_ADC_Init(ADC_init_t *ADC);
#if HAL_ADC_INT_EN ==EN
uint16_t HAL_ADC_READ_INT(ADC_TypeDef *Instance,uint8_t Flag,uint32_t ALLIGN);
#endif
#if HAL_ADC_INT_EN ==DIS
uint8_t HAL_ADC_READ(ADC_init_t *ADC,uint16_t *ADC_VAL);
#endif
/*---------Software Interfaces Declaration End-------*/


#endif /* HAL_ADC_H_ */
