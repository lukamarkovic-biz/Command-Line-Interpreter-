
#define modelReader_h

//Maximum length of command
#define CMDLINEMAX 513

#include <string>
#include <vector>
#include <iostream>

class ModelReader {
public:
	//Gets a line from console
	virtual void scanLine();

	//Calls apropirate command
	virtual void processLine();

protected:
private:
	static char cmdLine [CMDLINEMAX];
};

class ModelParser {
public:
	//Extracts vector of needed info from string
	virtual void extract();

protected:
private:
	static std::vector<char*> info;
};

class ModelCommand {
public:
	//Processes given option and argument
	virtual void process(char* arg);

protected:
	std::ostream* out;
	std::istream* in;
private:
};

