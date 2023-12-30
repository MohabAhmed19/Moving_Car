
idf_component_register(
    SRCS ultrasonic.c
    INCLUDE_DIRS .
    REQUIRES freertos
    PRIV_REQUIRES driver esp_timer
)
