// Licensed under the BSD-3-Cluause license. See LICENSE file in the project root for full license information.
/**
 * \class TC78H653FTG
 * \brief   Driver for TC78H653FTG
 * @file    TC78H653FTG.cpp
 * @author  Yuske Goto / Cerevo Inc
 * @version V0.1
 * @date    2022/3/5
 * @brief   C++ project file for TC78H653FTG.cpp module
 *
 * \par Description
 * This file is stepper motor driver for TC78H653FTG double H-bridge module.
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Yuske Goto         2022/2/28        0.1             Implemented Constant speed control
 * </pre>
 *
 */

#include "TC78H653FTG.h"

TC78H653FTG::TC78H653FTG(uint8_t pin1_PWM, uint8_t pin2, uint8_t pin3_PWM, uint8_t pin4, MICROSTEP_TYPE microStep) : _pin1_pwm(pin1_PWM), _pin2(pin2),
                                                                                               _pin3_pwm(pin3_PWM), _pin4(pin4), micro_step_type(microStep)
{
    micro_step_count = (uint16_t) micro_step_type;
    bit_shift_size = log(micro_step_count) / log(2); // log base 
    direction = STEPPER_FORWARD;
    counter = 0;

#ifndef USE_MASTER_STEP_PATTERN
    radian_one_step = M_PI / 8.0;
#endif
}

TC78H653FTG::~TC78H653FTG()
{}

void TC78H653FTG::init()
{
    pinMode(_pin1_pwm, OUTPUT);
    pinMode(_pin2, OUTPUT);
    pinMode(_pin3_pwm, OUTPUT);
    pinMode(_pin4, OUTPUT);
}

float TC78H653FTG::get_step_pattern(uint16_t current_step)
{
#ifdef USE_MASTER_STEP_PATTERN
    uint16_t interpolate_width = micro_step_count >> 3; // 8;
    uint16_t interpolate_location = current_step % interpolate_width;
    float master_value = STEP_SETTING_MASTER[current_step / interpolate_width];
    float master_value_next;
    if (current_step != micro_step_count)
        master_value_next = STEP_SETTING_MASTER[(current_step / interpolate_width) + 1];
    else
        master_value_next = STEP_SETTING_MASTER[8];
    return master_value + (master_value_next - master_value) * interpolate_location / interpolate_width;
#else // USE_VECTOR_STEP_PATTERN

        float delta = radian_one_step * (float)current_step / (float)micro_step_count;
    // float step_value = OFFSET + (1.0f - OFFSET) * pow((float)current_step / (float)micro_step_count, 2); // constant vector size transition
        // float step_value = OFFSET + (1.0f - OFFSET) * (sin(delta) / sin(radian_one_step)) * 0.8;
        float step_value = OFFSET + (1.0f - OFFSET) * sin(delta) / sin(radian_one_step);
        return step_value;
#endif
}

// Callback function for stepper motor
void TC78H653FTG::tick()
{
    uint8_t stepper_pin4_state = (counter >> (bit_shift_size + 1)) & 1;
    uint8_t stepper_pin2_state = (counter >> bit_shift_size) & 1;
    stepper_pin2_state = stepper_pin4_state ? stepper_pin2_state : !stepper_pin2_state;

    uint16_t counter_cycle = counter & (micro_step_count - 1);
    // float stepper_pin1_pwm = (counter >> bit_shift_size) & 1 ? get_step_pattern(1 + counter_cycle) : get_step_pattern(micro_step_count - 1 - counter_cycle);
    // float stepper_pin3_pwm = (counter >> bit_shift_size) & 1 ? get_step_pattern(micro_step_count - 1 - counter_cycle) : get_step_pattern(1 + counter_cycle);
    float stepper_pin1_pwm;
    float stepper_pin3_pwm;
    if(direction == STEPPER_FORWARD)
    {
        stepper_pin1_pwm = (counter >> bit_shift_size) & 1 ? get_step_pattern(1 + counter_cycle) : get_step_pattern(micro_step_count - 1 - counter_cycle);
        stepper_pin3_pwm = (counter >> bit_shift_size) & 1 ? get_step_pattern(micro_step_count - 1 - counter_cycle) : get_step_pattern(1 + counter_cycle);
    }
    else
    {
        stepper_pin1_pwm = (counter >> bit_shift_size) & 1 ? get_step_pattern(counter_cycle) : get_step_pattern(micro_step_count - counter_cycle);
        stepper_pin3_pwm = (counter >> bit_shift_size) & 1 ? get_step_pattern(micro_step_count - counter_cycle) : get_step_pattern(counter_cycle);
    }
    stepper_pin1_pwm *= 255;
    stepper_pin3_pwm *= 255;

    analogWrite(_pin1_pwm, (int)stepper_pin1_pwm);
    analogWrite(_pin3_pwm, (int)stepper_pin3_pwm);    
    digitalWrite(_pin2, stepper_pin2_state);
    digitalWrite(_pin4, stepper_pin4_state);

    // char serialBuf[32];
    // snprintf(serialBuf, 32, "%d %d %d %d %d %d %d", counter, bit_shift_size, counter_cycle, (int)stepper_pin1_pwm, stepper_pin2_state, (int)stepper_pin3_pwm, stepper_pin4_state);
    // Serial.println(serialBuf);

    // counting up / down according to counting direction
    counter += (int16_t) direction;
    // check for rollover
    counter = counter == (micro_step_count << 2) ? 0 : counter == -1 ? ((micro_step_count << 2) - 1) : counter;
    // counter = counter == ((micro_step_count << 2) - 1) ? 0 : counter + 1;
}
