/*
 * eYantraSeedSowing.h
 *
 * Created: 01-03-2014
 *  Author: Jayant Solanki
 */

#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <math.h> //included to support power function
#include "lcd.h"
#include "controls/globalvar.h"
#include "controls/lib.h"
#include "controls/movements.h"
#include "controls/sensorvals.h"


//Function to Initialize PORTS
void port_init()
{
	lcd_port_config();
	//adc_pin_config();
	motion_pin_config();
	left_encoder_pin_config();
	right_encoder_pin_config();
	buzzer_pin_config();	
}





void init_devices (void)
{
 	cli(); //Clears the global interrupts
	port_init();
	adc_init(0);
	servo_init();
	timer5_init();
	left_position_encoder_interrupt_init();
	right_position_encoder_interrupt_init();
	sei();   //Enables the global interrupts
}



//Main Function
int main(void)
{
	init_devices();
	lcd_set_4bit();
	lcd_init();
	
	
	holes[0]=1;
	holes[1]=1;
	holes[2]=1;
	holes[3]=1;
	holes[4]=1;
	holes[5]=1;
	holes[6]=1;
	holes[7]=2;
	holes[8]=3;
	holes[9]=1;
	holes[10]=3;
	holes[11]=3;
	holes[12]=1;
	holes[13]=2;
	holes[14]=2;
	holes[15]=1;
	holes[16]=1;
	holes[17]=2;
	holes[18]=3;
	holes[19]=2;
	holes[20]=1;
	holes[21]=1;
	holes[22]=1;
	holes[23]=1;
	holes[24]=1;
	holes[25]=1;
	holes[26]=1;
	holes[27]=1;
	
	servo_1(90); //default angle for disk, set on disk hole 1
	_delay_ms(800);
	
	gotoFrontNode();
	
	
}	

