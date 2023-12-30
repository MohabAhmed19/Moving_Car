
#include "Motor_control.h"

void motor_init(const bdc_motor_config_t *motor_config, const bdc_motor_mcpwm_config_t *mcpwm_config, bdc_motor_handle_t *motor)
{
    bdc_motor_new_mcpwm_device(motor_config, mcpwm_config, motor);
    bdc_motor_enable(*motor);
}

void motor_control_frd(bdc_motor_handle_t motor)
{
    bdc_motor_forward(motor);
}

void motor_control_back(bdc_motor_handle_t motor)
{
    bdc_motor_reverse(motor);
}

void motor_speed_control(bdc_motor_handle_t motor, uint8_t speed)
{
    bdc_motor_set_speed(motor, speed);
}

void car_init(const bdc_motor_mcpwm_config_t *mcpwm_config, car_t *car)
{
    bdc_motor_new_mcpwm_device(&car->right_motor_config, mcpwm_config, &car->right_motor);
    bdc_motor_enable(car->right_motor);
    bdc_motor_new_mcpwm_device(&car->left_motor_config, mcpwm_config, &car->left_motor);
    bdc_motor_enable(car->left_motor);
}

void car_move_frd(car_t car)
{
    bdc_motor_forward(car.right_motor);
    bdc_motor_forward(car.left_motor);
}

void car_move_back(car_t car)
{
    bdc_motor_reverse(car.right_motor);
    bdc_motor_reverse(car.left_motor);
}

void car_speed_control(car_t car, uint32_t speed)
{
    bdc_motor_set_speed(car.right_motor, speed);
    bdc_motor_set_speed(car.left_motor, speed);
}

void car_turn_right(car_t car, uint8_t speed)
{
    bdc_motor_forward(car.left_motor);
    bdc_motor_reverse(car.right_motor);
    bdc_motor_set_speed(car.right_motor, speed);
    bdc_motor_set_speed(car.left_motor, speed);
}

void car_turn_left(car_t car, uint8_t speed)
{
    bdc_motor_forward(car.right_motor);
    bdc_motor_reverse(car.left_motor);
    bdc_motor_set_speed(car.right_motor, speed);
    bdc_motor_set_speed(car.left_motor, speed);
}