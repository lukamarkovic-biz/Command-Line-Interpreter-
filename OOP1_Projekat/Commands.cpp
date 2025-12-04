#include <filesystem>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>
#include <fstream>
#include <cstdio>

#include "Interpreter.h"
#include "Commands.h"
#include "Exceptions.h"

//class Date

void Date::process(Stream* in, Stream* out){
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    std::ostringstream oss; // Kreiranje string stream-a
    oss << std::setfill('0') << std::setw(2) << now->tm_mday << '-'
        << std::setw(2) << (now->tm_mon + 1) << '-'
        << now->tm_year + 1900;
    out->writeLine(oss.str());
}

//class Time

void Time::process(Stream* in, Stream* out) {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    std::ostringstream oss; // Kreiranje string stream-a
    oss << std::setfill('0') << std::setw(2) << now->tm_hour << ':'
        << std::setw(2) << now->tm_min << ':'
        << std::setw(2) << now->tm_sec;
    out->writeLine(oss.str());
}

//class Echo


void Echo::process(Stream* in, Stream* out) {
    while (!in->isEOF()) {
        out->writeLine(in->getLine());
    }
}

//class Touch

void Touch::process(Stream* in, Stream* out) {
    std::string name = in->getLine();
    if (std::filesystem::exists(name)) {
        throw FileCommandException("File already exists");
    }
    std::ofstream file(name);
    file.close();
}

//class Wc

void Wc::process(Stream* in, Stream* out) {
    if (opt[0][1] == 'w')
        Wc::countWords(in, out);
    else if (opt[0][1] == 'c') Wc::countCharacters(in, out);
    else throw OptionException("Unknown option");
}

void Wc::countCharacters(Stream* in, Stream* out) {
    int cnt = 0;
    while (!in->isEOF()) {
        cnt += in->getLine().length();
    }
    out->writeLine(std::to_string(cnt));
}

void Wc::countWords(Stream* in, Stream* out) {
    int cnt = 0;
    while(!in->isEOF()) {
        bool fl = true;
        std::string line = in->getLine();
        for (int j = 0; j < line.length(); j++) {
            if (!std::isspace(line[j]) && fl) {
                cnt++;
                fl = false;
            }
            else if (std::isspace(line[j])) {
                fl = true;
            }
        }
    }
    out->writeLine(std::to_string(cnt));
}

//class Prompt

void Prompt::process(Stream* in, Stream* out) {
    Interpreter::Instance()->setPrompt(in->getLine());
}


//class Trunctate
void Truncate::process(Stream* in, Stream* out) {
    std::string name = in->getLine();
    if (!std::filesystem::exists(name)) {
        throw FileCommandException("File doesn't exist");
    }
    std::ofstream file(name, std::ios::trunc);
    file.close();
}

//class Rm

void Rm::process(Stream* in, Stream* out) {
    std::string name = in->getLine();
    if (!std::filesystem::exists(name)) {
        throw FileCommandException("File doesn't exist");
    }
    !std::filesystem::remove(name);
}

//class Tr

Tr::Tr(std::vector<std::string> opt){
    if (opt.size() == 1) {
        what = opt[0];
        with = "";
    }
    else if (opt.size() == 2) {
        what = opt[0];
        with = opt[1];
    }
    else if (opt.size() == 3) {
        what = opt[1];
        with = opt[2];
    }
    else throw SyntaxException("What cannot be \"\"");
}

void Tr::process(Stream* in, Stream* out) {
    std::string s;
    while(!in->isEOF()) {
        s = in->getLine();
        size_t pos = 0;
        while ((pos = s.find(what, pos)) != std::string::npos) {
            s.replace(pos, what.length(), with);
            pos += with.length();
        }
        out->writeLine(s);
    } 
}

//class Head

void Head::process(Stream* in, Stream* out) {
    int n = std::stoi(opt[0].substr(2, opt[0].length()));
    for (int i = 0; i < n; i++) {
        out->writeLine(in->getLine());
    }
}

//class Batch

void Batch::process(Stream* in, Stream* out){
    while (!in->isEOF()) {
        std ::string s = in->getLine();
        Interpreter::Instance()->run(s);
    }
}
