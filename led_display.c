/*  
    Filename: led_display.c
    Author: Tim Lindbom (tli89) & Haruka Yamamoto (hya73)
    Date: 17/10/22
    Description: Module used to manipulate the led display matrix
*/

#include "system.h"
#include "pio.h"
#include <stdint.h>

/** Define PIO pins driving LED matrix rows.  */
const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/** Displays the columns of a given bitmap. */
void display_column (uint8_t row_pattern, uint8_t current_column)
{
    static int prev_col = 0;
    pio_output_high(cols[prev_col]);
    for (uint8_t current_row = 0; current_row < 7; current_row++)
    {
        if ((row_pattern >> current_row) & 1) {
            pio_output_low(rows[current_row]);
        }
         else {
            pio_output_high(rows[current_row]);
        }
    }
    prev_col = current_column;
    pio_output_low(cols[current_column]);
}


void display_initialise(void)
{
    for (uint8_t i = 0; i<5; i++) {
        pio_config_set (cols[i], PIO_OUTPUT_HIGH);
    }

    for (uint8_t i = 0; i<7; i++) {
        pio_config_set (rows[i], PIO_OUTPUT_HIGH);
    }
}

/** Clears display in between functions that
    display something on the led display matrix. */
void wipe_display(void)
{
    for (uint8_t i = 0; i<5; i++) {
        pio_output_high (cols[i]);
    }

    for (uint8_t i = 0; i<7; i++) {
        pio_output_high (rows[i]);
    }
}


void display_pixel(uint8_t vertical, uint8_t horizontal)
{
    wipe_display();

    pio_output_low(rows[vertical]);
    pio_output_low(cols[horizontal]);
}
