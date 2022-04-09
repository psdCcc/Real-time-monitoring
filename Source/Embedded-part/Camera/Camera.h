#ifndef _CAMERA_H
#define _CAMERA_H

#include <pigpio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <unistd.h>

class Camera{
public:
    uint8_t init(int port);// Function uint8_t init(int port): create a stream server. Return 0 if succeeds or 1 if failes.
    uint8_t sendIPAddr(std::string serverIP);// Function uint8_t sendIPAddr(string serverIP): Send the IP address of raspberry pi to cloud server. Return 0 if succeeds or 1 if failes.
};

#endif
