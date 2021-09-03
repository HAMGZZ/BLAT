/*
 * BLAT! Commodore OEM Bi-model muffler actuator
 * Lewis Hamilton September 2021
 * Version 1.0.0-alpha
*/

#include <Arduino.h>
#define PWM_OUT 2
#define LED 3
#define STATE 1

int main()
{
    long int counter1 = 0;  // Turn on open delay
    long int ton;
    long int toff;

    while(1)
    {
        if(digitalRead(STATE) || counter1 <= 1000)
        {
            digitalWrite(LED, HIGH);
            ton = 3995;
            toff = 995;
        }
        else
        {
            digitalWrite(LED, LOW);
            ton = 995;
            toff = 3995;
        }

        digitalWrite(PWM_OUT, HIGH);
        delayMicroseconds(ton);
        digitalWrite(PWM_OUT, LOW);
        delayMicroseconds(toff);
        if(counter1 <= 1000)
        {
            counter1++;
        }

    }
    return 0;
}
