/*************************************************************************************
* File Name: Macros.h																 *
* Description: Header file for Macros Definition									 *
* Author: Mohamed Alaa																 *
**************************************************************************************/


#ifndef MACROS_H_
#define MACROS_H_

#define SET_BIT( REG , PIN )	( REG |= (1<<PIN) )
#define CLR_BIT( REG , PIN )	( REG &= ~(1<<PIN) )
#define TOG_BIT( REG , PIN )	( REG ^= (1<<PIN) )
#define RED_BIT( REG , PIN )	( REG & (1<<PIN) )

#endif /* MACROS_H_ */
