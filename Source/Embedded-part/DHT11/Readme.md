# DHT11 temperature and humidity sensor

![DHT11 module](DHT11.jpeg)

## Pins

|Pin|Function|Connection|
|:-:|:------:|:--------:|
|VCC|Power supply|3.3V - 5V|
|GND|Ground|GND|
|DOUT|Data pin|GPIO|

**Note: Serial data, single bus.**

## Sequence diagram

### **Begin signal of DHT11 module**
![DHT11 Beginning signal](DHT11_begin.png)
### **indication of bit '0' and '1' of DHT11 module**
![DHT11 bit '0' and '1'](DHT11_bits.png)

## Data format

> The temperature and humidity data of DHT11 is expressed in binary digital. 
> Before sending one bit, DHT11 will pull down the DOUT pin for 50us.
> The complete data includes 40 bits (5 bytes). They are: **1 bit humidity integer part +
> 1 bit humidity decimal part + 1 bit temperature integer part + 1 bit temperature decimal part + 1 bit check sum.**
