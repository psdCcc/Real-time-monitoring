#ifndef _RAIN_SENSOR_H
#define _RAIN_SENSOR_H

#define pin 2

#include <pigpio.h>
#include <iostream>

class RAIN{
public:
	uint8_t init(void);//Function uint8_t init(): Initialization. Return 0 if succeed or 1 if faile.
	uint8_t hasRain(void);//Function uint8_t hasRain(): Return 0 if has or 1 if no.
};

#endif
