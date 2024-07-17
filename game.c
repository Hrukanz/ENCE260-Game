/*  
    Filename: game.c
    Author: Tim Lindbom (tli89) & Haruka Yamamoto (hya73)
    Date: 17/10/22
    Description: Game file while main game loop
*/

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "missile.h"
#include "map.h"
#include "button.h"
#include "selection.h"
#include "led_display.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#include <stdint.h>
#include <stdbool.h>

#define MESSAGE_RATE 30
#define PACER_RATE 1000


int main(void)
{   
    /* intialise necessary modules */
    system_init ();
    button_init();
    navswitch_init ();
    display_initialise();
    pacer_init (PACER_RATE);
    ir_uart_init ();
    button_init();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    uint8_t ship_index;
    uint8_t score = 0;
    bool got_ship = false;
    char win;

    static uint8_t hit[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    static uint8_t miss[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

    tinygl_text("START \0");
    bool waiting_start = true;
    while (waiting_start) { // waiting to start game
        pacer_wait();
        tinygl_update();

        if (button_pressed_p()) {
            waiting_start = false;
        }
    }

    /* sending and receiving ships*/

    uint8_t my_ship = select_ship();
    ir_uart_putc (my_ship);
    while (!got_ship) {
        if (ir_uart_read_ready_p ()) {
            ship_index = ir_uart_getc();
            got_ship = true;
    
        }
    }

    wipe_display();

    uint8_t* enemy_ship = fleet[ship_index];

    /* main loop of game */
    while(1) {
        
        uint8_t* coords = aim(hit, miss) ;
        bool hit_miss = shoot(enemy_ship, coords[0], coords[1]);
        

        // if/else statement to add the shot to the correctly corresponding bitmap 
        if (hit_miss) {
            hit[coords[1]] = (hit[coords[1]] | (1 << coords[0]));
            score++;
        }
        
        miss[coords[1]] = (miss[coords[1]] | (1 << coords[0]));

       if (score == 15) { // win condition
            tinygl_text("WINNER\0");
            win = 'f';
            ir_uart_putc (win);
            while(1)
            {
                pacer_wait();
        
                tinygl_update();   
            }
       }

        if (ir_uart_read_ready_p ()) {
            if (ir_uart_getc () == 'f') {
                tinygl_text("LOSER\0");
                while (1) { // lose condition
                    pacer_wait();

                    tinygl_update();
                }
            }
        }
    }
}

