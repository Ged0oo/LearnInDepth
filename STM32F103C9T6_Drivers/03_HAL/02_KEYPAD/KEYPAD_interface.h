/* 
 * File:   KEYPAD_INTERFACE.h
 * Author: Mohamed_Nagy
 * https://github.com/Ged0oo 
 * https://www.linkedin.com/in/mohamednagyofficial/
 * Created on January 30, 2024, 8:41 PM
 */

#ifndef __KEYPAD_INTERFACE_H__
#define __KEYPAD_INTERFACE_H__

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "KEYPAD_config.h"

#define 		NOTPRESSED 				0xff
#define 		KEYPAD_ROWS    			4
#define 		KEYPAD_COLUMNS 			4

typedef struct
{
	GPIO_ConfigType row_pin[KEYPAD_ROWS];
	GPIO_ConfigType column_pin[KEYPAD_COLUMNS];
}ST_Keypad_t;

void keypad_initialize(ST_Keypad_t *_keypad_obj);
void keypad_get_value(ST_Keypad_t *_keypad_obj, uint8 *value);
char read_keypad(ST_Keypad_t *_keypad_obj);

#endif
