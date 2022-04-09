#include "RAIN_SENSOR.h"

int main(){
	if (gpioInitialise() < 0)
		std::cout << "GPIO Initialising failed/n" <<std::endl;
	else {
		RAIN rain;
		rain.init();
		while(1) {
			rain.hasRain();
			gpioSleep(PI_TIME_RELATIVE, 1, 0);
		};
	}
	return 0;
}
