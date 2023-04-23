#ifndef _TIME_H_
#define _TIME_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <regex>

struct Time {

	uint16_t hour;
	uint16_t min;

public:

	Time() {
		hour = 0;
		min = 0;
	};

	Time(uint16_t h, uint16_t m) {
		hour = h;
		min = m;
	}

	void setTime(uint16_t h, uint16_t m) {
		hour = h;
		min = m;
	}

	friend std::ostream& operator<<(std::ostream& os, const Time& t)
	{
		std::string hour = "";
		std::string min = "";

		if (t.hour <= 9) hour = "0" + std::to_string(t.hour);
		else hour = std::to_string(t.hour);

		if (t.min <= 9) min = "0" + std::to_string(t.min);
		else min = std::to_string(t.min);

		return os << hour << ":" << min << " ";
	}
	std::string toString() {
		std::string h = "";
		std::string m = "";

		if (hour <= 9) h = "0" + std::to_string(hour);
		else h = std::to_string(hour);

		if (min <= 9) m = "0" + std::to_string(min);
		else m = std::to_string(min);

		return  h + ":" + m;
	}

};
#endif

