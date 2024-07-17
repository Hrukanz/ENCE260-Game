/*
    Filename: missile.h
    Author: Tim Lindbom (tli89) & Haruka Yamamoto (hya73)
    Date: 17/10/22
    Description: Header file for module used to aim and shoot
*/

#ifndef MISSLE_H
#define MISSLE_H

#define LED_PIO PIO_DEFINE (PORT_C, 2)



uint8_t* aim(uint8_t*, uint8_t*);

/* the aim functio sets one LED on the matrix to high. The user can use the nav switch to
 move the single LED around the matrix to select where they want to shoot.
 Once the user has made their shot by clicking the navswitch in the function will
 return an array containing the coords of their shot*/


bool shoot(uint8_t*, uint8_t, uint8_t);

/* the shoot function takes in 3 variables, a pointer to the bit map of the enemy ship,
the horizontal value and the vetical value of the shot the was made in the aim function.
If the shot did hit the ship, the hit counter will increment by one and the pixel that was
shot will be removed from the bitmap (to prevent another shot in the same location counting
toward the hit score). */


void wait(uint8_t);
/* wait takes an input of a uint8 which is used to wait at the specified frequncy. */

#endif // MISSLE_H
