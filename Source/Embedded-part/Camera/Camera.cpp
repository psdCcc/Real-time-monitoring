#include "Camera.h"

uint8_t Camera::init(int port){
    std::string tcpIP = "tcp://0.0.0.0:" + std::to_string(port);
    if (execlp("libcamera-vid", "libcamera-vid", "-t", "0", "--inline", "--listen", "-o", 
    tcpIP.c_str(), nullptr) == -1){
        std::cout << "Initialization failed." << std::endl;
        return 1;
    }
    std::cout << "Initialization succeeded." << std::endl;
    return 0;
}

uint8_t Camera::sendIPAddr(std::string serverIP){
    return 0;
}
