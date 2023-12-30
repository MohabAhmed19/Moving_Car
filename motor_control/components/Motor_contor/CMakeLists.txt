
idf_component_register(
    SRCS Motor_control.c
    INCLUDE_DIRS .
    REQUIRES freertos espressif__bdc_motor esp_timer
    PRIV_REQUIRES driver
)
