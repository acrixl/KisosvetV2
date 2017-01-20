
#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

	//Direct PWM values which used for TIM4 registers
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
int LED1_CAL_VALUE = 10;
int LED2_CAL_VALUE = 10;
int LED3_CAL_VALUE = 10;
int LED4_CAL_VALUE = 10;
	//Values for external logic
int LED1_VALUE = 57020;
int LED2_VALUE = 57020;
int LED3_VALUE = 57020;
int LED4_VALUE = 57020;


int i = 0;
int MAX_PWM = 60400;
int MIN_PWM = 47000;

void char2int(char* pchar, int* pint);
void LED_SW(void);
int LEDnumValue(int);
int LED_CVAL(int VAL, int CAL); 

int LEDnumValue(int lednum)
{
	int value;
	
	if((lednum != 0) && (lednum != NULL)) {
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


void LED_CLI(char *led_num, char *led_en, char *led_pwm)
{
	int led_num_int; //LED number variable
	int led_en_int; //ON\OFF variable
	int led_pwm_int; //OWM value variable
//	char2int(led_num, &led_num_int);
//	char2int(led_en, &led_en_int);
//	char2int(led_pwm, &led_pwm_int);
	short error = 0; //Error flag
	
	short no_en_value = 0; //no convert char to int
	short no_lednum_value = 0; //no convert char to int
	short no_pwm_value = 0; //no convert char to int
	
	if (strncmp(led_num, "ALL", 3) == 0 ) { //Set all LED's ON
		//led_en_int = 1;
		led_num_int = 228;
		no_lednum_value = 1;
		}
	if (strncmp(led_en, "ON", 2) == 0 ) { //Set LED ON
		led_en_int = 1;
		no_en_value = 1;
		}
	if (strncmp(led_en, "OFF", 3) == 0 ) { //Set LED OFF
		led_en_int = 0;
		no_en_value = 1;
		}
	if ((strncmp(led_pwm, "MAX", 3) == 0) && (strncmp(led_num, "ALL", 3) == 0 )) { //If brightness arg is MAX and lednum arg is ALL
		LED1_VALUE = LED2_VALUE = LED3_VALUE = LED4_VALUE = MAX_PWM; //Set all LED's brightness to max
		led_pwm_int = MAX_PWM;
		no_pwm_value = 1;
		}
	if (strncmp(led_pwm, "MAX", 3) == 0) { //Set LED brightness to max
		led_pwm_int = MAX_PWM;
		no_pwm_value = 1;
		}
	if ((strncmp(led_pwm, "MIN", 3) == 0) && (strncmp(led_num, "ALL", 3) == 0 )) { //If brightness arg is MIN and lednum arg is ALL
		LED1_VALUE = LED2_VALUE = LED3_VALUE = LED4_VALUE = MIN_PWM; //Set all LED's brightness to min
		led_pwm_int = MIN_PWM;
		no_pwm_value = 1;
		}
	if (strncmp(led_pwm, "MIN", 3) == 0) { //Set LED brightness to min
		led_pwm_int = MIN_PWM;
		no_pwm_value = 1;
		}
//	if (strncmp(led_pwm, "+", 1) == 0) { //Set LED brightness to min
//		led_pwm_int = LEDnumValue(led_num) + 10;
//		no_pwm_value = 1;
//		}
//	if (strncmp(led_pwm, "++", 2) == 0) { //Set LED brightness to min
//		led_pwm_int = LEDnumValue(led_num) + 100;
//		no_pwm_value = 1;
//		}
//	if (strncmp(led_pwm, "+++", 3) == 0) { //Set LED brightness to min
//		led_pwm_int = LEDnumValue(led_num) + 1000;
//		no_pwm_value = 1;
//		}

switch(no_pwm_value) 
	{
	case 0:
	char2int(led_pwm, &led_pwm_int);
	break;
	case 1:
	break;
		default:
	break;
	}
switch(no_en_value) 
	{
	case 0:
	char2int(led_en, &led_en_int);
	break;
	case 1:
	break;
		default:
	break;
	}
switch(no_lednum_value) 
	{
	case 0:
	char2int(led_num, &led_num_int);
	break;
	case 1:
	break;
		default:
	break;
	}

	switch (led_num_int) //Process argument values
	{
		case 1:
				if ((no_pwm_value == 0) && (led_pwm_int != NULL)) { //If no text value and value is not null
				LED1_VALUE = led_pwm_int; //PWM value is argument variable
					}
		if (no_en_value == 0) { //If no text value and value is not null
			LED1_EN = led_en_int; //EN value is argument variable
			}
		break;
		case 2:
					if ((no_pwm_value == 0) && (led_pwm_int != NULL)) { //If no text value and value is not null
				LED2_VALUE = led_pwm_int; //PWM value is argument variable
					}
			if (no_en_value == 0) { //If no text value and value is not null
			LED2_EN = led_en_int; //EN value is argument variable
			}
		break;
		case 3:
					if ((no_pwm_value == 0) && (led_pwm_int != NULL)) { //If no text value and value is not null
				LED3_VALUE = led_pwm_int; //PWM value is argument variable
					}
		if (no_en_value == 0) { //If no text value and value is not null
			LED3_EN = led_en_int; //EN value is argument variable
			}
		break;
		case 4:
					if ((no_pwm_value == 0) && (led_pwm_int != NULL)) { //If no text value and value is not null
				LED4_VALUE = led_pwm_int; //PWM value is argument variable
					}
		if (no_en_value == 0) { //If no text value and value is not null
			LED4_EN = led_en_int; //EN value is argument variable
			}
		break;
		case 228: //set same parameters for ALL LED's
			LED1_VALUE = led_pwm_int;
			LED1_EN = led_en_int;
			LED2_VALUE = led_pwm_int;
			LED2_EN = led_en_int;
			LED3_VALUE = led_pwm_int;
			LED3_EN = led_en_int;
			LED4_VALUE = led_pwm_int;
			LED4_EN = led_en_int;
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


 
int LED_CVAL(int VAL, int CAL)  //Function for setting corrected PWM values
{	
	int PWM = VAL - CAL;
  return PWM;
	}	

void LED_SW() //Set LED's(PM's) on or off by variable values
{
	
		//Count PWM values
LED1_PWM = LED_CVAL(LED1_VALUE, LED1_CAL_VALUE);
LED2_PWM = LED_CVAL(LED2_VALUE, LED2_CAL_VALUE);
LED3_PWM = LED_CVAL(LED3_VALUE, LED3_CAL_VALUE);
LED4_PWM = LED_CVAL(LED4_VALUE, LED4_CAL_VALUE);
	
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
