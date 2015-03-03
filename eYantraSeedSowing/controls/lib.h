/*
 * lib.h
 *
 * Created: 28-02-2013 
 *  Author: Jayant Solanki
 */
 /*This header file contains definitions of all the low level functions directly 
interacting with hardware*/

/*
PC3 -> Buzzer
PC0-PC7 (except PC3) -> LCD
PH2 -> IR Proximity Sensors power control (active low)
PH3 -> SHARP RANGEFINDER power control (active low)
PF3 -> WhiteLine Right (ADC3)
PF2 -> WhiteLine Left (ADC2)
PF1 -> WhiteLine Center (ADC1)
PK1 -> SHARP RANGEFINDER 1, FRONT (ADC9)
PK3 -> SHARP RANGEFINDER 3, RIGHT (ADC11)
PK5 -> SHARP RANGEFINDER 5, LEFT (ADC13)
PJ0-PJ7 -> LED Bargraph
PA0 -> Left DC Motor (BACKWARD)
PA1 -> Left DC Motor (FORWARD)
PL3/OC5A -> Left DC Motor PWM out
PA3 -> Right DC Motor (BACKWARD)
PA2 -> Right DC Motor (FORWARD)
PL4/OC5B -> Left DC Motor PWM out
PE4/INT4 -> Left Position Encoder
PE5/INT5 -> Right Position Encoder

PORTA=9 ; BACKWARD
PORTA=6 ; FORWARD
PORTA=5 ; HARD LEFT
PORTA=10 ; HARD RIGHT
PORTA=2 ; SOFT RIGHT
PORTA=4 ; SOFT LEFT
*/



//Function to configure LCD port
void lcd_port_config (void)
{
	DDRC = DDRC | 0xF7; //all the LCD pin's direction set as output
	PORTC = PORTC & 0x80; // all the LCD pins are set to logic 0 except PORTC 7
}

//ADC pin configuration
void adc_pin_config (void)
{
	DDRF = 0x00;
	PORTF = 0x00;
	DDRK = 0x00;
	PORTK = 0x00;
}

//Function to configure ports to enable robot's motion
void motion_pin_config (void)
{
	DDRA = DDRA | 0x0F;
	PORTA = PORTA & 0xF0;
	DDRL = DDRL | 0x18;   //Setting PL3 and PL4 pins as output for PWM generation
	PORTL = PORTL | 0x18; //PL3 and PL4 pins are for velocity control using PWM.
}

// Timer Frequency:225.000Hz
void timer5_init()
{
	TCCR5B = 0x00;	//brake
	TCNT5H = 0xFF;	//Counter higher 8-bit value to which OCR5xH value is compared with
	TCNT5L = 0x01;	//Counter lower 8-bit value to which OCR5xH value is compared with
	OCR5AH = 0x00;	//Output compare register high value for Left Motor
	OCR5AL = 0xFF;	//Output compare register low value for Left Motor
	OCR5BH = 0x00;	//Output compare register high value for Right Motor
	OCR5BL = 0xFF;	//Output compare register low value for Right Motor
	OCR5CH = 0x00;	//Output compare register high value for Motor C1
	OCR5CL = 0xFF;	//Output compare register low value for Motor C1
	TCCR5A = 0xA9;	/*{COM5A1=1, COM5A0=0; COM5B1=1, COM5B0=0; COM5C1=1 COM5C0=0}
 					  For Overriding normal port functionality to OCRnA outputs.
				  	  {WGM51=0, WGM50=1} Along With WGM52 in TCCR5B for Selecting FAST PWM 8-bit Mode*/
	
	TCCR5B = 0x0B;	//WGM12=1; CS12=0, CS11=1, CS10=1 (Prescaler=64)
}

/*void adc_init()
{
	ADCSRA = 0x00;
	ADCSRB = 0x00;		//MUX5 = 0
	ADMUX = 0x20;		//Vref=5V external --- ADLAR=1 --- MUX4:0 = 0000
	ACSR = 0x80;
	ADCSRA = 0x86;		//ADEN=1 --- ADIE=1 --- ADPS2:0 = 1 1 0
}*/

//Function used for setting motor's direction
void motion_set (unsigned char Direction)
{
	unsigned char PortARestore = 0;

	Direction &= 0x0F; 		// removing upper nibbel for the protection
	PortARestore = PORTA; 		// reading the PORTA original status
	PortARestore &= 0xF0; 		// making lower direction nibbel to 0
	PortARestore |= Direction; // adding lower nibbel for forward command and restoring the PORTA status
	PORTA = PortARestore; 		// executing the command
}

//Function To Print Sensor Values At Desired Row And Coloumn Location on LCD
void print_sensor(char row, char coloumn,unsigned char channel)
{
	
	ADC_Value = ADC_Conversion(channel);
	lcd_print(row, coloumn, ADC_Value, 3);
}

//Function For ADC Conversion
unsigned char ADC_Conversion(unsigned char Ch)
{
	unsigned char a;
	if(Ch>7)
	{
		ADCSRB = 0x08;
	}
	Ch = Ch & 0x07;
	ADMUX= 0x20| Ch;
	ADCSRA = ADCSRA | 0x40;		//Set start conversion bit
	while((ADCSRA&0x10)==0);	//Wait for conversion to complete
	a=ADCH;
	ADCSRA = ADCSRA|0x10; //clear ADIF (ADC Interrupt Flag) by writing 1 to it
	ADCSRB = 0x00;
	return a;
}
void servo_init() //Initializes registers for Servo Motor 1 control
{
	DDRB  = DDRB | 0x20;  //making PORTB 5 pin output
	PORTB = PORTB | 0x20; //setting PORTB 5 pin to logic 1
	TCCR1B = 0x00; //stop
	TCNT1H = 0xFC; //Counter high value to which OCR1xH value is to be compared with
	TCNT1L = 0x01;	//Counter low value to which OCR1xH value is to be compared with
	OCR1AH = 0x03;	//Output compare Register high value for servo 1
	OCR1AL = 0xFF;	//Output Compare Register low Value For servo 1
	ICR1H  = 0x03;	
	ICR1L  = 0xFF;
	TCCR1A = 0xAB; /*{COM1A1=1, COM1A0=0; COM1B1=1, COM1B0=0; COM1C1=1 COM1C0=0}
 					For Overriding normal port functionality to OCRnA outputs.
				  {WGM11=1, WGM10=1} Along With WGM12 in TCCR1B for Selecting FAST PWM Mode*/
	TCCR1C = 0x00;
	TCCR1B = 0x0C; //WGM12=1; CS12=1, CS11=0, CS10=0 (Prescaler=256)
}

void disADCinterrupts() //Disables ADC interrupts
{
	ADCSRA = 0x80;
}

void switchOffProximitySensors() //Switches off IR Proximity sensors
{
	DDRH |= (1 << 2);
	PORTH |= (1 << 2);
}

void switchOnProximitySensors() //Switches on IR  Proximity sensors
{
	DDRH |= (1 << 2);
	PORTH &= 0xFB;
}

//Function used to configure INT4(PORTE4)pin as input for the left position encoder
void left_encoder_pin_config(void)
{
	DDRE=DDRE & 0xEF;
	PORTE=PORTE | 0x10;
}
//Function used to configure INT4(PORTE4)pin as input for the left position encoder
void right_encoder_pin_config(void)
{
	DDRE=DDRE & 0xDF;
	PORTE=PORTE | 0x20;
}
//Functions for configuring external interrupts for position encoders
void left_position_encoder_interrupt_init(void) //Interrupt 4 enable
{
	cli();
	EICRB=EICRB | 0x02;
	EIMSK=EIMSK | 0x10;
	sei();
}
void right_position_encoder_interrupt_init(void) //Interrupt 5 enable
{
	cli();
	EICRB=EICRB | 0x08;
	EIMSK=EIMSK | 0x20;
	sei();
}
//ISR for left position encoder
ISR(INT4_vect)
{

	ShaftCountLeft++;

}
//ISR for right position encoder
ISR(INT5_vect)
{
	
	ShaftCountRight++;
}


//Function for velocity control
void velocity (unsigned char left_motor, unsigned char right_motor)
{
	OCR5AL = (unsigned char)left_motor;
	OCR5BL = (unsigned char)right_motor;
}



// Function for buzzer
void buzzer_pin_config (void)
{
	DDRC = DDRC | 0x08;		//Setting PORTC 3 as output
	PORTC = PORTC & 0xF7;		//Setting PORTC 3 logic low to turnoff buzzer
}
void buzzer_on (void)
{
	unsigned char port_restore = 0;
	port_restore = PINC;
	port_restore = port_restore | 0x08;
	PORTC = port_restore;
}

void buzzer_off (void)
{
	unsigned char port_restore = 0;
	port_restore = PINC;
	port_restore = port_restore & 0xF7;
	PORTC = port_restore;
}

// This Function calculates the actual distance in millimeters(mm) from the input
// analog value of Sharp Sensor.
unsigned int Sharp_GP2D12_estimation(unsigned char adc_reading)
{
	float distance;
	unsigned int distanceInt;
	distance = (int)(10.00*(2799.6*(1.00/(pow(adc_reading,1.1546)))));
	distanceInt = (int)distance;
	if(distanceInt>800)
	{
		distanceInt=800;
	}
	return distanceInt;
}

void adc_init(char ch) //To initialize ADC; ch=1 -> enable with interrupts, ch=0 -> enable without interrupts
{
	DDRF = 0;
	PORTF = 0; //PORTF pins floating
	DDRK = 0;
	PORTK = 0; //PORTK pins floating
	ADMUX = 1;
	ADCSRB = 0;
	if (ch == 1)
	ADCSRA = 0XC8; //Enabling ADC, Activating Interrupt mode
	else
	ADCSRA = 0X80; //Enabling ADC, Without Interrupts
}

unsigned char adcval(char chnl) //returns converted ADC value on channel chnl
{
	ADC = 0;
	if (chnl > 3)
	{
		if (chnl > 7)
		ADCSRB = 0X08;
		chnl &= 0x07;
	}
	ADMUX = chnl | 0x20; //Left adjust enabled
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (0X10) == 0);
	ADCSRA |= (1 << ADIF);
	return(ADCH);
}