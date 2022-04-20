#include "sensors.h"

string Sensor::getUTCtime(){
	time_t timep;
	struct tm* tp;
	time(&timep);
	tp = gmtime(&timep);
	string month, day, hour, min, sec;

	if ((1 + tp->tm_mon) <= 9) month = "0" + to_string(1 + tp->tm_mon);
	else month = to_string(1 + tp->tm_mon);
	if (tp->tm_mday <= 9) day = "0" + to_string(tp->tm_mday);
	else day = to_string(tp->tm_mday);
	if (tp->tm_hour <= 9) hour = "0" + to_string(tp->tm_hour);
	else hour = to_string(tp->tm_hour);
	if (tp->tm_min <= 9) min = "0" + to_string(tp->tm_min);
	else min = to_string(tp->tm_min);
	if (tp->tm_sec <= 9) sec = "0" + to_string(tp->tm_sec);
	else sec = to_string(tp->tm_sec);
	
	string time_str = to_string(tp->tm_year + 1900) + "-" + month + "-" + day + "-" + hour + ":" + min + ":" + sec;
	return time_str;
}
