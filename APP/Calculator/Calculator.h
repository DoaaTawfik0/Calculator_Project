/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  APP           ***************/
/**************   SWC:    Program       ***************/
/******************************************************/
/******************************************************/


#ifndef  PROGRAM_H_
#define  PROGRAM_H_


typedef enum
{
	FSTATE_NOK,
	FSTATE_OK,
	FSTATE_NULLPTR,
	FSTATE_FIRST_INPUT_OPERATOR,
	FSTATE_MISSING_OPERAND,
	FSTATE_MAX_OPERANDS_NUM,
	FSTATE_DIV_BY_ZERO,
	FSTATE_INVALID_OPERATOR

}FSTATE_t;


#define   NULL_CHARACTER             '\0'
#define   ZERO_CHARACTER              '0'

#define   MAX_ARR_SIZE                 20



/************************************************************************************/
/************************************************************************************/
/**                              Functions ProtoTypes                              **/
/************************************************************************************/
/************************************************************************************/


FSTATE_t   perform_operation(s32 Copy_u8Operand1, s32 Copy_u8Operand2, char Copy_chOperator , s32* Copu_s32Result);
FSTATE_t   Divisible_by_Zero(u8 Copy_u8Operand2);
FSTATE_t   Check_First_Input_Operator();
FSTATE_t   Check_Missing_Operand();
FSTATE_t   Calculate_Postfix();


void       print_Syntax_error();
void       Start_calculating();
void       Reset_Calculator();
void       Infix_to_Postfix();
void       Get_Infix();


u8         Operator_Precedence (char Copy_chOperator);
u8         IS_Operator(char Copy_chOperator);
u8         Is_Digit(char Copy_chDigit);

#endif
