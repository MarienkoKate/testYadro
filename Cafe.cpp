#define _CRT_SECURE_NO_WARNINGS
#include "Cafe.h"
#include "Event1.h"
#include "Event2.h"
#include "Event3.h"
#include "Event4.h"

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
void chekFile(std::string fileName) {



	std::regex time("^(([0,1][0-9])|(2[0-3])):[0-5][0-9]\\s\(([0,1][0-9])|(2[0-3])):[0-5][0-9]$");
	std::regex number(R"(^\d*$)");
	std::string r;

	std::string line;
	unsigned int lineNum = 1;

	std::string ex;
	
	Time prevTime(0, 0);
	Time nowTime(0, 0);

	std::ifstream in(fileName);

	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (lineNum == 1) {
				if (!regex_match(line, number)) {
					ex = "Error: invalid data in line " + std::to_string(lineNum) + ": " + line;
					throw(ex);
				}
				r = "^(([0,1][0-9])|(2[0-3])):[0-5][0-9]\\s\[1-4]\\s\[a-z0-9_-]+(\\s\[1-" + line + "]|$)$";

			}
			else if (lineNum == 2) {
				if (!regex_match(line, time)) {
					ex = "Error: invalid data in line " + std::to_string(lineNum) + ": " + line;
					throw(ex);
				}
			}
			else if (lineNum == 3) {
				if (!regex_match(line, number)) {
					ex = "Error: invalid data in line " + std::to_string(lineNum) + ": " + line;
					throw(ex);
				}
			}
			else {
				if (!regex_match(line, std::regex(r))) {
					ex = "Error: invalid data in line " + std::to_string(lineNum) + ": " + line;
					throw(ex);
				}
				else {
					nowTime = Time(stringToTime(line));
					if (nowTime < prevTime) {
						ex = "Error: invalid data in line (previous time is greater than current time) " + std::to_string(lineNum) + ": " + line;
						throw(ex);
					}
					prevTime = nowTime;
				}
			}

			lineNum++;
		}

	}
	else {
		std::cout << "Error: cannot open input file " << fileName << std::endl;
	}
	in.close();

}


std::vector<std::string> splitString(std::string s) {
	std::regex regex1(" ");
	std::vector<std::string> out(
		std::sregex_token_iterator(s.begin(), s.end(), regex1, -1),
		std::sregex_token_iterator()
	);

	return out;
}
void readFile(std::string fileName, Cafe& cafe) {
	std::string line;
	unsigned int lineNum = 0;
	Time time = Time(0, 0);
	Event1 event1 = Event1();
	Event2 event2 = Event2();
	Event3 event3 = Event3();
	Event4 event4 = Event4();

	std::ifstream in(fileName);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (lineNum == 0) {
				int tableNum = std::stoi(line);
				cafe.createTables(tableNum);

			}
			else if (lineNum == 1) {

				cafe.setStartTime(stringToTime((splitString(line))[0]));
				cafe.setEndTime(stringToTime(splitString(line)[1]));
				std::cout << cafe.getStartTime() << std::endl;
			}
			else if (lineNum == 2) {
				cafe.setPrice(std::stoi(line));
			}
			else {
				std::cout << line << std::endl;
				std::vector<std::string> data = splitString(line);
				int id = std::stoi(data[1]);
				if (id == 1) {
					event1 = Event1(data);
					std::cout << event1.reactionOnEvent(cafe);

				}
				else if (id == 2) {
					event2 = Event2(data);
					std::cout << event2.reactionOnEvent(cafe);
				}
				else if (id == 3) {
					event3 = Event3(data);
					std::cout << event3.reactionOnEvent(cafe);
				}
				else if (id == 4) {
					event4 = Event4(data);
					std::cout << event4.reactionOnEvent(cafe);
				}

			}

			lineNum++;
		}

	}
	in.close();
	cafe.closeCafe();
	std::cout << cafe.getTablesInfo();

}

Cafe::Cafe() {

	tableNum = 0;
	startTime = Time(0, 0);
	endTime = Time(0, 0);
	price = 0;
	queue.resize(0);

}


void Cafe::createTables(int n) {
	tableNum = n;
	tables = std::vector<Table>(tableNum);
	for (int i = 0; i != tables.size(); i++) {
		tables[i].setTableNumber(i);
	}
}

bool Cafe::chekTableisFree(int num) {
	return !tables[num].getStatus();
}

int Cafe::chekFreeTable() {
	for (int i = 0; i != tables.size(); i++) {
		if (!tables[i].getStatus()) return i;
	}
	return -1;
}

bool Cafe::checkIsHere(std::string name) {
	bool flag = 0;
	for (int i = 0; i != tables.size(); i++)
		if (tables[i].getClient().getName() == name) flag = 1;

	for (auto i = allClients.begin(); i != allClients.end(); ++i) {
		if (i->getName() == name) flag = 1;
	}
	for (auto i = queue.begin(); i != queue.end(); ++i) {
		if (i->getName() == name) flag = 1;
	}
	return flag;
}
bool Cafe::checkWorkTime(Time t) {

	if (t.hour < startTime.hour || (t.hour < startTime.hour && t.min < startTime.min)) return 1;
	else return 0;
}
bool Cafe::checkFreeTable() {
	bool flag = 0;
	for (int i = 0; i != tables.size(); i++) if (!tables[i].getStatus()) flag = 1;
	return flag;
}
int Cafe::checkQueueSize() {
	if (queue.size() > tables.size()) return -1;
	else if (queue.size() == tables.size()) return 0;
	else return 1;
}
Client Cafe::getClient(std::string name) {
	Client cl = Client();

	for (auto i = allClients.begin(); i != allClients.end(); ++i) {
		if (i->getName() == name) cl = *i;
	}
	for (auto i = queue.begin(); i != queue.end(); ++i) {
		if (i->getName() == name) cl = *i;
	}
	for (int i = 0; i != tables.size(); i++)
		if (tables[i].getClient().getName() == name) cl = tables[i].getClient();

	return cl;
}
Client Cafe::getClientFromQueue(std::string name) {
	Client cl;
	for (auto i = queue.begin(); i != queue.end(); ++i) {
		if (i->getName() == name) cl = *i;
	}

	return cl;
}
Client Cafe::getFirstInQueue() {
	return queue.front();
}
Time Cafe::getStartTime() {
	return startTime;
}
Time Cafe::getEndTime() {
	return endTime;
}
std::list<Client> Cafe::getQueue() {
	return queue;
}
unsigned int Cafe::getPrice() {
	return price;
}
void Cafe::setPrice(unsigned int p) {
	price = p;
}
void Cafe::setStartTime(Time st) {
	startTime = st;
}
void Cafe::setEndTime(Time et) {
	endTime = et;
}
int Cafe::sitClientAtTable(Client client, int tableNum) {
	if (tables[tableNum].getStatus()) return -1;
	else {
		tables[tableNum].addClient(client);
		tables[tableNum].setStatus(true);
		return 1;
	}
}
void Cafe::setClientOnQueue(Client c) {

	c.setInQueue(true);
	queue.push_back(c);


}
void Cafe::setClientOnAllClients(Client c) {

	Cafe::allClients.push_back(c);


}

void Cafe::deleteFromQueue(Client c) {
	std::list<Client>::iterator it;
	bool itNotEmpty = 0;
	for (auto i = queue.begin(); i != queue.end(); ++i) {
		if (*i == c) {
			it = i;
			itNotEmpty = 1;
		}
	}
	if (itNotEmpty) queue.erase(it);
}
void Cafe::deleteFromAllClients(Client c) {
	std::list<Client>::iterator it;
	bool itNotEmpty = 0;
	for (auto i = allClients.begin(); i != allClients.end(); ++i) {
		if (*i == c) {
			it = i;
			itNotEmpty = 1;
		}
	}
	if (itNotEmpty) allClients.erase(it);
}
void Cafe::cleanTable(int num, Time endTime) {

	tables[num].countRev(price, endTime);
	tables[num].countTime(endTime);
	tables[num].clean();
}

void Cafe::clientGone(Client client) {
	if (client.getInQueue() == 1) deleteFromQueue(client);
	deleteFromAllClients(client);
}
void Cafe::closeCafe() {

	for (int i = 0; i != tables.size(); i++) {
		if (tables[i].getStatus() != 0) cleanTable(i, endTime);
	}

	allClients.sort();

	for (auto i = allClients.begin(); i != allClients.end(); i++) {
		std::cout << endTime << "11 " << i->getName() << std::endl;
	}
	std::cout << endTime << std::endl;
}
std::string Cafe::getTablesInfo() {
	std::string str = "";
	for (int i = 0; i != tables.size(); i++) {
		str += std::to_string(i + 1) + " " + tables[i].getWorkTime().toString() + " " + std::to_string(tables[i].getRev()) + "\n";
	}

	return str;
}
