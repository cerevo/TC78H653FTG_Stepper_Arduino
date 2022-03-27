// Licensed under the BSD-3-Cluause license. See LICENSE file in the project root for full license information.
// This sample is for Arduino UNO. See readme as well all our blog post for implementation detail.

#include <Arduino.h>
#include "TC78H653FTG.h"

// Pin config
#define STEPPER_PWM_PIN1 9
#define STEPPER_PIN2 2
#define STEPPER_PWM_PIN3 10
#define STEPPER_PIN4 4

// Step timer setting
#define STEPPER_TIMER_MS 2

bool led_state = false;

uint32_t direction_timer = 0;
#define DIRECTION_CHANGE_PERIOD_MS 2000

TC78H653FTG stepper(STEPPER_PWM_PIN1, STEPPER_PIN2, STEPPER_PWM_PIN3, STEPPER_PIN4, MICROSTEP64);

void setup()
{
    // set PWM freq to 62745.10 Hz for the PIN 9 and 10
    TCCR1B = (TCCR1B & B11111000) | (1 << CS10);
    Serial.begin(9600);

    stepper.init();
    Serial.println("TC78H653FTG driver sample");
    pinMode(LED_BUILTIN, OUTPUT);
    stepper.direction = STEPPER_REVERSE;
}


void loop()
{
    static bool stepperState = false;

    digitalWrite(LED_BUILTIN, stepperState);
    stepperState = !stepperState;
    
    // You need call tick() to move the stepper forward
    stepper.tick();

    if(millis() - direction_timer > DIRECTION_CHANGE_PERIOD_MS)
    {
        direction_timer = millis();
        if(stepper.direction == STEPPER_FORWARD)
        {
            stepper.direction = STEPPER_REVERSE;
        }
        else
        {
            stepper.direction = STEPPER_FORWARD;
        }
    }
    
    delay(STEPPER_TIMER_MS);
}
