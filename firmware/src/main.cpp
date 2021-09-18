/*
 * BLAT! Commodore OEM Bi-model muffler actuator
 * Lewis Hamilton September 2021
 * Version 1.1.0
 * 
 * Change log:
 * Version 1.1.1:
 * - Added pin directions
 * 
 * Version 1.1.0:
 * - Added a delay so the valved could only be closed/opened after 1.5 seconds of previous change.
 * - Added defines for variables that might need to be changed
 * 
 * Version 1.0.0-alpha:
 * - Initial release
*/

#include <Arduino.h>

#define PWM_OUT 2
#define LED     3
#define STATE   1

#define CHANGE_DELAY    100
#define TURN_ON_DELAY   1000
#define LONG_TIME       3995    // 4 miliseconds for 80% on or off
#define SHORT_TIME      995     // 1 milisecond for 20% on or off

int main()
{
    long int counter1 = 0;  // Turn on open delay
    long int counter2 = 0;  // Change delay -- no recent changes so set this high
    long int ton;
    long int toff;
    bool currentlyOpen = false;
    pinMode(STATE, INPUT_PULLUP);
    pinMode(PWM_OUT, OUTPUT);
    pinMode(LED, OUTPUT);

    while(1)
    {
        if(((digitalRead(STATE) || counter1 <= TURN_ON_DELAY) && !currentlyOpen) && !counter2)
        {
            digitalWrite(LED, HIGH);
            ton = LONG_TIME;
            toff = SHORT_TIME;
            counter2 = CHANGE_DELAY;
            currentlyOpen = true;
        }
        else if((!digitalRead(STATE) && currentlyOpen) && !counter2)
        {
            digitalWrite(LED, LOW);
            ton = SHORT_TIME;
            toff = LONG_TIME;
            counter2 = CHANGE_DELAY;
            currentlyOpen = false;
        }

        digitalWrite(PWM_OUT, HIGH);
        delayMicroseconds(ton);
        digitalWrite(PWM_OUT, LOW);
        delayMicroseconds(toff);


        if(counter1 <= TURN_ON_DELAY)
        {
            counter1++;
        }
        if(counter2)
        {
            counter2--;
        }

    }
    return 0;
}
