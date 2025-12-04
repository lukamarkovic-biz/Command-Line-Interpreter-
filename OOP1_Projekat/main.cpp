#include "Commands.h"
#include "Interpreter.h"
#include "Reader.h"
using namespace std;


int main() {
	while (true) {
		Interpreter::Instance()->ready();
		std::string line = Reader::getLine();
		Interpreter::Instance()->run(line);
	}

	return 0;
}