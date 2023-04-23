#ifndef _EVENT3_H_
#define _EVENT3_H_
#include "Event.h"
Time stringToTime(std::string);
class Event3 : public Event {

	std::string name;

public:
	Event3() : Event() {
		name = "";
	}
	Event3(const int id, Time time, std::string n) : Event(id, time) {
		name = n;
	}
	Event3(std::vector<std::string> data) {
		time = stringToTime(data[0]);
		id = stoi(data[1]);
		name = data[2];

	}
	friend std::ostream& operator<<(std::ostream& os, const Event3& e) {

		return os << e.time << " " << e.id << e.name << " ";
	}
	virtual std::string reactionOnEvent(Cafe& c) {
		Client client = c.getClient(name);
		client.setInQueue(true);
		c.setClientOnQueue(client);
		if (c.checkFreeTable()) return eventId13("ICanWaitNoLonger!\n");
		else if (c.checkQueueSize() == -1) {
			c.clientGone(client);

			return eventId11();
		}
		else return "";
	}
	std::string eventId11() {

		return   time.toString() + " 11 " + name + "\n";
	}
};
#endif