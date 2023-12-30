

#ifndef __Motor_control_H__
#define __Motor_control_H__

#include "bdc_motor.h"
#include "driver/pulse_cnt.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>

typedef struct
{
    bdc_motor_handle_t right_motor;
    bdc_motor_config_t right_motor_config;
    bdc_motor_handle_t left_motor;
    bdc_motor_config_t left_motor_config;
} car_t;

#define BDC_MCPWM_TIMER_RESOLUTION_HZ 10000000                                      // 10MHz, 1 tick = 0.1us
#define BDC_MCPWM_FREQ_HZ 25000                                                     // 25KHz PWM
#define BDC_MCPWM_DUTY_TICK_MAX (BDC_MCPWM_TIMER_RESOLUTION_HZ \ BDC_MCPWM_FREQ_HZ) // maximum value we can set for the duty cycle, in ticks

void motor_init(const bdc_motor_config_t *motor_config, const bdc_motor_mcpwm_config_t *mcpwm_config, bdc_motor_handle_t *motor);

void motor_control_frd(bdc_motor_handle_t motor);

void motor_control_back(bdc_motor_handle_t motor);

void motor_speed_control(bdc_motor_handle_t motor, uint8_t speed);

void car_init(const bdc_motor_mcpwm_config_t *mcpwm_config, car_t *car);

void car_move_frd(car_t car);

void car_move_back(car_t car);

void car_speed_control(car_t car, uint32_t speed);

void car_turn_right(car_t car, uint8_t speed);

void car_turn_left(car_t car, uint8_t speed);

#endif /*__Motor_control_H__*/
