#ifndef _DHT11_H
#define _DHT11_H

#include <pigpio.h>
#include <iostream>

#define pin 3

class DHT11{
public:
	uint8_t init(void);//Function init(): Initialize DHT11 module. Return 0 if succeed or 1 if faile.
	void reset(void);//Function reset(): Reset DHT11 and send a start signal to DTH11 module.
	uint8_t check(void);//Function check(): check whether DHT11 module works well. Return 0 if yes or 1 if no.
	uint8_t read_bit(void);//Function read_bit(): Read 1 bit from DHT11 module. Return 1 or 0.
	uint8_t read_byte(void);//Function read_byte(): Read 1 byte from DHT11 module. Return the data read from DHT11.
	uint8_t read_data(uint8_t *buffer);//Function read_data(uint8_t *temp, uint8_t *humi): Read complete data from DHT11 module.
};

#endif
