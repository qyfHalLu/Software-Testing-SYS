#include "mbed.h"
#include "board_freedom.h"
#include "oled_ssd1322.h"
#include "keypad.h"
#include <cstdio>
  //smart-home
// main() runs in its own thread in the OS
int main()
{

    DigitalOut Garden_Lamp(PTB18);
    DigitalOut Garage_Door (PTB11);
    DigitalIn  Car_Sensor(PTE25);
    // DigitalOut Fan (PTC12);
    DigitalOut Door (PTE24);
    DigitalOut Curtains (PTC7);
    // DigitalIn Light_Sensor ();

    pwm0.write (0.5); // lamp
    pwm0.period_ms(10);
    pwm1.write (0.5); // garage
    pwm1.period_ms(10);
    pwm2.write (0.5); // car
    pwm2.period_ms(10);
    // pwm3.write(0.5); // heater on
    // pwm3.period_ms(10);


    // if(keypad_get_key()==1){
    Garden_Lamp = 1;
    Curtains = 1;
    ThisThread::sleep_for(5s);
    Curtains = 0;
    ThisThread::sleep_for(5s);
    Door = 1;
    ThisThread::sleep_for(5s);
    Door = 0;
}