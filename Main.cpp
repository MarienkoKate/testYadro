#define _CRT_SECURE_NO_WARNINGS
#define EXIT_SUCCESS
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <regex>
#include <algorithm>
#include "Cafe.h"
#include "Event1.h"
#include "Event2.h"
#include "Event3.h"
#include "Event4.h"
#include <cassert>

void chekFile(std::string fileName) {
	
	//std::string str = "08:48 1 client1";

	std::regex time("^(([0,1][0-9])|(2[0-3])):[0-5][0-9]\\s\(([0,1][0-9])|(2[0-3])):[0-5][0-9]$");
	std::regex number(R"(^\d*$)");
	std::string r; //= //"^(([0,1][0-9])|(2[0-3])):[0-5][0-9]\\s\[1-4]\\s\[a-z0-9_-]+(\\s\[1-" + z + "]|$)$";
	
	

	std::string line;
	unsigned int lineNum = 1;

	//r = "^(([0,1][0-9])|(2[0-3])):[0-5][0-9]\\s\[1-4]\\s\[a-z0-9_-]+(\\s\[1-3]|$)$";
	std::ifstream in(fileName);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (lineNum == 1) {
				if (!regex_match(line, number)) {
					std::string ex = "invalid value in line " + std::to_string(lineNum);
				
					char* cstr = new char[ex.length() + 1];
					strcpy(cstr, ex.c_str());
					// do stuff
					throw std::exception(cstr);
					delete[] cstr;
				
				}
				r = "^(([0,1][0-9])|(2[0-3])):[0-5][0-9]\\s\[1-4]\\s\[a-z0-9_-]+(\\s\[1-" + line + "]|$)$";
				
			}
			else if (lineNum == 2) {
				if (!regex_match(line, time)) throw std::exception("invalid value in line " + lineNum);
			}
			else if (lineNum == 3) {
				if (!regex_match(line, number)) std::cout << "invalid value in line " + std::to_string(lineNum) << std::endl;//throw("invalid value in line " + lineNum);
			}
			else {
				if (!regex_match(line, std::regex(r))) std::cout << "invalid value in line " + lineNum << std::endl;//throw("invalid value in line " + lineNum);
			}

			lineNum++;
		}

	}
	in.close();
	
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
				cafe.setPriñe(std::stoi(line));
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

int main() {
	Cafe c;
	try {
		chekFile("cafffe.txt");
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		exit(0);
	}
	readFile("cafffe.txt", c);
	
	///return 0;
}