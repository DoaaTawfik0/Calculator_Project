/******************************************************/
/******************************************************/
/**************   Author: Doaa Tawfik   ***************/
/**************   Layer:  App           ***************/
/**************   SWC:    Stack         ***************/
/******************************************************/
/******************************************************/

#ifndef  STACK_H_
#define  STACK_H_



#define     MAX_SIZE       12   //Max Number of Operands user can input is 10 Operands
#define     stackEntry     s32  //Operands Type




/************************************************************************************/
/************************************************************************************/
/** Description     : This Is a Structure For Operands                             **/
/** Components                                                                     **/
/** 1-Top->Referes to Top Of Stack                                                 **/
/** 2-entry-> it's an array of Type stackEntry(s32) & it's size is 12 element       **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

typedef struct
{
	s16 Top;
    stackEntry entry[MAX_SIZE];
} Operands_Stack_t;


/************************************************************************************/
/************************************************************************************/
/** Description     : This Is a Structure For Operators                            **/
/** Components                                                                     **/
/** 1-Top->Referes to Top Of Stack                                                 **/
/** 2-entry-> it's an array of Type char & it's size is 12 element                 **/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

typedef struct
{
    s16 Top;
    char entry[MAX_SIZE];
} Operators_Stack_t;



/************************************************************************************/
/************************************************************************************/
/**                 Functions ProtoTypes For Stack Of Operands                     **/
/************************************************************************************/
/************************************************************************************/

void pop_OPerand(Operands_Stack_t* Copy_pstrOperandStack, stackEntry* Copy_pu8ReturnElement);
void push_Operand(Operands_Stack_t* Copy_pstrOperandStack , stackEntry Copy_u8Element);
u8  Operands_stackEmpty(Operands_Stack_t* Copy_pstrOperandStack);
u8  Operands_stackFull(Operands_Stack_t* Copy_pstrOperandStack);
u8  Operands_stackSize(Operands_Stack_t* Copy_pstrOperandStack);



/************************************************************************************/
/************************************************************************************/
/**                Functions ProtoTypes For Stack Of Operators                     **/
/************************************************************************************/
/************************************************************************************/

void pop_OPerator( Operators_Stack_t *ps , char *pe);//.........................
void push_Operator(Operators_Stack_t* Copy_pstrOperatorStack  , char Copy_chElement);
u8  Operators_stackEmpty(Operators_Stack_t* Copy_pstrOperatorStack );
u8  Operators_stackFull(Operators_Stack_t* Copy_pstrOperatorStack );
u8  Operators_stackSize(Operators_Stack_t* Copy_pstrOperatorStack );

#endif
