/*
    Filename: map.c
    Author: Tim Lindbom (tli89) & Haruka Yamamoto (hya73)
    Date: 17/10/22
    Description: Module used to show and toggle previous shots
*/


#include "system.h"
#include "pio.h"
#include "button.h"
#include "pacer.h"
#include "led.h"
#include "map.h"
#include "timer.h"
#include "led_display.h"
#include "missile.h"


/** Function to display map
    @param pointer to the bitmap of hits
    @param pointer to the bitmap of misses
    @param current state of map_view
    @returns map_view state at the end of the fucntion
*/
bool show_map(uint8_t* hit, uint8_t* miss, bool map_view)
{   

    uint8_t current_column = 0;
    uint16_t button_tick = 0;

    /** while loop to display map until button pressed again */
    while(map_view == true) {

        /** if else statement to flash misses and keep hits solid */
        if(button_tick >= 250) {

            display_column (hit[current_column], current_column);
            pacer_wait();

            wipe_display();

        } else {

            display_column (miss[current_column], current_column);
            pacer_wait();

            wipe_display();
        }

        /** reset ticks to ensure flashing */
        if (button_tick >= 500){
            button_tick = 0;
        }

        button_tick++;
        
        current_column++;
        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }  

        /** check button press and map_view state to end loop and function */
        if((button_pressed_p()) && (map_view == true)) {
            map_view = false;
            wait(1);
            
        } 
    }
    return map_view;
}
