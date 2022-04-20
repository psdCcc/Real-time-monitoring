#include "DHT11.DHT11.h"
#include "Camera/Camera.h"

int main(){
    Camera camera;
    DHT11 dht11;
    dht11.test();
    camera.test();
}
