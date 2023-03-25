/*
 * Ultrasonic_implemtation.c
 *
 * Created: 11-Nov-22 12:17:18 AM
 * Author : Mosalah  Port said
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "STD_types.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "TIMER1_interface.h"
#include "UltraSonic_Interface.h"


int main(void)
{


DIO_Void_Init();
LCD_Void_Init();
Timer1_Init();

LCD_voidSendString("Distance =");
	

u32 x;
    while (1) 
    {    LCD_voidSetCursor(1,1);
	    LCD_voidSendString("cm");
		x=Ultrasonic_GetDistance();
		LCD_voidSetCursor(1,0);
		LCD_Display_Number(x);
	   _delay_ms(200);
    }
}


