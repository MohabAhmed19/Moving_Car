

#ifndef __Motor_control_H__
#define __Motor_control_H__

#define MOTOR_TIMEBASE_RESOLUTION_HZ 10000000
#define MOTOR_TIMEBASE_PERIOD 100

void motor_control(uint8_t GPIO, uint8_t speed);

#endif /*__Motor_control_H__*/
