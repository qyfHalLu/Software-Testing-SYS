#include "mbed.h"
#include <stdio.h>
#include <string>
#include <string.h>
#include "board_freedom.h"
#include "adc.h"
#include "oled_ssd1322.h"

using namespace std;


// TODO: Don't forget mbed_app.json!!!


int main()
{
    double voltage;
    double temp;
    string temps;
    board_init();
    PwmOut heater_power(PTC2);
    DigitalOut redLed(PTB2);
    DigitalOut greenLed(PTB3);

    heater_power = 0;

    u8g2_ClearBuffer(&oled);

    // Ensure a font is set (only required once)
    u8g2_SetFont(&oled, u8g2_font_nokiafc22_tr);

    // Draw text to the screen
    u8g2_int_t x = 30;
    u8g2_int_t y = 20;
    char heater[] = "heater is OFF";
    string message = "Temperature: ";
    while (true) {
        u8g2_ClearBuffer(&oled);
        uint16_t analog_in_value = adc_read(0);

        // Convert 16 bit value to voltage and temperature.
        voltage = analog_in_value * 3 / 65535.0;
        temp = (voltage * 1000 - 400) / 19.5;
        temps = to_string(temp);
        message = "Temperature: " + to_string(temp);

        if (analog_in_value < 5000){
            greenLed = 0;
            redLed = 0;
            message = "No sensor detected.";
            heater_power = 0;
            strcpy(heater, "heater is OFF");
        }
        else{
            if(temp <= 30){
                heater_power = 1;
                greenLed = 0;
                redLed = 1;
                strcpy(heater, "heater is ON");
            }
            else if(temp > 30 && temp <= 34){
                heater_power = 1;
                greenLed = 1;
                redLed = 0;
                strcpy(heater, "heater is ON");
            }
            else if(temp > 34 && temp < 35){
                heater_power = 0;
                greenLed = 1;
                redLed = 0;
                strcpy(heater, "heater is OFF");
            }
            else if(temp >= 35){
                heater_power = 0;
                greenLed = 0;
                redLed = 0;
                strcpy(heater, "heater is OFF");
            }
            else{
                heater_power = 0;
                greenLed = 0;
                redLed = 0;
                strcpy(heater, "heater is OFF");
            }
        }


        char char_array[message.length() + 1];
        strcpy(char_array, message.c_str());
        u8g2_DrawUTF8(&oled, x, y, char_array);

        u8g2_int_t x2 = 30;
        u8g2_int_t y2 = 40;
        u8g2_DrawUTF8(&oled, x2, y2, heater);
        // Put all the changes in the buffer onto the screen.
        u8g2_SendBuffer(&oled);


        printf("Temperature is - %i\n", analog_in_value);

        ThisThread::sleep_for(1000ms);
    }

    // ThisThread::sleep_for(200s);
    // pwm1.write(0.1);
    // pwm1.period_ms(10);
}
