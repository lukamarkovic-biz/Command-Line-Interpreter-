#include "Streams.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "Exceptions.h"

//class Stream
std::string Stream::getLine() {
	if (i < arg.size()) {
		return arg[i++];
	}
	return "";
}

void Stream::writeLine(std::string line) {
	arg.push_back(line);
}

bool Stream::isEOF() {
	return i == arg.size();
}

//class InputStream

InputStream::InputStream(CommandInfo info){
	i = 0;
	std::string s;
	std::istream* input;
	std::ifstream file;
	if (info.inLine.size() == 1){
		arg.push_back(info.inLine[0]);
		return;
	}
	if (!info.inputRedirect.empty()) {
		if (!std::filesystem::exists(info.inputRedirect)) {
			throw FileCommandException("File doesn't exist");
		}
		file = std::ifstream(info.inputRedirect);
		input = &file;
	}
	else if (!info.fileName.empty()) {
		if (!std::filesystem::exists(info.fileName)) {
			throw FileCommandException("File doesn't exist");
		}
		file = std::ifstream(info.fileName);
		input = &file;
	}
	else {
		input = &std::cin;
	}
	while (std::getline(*input, s)) {
        arg.push_back(s);
    }
}

//class OutputStream

OutputStream::OutputStream(CommandInfo info){
	fileName = info.outputRedirect;
	append = info.append;
}

void OutputStream::flush(){
	std::ostream* destination;
	std::fstream file;
	if (fileName == "") {
		destination = &std::cout;
	}
	else {
		if (append) {
			file.open(fileName, std::ios::out | std::ios::app);
		}
		else {
			file.open(fileName, std::ios::out | std::ios::trunc);
		}
		destination = &file;
	}
	for (int i = 0; i < arg.size(); i++) {
		(*destination) << arg[i];
		if ((i != (arg.size() - 1)) || fileName.empty()) {
			(*destination) << std::endl;
		}
	}
	file.close();
}

//class InputStreamTr

InputStreamTr::InputStreamTr(CommandInfo info){
	i = 0;
	std::string s;
	std::istream* input;
	std::ifstream file;
	if (info.inLine.size() == 3) {
		arg.push_back(info.inLine[0]);
		return;
	}
	if (!info.inputRedirect.empty()) {
		if (!std::filesystem::exists(info.inputRedirect)) {
			throw FileCommandException("File doesn't exist");
		}
		file = std::ifstream(info.inputRedirect);
		input = &file;
	}
	else if (!info.fileName.empty()) {
		if (!std::filesystem::exists(info.fileName)) {
			throw FileCommandException("File doesn't exist");
		}
		file = std::ifstream(info.fileName);
		input = &file;
	}
	else {
		input = &std::cin;
	}
	while (std::getline(*input, s)) {
		arg.push_back(s);
	}
}

InputStreamFile::InputStreamFile(CommandInfo info){
	arg.push_back(info.fileName);
}
