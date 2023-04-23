#ifndef _TABLE_H_
#define _TABLE_H_
//#include "Cafe.h"

struct Table {
private:

	Client client;
	int tableNum = -1;
	bool isBisyNow = 0;
	Time workTime = Time(0, 0);
	int rev = 0;

public:
	void addClient(Client& c) {

		c.setTableNum(tableNum);
		c.setInQueue(false);
		client = c;
	}

	void setStatus(bool st) {
		isBisyNow = st;
	}
	int getStatus() {
		return isBisyNow;
	}
	void setTableNumber(int n) {
		tableNum = n;
	}

	Client getClient() {
		return client;
	}

	int getRev() {
		return rev;
	}
	Time getWorkTime() {
		return workTime;
	}

	void clean() {

		client = Client();
		isBisyNow = 0;

	}
	void countRev(int n, Time endTime) {

		Time startTime = client.getStartTime();
		int min = 0, hour = 0;

		min = (endTime.hour - startTime.hour) * 60 + (endTime.min - startTime.min);

		hour = min / 60;
		min = min % 60;

		if (min != 0) hour += 1;

		rev += (hour * n);

	}
	void countTime(Time endTime) {

		Time startTime = client.getStartTime();

		int min = 0, hour = 0, wMin = workTime.min, wHour = workTime.hour;
		min = (endTime.hour - startTime.hour) * 60 + (endTime.min - startTime.min);

		hour = min / 60;
		min = min % 60;
		wMin = min + wMin;
		wHour = hour + wHour;

		if (wMin > 59) {
			wMin = wMin % 60;
			wHour++;
		}
		workTime = Time(wHour, wMin);

	}

};

#endif
