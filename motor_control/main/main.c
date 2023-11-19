#include <stdio.h>
#include <stdbool.h>
//#include <freertos/FreeRTOS.h>
//#include <freertos/task.h>
#include <esp_err.h>
#include "../components/Motor_contor/Motor_control.h"

void app_main(void)
{
	while(1)
	{
		motor_control(0, 90);
		while(1);
	}
}

