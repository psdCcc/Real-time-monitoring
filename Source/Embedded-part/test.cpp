#include "DHT11/DHT11.h"
#include "Camera/Camera.h"

int main(){
    DHT11 dht11;
    Camera camera;
    dht11.test();
    camera.test();
}
