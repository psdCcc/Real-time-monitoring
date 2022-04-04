#include "RAIN_SENSOR.h"
using std::cout;
using std::endl;

//Function uint8_t init(): Initialization. Return 0 if succeed or 1 if faile.
uint8_t RAIN::init(void){
	cout << "Rain sensor initializing..." << endl;
	if (gpioSetMode(pin, PI_INPUT) || gpioSetPullUpDown(pin, PI_PUD_UP)) {
		gpioSleep(PI_TIME_RELATIVE, 1, 0);
		cout << "Rain sensor sets GPIO mode succeeded" << endl;
		return 0;
	}
	else {
		cout << "Rain sensor sets GPIO mode failed" << endl;
		return 1;
	}
}
//Function uint8_t hasRain(): Return 0 if has or 1 if no.
uint8_t RAIN::hasRain(void){
	if (!gpioRead(pin)) {//has
		cout << "Rain" << endl;
		return 0;
	}
	else {
		cout << "No rain" << endl;
		return 1;
	}
}
