// Licensed under the BSD-3-Cluause license. See LICENSE file in the project root for full license information.
/**
 * \class TC78H653FTG
 * \brief   Driver for TC78H653FTG
 * @file    TC78H653FTG.h
 * @author  Yuske Goto / Cerevo Inc
 * @version V0.1
 * @date    2022/3/5
 * @brief   Header file for TC78H653FTG.cpp module
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

#ifndef _TC78H653FTG_H_
#define _TC78H653FTG_H_

enum MICROSTEP_TYPE
{
    MICROSTEP8 = 8,
    MICROSTEP16 = 16,
    MICROSTEP32 = 32,
    MICROSTEP64 = 64,
    MICROSTEP128 = 128,
    MICROSTEP256 = 256,
    MICROSTEP512 = 512
};
enum STEPPER_DIRECTION
{
    STEPPER_FORWARD = 1,
    STEPPER_REVERSE = -1
};

#define USE_MASTER_STEP_PATTERN
#define OFFSET 0.55

#include <Arduino.h>

class TC78H653FTG
{
public:
    TC78H653FTG(uint8_t pin1_PWM, uint8_t pin2, uint8_t pin3_PWM, uint8_t pin4, MICROSTEP_TYPE microStep); // Initializer
    ~TC78H653FTG();
    // Resetting the driver several times causes the chips to halt
    void init();
    void tick();
    STEPPER_DIRECTION direction;

    uint8_t _pin1_pwm, _pin2, _pin3_pwm, _pin4;
    int16_t counter;

private:
    MICROSTEP_TYPE micro_step_type;
    uint16_t micro_step_count;

    float get_step_pattern(uint16_t current_step);

    uint8_t bit_shift_size;

#ifdef USE_MASTER_STEP_PATTERN
    float STEP_SETTING_MASTER[9] = {0.55, 0.7, 0.75, 0.825, 0.875, 0.925, 0.95, 0.975, 1.0};
    // float STEP_SETTING_MASTER[9] = {0.5f, 0.6f, 0.7f, 0.75f, 0.8f, 0.85f, 0.9f, 0.95f, 1.0f};
#else
    float radian_one_step;
#endif // USE_MASTER_STEP_PATTERN


};

#endif // _TC78H653FTG_H_