#ifndef _EVENT1_H_
#define _EVENT1_H_
#include "Cafe.h"
#include "Event.h"

class Event1 : public Event {

	std::string name;

public:
	Event1() : Event() {
		name = "";
	}
	Event1(const int id, Time time, std::string n) : Event(id, time) {
		name = n;
	}
	Event1(std::vector<std::string> data) {
		time = stringToTime(data[0]);
		id = stoi(data[1]);
		name = data[2];
	}
	friend std::ostream& operator<<(std::ostream& os, const Event1& e) {

		return os << e.time << " " << e.id << e.name << " ";
	}
	virtual std::string reactionOnEvent(Cafe& c) {
		Client cl = Client(name);
		if (c.checkIsHere(name)) return eventId13("YouShallNotPass\n");
		if (c.checkWorkTime(time)) return eventId13("NotOpenYet\n");
		else c.setClientOnAllClients(cl);
		return "";
	}
	std::string eventId11() {

		return   time.toString() + " 11 " + name + "\n";
	}

};
#endif