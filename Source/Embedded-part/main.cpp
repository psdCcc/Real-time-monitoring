#include "DHT11.h"
#include "Camera.h"
#include <sys/wait.h>

int main(int argc, char* argv[]){
    //initialization of pigpio library
    if (gpioInitialise() < 0)
		std::cout << "GPIO Initialising failed/n" <<std::endl;
	else {
        dht11_para dht11_p;
        camera_para camera_p;
        DHT11 dht11;
        Camera camera;
        dht11_p.dht11 = &dht11;
        camera_p.camera = &camera;
        camera_p.port = 9999;
        pid_t c, w;
        c = fork();
        if (c == 0){
            camera.start(&camera_p);
        }
        else{
            dht11.start(&dht11_p);
            w = waitpid(c, nullptr, 0);
        }
    }
    
    gpioTerminate();
    return 0;
}
