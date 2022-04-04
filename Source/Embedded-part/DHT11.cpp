#include "DHT11.h"

//Function init(): Initialize DHT11 module. Return 0 if succeed or 1 if faile.
uint8_t DHT11::init(){
	gpioSetMode(pin, PI_OUTPUT);
	gpioWrite(pin, 1);
	gpioSleep(PI_TIME_RELATIVE, 1, 0);// 1s
	this->reset();
	return this->check();
}
//Function reset(): Reset DHT11 and send a start signal to DTH11 module.
void DHT11::reset(){
	gpioSetMode(pin, PI_OUTPUT);
	gpioWrite(pin, 0);
	gpioSleep(PI_TIME_RELATIVE, 0, 25 * 1000);// 25ms
	gpioWrite(pin, 1);
	gpioDelay(30);// 30us
}
//Function check(): check whether DHT11 module works well. Return 0 if yes or 1 if no.
uint8_t DHT11::check(){
	uint8_t tryCount = 0;
	gpioSetMode(pin, PI_INPUT);
	gpioSetPullUpDown(pin, PI_PUD_UP);
	while(gpioRead(pin) && (tryCount<100)) {// wait low level for at most 100us
		tryCount++;
		gpioDelay(1);// 1us
	};
	if (tryCount >= 100) return 1;
	else tryCount = 0;
	while((!gpioRead(pin)) && (tryCount<100)) {// wait high level for at most 100us.
		tryCount++;
		gpioDelay(1);// 1us
	};
	if (tryCount >= 100) return 1;
	return 0;
}
//Function read_bit(): Read 1 bit from DHT11 module. Return 1 or 0.
uint8_t DHT11::read_bit(){
	uint8_t tryCount = 0;
	while(gpioRead(pin) && (tryCount<100)){// wait for low level
		tryCount++;
		gpioDelay(1);// 1us
	};
	tryCount = 0;
	while((!gpioRead(pin) && (tryCount<100))){// wait for high level
		tryCount++;
		gpioDelay(1);// 1us
	};
	gpioDelay(40);// wait 40us after the gpio is changed to high level
	// 23 to 27us high level means 0; 68 to 74us high level means 1. So now high level means 1 and low level means 0.
	return (uint8_t)gpioRead(pin);
}
//Function read_byte(): Read 1 byte from DHT11 module. Return the data read from DHT11.
uint8_t DHT11::read_byte(){
	uint8_t i = 0, data = 0;
	for (;i < 8; i++){
		data <<= 1;
		data |= this->read_bit();
	}
	return data;
}
//Function read_data(uint8_t *temp, uint8_t *humi): Read complete data from DHT11 module.
uint8_t DHT11::read_data(uint8_t *buffer){
	uint8_t i = 0;
	this->reset();
	if (this->check() == 0){
		if ((buffer[0] + buffer[1] + buffer[2] + buffer[3]) == buffer[4]){// verify the data with 8 bits check sum
			for (;i < 5; i++){
				buffer[i] = this->read_byte();
			}
		}
	}
	else return 1;
	return 0;
}
