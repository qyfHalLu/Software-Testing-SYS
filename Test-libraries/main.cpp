#include "mbed.h"
#include "board_freedom.h"
// main() runs in its own thread in the OS
int main()
{
    board_init();
    pwm3.write (10);
    pwm3.period_ms(10);
}