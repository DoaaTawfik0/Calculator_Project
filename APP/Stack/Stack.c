/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  App           ***************/
/**************   SWC:    Stack         ***************/
/******************************************************/
/******************************************************/

#include  "../../LIB/STD_TYPES.h"
#include  "../../LIB/ERROR_STATE.h"

#include  "../Stack/Stack.h"

#include  "../../MCAL/DIO/DIO_Interface.h"
#include  "../../HAL/Character_LCD/CLCD_Interface.h"
#include  "../../HAL/KeyPad/KeyPad_Interface.h"

#include  "util/delay.h"


/************************************************************************************/
/************************************************************************************/
/**                    Functions For Stack Of Operands                             **/
/************************************************************************************/
/************************************************************************************/


/*Function to Pop Top Operand in stack*/
void pop_OPerand(Operands_Stack_t* Copy_pstrOperandStack, stackEntry* Copy_ps32ReturnElement)
{
	*Copy_ps32ReturnElement = Copy_pstrOperandStack->entry[Copy_pstrOperandStack->Top--];
}


/*Function to Push Operand in the Top Of The stack*/
void push_Operand(Operands_Stack_t* Copy_pstrOperandStack , stackEntry Copy_s32Element)
{
	Copy_pstrOperandStack->entry[++Copy_pstrOperandStack->Top] = Copy_s32Element;
}


/*Function to check if the stack is empty*/
u8  Operands_stackEmpty(Operands_Stack_t* Copy_pstrOperandStack)
{
	if((Copy_pstrOperandStack->Top) < 0)
		return 1;
	else
		return 0;
}


/*Function to check if the stack is full*/
u8  Operands_stackFull(Operands_Stack_t* Copy_pstrOperandStack)
{

	if((Copy_pstrOperandStack->Top) >= MAX_SIZE)
		return 1;
	else
		return 0;

}


/*Function to get Size of The stack*/
u8  Operands_stackSize(Operands_Stack_t* Copy_pstrOperandStack)
{
	return Copy_pstrOperandStack->Top;
}


/************************************************************************************/
/************************************************************************************/
/**                    Functions For Stack Of Operators                            **/
/************************************************************************************/
/************************************************************************************/


/*Function to Pop Top Operator in stack*/
void pop_OPerator(Operators_Stack_t* Copy_pstrOperatorStack ,char* Copy_pchReturnElement)
{
	*Copy_pchReturnElement = Copy_pstrOperatorStack->entry[Copy_pstrOperatorStack->Top--];
}


/*Function to Push Operator in the Top Of The stack*/
void push_Operator(Operators_Stack_t* Copy_pstrOperatorStack  , char Copy_chElement)
{
	Copy_pstrOperatorStack->entry[++Copy_pstrOperatorStack->Top] = Copy_chElement;
}


/*Function to check if the stack is empty*/
u8  Operators_stackEmpty(Operators_Stack_t* Copy_pstrOperatorStack)
{
	if((Copy_pstrOperatorStack->Top) < 0)
		return 1;
	else
		return 0;
}


/*Function to check if the stack is full*/
u8  Operators_stackFull(Operators_Stack_t* Copy_pstrOperatorStack)
{
	if((Copy_pstrOperatorStack->Top) >= MAX_SIZE)
		return 1;
	else
		return 0;
}


/*Function to get Size of The stack*/
u8  Operators_stackSize(Operators_Stack_t* Copy_pstrOperatorStack)
{
	return ++Copy_pstrOperatorStack->Top;
}


