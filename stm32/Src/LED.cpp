
#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

	//Direct PWM values which used for TIM4 registers//
int LED1_PWM = 0;
int LED2_PWM = 0;
int LED3_PWM = 0;
int LED4_PWM = 0;
	//Enable flags for each LED
int LED1_EN = 0;
int LED2_EN = 0;
int LED3_EN = 0;
int LED4_EN = 0;

	//Calibration values as addition to hardware calibration
int LED1_CAL_VALUE = 1000;
int LED2_CAL_VALUE = 1000;
int LED3_CAL_VALUE = 3200;
int LED4_CAL_VALUE = 1000;
	//Calibration signs
char LED1_CAL_SIGN = '-';
char LED2_CAL_SIGN = '+';
char LED3_CAL_SIGN = '-';
char LED4_CAL_SIGN = '-';
	//Values for external logic
int LED1_VALUE = 57020;
int LED2_VALUE = 57020;
int LED3_VALUE = 57020;
int LED4_VALUE = 57020;
	//For ALL mode
int LED1_ALL_VALUE = 0;
int LED2_ALL_VALUE = 0;
int LED3_ALL_VALUE = 0;
int LED4_ALL_VALUE = 0;


int i = 0;
int MAX_PWM = 60400;
int MIN_PWM = 49000;

int old_led_pwm_value = 0;
int old_led_en_value = 0;

void char2int(char* pchar, int* pint);
void LED_SW(void);
int LEDnumValue(int);
int LED_CVAL(int VAL, int CAL, char sign); 
int LED_ValuebyNum (int lednum);
int LED_PWMbyNum(int lednum);
int LED_StatebyNum(int lednum);


int LED_ValuebyNum (int lednum) //Returns corrected PWM value by LED number
{
	int value;
	
	if ((lednum != 0) && (lednum != NULL)) 
	{
		switch (lednum)
		{
		case 1:
			value = LED1_VALUE;
			break;
		case 2:
			value = LED2_VALUE;
			break;
		case 3:
			value = LED3_VALUE;
			break;
		case 4:
			value = LED4_VALUE;
			break;
		default:
			break;
		}
	}
	return value;
}

int LED_PWMbyNum(int lednum) //Returns direct PWM value by LED number
{
	int value;
	
	if ((lednum != 0) && (lednum != NULL)) 
	{
		switch (lednum)
		{
		case 1:
			value = LED1_PWM;
			break;
		case 2:
			value = LED2_PWM;
			break;
		case 3:
			value = LED3_PWM;
			break;
		case 4:
			value = LED4_PWM;
			break;
		default:
			break;
		}
	}
	return value;
}

int LED_StatebyNum(int lednum) //Returns ON\OFF state by LED number
{
	int value;
	
	if ((lednum != 0) && (lednum != NULL)) 
	{
		switch (lednum)
		{
		case 1:
			value = LED1_EN;
			break;
		case 2:
			value = LED2_EN;
			break;
		case 3:
			value = LED3_EN;
			break;
		case 4:
			value = LED4_EN;
			break;
		default:
			break;
		}
	}
	return value;
}


void LED_CLI(char *led_num, char *led_en, char *led_pwm) //Command-line interface functions
{
	int led_num_int = 0; //LED number variable
	int led_en_int = 0; //ON\OFF variable
	int led_pwm_int = 0; //PWM value variable

	short error = 0; //Error flag
	
	short no_en_value = 0; //no convert char to int flag
	short no_lednum_value = 0; //no convert char to int flag
	short no_pwm_value = 0; //no convert char to int flag
	
	if (strncmp(led_num, "ALL", 3) == 0 )  //Set all LED's ON
	{	
		led_num_int = 228;
		no_lednum_value = 1;
		}
	if (strncmp(led_en, "ON", 2) == 0 )  //Set LED ON
	{
		led_en_int = 1;
		no_en_value = 1;
		}
	if (strncmp(led_en, "OFF", 3) == 0 )  //Set LED OFF
	{
		led_en_int = 0;
		no_en_value = 1;
		}
	if (strncmp(led_en, "NC", 2) == 0 )  //No change
	{
		led_en_int = 0;
		no_en_value = 2;
		}
	
		
		
		
	if ((strncmp(led_pwm, "MAX", 3) == 0) && (strncmp(led_num, "ALL", 3) == 0 ))  //If brightness arg is MAX and lednum arg is ALL
	{
		LED1_VALUE = LED2_VALUE = LED3_VALUE = LED4_VALUE = MAX_PWM; //Set all LED's brightness to max
		led_pwm_int = MAX_PWM;
		no_pwm_value = 1;
		}
	if (strncmp(led_pwm, "MAX", 3) == 0)  //Set LED brightness to max
	{
		led_pwm_int = MAX_PWM;
		no_pwm_value = 1;
		}
	if ((strncmp(led_pwm, "MIN", 3) == 0) && (strncmp(led_num, "ALL", 3) == 0 ))  //If brightness arg is MIN and lednum arg is ALL
	{
		LED1_VALUE = LED2_VALUE = LED3_VALUE = LED4_VALUE = MIN_PWM; //Set all LED's brightness to min
		led_pwm_int = MIN_PWM;
		no_pwm_value = 1;
		}
	if (strncmp(led_pwm, "MIN", 3) == 0)  //Set LED brightness to min
	{
		led_pwm_int = MIN_PWM;
		no_pwm_value = 1;
		}
	if ((strncmp(led_en, "ON", 2) == 0) && (strncmp(led_num, "ALL", 3) == 0 ))  //If brightness arg is MAX and lednum arg is ALL
	{
		LED1_EN = LED2_EN = LED3_EN = LED4_EN = 1; //Set all LED's ON
		no_en_value = 1;
		}
	if ((strncmp(led_en, "OFF", 3) == 0) && (strncmp(led_num, "ALL", 3) == 0 ))  //If brightness arg is MAX and lednum arg is ALL
	{
		LED1_EN = LED2_EN = LED3_EN = LED4_EN = 0; //Set all LED's OFF
		no_en_value = 1;
		}
		
	switch(no_lednum_value) 
		{
		case 0:
		char2int(led_num, &led_num_int);
		if ((led_num_int <= 0) || (led_num_int > 4)) //If lednum less than 0 or mire than 4 
			{ 
				error = 1; //error
				printf("Wrong LED number value \n\r");
			}
		break;
		case 1:
		break;
			default:
		break;
		}		

	switch(no_en_value) 
		{
		case 0:
		old_led_en_value = led_en_int;
		char2int(led_en, &led_en_int);
				if ((led_en_int != 0) && (led_en_int != 1)) //If EN values is not 0 or 1
			{ 
				error = 1; //error
				led_en_int = old_led_en_value;
				printf("Wrong EN value \n\r");
			}
		break;
		case 1:
		break;
			default:
		break;
		}
	 
		//increment\decrement if LEDNUM is not ALL
	if (strncmp(led_pwm, "+1", 2) == 0 && (strncmp(led_num, "ALL", 3) != 0 ))  //
	{
		led_pwm_int = LED_ValuebyNum(led_num_int) + 10;
		no_pwm_value = 2;
	
		}
	if (strncmp(led_pwm, "+2", 2) == 0 && (strncmp(led_num, "ALL", 3) != 0 ))
	{		
		led_pwm_int = LED_ValuebyNum(led_num_int) + 100;
		no_pwm_value = 2;
		
		}
	if (strncmp(led_pwm, "+3", 2) == 0 && (strncmp(led_num, "ALL", 3) != 0 ))
	{
		led_pwm_int = LED_ValuebyNum(led_num_int) + 1000;
		no_pwm_value = 2;
		
		}
	if (strncmp(led_pwm, "+4", 2) == 0 && (strncmp(led_num, "ALL", 3) != 0 ))
	{
		led_pwm_int = LED_ValuebyNum(led_num_int) + 10000;
		no_pwm_value = 2;
		
		}
	
	if (strncmp(led_pwm, "-1", 2) == 0 && (strncmp(led_num, "ALL", 3) != 0 ))
	{
		led_pwm_int = LED_ValuebyNum(led_num_int) - 10;
		no_pwm_value = 2;

		}
	if (strncmp(led_pwm, "-2", 2) == 0 && (strncmp(led_num, "ALL", 3) != 0 ))
	{		
		led_pwm_int = LED_ValuebyNum(led_num_int) - 100;
		no_pwm_value = 2;
		
		}
	if (strncmp(led_pwm, "-3", 2) == 0 && (strncmp(led_num, "ALL", 3) != 0 ))
	{
		led_pwm_int = LED_ValuebyNum(led_num_int) - 1000;
		no_pwm_value = 2;
		
		}
	if (strncmp(led_pwm, "-4", 2) == 0 && (strncmp(led_num, "ALL", 3) != 0 ))
	{
		led_pwm_int = LED_ValuebyNum(led_num_int) - 10000;
		no_pwm_value = 2;
		
		}
	
		
		
	switch(no_pwm_value) 
		{
		case 0:
		old_led_pwm_value = led_pwm_int;
		char2int(led_pwm, &led_pwm_int); //If PWM value greater than 65535 and less or equals zero 
		//if ((led_pwm_int >= 65535) || (led_pwm_int == NULL)) //FIX
		if (led_pwm_int >= 65535) //FIX
			{ 
				error = 1; //error
				led_pwm_int = old_led_pwm_value;
				printf("Wrong PWM value \n\r");
			}
		break;
		case 1:
		break;
		case 2:
		break;
			default:
		break;
		}

	switch (led_num_int) //Process argument values
	{
		case 1:
				if ((no_pwm_value != 1) && (led_pwm_int != NULL)) { //If no text value and value is not null
				LED1_VALUE = led_pwm_int; //PWM value is argument variable
					}
		if (no_en_value == 0) { //If no text value and value is not null
			LED1_EN = led_en_int; //EN value is argument variable
			}
		break;
		case 2:
					if ((no_pwm_value != 1) && (led_pwm_int != NULL)) { //If no text value and value is not null
				LED2_VALUE = led_pwm_int; //PWM value is argument variable
					}
			if (no_en_value == 0) { //If no text value and value is not null
			LED2_EN = led_en_int; //EN value is argument variable
			}
		break;
		case 3:
					if ((no_pwm_value != 1) && (led_pwm_int != NULL)) { //If no text value and value is not null
				LED3_VALUE = led_pwm_int; //PWM value is argument variable
					}
		if (no_en_value == 0) { //If no text value and value is not null
			LED3_EN = led_en_int; //EN value is argument variable
			}
		break;
		case 4:
					if ((no_pwm_value != 1) && (led_pwm_int != NULL)) { //If no text value and value is not null
				LED4_VALUE = led_pwm_int; //PWM value is argument variable
					}
		if (no_en_value == 0) { //If no text value and value is not null
			LED4_EN = led_en_int; //EN value is argument variable
			}
		break;
		case 228: //set same parameters for ALL LED's
			
			//increment\decrement if for ALL
	if (strncmp(led_pwm, "+1", 2) == 0)  //
	{
		LED1_VALUE = LED_ValuebyNum(1) + 10;
		LED2_VALUE = LED_ValuebyNum(2) + 10;
		LED3_VALUE = LED_ValuebyNum(3) + 10;
		LED4_VALUE = LED_ValuebyNum(4) + 10;
		no_pwm_value = 2;
	
		}
	if (strncmp(led_pwm, "+2", 2) == 0)  //
	{		
		LED1_VALUE = LED_ValuebyNum(1) + 100;
		LED2_VALUE = LED_ValuebyNum(2) + 100;
		LED3_VALUE = LED_ValuebyNum(3) + 100;
		LED4_VALUE = LED_ValuebyNum(4) + 100;
		no_pwm_value = 2;
		
		}
	if (strncmp(led_pwm, "+3", 2) == 0)  //
	{
		LED1_VALUE = LED_ValuebyNum(1) + 1000;
		LED2_VALUE = LED_ValuebyNum(2) + 1000;
		LED3_VALUE = LED_ValuebyNum(3) + 1000;
		LED4_VALUE = LED_ValuebyNum(4) + 1000;
		no_pwm_value = 2;
		
		}
	if (strncmp(led_pwm, "+4", 2) == 0)  //
	{
		LED1_VALUE = LED_ValuebyNum(1) + 10000;
		LED2_VALUE = LED_ValuebyNum(2) + 10000;
		LED3_VALUE = LED_ValuebyNum(3) + 10000;
		LED4_VALUE = LED_ValuebyNum(4) + 10000;
		no_pwm_value = 2;
		
		}
	
	if (strncmp(led_pwm, "-1", 2) == 0)  //
	{
		LED1_VALUE = LED_ValuebyNum(1) - 10;
		LED2_VALUE = LED_ValuebyNum(2) - 10;
		LED3_VALUE = LED_ValuebyNum(3) - 10;
		LED4_VALUE = LED_ValuebyNum(4) - 10;
		no_pwm_value = 2;
		
		}
	if (strncmp(led_pwm, "-2", 2) == 0)  //
	{		
		LED1_VALUE = LED_ValuebyNum(1) - 100;
		LED2_VALUE = LED_ValuebyNum(2) - 100;
		LED3_VALUE = LED_ValuebyNum(3) - 100;
		LED4_VALUE = LED_ValuebyNum(4) - 100;
		no_pwm_value = 2;
		
		}
	if (strncmp(led_pwm, "-3", 2) == 0)  //
	{
		LED1_VALUE = LED_ValuebyNum(1) - 1000;
		LED2_VALUE = LED_ValuebyNum(2) - 1000;
		LED3_VALUE = LED_ValuebyNum(3) - 1000;
		LED4_VALUE = LED_ValuebyNum(4) - 1000;
		no_pwm_value = 2;
		
		}
	if (strncmp(led_pwm, "-4", 2) == 0)  //
	{
		//printf("LED1 VALUE BEFORE = %i\n\r", LED1_VALUE); //FIX
		LED1_VALUE = LED_ValuebyNum(1) - 10000;
		LED2_VALUE = LED_ValuebyNum(2) - 10000;
		LED3_VALUE = LED_ValuebyNum(3) - 10000;
		LED4_VALUE = LED_ValuebyNum(4) - 10000;
		no_pwm_value = 2;
		//printf("LED1 VALUE AFTER = %i\n\r", LED1_VALUE); //FIX
		
		}
	
		if ((led_pwm_int != NULL) && (no_pwm_value != 2))
		{
			LED1_VALUE = led_pwm_int;
			LED2_VALUE = led_pwm_int;
			LED3_VALUE = led_pwm_int;
			LED4_VALUE = led_pwm_int;
		}
		if ((led_en_int != NULL && (led_en_int != 2) && ((led_en_int == 0) || (led_en_int == 1)))) //CHECK!
		{
			LED1_EN = led_en_int;
			LED2_EN = led_en_int;
			LED3_EN = led_en_int;
			LED4_EN = led_en_int;
		}
			
		break;
		default:
			printf("Syntax error near LED \n\r");
			error = 1;
break;
	}
	
	LED_SW();
	if(error != 1) {
	printf("OK \n\r");
	}
}


 
int LED_CVAL(int VAL, int CAL, char sign)  //Function for setting corrected PWM values
{	
	int PWM;
		if (sign == '-') {
	PWM = VAL - CAL;
		}
		if (sign == '+') {
	PWM = VAL + CAL;
		}
		if (PWM > 65535) //prevent overflow
		{
			PWM = 65535;
		}
  return PWM;
	}	

void LED_SW() //Set LED's(PM's) parameters
{
	
		//Count PWM values
LED1_PWM = LED_CVAL(LED1_VALUE, LED1_CAL_VALUE, LED1_CAL_SIGN);
LED2_PWM = LED_CVAL(LED2_VALUE, LED2_CAL_VALUE, LED2_CAL_SIGN);
LED3_PWM = LED_CVAL(LED3_VALUE, LED3_CAL_VALUE, LED3_CAL_SIGN);
LED4_PWM = LED_CVAL(LED4_VALUE, LED4_CAL_VALUE, LED4_CAL_SIGN);
	
	  //Set PWM values into TIM4 registers
TIM4->CCR1 = LED1_PWM;
TIM4->CCR2 = LED2_PWM;
TIM4->CCR3 = LED3_PWM;
TIM4->CCR4 = LED4_PWM;
	
	
		//LED1-4 ON\OFF by variables
switch(LED1_EN)
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
	break;
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
	break;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
	default:
break;
}


switch(LED2_EN)
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
	break;
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	break;
//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	default:
break;
}


switch(LED3_EN)
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	break;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	break;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
	default:
break;
}


switch(LED4_EN)
{
	case 1:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	break;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
	case 0:
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	break;
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
	default:
break;
}
	}
