#include <xc.h>
#include <stdio.h>
#include "lcd.h"

#define _XTAL_FREQ 20000000  // 20 MHz oscillator
#define TRIG RD0
#define ECHO RD1

#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = ON
#pragma config LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF

void initialize();
unsigned int measure_distance();
void display_distance(unsigned int distance);

void main() {
    initialize();
    while (1) {
        unsigned int distance = measure_distance();
        display_distance(distance);
        __delay_ms(500);
    }
}

void initialize() {
    TRISD0 = 0;  // RD0 as output
    TRISD1 = 1;  // RD1 as input
    lcd_init();
    lcd_clear();
    lcd_set_cursor(1, 1);
    lcd_write_string("Distance:");
}

unsigned int measure_distance() {
    unsigned int time;
    unsigned int distance;
    unsigned int timeout;
    unsigned int max_timeout = 60000;  // adjust as needed

    // Trigger the ultrasonic pulse
    TRIG = 1;
    __delay_us(10);
    TRIG = 0;

    // Wait for echo to go high with timeout protection
    timeout = 0;
    while (!ECHO && timeout < max_timeout) {
         timeout++;
    }
    if(timeout >= max_timeout) {
         return 0;  // timeout waiting for echo high
    }

    // Start Timer1 when echo becomes high
    TMR1 = 0;
    T1CON = 0x10;  // start Timer1
    timeout = 0;
    // Wait for echo to go low with timeout protection
    while (ECHO && timeout < max_timeout) {
         timeout++;
    }
    T1CON = 0x00;  // stop Timer1
    time = TMR1;

    // Calculate distance using integer arithmetic: distance in cm = (time * 343) / 20000
    distance = (time * 343) / 20000;
    return distance;
}

void display_distance(unsigned int distance) {
    char buffer[16];
    sprintf(buffer, "%u cm", distance);
    lcd_set_cursor(1, 10);
    lcd_write_string(buffer);
}
