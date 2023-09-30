/*****************************************************/
/*****************************************************/
/**************   Author: Doaa Tawfik  ***************/
/**************   Layer: HAL           ***************/
/**************   SWC: KeyPad          ***************/
/**************   Version: 2.00        ***************/
/*****************************************************/
/*****************************************************/

#include  "../../LIB/STD_TYPES.h"
#include  "../../LIB/ERROR_STATE.h"

#include  "../../MCAL/DIO/DIO_Interface.h"

#include  "Keypad_Config.h"
#include  "KeyPad_Interface.h"
#include  "KeyPad_Private.h"

ES_t  KPD_enuInitialize(void)
{

	ES_t  Local_enuErrorState = ES_NOK;

	/*Setting Direction Of Rows AS INPUT*/
	Local_enuErrorState  = DIO_enuSetPinDirection(KPD_ROW0_PORT , KPD_ROW0_PIN , INPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(KPD_ROW1_PORT , KPD_ROW1_PIN , INPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(KPD_ROW2_PORT , KPD_ROW2_PIN , INPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(KPD_ROW3_PORT , KPD_ROW3_PIN , INPUT);

	/*Setting Direction Of Colums AS OUTPUT*/
	Local_enuErrorState |= DIO_enuSetPinDirection(KPD_COL0_PORT , KPD_COL0_PIN , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(KPD_COL1_PORT , KPD_COL1_PIN , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(KPD_COL2_PORT , KPD_COL2_PIN , OUTPUT);
	Local_enuErrorState |= DIO_enuSetPinDirection(KPD_COL3_PORT , KPD_COL3_PIN , OUTPUT);

	/*Setting Initial Value Of Rows AS HIGH to be (PULL_UP)*/
	Local_enuErrorState |= DIO_enuSetPinValue(KPD_ROW0_PORT , KPD_ROW0_PIN , HIGH);
	Local_enuErrorState |= DIO_enuSetPinValue(KPD_ROW1_PORT , KPD_ROW1_PIN , HIGH);
	Local_enuErrorState |= DIO_enuSetPinValue(KPD_ROW2_PORT , KPD_ROW2_PIN , HIGH);
	Local_enuErrorState |= DIO_enuSetPinValue(KPD_ROW3_PORT , KPD_ROW3_PIN , HIGH);

	/*Setting Initial Value Of Colums AS HIGH */
	Local_enuErrorState |= DIO_enuSetPinValue(KPD_COL0_PORT , KPD_COL0_PIN , HIGH);
	Local_enuErrorState |= DIO_enuSetPinValue(KPD_COL1_PORT , KPD_COL1_PIN , HIGH);
	Local_enuErrorState |= DIO_enuSetPinValue(KPD_COL2_PORT , KPD_COL2_PIN , HIGH);
	Local_enuErrorState |= DIO_enuSetPinValue(KPD_COL3_PORT , KPD_COL3_PIN , HIGH);

	return Local_enuErrorState;

}

ES_t  KPD_enuGetPressedKey(u8* Copy_pu8PressedKey)
{
	ES_t  Local_enuErrorState = ES_NOK;

	u8 Local_u8RowIndex , Local_u8ColumnIndex , Local_Pin_State;


	/*Local Array to hold values of Keypad*/
	static u8 Local_u8KPDConfig[ROWS_NUM][COLUMS_NUM] = KeyPad_Config;

	/*2 Arrays For Colums & rows Pins*/
	static u8 Local_u8KPDColumnsArrayPins[COLUMS_NUM] = {KPD_COL0_PIN , KPD_COL1_PIN , KPD_COL2_PIN , KPD_COL3_PIN};
	static u8 Local_u8KPDRowsArrayPins[ROWS_NUM] = {KPD_ROW0_PIN , KPD_ROW1_PIN , KPD_ROW2_PIN , KPD_ROW3_PIN};
	/*2 Arrays For Colums & rows Ports*/
	static u8 Local_u8KPDColumnsArrayPorts[COLUMS_NUM] = {KPD_COL0_PORT , KPD_COL1_PORT, KPD_COL2_PORT , KPD_COL3_PORT};
	static u8 Local_u8KPDRowsArrayPorts[ROWS_NUM] = {KPD_ROW0_PORT, KPD_ROW1_PORT , KPD_ROW2_PORT , KPD_ROW3_PORT};

	if(Copy_pu8PressedKey != NULL)
	{
		*Copy_pu8PressedKey = KPD_NO_PRESSED_KEY;

		for(Local_u8ColumnIndex = 0 ; Local_u8ColumnIndex < COLUMS_NUM ; Local_u8ColumnIndex++)
		{
			/* Activation Current Column by setting its value with LOW */
			Local_enuErrorState = DIO_enuSetPinValue(Local_u8KPDColumnsArrayPorts[Local_u8ColumnIndex] , Local_u8KPDColumnsArrayPins[Local_u8ColumnIndex] , LOW);

			for(Local_u8RowIndex = 0 ; Local_u8RowIndex < ROWS_NUM ; Local_u8RowIndex++)
			{
				/*Reading Current Row Value*/
				Local_enuErrorState |= DIO_enuGetPinValue(Local_u8KPDRowsArrayPorts[Local_u8RowIndex] , Local_u8KPDRowsArrayPins[Local_u8RowIndex] , &Local_Pin_State);

				/*Checking on Pin State*/
				if(Local_Pin_State == LOW)
				{
					*Copy_pu8PressedKey = Local_u8KPDConfig[Local_u8RowIndex][Local_u8ColumnIndex];
					/*Polling(Busy Waiting until key is released)*/
					while(Local_Pin_State == LOW)
					{
						Local_enuErrorState |= DIO_enuGetPinValue(Local_u8KPDRowsArrayPorts[Local_u8RowIndex] , Local_u8KPDRowsArrayPins[Local_u8RowIndex] , &Local_Pin_State);
					}
					return Local_enuErrorState;
				}
			}
			/* Deactivate Current Column by setting its value with HIGH */
			DIO_enuSetPinValue(Local_u8KPDColumnsArrayPorts[Local_u8ColumnIndex] , Local_u8KPDColumnsArrayPins[Local_u8ColumnIndex] , HIGH);
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}
