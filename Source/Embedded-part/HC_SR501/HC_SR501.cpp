#include "HC_SR501.h"
using std::cout;
using std::endl;

//Function uint8_t init(): initialize HC_SR501 module. Return 0 if succeed or 1 if faile.
uint8_t HC_SR501::init(){
	cout << "HC_SR501 initializing..." << endl;
	gpioSleep(PI_TIME_RELATIVE, 60, 0);
	if(gpioSetMode(pin, PI_INPUT) || gpioSetPullUpDown(pin, PI_PUD_DOWN)) {
		cout << "Set GPIO mode failed." << endl;
		return 1;
	}
	else cout << "Set GPIO mode succeeded.\nFinish initialization" << endl;
	return 0;
}
//Fucntion uint8_t hasHuman(). Return 0 if has or 1 if no.
uint8_t HC_SR501::hasHuman(){
	if (gpioRead(pin)) {// Has human
		cout << "Has human." << endl;
		return 0;
	}
	else {
		cout << "No human" << endl;
		return 1;
	}
}
