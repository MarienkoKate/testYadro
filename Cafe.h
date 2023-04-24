#ifndef _CAFE_H_
#define _CAFE_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <regex>
#include <list>
#include "Client.h"
#include "Time.h"
#include "Table.h"

class Cafe {

private:

	Time startTime;
	Time endTime;

	unsigned int priñe;
	unsigned int tableNum;

	std::vector<Table> tables;
	std::list<Client> allClients;
	std::list<Client> queue;


public:
	Cafe();
	void createTables(int n);
	bool chekTableisFree(int num);
	int chekFreeTable();
	bool checkIsHere(std::string name);
	bool checkWorkTime(Time t);
	bool checkFreeTable();
	int checkQueueSize();
	Client getClient(std::string name);
	Client getClientFromQueue(std::string name);
	Client getFirstInQueue(); 
	Time getStartTime(); 
	Time getEndTime();
	std::list<Client> getQueue();
	unsigned int getPrice();
	void setPriñe(unsigned int p);
	void setStartTime(Time st);
	void setEndTime(Time et);
	int sitClientAtTable(Client client, int tableNum);
	void setClientOnQueue(Client c);
	void setClientOnAllClients(Client c);
	void deleteFromQueue(Client c);
	void deleteFromAllClients(Client c);
	void cleanTable(int num, Time endTime);
	void clientGone(Client client);
	void closeCafe();
	std::string getTablesInfo();
};

Time stringToTime(std::string s);
void chekFile(std::string fileName);
std::vector<std::string> splitString(std::string s);
void readFile(std::string fileName, Cafe& cafe);
#endif