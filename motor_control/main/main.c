#include <stdio.h>
#include <stdbool.h>
#include "driver/mcpwm_timer.h"
#include "driver/mcpwm_prelude.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_err.h>


#define MOTOR_TIMEBASE_RESOLUTION_HZ 10000000
#define MOTOR_TIMEBASE_PERIOD 100
#define MOTOR1_PULSE_GPIO 0


    

void app_main(void)
{
    uint8_t speed=0;

    mcpwm_timer_handle_t timer = NULL;
    mcpwm_timer_config_t timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = MOTOR_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = MOTOR_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &timer));

    mcpwm_oper_handle_t oper = NULL;
    mcpwm_operator_config_t operator_config = {
        .group_id = 0,
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &oper));

    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

    mcpwm_cmpr_handle_t comparator = NULL;
    mcpwm_comparator_config_t comparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &comparator_config, &comparator));

    mcpwm_gen_handle_t generator = NULL;
    mcpwm_generator_config_t generator_config = {
        .gen_gpio_num = MOTOR1_PULSE_GPIO,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(oper, &generator_config, &generator));

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, speed));

    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generator,
                    MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generator,
                    MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)));

    ESP_ERROR_CHECK(mcpwm_timer_enable(timer));

    ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));

    while(1)
    {
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, speed));

        vTaskDelay( 500 / portTICK_PERIOD_MS );

        if(speed<1)
        {
            (speed)++;
        }
        else
        {
            speed=0;
        }
    }
}