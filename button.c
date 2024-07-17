/*  Filename: Button.c
    Author: Tim Lindbom (tli89) & Haruka Yamamoto (hya73)
    Date: 17/10/22
    Description Module used to intialise and press the button 
*/

#include "pio.h"
#include "button.h"

/** Return non-zero if button pressed.  */
int button_pressed_p (void)
{
    return((PIND &(1<<7)) != 0);
}


/** Initialise button1.  */
void button_init (void)
{
    DDRD &= ~(1 << 7);
}

