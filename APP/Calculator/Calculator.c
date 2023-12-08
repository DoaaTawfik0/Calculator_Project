/*******************************************************/
/*******************************************************/
/**************   Author: Doaa Tawfik    ***************/
/**************   Layer:  APP            ***************/
/**************   SWC:    Calculator     ***************/
/*******************************************************/
/*******************************************************/



#include  "../../LIB/STD_TYPES.h"
#include  "../../LIB/ERROR_STATE.h"

#include  "../../MCAL/DIO/DIO_Interface.h"
#include  "../../HAL/Character_LCD/CLCD_Interface.h"
#include  "../../HAL/KeyPad/KeyPad_Interface.h"

#include  "../Stack/Stack.h"

#include "Calculator.h"


char Global_chAInFixArr[MAX_ARR_SIZE] = {'0'} ;
char Global_chAPostFixArr[MAX_ARR_SIZE] = {'0'};

u8 Global_u8Infix_Iterator;
u8 Global_u8Operands_Num , Global_u8Operators_Num;

u8 Global_u8InputCharacter  ;

FSTATE_t Global_enuErrorFlag = FSTATE_NOK;

s32 Global_s32Result;




/***************************************************************************************/
/***************************************************************************************/
/** Function Name   : Start_calculating.                                              **/
/** Return Type     : Void                                                            **/
/** Arguments       : Void                                                            **/
/** Functionality   : Main Function of the Program                                    **/
/**This function will start calculator when user press on 'C' Button                  **/
/**It'll call other functions like GET_Infix , Infix_to_Postfix & Calculate_Postfix   **/
/**It'll check in Errors that will happen during Calculations like:                   **/
/** 1)Division by Zero     2)Missing Operand   3)First Input is Operator('*','/')     **/
/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

void Start_calculating()
{
	CLCD_enuClearDisplay();

	while(1)
	{
		KPD_enuGetPressedKey(&Global_u8InputCharacter);
		if(Global_u8InputCharacter == 0XFF)
			continue;

		/*If 'C' Button is pressed ,Calculator will start to Operate*/
		if(Global_u8InputCharacter == 'C')
		{
			Reset_Calculator();
			Get_Infix();

			if(Global_enuErrorFlag == FSTATE_MAX_OPERANDS_NUM)
			{
				CLCD_enuControl_Cursor_Blink(1);
			}
			else
			{
				Global_enuErrorFlag = Check_First_Input_Operator();

				if(Global_enuErrorFlag == FSTATE_FIRST_INPUT_OPERATOR)
				{
					Reset_Calculator();
					print_Syntax_error();
				}
				else if(Global_enuErrorFlag == FSTATE_OK)
				{
					Global_enuErrorFlag = Check_Missing_Operand();
					if(Global_enuErrorFlag == FSTATE_MISSING_OPERAND)
					{
						Reset_Calculator();
						print_Syntax_error();
					}
					else if(Global_enuErrorFlag == FSTATE_OK)
					{
						Infix_to_Postfix();
						Global_enuErrorFlag = Calculate_Postfix(Global_chAPostFixArr , &Global_s32Result);
						if(Global_enuErrorFlag == FSTATE_DIV_BY_ZERO)
						{
							Reset_Calculator();
							print_Syntax_error();
						}
						else if(Global_enuErrorFlag == FSTATE_OK)
							CLCD_enuWriteNumber(Global_s32Result);
					}
				}
			}
		}

	}

}


/***************************************************************************************/
/***************************************************************************************/
/** Function Name   : Check_Missing_Operand.                                          **/
/** Return Type     : FSTATE_t                                                        **/
/** Arguments       : Void                                                            **/
/** Functionality   : Check if there is a Missig Operand                              **/
/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

FSTATE_t Check_Missing_Operand()
{
	if (Global_u8Operators_Num >= Global_u8Operands_Num)
		return FSTATE_MISSING_OPERAND;
	return FSTATE_OK;
}


/***************************************************************************************/
/***************************************************************************************/
/** Function Name   : Reset_Calculator.                                               **/
/** Return Type     : Void                                                            **/
/** Arguments       : Void                                                            **/
/** Functionality   : Reset Calculator by :                                           **/
/** 1)Clearing LCD Display  2)Initializing 2 Global Arrays with Zero Character        **/
/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

void Reset_Calculator()
{
	u8 Local_u8Iterator;

	CLCD_enuClearDisplay();
	for(Local_u8Iterator = 0 ; Local_u8Iterator < MAX_SIZE ; Local_u8Iterator++)
	{
		Global_chAInFixArr[Local_u8Iterator] = '0';
		Global_chAPostFixArr[Local_u8Iterator] = '0';
		Global_u8Infix_Iterator = 0;
	}
}


/***************************************************************************************/
/***************************************************************************************/
/** Function Name   : print_Syntax_error.                                             **/
/** Return Type     : Void                                                            **/
/** Arguments       : Void                                                            **/
/** Functionality   : Printing Syntax Error On LCD                                    **/
/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

void print_Syntax_error()
{
	CLCD_enuGoToXY(0,5);
	CLCD_enuSendString("SYNTAX");
	CLCD_enuGoToXY(1,5);
	CLCD_enuSendString("ERROR!");
}



/***************************************************************************************/
/***************************************************************************************/
/** Function Name   : Check_First_Input_Operator.                                     **/
/** Return Type     : FSTATE_t                                                        **/
/** Arguments       : Void                                                            **/
/** Functionality   : Check if First Input Is Operator('+' , '-' . '*' , '/')         **/
/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

FSTATE_t Check_First_Input_Operator()
{
	u8 Local_u8Iterator = 0;
	if ((Global_chAInFixArr[Local_u8Iterator] == '*') || (Global_chAInFixArr[Local_u8Iterator]  == '/') || (Global_chAInFixArr[Local_u8Iterator]  == '+') || (Global_chAInFixArr[Local_u8Iterator]  == '-'))
		return FSTATE_FIRST_INPUT_OPERATOR;
	return FSTATE_OK;
}


/***************************************************************************************/
/***************************************************************************************/
/** Function Name   : Get_Infix.                                                      **/
/** Return Type     : Void                                                            **/
/** Arguments       : Void                                                            **/
/** Functionality   : Get Infix From User                                             **/
/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

void Get_Infix()
{
	for(Global_u8Infix_Iterator = 0 ; Global_u8Infix_Iterator < MAX_ARR_SIZE ; Global_u8Infix_Iterator++)
	{
		do
		{
			KPD_enuGetPressedKey(&Global_u8InputCharacter);
		}while(Global_u8InputCharacter == 0XFF);


		if (Is_Digit(Global_u8InputCharacter))
			Global_u8Operands_Num++;/*Counting Number Of Operands*/
		else if(IS_Operator(Global_u8InputCharacter))
			Global_u8Operators_Num++;/*Counting Number Of Operators*/


		if(Global_u8Infix_Iterator == 16)
			CLCD_enuGoToXY(1,0);//Handling Printing on Lcd To Show all Inputs
		CLCD_enuSendCharacter(Global_u8InputCharacter);

		if(Global_u8InputCharacter == '=')
		{
			Global_chAInFixArr[Global_u8Infix_Iterator] = NULL_CHARACTER;//Terminating The Infix Array
			Global_enuErrorFlag = FSTATE_OK;
			return;
		}
		else
		{
			Global_chAInFixArr[Global_u8Infix_Iterator] = Global_u8InputCharacter;//Pushing Input Character in Infix Array
		}

	}
	Global_enuErrorFlag = FSTATE_MAX_OPERANDS_NUM; // User has Reached the Max Number of Operands to enter
}


/***************************************************************************************/
/***************************************************************************************/
/** Function Name   : Infix_to_Postfix.                                               **/
/** Return Type     : Void                                                            **/
/** Arguments       : Void                                                            **/
/** Functionality   : Converting Infix To Postfix Using Stack Implementation          **/
/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

void Infix_to_Postfix()
{
	u8 Local_u8Infix_Iterator = 0, Local_u8PostFix_Iterator = 0;

	char Operand_x;

	Operators_Stack_t Operator_Stack; //Creating Object Of Type Operators_Stack_t
	Operator_Stack.Top = -1; //Initializing Top Of The Stack With -1

	while (Global_chAInFixArr[Local_u8Infix_Iterator] != NULL_CHARACTER)
	{
		Operand_x = Global_chAInFixArr[Local_u8Infix_Iterator];

		if (Is_Digit(Operand_x))
		{
			// If it's a digit, Add it to PostFix Array
			Global_chAPostFixArr[Local_u8PostFix_Iterator++] = Operand_x;

		}
		else if(IS_Operator(Operand_x))
		{
			/*Check if Stack isn't Empty & The Precedence of Incoming Element*/
			while((Operator_Stack.Top >= 0) && (Operator_Precedence(Operator_Stack.entry[Operator_Stack.Top]) >= Operator_Precedence(Operand_x)))
			{
				pop_OPerator(&Operator_Stack, &Global_chAPostFixArr[Local_u8PostFix_Iterator++]);
			}
			push_Operator(&Operator_Stack, Operand_x);
		}
		Local_u8Infix_Iterator++;
	}
	/*Pop any remaining operators from the stack and add to the postfix array*/
	while (!Operators_stackEmpty(&Operator_Stack))
	{
		pop_OPerator(&Operator_Stack, &Global_chAPostFixArr[Local_u8PostFix_Iterator++]);
	}
	/*Terminating the postfix array with Null Character*/
	Global_chAPostFixArr[Local_u8PostFix_Iterator] = NULL_CHARACTER;
}


/***************************************************************************************/
/***************************************************************************************/
/** Function Name   : Calculate_Postfix.                                              **/
/** Return Type     : FSTATE_t                                                        **/
/** Arguments       : Void                                                            **/
/** Functionality   : Calculating Postfix Using Stack Implementation                  **/
/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

FSTATE_t Calculate_Postfix()
{

	FSTATE_t Local_enuFlagState = FSTATE_NOK;

	u8 Local_u8PostFix_Iterator = 0 , Local_u8TempOperand;
	s32 Local_s32Result ,  Local_s32Operand1 , Local_s32Operand2 ;

	char Local_chOperand_X;

	Operands_Stack_t  Operand_Stack;//Creating Object Of Type Operands_Stack_t
	Operand_Stack.Top = -1; //Initializing Top Of The Stack With -1

	while (Global_chAPostFixArr[Local_u8PostFix_Iterator] != NULL_CHARACTER)
	{
		Local_chOperand_X = Global_chAPostFixArr[Local_u8PostFix_Iterator] ;

		if (Is_Digit(Local_chOperand_X))
		{
			Local_u8TempOperand = Local_chOperand_X - ZERO_CHARACTER;
			push_Operand(&Operand_Stack , Local_u8TempOperand);
		}
		else if (IS_Operator(Local_chOperand_X))
		{
			pop_OPerand(&Operand_Stack , &Local_s32Operand2);
			pop_OPerand(&Operand_Stack , &Local_s32Operand1  );
			Local_enuFlagState = perform_operation(Local_s32Operand1 , Local_s32Operand2 , Local_chOperand_X , &Global_s32Result);

			if(Local_enuFlagState == FSTATE_DIV_BY_ZERO)
			{
				return Local_enuFlagState; //Return if There is Division By Zero
			}
			push_Operand(&Operand_Stack , Global_s32Result);
		}

		Local_u8PostFix_Iterator++;

	}
	Local_enuFlagState = FSTATE_OK;

	pop_OPerand(&Operand_Stack , &Local_s32Result);

	return Local_enuFlagState;
}


/*********************************************************************************************/
/*********************************************************************************************/
/** Function Name   : perform_operation.                                                    **/
/** Return Type     : FSTATE_t                                                              **/
/** Arguments       : Copy_u8Operand1 , Copy_u8Operand2 , Copy_chOperator ,  Copu_s32Result **/
/** Functionality   : Perform Arithmetic Operation On 2 Operands                            **/
/*********************************************************************************************/
/*********************************************************************************************/
/*********************************************************************************************/

FSTATE_t perform_operation(s32 Copy_u8Operand1, s32 Copy_u8Operand2, char Copy_chOperator , s32* Copu_s32Result)
{
	FSTATE_t Local_enuFlagState = FSTATE_NOK;

	switch (Copy_chOperator)
	{
	case '+':
		*Copu_s32Result = Copy_u8Operand1 + Copy_u8Operand2;
		return FSTATE_OK;
	case '-':
		*Copu_s32Result = Copy_u8Operand1 - Copy_u8Operand2;
		return FSTATE_OK;
	case '*':
		*Copu_s32Result = Copy_u8Operand1 * Copy_u8Operand2;
		return FSTATE_OK;
	case '/':
		Local_enuFlagState = Divisible_by_Zero(Copy_u8Operand2) ;
		if (Local_enuFlagState == FSTATE_OK)
		{
			*Copu_s32Result = Copy_u8Operand1 / Copy_u8Operand2;
		}
		return Local_enuFlagState;
	default:
		return FSTATE_INVALID_OPERATOR;

	}

}


/*********************************************************************************************/
/*********************************************************************************************/
/** Function Name   : Operator_Precedence.                                                  **/
/** Return Type     : u8                                                                    **/
/** Arguments       : Copy_chOperator                                                       **/
/** Functionality   : Return The Precedence of The Operator                                 **/
/*********************************************************************************************/
/*********************************************************************************************/
/*********************************************************************************************/

u8 Operator_Precedence (char Copy_chOperator)
{
	if((Copy_chOperator == '+') || (Copy_chOperator == '-'))
		return 1;
	else if((Copy_chOperator == '*') || (Copy_chOperator == '/'))
		return 2;
	return 0;
}


/*********************************************************************************************/
/*********************************************************************************************/
/** Function Name   : IS_Operator.                                                          **/
/** Return Type     : u8                                                                    **/
/** Arguments       : Copy_chOperator                                                       **/
/** Functionality   : Return True if it's an Operator                                       **/
/*********************************************************************************************/
/*********************************************************************************************/
/*********************************************************************************************/

u8  IS_Operator(char Copy_chOperator)
{

	return (Copy_chOperator == '+' || Copy_chOperator == '-' || Copy_chOperator == '*' || Copy_chOperator == '/');
}


/*********************************************************************************************/
/*********************************************************************************************/
/** Function Name   : Is_Digit.                                                             **/
/** Return Type     : u8                                                                    **/
/** Arguments       : Copy_chDigit                                                          **/
/** Functionality   : Return True if it's a Digit                                           **/
/*********************************************************************************************/
/*********************************************************************************************/
/*********************************************************************************************/

u8  Is_Digit(char Copy_chDigit)
{
	return ((Copy_chDigit >= '0') && (Copy_chDigit <= '9'));
}


/*********************************************************************************************/
/*********************************************************************************************/
/** Function Name   : Divisible_by_Zero.                                                    **/
/** Return Type     : FSTATE_t                                                              **/
/** Arguments       : Copy_u8Operand2                                                       **/
/** Functionality   : Check if the value of second Operand Equals to Zero                   **/
/*********************************************************************************************/
/*********************************************************************************************/
/*********************************************************************************************/

FSTATE_t Divisible_by_Zero(u8 Copy_u8Operand2)
{
	if(Copy_u8Operand2 == 0)
		return FSTATE_DIV_BY_ZERO;
	else
		return FSTATE_OK;

}


