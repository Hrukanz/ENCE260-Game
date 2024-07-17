/*
    Filename: missile.c
    Author: Tim Lindbom (tli89) & Haruka Yamamoto (hya73)
    Date: 17/10/22
    Description: Module containing the aiming and shooting aspect of game
*/

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "led.h"
#include "missile.h"
#include "map.h"
#include "button.h"
#include "led_display.h"
#include <avr/io.h>

#include <stdbool.h>
#include <stdint.h>

void wait(uint8_t freq) {

    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;

    uint16_t stop = freq * (500/0.128);

    TCNT1 = 0;
    while(TCNT1 < stop){
        continue;
    }

}

/** 
    Used to aim shots on led display
    @param pointer to bitmap of hits
    @param pointer to bitmap of misses
    @returns coords of aimed shot
*/
uint8_t* aim(uint8_t* hit, uint8_t* miss) {


    uint8_t vertical = 3;
    uint8_t horizontal = 2;

    static uint8_t coords[2];
    uint8_t map_view = false;
    bool shot = false;

    /** loop updating coords using navswitch updates */
    while(shot == false) {

        navswitch_update ();

        display_pixel((vertical % 7), (horizontal % 5));

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            vertical--;
        }   
        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            vertical++;
        }
        if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            horizontal++;
        }
        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            horizontal--;
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            shot = true;
        }     

        /** toggle show_map while aiming if button pressed */
        if ((button_pressed_p()) && (map_view == false)) { 
                        
            map_view = !map_view;
            wipe_display();
            show_map(hit, miss, map_view);
            wait(1);
        }

    }

    coords[0] = (vertical % 7);
    coords[1] = (horizontal % 5);
    return coords;
}

/**
    Used to shoot previously aimed shot
    @param pointer to enemy ship bitmap
    @param shot vertical coord
    @param shot horizontal coord
    @returns boolean of hit
*/
bool shoot(uint8_t* ship, uint8_t vertical, uint8_t horizontal)
{

    bool hit = false;
    
    if ((ship[horizontal] | (1 << vertical)) == ship[horizontal])
    {
        hit = true;
    }
    
    if (hit) {
        
        ship[horizontal] = ship[horizontal] & ~(1<<vertical); // removes pixel from the bitmap if the shot has hit the ship

        pio_output_high (LED_PIO);
        wait(1);
    
        pio_output_low(LED_PIO);

    } 

    return hit;
}
