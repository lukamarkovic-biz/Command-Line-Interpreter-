#define commands_h
#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include <iostream>
#include <vector>
#include "Streams.h"

class Command {
public:

	virtual ~Command() = default;

	//Runs the needed command
	virtual void process(Stream* in, Stream* out) = 0;

	//Sets output file name

protected:
private:
};

class OptCommand : public Command {
public:
	OptCommand(std::vector<std::string> opt);
protected:

	//Command option
	std::vector<std::string> opt;

private:
};


class Date : public Command {
public:

	//Prints current date to the output stream
	void process(Stream* in, Stream* out);

protected:
private:
};

class Time : public Command {
public:

	//Prints current time to the output stream
	void process(Stream* in, Stream* out);

protected:
private:
};

class Echo : public Command {
public:

	//Prints input argument to the output stream
void process(Stream* in, Stream* out); 
protected:
private:
};

class Touch : public Command {
public:

	//Creates file with name of argument
void process(Stream* in, Stream* out); 
protected:
private:
};

class Wc : public OptCommand {
public:
	Wc(std::vector<std::string> opt) : OptCommand(opt) {};

	//Counts number of characters or words in arg
	void process(Stream* in, Stream* out);

protected:
private:
	//Counts number of words in arg
	void countWords(Stream* in, Stream* out);
	
	//Counts number of characters in arg
	void countCharacters(Stream* in, Stream* out);
};

class Prompt : public Command {
public:

	void process(Stream* in, Stream* out);

};

class Truncate : public Command {
public:

	void process(Stream* in, Stream* out);
};

class Rm : public Command {
public:

	void process(Stream* in, Stream* out);
};

class Tr : public Command {
public:
	Tr(std::vector<std::string> opt);

	void process(Stream* in, Stream* out);
protected:
private:
	std::string with;
	std::string what;
};

class Head :public OptCommand {
public:
	Head(std::vector<std::string> opt) : OptCommand(opt) {};

	void process(Stream* in, Stream* out);

protected:
private:
};

class Batch : public Command {
public:
	void process(Stream* in, Stream* out);
};


inline OptCommand::OptCommand(std::vector<std::string> opt){
	this->opt = opt;
}


#endif 