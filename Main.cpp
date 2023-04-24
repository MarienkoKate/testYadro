#include "Cafe.h"

int main(int argc, char* argv[]) {
	Cafe c;
	
    	if (argc < 2) {
	    std::cout << "not enough arguments to call" << std::endl;
	    exit(1);
	}
	try {
		std::string fileName = argv[1];
		chekFile(fileName);
		readFile(fileName, c);
	}
	catch (const std::string& e) {
		std::cerr << e << std::endl;
		exit(1);
	}
	
	
}
