# This is the source code that will run on the raspberry pi.

- [**DHT11 module**](https://github.com/psdCcc/Real-time-monitoring/tree/main/Source/Embedded-part/DHT11): measure the temperature and humidity.  
- [**Camera**](https://github.com/psdCcc/Real-time-monitoring/tree/main/Source/Embedded-part/Camera): Create a real-time video stream server.

## Use test.cpp to test module:
### 1. compile:
g++ -Wall -pthread -o test test.cpp ./DHT11/DHT11.cpp ./Camera/Camera.cpp ./Camera.sensors.cpp -lpigpio -lrt
## 2. run
sudo ./test
