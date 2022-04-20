#include "DHT11.h"

//Function uint8_t init(void* args): Initialize DHT11 module. Return 0 if succeed or 1 if faile.
uint8_t DHT11::init(void* args){
	gpioSetMode(pin, PI_OUTPUT);
	gpioWrite(pin, 1);
	gpioSleep(PI_TIME_RELATIVE, 1, 0);// 1s
	this->reset();
	return this->check();
}
//Function reset(): Reset DHT11 and send a start signal to DTH11 module.
void DHT11::reset(){
	gpioSetMode(pin, PI_OUTPUT);
	gpioWrite(pin, 0);
	gpioSleep(PI_TIME_RELATIVE, 0, 25 * 1000);// 25ms
	gpioWrite(pin, 1);
	gpioDelay(30);// 30us
}
//Function check(): check whether DHT11 module works well. Return 0 if yes or 1 if no.
uint8_t DHT11::check(){
	uint8_t tryCount = 0;
	gpioSetMode(pin, PI_INPUT);
	gpioSetPullUpDown(pin, PI_PUD_UP);
	while(gpioRead(pin) && (tryCount<100)) {// wait low level for at most 100us
		tryCount++;
		gpioDelay(1);// 1us
	};
	if (tryCount >= 100) return 1;
	else tryCount = 0;
	while((!gpioRead(pin)) && (tryCount<100)) {// wait high level for at most 100us.
		tryCount++;
		gpioDelay(1);// 1us
	};
	if (tryCount >= 100) return 1;
	return 0;
}
//Function read_bit(): Read 1 bit from DHT11 module. Return 1 or 0.
uint8_t DHT11::read_bit(){
	uint8_t tryCount = 0;
	while(gpioRead(pin) && (tryCount<100)){// wait for low level
		tryCount++;
		gpioDelay(1);// 1us
	};
	tryCount = 0;
	while((!gpioRead(pin) && (tryCount<100))){// wait for high level
		tryCount++;
		gpioDelay(1);// 1us
	};
	gpioDelay(40);// wait 40us after the gpio is changed to high level
	// 23 to 27us high level means 0; 68 to 74us high level means 1. So now high level means 1 and low level means 0.
	return (uint8_t)gpioRead(pin);
}
//Function read_byte(): Read 1 byte from DHT11 module. Return the data read from DHT11.
uint8_t DHT11::read_byte(){
	uint8_t i = 0, data = 0;
	for (;i < 8; i++){
		data <<= 1;
		data |= this->read_bit();
	}
	return data;
}
//Function read_data(uint8_t *temp, uint8_t *humi): Read complete data from DHT11 module.
uint8_t DHT11::read_data(uint8_t *buffer){
	uint8_t i = 0;
	this->reset();
	if (this->check() == 0){
		for (;i < 5; i++){
				buffer[i] = this->read_byte();
		}
		if ((buffer[0] + buffer[1] + buffer[2] + buffer[3]) != buffer[4]){// verify the data with 8 bits check sum
			return 1;
		}
	}
	else return 1;
	return 0;
}
string DHT11::get_datastr(uint8_t* buffer){
	string b[4];
	
	for (int i = 0; i < 4; i++){
		b[i] = to_string(buffer[i]);
		if (b[i].length() == 1) b[i] = "0" + b[i];
		if (b[i].length() == 3) b[i] = "00";
	}
	
	return (this->getUTCtime() + "-" + b[0] + "." + b[1] + "-" + b[2] + "." + b[3]);
}

string getIP(){
	int sock;
	struct sockaddr_in sin;
	struct ifreq ifr;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
	{
		perror("socket");
		return string("");
	}

	strncpy(ifr.ifr_name, "eth0", IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ - 1] = 0;

	if (ioctl(sock, SIOCGIFADDR, &ifr) < 0){
		perror("ioctl");
		return string("");
	}
	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	return string(inet_ntoa(sin.sin_addr));
}

struct timerPara{
	uint8_t* buffer;
	int fd;
	struct sockaddr_in* serv;
	DHT11* dht11;
};

void sendFunc(void* args){
	struct timerPara para = *(struct timerPara*) args;
	
	string data;
	for (int i = 0; i < 5; i++) para.buffer[i] = 0;
	para.dht11->read_data(para.buffer);
	data = "1" + para.dht11->get_datastr(para.buffer);
	
	string b[4];
	/*
	for (int i = 0; i < 4; i++){
		b[i] = to_string(para.buffer[i]);
		if (b[i].length() == 1) b[i] = "0" + b[i];
		if (b[i].length() == 3) b[i] = "00";
	}
	
	data += ("1" + para.dht11->getUTCtime() + "-" + b[0] + "." + b[1] + "-" + b[2] + "." + b[3]);
	* */
	cout << data << endl;
	// send data - server - IP port
	send(para.fd, data.c_str(), data.length(), 0);
}
//Function static void* start(void* args): The function that will be run when create a new thread.
/*
args: 
struct init_para{
	string IP;//IP address of server, including port.
	DHT11* dht11; // Pointer points to a DHT11 object.
	int period;// time period between two adjacent measurements.
}
*/
void* DHT11::start(void* args){
	dht11_para para = *(dht11_para*) args;
	string port = para.IP.substr(para.IP.find(":") + 1);
	string IP = para.IP.substr(0, para.IP.length() - port.length() - 1);
	
	uint8_t buffer[5] = {0};
	if (!para.dht11->init(nullptr)) printf("DHT11 initialized\n");
	gpioSleep(PI_TIME_RELATIVE, 1, 0);
	
	// create socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket error");
        exit(1);
    }

    // initializing IP and port of server
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(stoi(port));
    serv.sin_addr.s_addr = inet_addr("101.34.165.230");
    
	if (connect(fd, (struct sockaddr*)&serv, sizeof(serv)) < 0){
		cout << "connection failed" << endl; 
	}
	else cout << "connection succeed" << endl;
	
	string ip = "0" + getIP();
	send(fd, ip.c_str(), ip.length(), 0);
	
	struct timerPara tpara = {buffer, fd, &serv, para.dht11};
	//timer calls sendFunc every 1 second
	gpioSetTimerFuncEx(0, para.period * 1000, sendFunc, &tpara);
    
    while(1){}
    
    close(fd);
    
    return (void*)1;
}
//Function test(): Test function
void DHT11::test(){
	if (gpioInitialise() < 0)
		std::cout << "GPIO Initialising failed/n" <<std::endl;
	else {
		uint8_t buffer[5];
		if (!dht11.init()) {
			printf("DHT11 initialized\n");
			gpioSleep(PI_TIME_RELATIVE, 1, 0);
			if (!dht11.read_data(buffer)) printf("DHT11 succeeds\n");
			else printf("DHT11 failes\n");
		}
		else printf("DHT11 failes\n");
	}
	gpioTerminate();
}
