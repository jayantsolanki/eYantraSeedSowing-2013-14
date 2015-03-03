void getLineVals() //Gets Values from WhiteLine Sensors and stores them in line[] array
{
	char i;
	adc_init(0);
	for (i = 0; i < 2; i++)
	{
		line[0] = ADC_Conversion(2);//right
		line[1] = ADC_Conversion(3);//center
		line[2] = ADC_Conversion(1);//left
	}
	//addtoLineValHistory();
}

