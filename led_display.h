/*
    Filename: led_display.h
    Author: Tim Lindbom (tli89) & Haruka Yamamoto (hya73)
    Date: 17/10/22
    Description: Header file for led_display module used to manipulate the led display
*/


#ifndef DISPLAY_H
#define DISPLAY_H

#include "system.h"
#include "pio.h"
#include <stdint.h>


void display_column (uint8_t, uint8_t);
/* display_column is uded to display the entire ship/pattern on the LED matrix by
being called with an index used to light each column at a time. */

void display_initialise(void);
/* Used to initialise the display matrix */

void wipe_display(void);
/* Used to completly wipe the dispolay matrix clean */

void display_pixel(uint8_t, uint8_t);
/* display_poxel is used to display one pixel at a time, with the to inputs 
being the co-ordinates the pixel is at  */


#endif //DISPLAY_H
