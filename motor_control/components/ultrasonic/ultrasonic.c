#include "ultrasonic.h"

void Ultrasonic_init(const ultrasonic_s *ultra)
{
    gpio_set_direction(ultra->trigger, GPIO_MODE_OUTPUT);
    gpio_set_direction(ultra->echo, GPIO_MODE_INPUT);

    gpio_set_level(ultra->trigger, 0);
}

uint8_t distance_measure_cm(const ultrasonic_s *ultra, int *distance)
{
    int64_t start, end;
    if (gpio_get_level(ultra->echo) == 1)
    {
        return 1;
    }
    gpio_set_level(ultra->trigger, 0);
    ets_delay_us(10);
    gpio_set_level(ultra->trigger, 1);
    ets_delay_us(10);
    gpio_set_level(ultra->trigger, 0);

    start = esp_timer_get_time();
    if (gpio_get_level(ultra->echo) == 0)
    {
        return 2;
    }

    while (gpio_get_level(ultra->echo) != 0)
    {
        end = esp_timer_get_time();
        *distance = ((343 * (end - start)) / 10000);
        if ((*distance) > 200)
        {
            break;
        }
    }
    return 0;
}
