#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLI.h"
#include <stdbool.h>


const char c_return = '\r';
const char n_line = '\n';
const char space_char = ' ';
char parsed_line[200];
char command[20];

char argument1[20];
char argument2[20];
char argument3[20];
char argument4[20];

char *ptr;
char *ptr1;



short parsed_line_length = 0;
short receiveBuffer_length = 0;
short ret_pos;


void ParseCmdString(void);
void CReturnCmd(void);
void substring_cut(void);
void string_wipe(char *stringtowipe);
void SliceCmd(void);
void ClearCmdAndArguments(void);
void GetCommands(void);

void CReturnCmd(void) { 

if(stringComplete == true) //if we got carrier return we know than string is completed
	{ 
		ClearCmdAndArguments(); //wipe parsed strings before writing new data
		printf("\n\r"); //Carrier return + newline, for writing new string
		stringComplete = false; //set flag to false
		ParseCmdString(); //call function which parses received string
	}
	return;
}

void ParseCmdString(void) {
	receiveBuffer_length = strlen(receiveBuffer);
	parsed_line_length = strlen(parsed_line);
	ptr = strrchr(receiveBuffer, '\r'); //find carrier return and replace to null-terminating character
	if (ptr != NULL) {
    //*ptr = ' ';
		*ptr = '\0';
 }
	substring_cut(); //call function which parses received text to command and arguments
	memset(receiveBuffer,0,receiveBuffer_cnt); //clear secondary(global) receive buffer
	return;
}

void substring_cut(void)
{		
		memset(parsed_line,0,parsed_line_length); //clear last received string by measured string length
		strncpy(parsed_line, receiveBuffer, strlen(receiveBuffer)); //copy receivedBuffer content to parsed_line content
		parsed_line_length = strlen(parsed_line); //update parsed_line string length
 		//memset(command,0,sizeof(command)); //clear command string
		//strncpy(command, parsed_line, parsed_line_length + 1); //copy command part of parsed_line
		SliceCmd();
		return;
}


void string_wipe(char *stringtowipe)
{ 
	//char stringtowipe;
	short string_length = ret_pos;
	short i;
	for (i=0; i < string_length; i++)
{
  stringtowipe[i] = 0;
}
	return;;
}

void SliceCmd(void) //function wich provide cutting seperate words to command and her arguments
{
	short tkn_cnt;
	tkn_cnt = 0; //start from zero
	char *token;
	token = strtok(parsed_line, &space_char); //words are separated by space
	//strncpy(command, token, strlen(token) + 1); //copy command part of parsed_line
	//tkn_cnt++; //increment counter
	
		 while( token != NULL && tkn_cnt < 5 ) 
   { 
		 switch(tkn_cnt) //write arguments in separate strings by counter value
	{
		case 0:
		strncpy(command, token, strlen(token) + 1); //copy command part of parsed_line
		case 1:
		strncpy(argument1, token, strlen(token) + 1);
		break;
		case 2:
		strncpy(argument2, token, strlen(token) + 1);
		break;
		case 3:
		strncpy(argument3, token, strlen(token) + 1);
		break;
		case 4:
		strncpy(argument4, token, strlen(token) + 1);
		break;
			default:
break;
	}
	tkn_cnt++; //increment counter
	token = strtok(NULL, &space_char);
   } 
	
	return;
}

void ClearCmdAndArguments(void) //function which clears parsed command and arguments strings
{
	memset(command,0,sizeof(command)); //clear command string
	memset(argument1,0,sizeof(argument1)); //clear argument1 string
	memset(argument2,0,sizeof(argument2)); //clear argument1 string
	memset(argument3,0,sizeof(argument3)); //clear argument1 string
	memset(argument4,0,sizeof(argument4)); //clear argument1 string
	
	return;
}

void GetCommands(void) {
	
	if(strncmp(command, "LED", 3) == 0) {
		
	}
		
}


