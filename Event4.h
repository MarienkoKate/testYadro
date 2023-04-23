#ifndef _EVENT4_H_
#define _EVENT4_H_
#include "Event.h"

class Event4 : public Event {

	std::string name;

public:
	Event4() : Event() {
		name = "";
	}
	Event4(const int id, Time time, std::string n) : Event(id, time) {
		name = n;
	}
	Event4(std::vector<std::string> data) {
		time = stringToTime(data[0]);
		id = stoi(data[1]);
		name = data[2];

	}

	friend std::ostream& operator<<(std::ostream& os, const Event4& e) {

		return os << e.time << " " << e.id << e.name << " ";
	}
	virtual std::string reactionOnEvent(Cafe& c) {
		Client client = c.getClient(name);
		if (!c.checkIsHere(name)) return eventId13("ClientUnknown\n");
		else {

			c.cleanTable(client.getTableNum(), time);

			if (c.getQueue().size() != 0) {

				int tn = client.getTableNum();
				c.clientGone(client);
				Client newClient = c.getFirstInQueue();
				newClient.setStartTime(time);
				c.sitClientAtTable(newClient, tn);
				c.deleteFromQueue(newClient);
				return eventId12(newClient.getName() + " " + std::to_string(tn + 1));

			}
			c.clientGone(client);
			return "";
		}
	}
	std::string eventId11() {

		return   time.toString() + " 11 " + name + "\n";
	}
	std::string eventId12(std::string data) {

		if (data.size() != 0) return   time.toString() + " 12 " + data + "\n";
		else return "";

	}

};
#endif