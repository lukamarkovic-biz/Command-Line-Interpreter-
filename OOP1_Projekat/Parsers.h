#define parsers_h
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>


//class Parser
struct CommandInfo {
	std::string name;                  
	std::string fileName;
	std::vector<std::string> tokens;    
	std::vector<std::string> options;   
	std::vector<std::string> inLine;	
	std::string inputRedirect;          
	std::string outputRedirect;         
	bool append = false;                
	bool isPipedInput;
	bool isPipedOutput;
};

class Parser {
public:
    // Splits a given string into tokens (by whitespaces and quotes)
    static std::vector<std::string> splitString(std::string line);

    // Splits a command line into separate commands based on pipes ("|")
    static std::vector<std::string> pipeParse(std::string line);

    // Extracts the command name from tokens
    static std::string commandParse(std::vector<std::string>& tokens);

    // Extracts command options (tokens starting with "-")
    static std::vector<std::string> optionsParse(std::vector<std::string>& tokens);

    // Extracts a single argument (if present)
    static std::string argumentParse(std::vector<std::string>& tokens);

    // Extracts input redirection ("< filename")
    static std::string inputParse(std::vector<std::string>& tokens);

    // Extracts inline arguments (e.g., for commands like "tr a b")
    static std::vector<std::string> inlineParse(std::vector<std::string>& tokens);

    // Extracts output redirection ("> filename" or ">> filename")
    // Sets *append = true if ">>" is detected
    static std::string outputParse(std::vector<std::string>& tokens, bool* append);

    // Parses the full line into a list of CommandInfo objects (for pipelines)
    static std::vector<CommandInfo> parseLine(std::string line);
};

#endif