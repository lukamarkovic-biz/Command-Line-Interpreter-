#pragma once
#include <exception>
#include <string>

// Osnovna klasa izuzetka za komande
class CommandException : public std::exception {
protected:
    std::string message;
public:
    CommandException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

// Greška u opcijama komande
class OptionException : public CommandException {
public:
    OptionException(const std::string& msg) : CommandException("Option Error: " + msg) {}
};

// Greška u argumentima komande
class ArgumentException : public CommandException {
public:
    ArgumentException(const std::string& msg) : CommandException("Argument Error: " + msg) {}
};

// Greška u redirekciji ulaza/izlaza
class RedirectionException : public CommandException {
public:
    RedirectionException(const std::string& msg) : CommandException("Redirection Error: " + msg) {}
};

// Greška sintakse (npr. pogrešan redosled tokena)
class SyntaxException : public CommandException {
public:
    SyntaxException(const std::string& msg) : CommandException("Syntax Error: " + msg) {}
};

// Greška kada komanda ne postoji ili nije implementirana
class UnknownCommandException : public CommandException {
public:
    UnknownCommandException(const std::string& msg) : CommandException("Unknown Command: " + msg) {}
};

class FileCommandException : public CommandException {
public:
    FileCommandException(const std::string& msg) : CommandException("File error: " + msg) {}
};
