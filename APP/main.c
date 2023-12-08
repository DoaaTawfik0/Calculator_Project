/*
 * main.c
 *
 *  Created on: Sep 27, 2023
 *      Author: Doaa Tawfik
 */

#include  "../LIB/STD_TYPES.h"
#include  "../LIB/BIT_MATH.h"
#include  "../LIB/ERROR_STATE.h"

#include  "../MCAL/DIO/DIO_Interface.h"
#include  "../HAL/KeyPad/KeyPad_Interface.h"
#include  "../HAL/Character_LCD/CLCD_Interface.h"



#include "Calculator/Calculator.h"
#include  "Stack/Stack.h"



int main()
{

	CLCD_enuInitialize();
	KPD_enuInitialize();

	Start_calculating();

	return  0;
}

