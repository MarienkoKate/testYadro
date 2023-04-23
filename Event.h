#ifndef _EVENT_H_
#define _EVENT_H_

class Event {

protected:

	int id;
	Time time;

public:
	/*Event() {}*/
	Event(const int i, Time t) {
		id = i;
		time = t;
	}
	Event() {
		id = 0;
		time = Time(0, 0);
	}

	Time stringToTime(std::string s) {

		std::regex regex1(":");
		std::vector<std::string> out(
			std::sregex_token_iterator(s.begin(), s.end(), regex1, -1),
			std::sregex_token_iterator()
		);
		int min = 0, hour = 0;
		std::vector<Time> delimTime;

		for (int i = 0; i != out.size(); i++) {

			int tmp = std::stoi(out[i]);

			if (i % 2 == 0) hour = tmp;
			else min = tmp;

			if (i % 2 == 1 && i != 0) return Time(hour, min);


		}
		return Time();
	}

	virtual std::string reactionOnEvent(Cafe& c) {

		return "";
	}
	std::string eventId13(std::string massege) {

		return   time.toString() + " 13 " + massege;
	}
};
#endif