#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_err.h>
#include "../components/Motor_contor/Motor_control.h"
#include "../components/ultrasonic/ultrasonic.h"

#define trigger_pin 4
#define echo_pin 5

#define BDC_MCPWM_GPIO_1A 15
#define BDC_MCPWM_GPIO_1B 2

#define BDC_MCPWM_GPIO_2A 18
#define BDC_MCPWM_GPIO_2B 19

int distance;

uint8_t curr_speed = 0;

void app_main(void)
{
	ultrasonic_s ultra_argument = {.trigger = trigger_pin, .echo = echo_pin};

	bdc_motor_handle_t motor1 = NULL;

	bdc_motor_handle_t motor2 = NULL;

	bdc_motor_config_t motor1_config = {
		.pwm_freq_hz = BDC_MCPWM_FREQ_HZ,
		.pwma_gpio_num = BDC_MCPWM_GPIO_1A,
		.pwmb_gpio_num = BDC_MCPWM_GPIO_1B,
	};

	bdc_motor_config_t motor2_config = {
		.pwm_freq_hz = BDC_MCPWM_FREQ_HZ,
		.pwma_gpio_num = BDC_MCPWM_GPIO_2A,
		.pwmb_gpio_num = BDC_MCPWM_GPIO_2B,
	};

	bdc_motor_mcpwm_config_t mcpwm_config = {
		.group_id = 0,
		.resolution_hz = BDC_MCPWM_TIMER_RESOLUTION_HZ,
	};

	car_t car1 = {
		.right_motor = motor1,
		.right_motor_config = motor1_config,
		.left_motor = motor2,
		.left_motor_config = motor2_config};

	Ultrasonic_init(&ultra_argument);
	car_init(&mcpwm_config, &car1);
	while (1)
	{
		if (distance_measure_cm(&ultra_argument, &distance) == 0)
		{
			printf("distance is %d\n", distance);
			if (distance > 200)
			{
				curr_speed = 90;

				car_move_frd(car1);
				car_speed_control(car1, curr_speed);
			}
			else if (distance > 70 /*&& distance <=200*/)
			{
				curr_speed = 40;
				car_move_frd(car1);
				car_speed_control(car1, curr_speed);
			}
			else if (distance > 20 /*&& distance<=70*/)
			{
				curr_speed = 5;
				car_turn_right(car1, curr_speed);
				car_speed_control(car1, curr_speed);
			}
			else
			{
				curr_speed = 10;
				car_move_back(car1);
				car_speed_control(car1, curr_speed);
			}

			vTaskDelay(200 / portTICK_PERIOD_MS);
		}
	}
}
