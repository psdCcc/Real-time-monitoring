#ifndef _CAMERA_H
#define _CAMERA_H

#include <pigpio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <unistd.h>

using std::string;
using std::stoi;
using std::to_string;
using std::cout;
using std::endl;

class Camera{
public:
    uint8_t init(void* port);// Function uint8_t init(void* port): create a stream server. Return 0 if succeeds or 1 if failes.
    static void* start(void* args);
};

struct camera_para{
    int port;//port of the stream
    Camera* camera;//Pointer points to a camera object
};

#endif
