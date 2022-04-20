#ifndef _DHT11_H
#define _DHT11_H

#include "sensors.h"

#define pin 3

class DHT11 : public Sensor{
public:
	uint8_t init(void* args);//Function uint8_t init(void* args): Initialize DHT11 module. Return 0 if succeed or 1 if faile.
	void reset(void);//Function reset(): Reset DHT11 and send a start signal to DTH11 module.
	uint8_t check(void);//Function check(): check whether DHT11 module works well. Return 0 if yes or 1 if no.
	uint8_t read_bit(void);//Function read_bit(): Read 1 bit from DHT11 module. Return 1 or 0.
	uint8_t read_byte(void);//Function read_byte(): Read 1 byte from DHT11 module. Return the data read from DHT11.
	uint8_t read_data(uint8_t *buffer);//Function read_data(uint8_t *temp, uint8_t *humi): Read complete data from DHT11 module.
	string get_datastr(uint8_t *buffer);//Function get_datastr(void): Get the string format data of temp and humi.
	static void* start(void* args);//Function static void* start(void* args): The function that will be run when create a new thread.
	void test();
};

struct dht11_para{
	string IP = "101.34.165.230:9002"; // server IP:port string.
	DHT11* dht11; // Pointer points to a DHT11 objects.
	int period = 1; // time period between two adjacent measurements.
};

#endif
