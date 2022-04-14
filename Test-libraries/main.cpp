#include "mbed.h"
#include "board_freedom.h"

#define PWM_MIN 820
#define PWM_MAX 1700

// 860, 1720
int main()
{
    unsigned int pwm_min = PWM_MIN;

    board_init();
    pwm0.period_ms(20);

    while(true)
    {
        pwm0.pulsewidth_us(pwm_min);
        ThisThread::sleep_for(1s);

        for (int i = 0; i < 100; i++)
        {
            pwm0.pulsewidth_us(pwm_min + i * (PWM_MAX - PWM_MIN) / 100);
            ThisThread::sleep_for(40ms);
        }

        ThisThread::sleep_for(1s);
    }
}