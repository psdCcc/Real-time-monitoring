#include "DHT11.h"
#include <stdio.h>

int main(){
	if (gpioInitialise() < 0)
		std::cout << "GPIO Initialising failed/n" <<std::endl;
	else {
		uint8_t buffer[5] = {0};
		DHT11 dht11;
		if (!dht11.init()) printf("DHT11 initialized\n");
		gpioSleep(PI_TIME_RELATIVE, 1, 0);
		dht11.read_data(buffer);
		printf("Buffer: %d, %d, %d, %d, %d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
	}
	gpioTerminate();
	return 0;
}
