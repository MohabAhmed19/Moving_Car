
#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_timer.h>
#include <rom/ets_sys.h>
#include <driver/gpio.h>
#include <esp_err.h>

typedef const struct
{
    uint8_t trigger;
    uint8_t echo;
} ultrasonic_s;

void Ultrasonic_init(const ultrasonic_s *ultra);

uint8_t distance_measure_cm(const ultrasonic_s *ultra, int *distance);

#endif /* __ULTRASONIC_H__ */
