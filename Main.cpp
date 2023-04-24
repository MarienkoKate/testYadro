#include "Cafe.h"

int main(int argc, char* argv[]) {
	Cafe c;
	try {
		chekFile(argv[1]);
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		exit(0);
	}
	readFile(argv[1], c);
	
	return 0;
}