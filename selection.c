/*
    Filename: selection.c
    Author: Tim Lindbom (tli89) & Haruka Yamamoto (hya73)
    Date: 17/10/22
    Description: Module used to select ship
*/

#include <stdbool.h>
#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "selection.h"
#include "led_display.h"
#include "display.h"

/** Used to select ship at start of game.
    @returns chosen ship index within fleet array
*/
uint8_t select_ship (void)
{
    uint8_t current_column = 0;
    uint8_t mothership = 0;
    


    while (1)
    {
        navswitch_update ();
        pacer_wait ();


            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                mothership++;

            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                mothership--;
            }

            display_column (fleet[(mothership % 10)][current_column], current_column);

            current_column++;
            if (current_column > (LEDMAT_COLS_NUM - 1))
            {
                current_column = 0;
            }           

            if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                return (mothership % 10);
            }
    }   
}
