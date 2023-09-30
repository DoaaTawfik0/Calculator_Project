/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  MCAL          ***************/
/**************   SWC:    PORT          ***************/
/**************   Version: 2.00         ***************/
/******************************************************/
/******************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/ERROR_STATE.h"

#include "Port_Config.h"
#include "Port_Interface.h"
#include "Port_Private.h"
#include "Port_Register.h"



/*****************************************************************************/
/*****************************************************************************/
/** Function Name   : PORT_enuInitialize.                                   **/
/** Return Type     : Error_State enum.                                     **/
/** Arguments       : VOID.                                                 **/
/** Functionality   : Setting Port Direction & initial value                **/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

ES_t  PORT_enuInitialize(void)
{
	ES_t  Local_enuErrorState = ES_NOK;

	/*SET Direction of each Port*/

	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;


	/*SET Initial Value of each Port*/

	PORTA = PORTA_INITIAL_VALUE;
	PORTB = PORTB_INITIAL_VALUE;
	PORTC = PORTC_INITIAL_VALUE;
	PORTD = PORTD_INITIAL_VALUE;

	return  Local_enuErrorState;
}
