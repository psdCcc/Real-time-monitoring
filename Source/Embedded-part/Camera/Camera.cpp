#include "Camera.h"

uint8_t Camera::init(void* Port){
    int port = *(int*) Port;
    string tcpIP = "tcp://0.0.0.0:" + to_string(port);
    if (execlp("libcamera-vid", "libcamera-vid", "-t", "0", "--inline", "--listen", "-o", 
    tcpIP.c_str(), nullptr) == -1){
        cout << "Initialization failed." << endl;
        return 1;
    }
    cout << "Initialization succeeded." << endl;
    return 0;
}

void* Camera::start(void* args){
    camera_para para = *(camera_para*) args;
    para.camera->init(&para.port);
    
    return (void*) 1;
}

void Camera::test(){
    if (this.init(9999)) cout << "Camera: succeed" << endl;
    else cout << "Camera: faile" << endl;
}
