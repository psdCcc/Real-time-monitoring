#include "HC_SR501.h"

int main(){
	if (gpioInitialise() < 0)
		std::cout << "GPIO Initialising failed/n" <<std::endl;
	else {		
		HC_SR501 infra;
		infra.init();
		while(1) {
			infra.hasHuman();
			gpioSleep(PI_TIME_RELATIVE, 5, 0);
		};
	}
	return 0;
}
