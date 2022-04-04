#ifndef _HC_SR501_H
#define _HC_SR501_H

#include <pigpio.h>
#include <iostream>

#define pin 4

class HC_SR501{
public:
	uint8_t init(void);//Function uint8_t init(): initialize HC_SR501 module. Return 0 if succeed or 1 if faile.
	uint8_t hasHuman(void);//Fucntion uint8_t hasHuman(). Return 0 if has or 1 if no.
};

#endif
