#include "Cafe.h"

Cafe::Cafe() {

	tableNum = 0;
	startTime = Time(0, 0);
	endTime = Time(0, 0);
	priñe = 0;
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
	return priñe;
}
void Cafe::setPriñe(unsigned int p) {
	priñe = p;
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

	tables[num].countRev(priñe, endTime);
	tables[num].countTime(endTime);
	tables[num].clean();
}

void Cafe::clientGone(Client client) {
	if (client.getInQueue() == 1) deleteFromQueue(client);
	deleteFromAllClients(client);
}
void Cafe::closeCafe() {

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