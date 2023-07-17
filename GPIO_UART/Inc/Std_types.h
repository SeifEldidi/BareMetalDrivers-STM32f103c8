/*
 * Std_types.h
 *
 *  Created on: Jul 16, 2023
 *      Author: Seif pc
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*---------Includes Section Start----------*/
#include <stdint.h>
#include "stm32f103xb.h"
/*---------Includes Section End------------*/

/*---------Macro Declarations Start----------*/
#define BIT_MASK 0x01U
#define NULL (void *)0
#define CLEAR_MASK_GPIO 0x00000000FUL
/*---------Macro Declarations End------------*/

/*---------Function Macro Declarations Start---------*/
#define SET_BIT(REG,BIT_POS) 	(REG|=(BIT_MASK<<BIT_POS))
#define CLEAR_BIT(REG,BIT_POS)	(REG&=(~(BIT_MASK<<BIT_POS)))
#define TOGGLE_BIT(REG,BIT_POS) (REG^=(BIT_MASK<<BIT_POS))

#define READ_BIT(REG,BIT_POS)   ((REG>>BIT_POS)&BIT_MASK)
/*---------Function Macro Declarations End-----------*/

/*---------Data Types Section Declaration Start------*/

/*---------Data Types Section Declaration End--------*/

/*---------Software Interfaces Declaration Start-------*/



/*---------Software Interfaces Declaration End-------*/


#endif /* STD_TYPES_H_ */
