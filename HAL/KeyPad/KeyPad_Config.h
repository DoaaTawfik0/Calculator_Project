/*****************************************************/
/*****************************************************/
/**************   Author: Doaa Tawfik  ***************/
/**************   Layer: HAL           ***************/
/**************   SWC: KeyPad          ***************/
/**************   Version: 2.00        ***************/
/*****************************************************/
/*****************************************************/


#ifndef  KEYPAD_CONFIG_H_
#define  KEYPAD_CONFIG_H_



#define KPD_NO_PRESSED_KEY      0xff

/*Defining Ports & Pins For Rows*/

#define KPD_ROW0_PORT           DIO_PORTA
#define KPD_ROW0_PIN            DIO_PIN0

#define KPD_ROW1_PORT           DIO_PORTA
#define KPD_ROW1_PIN            DIO_PIN1

#define KPD_ROW2_PORT           DIO_PORTA
#define KPD_ROW2_PIN            DIO_PIN2

#define KPD_ROW3_PORT           DIO_PORTA
#define KPD_ROW3_PIN            DIO_PIN3

/*Defining Ports & Pins For Colums*/

#define KPD_COL0_PORT           DIO_PORTA
#define KPD_COL0_PIN            DIO_PIN4

#define KPD_COL1_PORT           DIO_PORTA
#define KPD_COL1_PIN            DIO_PIN5

#define KPD_COL2_PORT           DIO_PORTA
#define KPD_COL2_PIN            DIO_PIN6

#define KPD_COL3_PORT           DIO_PORTA
#define KPD_COL3_PIN            DIO_PIN7


#define KeyPad_Config { {'7','8','9','/'} , {'4','5','6','*'} , {'1','2','3','-'} , {'C','0','=','+'} }

#endif
