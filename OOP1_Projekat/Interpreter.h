#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "Commands.h"
#include "Parsers.h"
#include "Checkers.h"

class Interpreter {
public:
    // Returns the singleton instance of Interpreter
    static Interpreter* Instance();

    // Prints the prompt sign to indicate readiness
    void ready();

    // Executes a command line from the console
    void run(std::string line);

    // Sets the prompt string
    void setPrompt(std::string prompt);

protected:
    // Constructor is protected for Singleton pattern
    Interpreter();

private:
    // The prompt string shown to the user
    std::string prompt;

    // Creates a vector of Command objects from parsed CommandInfo
    std::vector<Command*> pipeLine(std::vector<CommandInfo> infos);

    // Creates a single Command object based on CommandInfo
    Command* createCommand(CommandInfo info);

    // Maps command names to factory functions that create commands
    std::unordered_map<std::string, std::function<Command* (CommandInfo info)>> factories;

    // Maps command names to factory functions that create input streams
    std::unordered_map<std::string, std::function<InputStream* (CommandInfo info)>> inputFactories;

    // Maps command names to factory functions that create checker objects
    std::unordered_map<std::string, std::function<Checker* ()>> checkerFactories;
};

inline void Interpreter::setPrompt(std::string prompt) {
    this->prompt = prompt;
}
