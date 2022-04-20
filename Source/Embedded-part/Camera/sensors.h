#ifndef _SENSORS_H
#define _SENSORS_H

#include <pigpio.h>
#include <iostream>
#include <time.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_arp.h>


using std::string;
using std::stoi;
using std::to_string;
using std::cout;
using std::endl;

class Sensor{
public:
	virtual uint8_t init(void* args) = 0;
	string getUTCtime();
};

#endif
