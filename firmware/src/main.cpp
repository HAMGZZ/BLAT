/*
 * BLAT! Commodore OEM Bi-model muffler actuator
 * Lewis Hamilton September 2021
 * 
 * Version 1.0.1:
 * - Added pin direction & tuned delay times
 * 
 * Version 1.0.0-alpha:
 * - Initial release
*/

#include <Arduino.h>

#define PWM_OUT 2
#define LED     3
#define STATE   1

#define LONG_TIME       3989    // 4 miliseconds for 80% on or off
#define SHORT_TIME      988     // 1 milisecond for 20% on or off

int main()
{
    long int ton;
    long int toff;
    pinMode(STATE, INPUT_PULLUP);
    pinMode(PWM_OUT, OUTPUT);
    pinMode(LED, OUTPUT);

    while(1)
    {
        if(((digitalRead(STATE))))
        {
            digitalWrite(LED, HIGH);
            ton = LONG_TIME;
            toff = SHORT_TIME;
        }
        else if((!digitalRead(STATE)))
        {
            digitalWrite(LED, LOW);
            ton = SHORT_TIME;
            toff = LONG_TIME;
        }

        digitalWrite(PWM_OUT, HIGH);
        delayMicroseconds(ton);
        digitalWrite(PWM_OUT, LOW);
        delayMicroseconds(toff);

    }
    return 0;
}
