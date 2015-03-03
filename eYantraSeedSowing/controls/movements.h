/*
 * movement.h
 *
 * Created: 01-03-2014
 *  Author: Jayant Solanki
 */ 

//----------------------------------------------Line follow----------------------------------------------------------------

void gotoFrontNode() //Takes bot to node directly in front of it.
{
	while(1)
	{

		Left_white_line = ADC_Conversion(3);	//Getting data of Left WL Sensor
		Center_white_line = ADC_Conversion(2);	//Getting data of Center WL Sensor
		Right_white_line = ADC_Conversion(1);	//Getting data of Right WL Sensor


		print_sensor(1,1,3);	//Prints value of White Line Sensor1
		print_sensor(1,5,2);	//Prints Value of White Line Sensor2
		print_sensor(1,9,1);	//Prints Value of White Line Sensor3
		on_line();
		
	/*	sharp1 = ADC_Conversion(9);						//Stores the Analog value of front sharp connected to ADC channel 11 into variable "sharp"
		distanceleft = Sharp_GP2D12_estimation(sharp1);				//Stores Distance calculated in a variable "value".
		lcd_print(2,10,distanceleft,3); 						//Prints Value Of Distance in MM measured by Sharp Sensor.
		sharp2 = ADC_Conversion(13);						//Stores the Analog value of front sharp connected to ADC channel 11 into variable "sharp"
		distanceright = Sharp_GP2D12_estimation(sharp2);				//Stores Distance calculated in a variable "value".
		lcd_print(2,14,distanceright,3);
				
		if(sharpflag==1 && distanceleft <LEFT_SURFACE_DETECT_THRESHOLD && distanceright<RIGHT_SURFACE_DETECT_THRESHOLD)
		{
		sharpflag=0; //start filling holes again on detecting thermacol surface again
		buzzer_on();
		}		
	//	if(sharpflag==0) //holes are not filled when flag is set to 1
		//{
		else if(sharpflag==0 && distanceleft>LEFT_SHARPSENSOR_THRESHOLD && distanceright>RIGHT_SHARPSENSOR_THRESHOLD)//fill seedhole
		{
			brake();
			sharpflag=1;
			buzzer_off();
			
			//buzzer_on(); //debug check
				if(counter>=1 && counter<=7)//code here
				{
					lcd_print(2,1,counter,2);
					seedfillleft(holes[counter-1]);
			
			
			//code here
					lcd_print(2,4,counter+7,2);
					seedfillright(holes[counter+6]);
			
					servo_1(90); //reset the disk to initial position on feeling each hole
					SEED_DROP_DELAY;
		//}//end of for loop
					counter++;
						if(counter==8)
						{
							counter=28;//level up
							forward();
							velocity(220,220);
							_delay_ms(400);
						//	sharpflag=1;
			//buzzer_on();
			
			 //unless zero hole filling wont restart
						}
					}
					else
					{
				//buzzer_off();
				//code here
						lcd_print(2,1,counter,2);
						seedfillleft(holes[counter-1]);
						
				//code here
						lcd_print(2,4,counter-7,2);
						seedfillright(holes[counter-8]);
						servo_1(90); //reset the disk to initial position on feeling each hole
						SEED_DROP_DELAY;
			//}//end of for loop
						counter--;
					}		
					servo_1_free();
					forward();
					velocity(180,180);
					_delay_ms(1000);
				}*/	
			}			
		//}
}


void on_line(void)
{
	int flag=0;
	
	if(Center_white_line>0x20)
	{
		//flag=1;
		forward();
		velocity(200,200);
	}

	if(Left_white_line>14)
	{
		//flag=1;
		forward();
		velocity(130,200);
		
		
	}

	if(Right_white_line>14)
	{
		//flag=1;
		forward();
		velocity(200,130);
	}
	if(Center_white_line>32 && Right_white_line>32 && Left_white_line<40) //right turn encoder
	{
		_delay_ms(200);
		brake();
		//_delay_ms(500);
		soft_right_degrees(83);
	}
	if(Right_white_line<0x10 && Left_white_line<0x10 && Center_white_line<0x10)
	{
		//flag=1;
		forward();
		velocity(200,200);
		
	}
	if(Center_white_line>70 && Left_white_line>70 && Right_white_line>70)
	{
		
		brake();
		buzzer_on();
		_delay_ms(1000);
		buzzer_off();
		_delay_ms(1000);
		buzzer_on();
		_delay_ms(1000);
		buzzer_off();
		_delay_ms(1000);
		buzzer_on();
		_delay_ms(1000);
		buzzer_off();
		_delay_ms(1000);
		buzzer_on();
		_delay_ms(1000);
		buzzer_off();
		_delay_ms(1000);
		buzzer_on();
		_delay_ms(1000);
		buzzer_off();
		_delay_ms(1000);
		exit(1);
	}
}
	
	
	//Function used for turning robot by specified degrees
	void angle_rotate(unsigned int Degrees)
	{
		
		float ReqdShaftCount=0;
		unsigned long int ReqdShaftCountInt=0;


		ReqdShaftCount=(float)Degrees/4.090; //division by resolution to get shaft count
		ReqdShaftCountInt=(unsigned int)ReqdShaftCount;
		ShaftCountRight=0;
		ShaftCountLeft=0;

		while(1)
		{
			if((ShaftCountRight>=ReqdShaftCountInt) | (ShaftCountLeft>=ReqdShaftCountInt))
			break;
		}
		brake(); //brake bot
	}
	

	//Right in degrees
	void right_degrees(unsigned int Degrees)
	{
		//88 pulses for 360 degrees rotation 4.090 degrees per count
		right();
		angle_rotate(Degrees);
	}

	//forward in MM
	/*
	void forward_mm(unsigned int DistanceInMM)
	{
		//forward();
		linear_distance_mm(DistanceInMM);
	}
	*/

	void forward (void)
	{
		motion_set (0x06);
	}
	void soft_right_degrees(unsigned int Degrees)
	{
		
		// 176 pulses for 360 degrees rotation 2.045 degrees per count
		soft_right();  //Turn soft right
		Degrees=Degrees*2;
		angle_rotate(Degrees);
		
	}
	void right(void)
	{
		motion_set(0x0A);
		//velocity(150,150);
	}
	void soft_right (void) //Left wheel forward, Right wheel is stationary
	{
		motion_set(0x02);
	}
	void brake (void)
	{
		motion_set(0x00);

	}
	
	//-----------------------------------------servo control------------------------------------------------------
	//Function to rotate Servo 1 by a specified angle in the multiples of 1.86 degrees
	void servo_1(unsigned char degrees) //servo motor 1 controller
	{
		float PositionPanServo = 0;
		PositionPanServo = ((float)degrees / 1.86) + 35.0;

		
		
		OCR1AH = 0x00;
		OCR1AL = PositionPanServo;
		
	}

	void servo_1_free (void) //makes servo 1 free rotating
	{
		OCR1AH = 0x03;
		OCR1AL = 0xFF; //Servo 1 off
	}
	
	void filldiskhole(int n) //to fill the empty hole in the disk
	{
		switch(n)
		{
			case 1:
			servo_1(90); //disk hole 1
			break;
			case 2:
			servo_1(50); //hole 2
			break;
		}
	}


	void seedfillright(int n) //fills the seed holes on the right side of the bot
	{
		for (j=0;j<=n;j++)
		{
			if(j==3)
			{
				filldiskhole(1);
				_delay_ms(540);
				servo_1(189);
				_delay_ms(540);
			}
			else if(j==2) // needs fine tuning for different angles // hole 1 comes over right pot
			{
				servo_1(189);
				_delay_ms(500);
			}
			else if(j==1) // hole 2 comes over right pot
			{
				servo_1(140);
				_delay_ms(700);
			}
			
		}
	}

	void seedfillleft(int n) // fills the seed holes on the left side of the bot
	{
		for (j=0;j<=n;j++)
		{
			if(j==3)
			{
				filldiskhole(2);
				_delay_ms(270);
				servo_1(0);
				_delay_ms(300);
			}
			else if(j==2) // hole 2 comes over left pot
			{
				servo_1(0);
				_delay_ms(300); //subjected to change
			}
			else if(j==1) // hole 1 comes over left pot
			{
				servo_1(45);
				_delay_ms(300);
			}
			
		}
	}

	void fillhole(unsigned int k)
	{
		brake();
		
		if(k >=1 && k<=7)
		{
		//for(k=0;k<2;k++) //subjected to change
		//{
			//code here
			seedfillleft(holes[k-1]);
			lcd_print(2,1,k,2);
			
			//code here
			seedfillright(holes[k+6]);
			lcd_print(2,4,k+7,2);
			servo_1(90); //reset the disk to initial position on feeling each hole
			_delay_ms(500);
		//}//end of for loop
		counter++;
		if(counter==8)
		{
		counter=28;//level up
		sharpflag=1; //unless zero hole filling wont restart
		}		
		
		}		

		if(k >=21 && k<=28)
		{
		//for(k=14;k<21;k++) //subjected to change
		//{
			
			
			//code here
			seedfillleft(holes[k-1]);
			lcd_print(2,1,k,2);
			//code here
			seedfillright(holes[k-8]);
			lcd_print(2,1,k-7,2);
			servo_1(90); //reset the disk to initial position on feeling each hole
			SEED_DROP_DELAY;
			//}//end of for loop
			counter--;
			}		
			forward();
			velocity(180,180);
			_delay_ms(1000);
		}
			



