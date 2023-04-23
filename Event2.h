#ifndef _EVENT2_H_
#define _EVENT2_H_
#include "Event.h"

class Event2 : public Event {

	std::string name;
	int tableNum;

public:
	Event2() : Event() {
		name = "";
	}
	Event2(const int id, Time time, std::string n) : Event(id, time) {
		name = n;
	}
	Event2(std::vector<std::string> data) {
		time = stringToTime(data[0]);
		id = stoi(data[1]);
		name = data[2];
		tableNum = stoi(data[3]) - 1;
	}
	friend std::ostream& operator<<(std::ostream& os, const Event2& e) {

		return os << e.time << " " << e.id << e.name << e.tableNum << " ";
	}
	virtual std::string reactionOnEvent(Cafe& c) {

		Client client = c.getClient(name);

		if (!c.checkIsHere(name)) return eventId13("ClientUnknown\n");
		else if (c.chekTableisFree(tableNum)) {

			if (client.getTableNum() != -1) c.cleanTable(client.getTableNum(), time);
			else if (client.getInQueue()) c.deleteFromQueue(client);
			client.setStartTime(time);
			c.sitClientAtTable(client, tableNum);
			return "";
		}
		else return eventId13("PlaceIsBusy\n");

	}


};
#endif