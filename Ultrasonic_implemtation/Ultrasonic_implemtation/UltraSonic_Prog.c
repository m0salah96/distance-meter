/***********************************************/
/****By:mohamed salah***************************/
/****CAR_PROGRAM.C   ***************************/
/****19/8/2022 9:39pm Portsaid East**************/ 
/***********************************************/
  
  
 #include "STD_types.h"
 #include "Bit_math.h"
 #include "STD_types.h"
 #include "DIO_interface.h"
 #include "TIMER1_interface.h"
 #include "UltraSonic_Config.h"
 #include "UltraSonic_Interface.h"
#define F_CPU 16000000UL
 #include <avr/interrupt.h>
 #include <util/delay.h>
 
 static u8 no_OVF;
  



  u32 Ultrasonic_GetDistance(){
	  
	  u32 time_measured;
	  u32  distance;
	 //	Enable Interrupt
	 sei();
	 SetBit(TIMSK,TOIE1);
	//Initialize timer pre-scaler
	Timer1_Start();
	 //ICU Rising edge
	 SetBit(TCCR1B,ICES1);
	 //reset flag
	 SetBit(TIFR,ICF1);
		//zero o.v. flag
		Timer1_Reset();
		no_OVF=0;
	//trigger pulse 
	DIO_Void_SetPin(Ultra_Sonic_Trigger_PORT,Ultra_Sonic_Trigger_PIN);  
	_delay_us(20);  
	DIO_Void_ClearPin(Ultra_Sonic_Trigger_PORT,Ultra_Sonic_Trigger_PIN); 
	//wait for echo set
	while(GetBit(TIFR,ICF1)==0);

	//reset flag
	SetBit(TIFR,ICF1);

	 //ICU Falling edge
	 ClearBit(TCCR1B,ICES1);	  
     //wait for capture 
     while(GetBit(TIFR,ICF1)==0);
     time_measured=ICR1+no_OVF*65535;
     distance=time_measured/115;
     _delay_ms(50);
      return distance;
  
  }

ISR(TIMER1_OVF_vect){

no_OVF++;

}
                                                                                                                                                          

	
