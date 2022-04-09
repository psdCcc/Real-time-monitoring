#include "./DHT11/DHT11.h"
#include "./HC_SR501/HC_SR501.h"
#include "./Rain/RAIN_SENSOR.h"
#include "./CameraCamera.h"

int main(int argc, char* argv[]){
    DHT11 dht11;
    HC_SR501 hc_sr501;
    RAIN rain;
    Camera camera;
    //initialization of pigpio library
    if (gpioInitialise() < 0)
		std::cout << "GPIO Initialising failed/n" <<std::endl;
	else {
        //initializtion of the modules
        dht11.init();
        hc_sr501.init();
        rain.init();
        camera.init();
    }
    
    
    return 0;
}
