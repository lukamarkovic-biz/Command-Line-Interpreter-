#define streams_h
#ifndef STREAMS_H
#define STREAMS_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Parsers.h"

class Stream {
public:
	Stream();
	std::string getLine();
	void writeLine(std::string line);
	bool isEOF();
protected:
	std::vector<std::string> arg;
	int i;
	
};

class InputStream : public Stream{
public:
	InputStream() {};
	InputStream(CommandInfo info);

private:
};

class InputStreamTr : public InputStream {
public:
	InputStreamTr(CommandInfo info);
};

class InputStreamFile : public InputStream {
public:
	InputStreamFile(CommandInfo info);
};

class OutputStream : public Stream{
public: 
	OutputStream(CommandInfo info);
	void flush();
private:
	std::string fileName;
	bool append;
};

inline Stream::Stream() : arg({}), i(0) {}

#endif