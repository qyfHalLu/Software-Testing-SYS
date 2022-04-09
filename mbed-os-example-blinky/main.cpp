/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define FREQUENCY 2000
#define INTERVAL 2000000

DigitalOut redLed(PTC12);

/* Generate pulse signal for INTERVAL microseconds */
void do_pwm(int duty)
{ 
    int step = 1000000 / FREQUENCY;

    for (int elapsed = 0; elapsed < INTERVAL; elapsed += step) {
        // compute duty times
        int on_time = step * duty / 100;
        int off_time = step * (100 - duty) / 100;

        redLed = 1;
        wait_us(on_time);
        redLed = 0;
        wait_us(off_time);
    }
}

int main()
{
    int duty;

    // sweep PWM from 10% to 90%
    for (duty = 10; duty < 90; duty += 10)
        do_pwm(duty);

    // run forever
    while(true)
        do_pwm(duty);
}
