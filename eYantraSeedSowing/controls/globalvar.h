/*
 * globalvar.h
 *
 * Created: 28-02-2014 
 *  Author: Jayant Solanki
 */ 



#define F_CPU 14745600

unsigned char devDir = 1, orr = 4; //check this back

//#define VIRTUAL_SENSORS_ENABLED ((line[0] < 10) && (line[1] < 10) && (line[2] < 10)) //VIRTUAL_SENSORS_ENABLED

#define LEFT_SENSOR_THRESHOLD 10
#define RIGHT_SENSOR_THRESHOLD 10

#define LEFT_SENSOR_NODE_DETECTION_THRESHOLD 48
#define MIDDLE_SENSOR_NODE_DETECTION_THRESHOLD 60
#define RIGHT_SENSOR_NODE_DETECTION_THRESHOLD 48
#define LEFT_SHARPSENSOR_THRESHOLD 150
#define RIGHT_SHARPSENSOR_THRESHOLD 150
#define LEFT_SURFACE_DETECT_THRESHOLD 125
#define RIGHT_SURFACE_DETECT_THRESHOLD 125

#define MIDDLE_SENSOR_90_DEGREE_TURN_THRESHOLD 20
#define SEED_DROP_DELAY _delay_ms(1500)

#define Right_white_line line[0]
#define Left_white_line line[2]
#define Center_white_line line[1]


void port_init();
void seedfillright(int);
void seedfillleft(int);
void servo_1(unsigned char);
void timer5_init();
void velocity(unsigned char, unsigned char);
void motors_delay();
void servo_1_free();
unsigned char ADC_Conversion(unsigned char);
unsigned char ADC_Value;
//unsigned char flag1 = 0;
unsigned char sharp1;
unsigned char sharp2;
unsigned char distanceleft,distanceright;
volatile unsigned long int ShaftCountRight;
volatile unsigned long int ShaftCountLeft;
volatile unsigned int Degrees;
unsigned char line[3], leftSpeed, rightSpeed;
unsigned int l,j; //removed k
unsigned int flag,sharpflag=1;
unsigned int seeds;
int holes[28];
unsigned int counter=1;



char modulus(signed char num) //Mathematical MOD function.
{
	if (num < 0)
		return num * (-1);
	return num;
}


void printOnLCDLower(unsigned char le, unsigned char ri) //Prints input arguments on lcd in second row
{
	lcd_print(2, 1, le, 3);
	lcd_print(2, 5, ri, 3);
}

void printOnLCDUpper(unsigned char le, unsigned char ri) //Prints input arguments on lcd in first row
{
	lcd_print(1, 1, le, 3);
	lcd_print(1, 5, ri, 3);
}
