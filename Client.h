#ifndef _CLIENT_H_
#define _CLIENT_H_
#include "Time.h"

struct Client {

private:

	std::string name = "";
	int tableNum = -1;
	bool inQueue = 0;
	Time startTime = Time(0, 0);

public:

	Client(std::string n) {
		name = n;
	}
	Client() {}

	std::string getName() {
		return name;
	}

	int getTableNum() {
		return tableNum;
	}

	void setTableNum(int n) {
		tableNum = n;
	}

	void setStartTime(Time s) {
		startTime = s;
	}

	Time getStartTime() {
		return startTime;
	}

	void setInQueue(bool flag) {
		inQueue = flag;
	}

	bool getInQueue() {
		return inQueue;
	}

	bool operator == (const Client& c) {
		if (name == c.name) return true;
		else return false;
	}
	bool operator < (const Client& c) {
		size_t size = 0;
		if (name.size() > c.name.size()) size = c.name.size();
		else size = name.size();
		for (int i = 0; i != size; i++) {
			if (name[i] < c.name[i]) return true;
			else if (name[i] > c.name[i]) return false;
		}
		if (name.size() < c.name.size()) return true;
		else return false;
	}


};
#endif