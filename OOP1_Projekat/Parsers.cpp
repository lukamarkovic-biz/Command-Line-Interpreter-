#include "Parsers.h"
#include "Reader.h"

std::vector<std::string> Parser::splitString(std::string line) {
    std::vector<std::string> result;
    std::string token;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == '"') {
            inQuotes = !inQuotes;
 //           continue; // ne dodaj navodnik u token
        }

        if (!inQuotes) {
            if (std::isspace(c)) {
                if (!token.empty()) {
                    result.push_back(token);
                    token.clear();
                }
                continue;
            }

            // Proveri redirekcione znakove
            if (c == '>' || c == '<') {
                std::string redirect;
                redirect.push_back(c);

                // Ako je >>, spojimo
                if (c == '>' && i + 1 < line.size() && line[i + 1] == '>') {
                    redirect.push_back('>');
                    i++;
                }

                // preskoèi eventualne praznine i prilepi prvi desni token
                size_t j = i + 1;
                while (j < line.size() && std::isspace(line[j])) j++;

                std::string nextToken;
                while (j < line.size() && !std::isspace(line[j])) {
                    nextToken.push_back(line[j]);
                    j++;
                }

                if (!nextToken.empty()) {
                    redirect += nextToken;
                    i = j - 1;
                }

                if (!token.empty()) {
                    result.push_back(token);
                    token.clear();
                }
                result.push_back(redirect);
                continue;
            }
        }

        token.push_back(c);
    }

    if (!token.empty()) {
        result.push_back(token);
    }

    return result;
}

std::vector<std::string> Parser::pipeParse(std::string line)
{
    std::vector<std::string> inputs = {};
    std::string part = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '|'){
            inputs.push_back(part);
            part = "";
        }
        else {
            part += line[i];
        }
    }
    inputs.push_back(part);
    return inputs;
}

std::string Parser::commandParse(std::vector<std::string>& tokens){
    if (tokens.empty()) {
        return {};
    }
    std::string first = tokens.front();
    tokens.erase(tokens.begin());
    return first;
}

std::vector<std::string> Parser::optionsParse(std::vector<std::string>& tokens)
{
    std::vector<std::string> options;
    auto it = tokens.begin();

    while (it != tokens.end() && !it->empty() && (*it)[0] == '-') {
        std::string opt = *it;
        opt.erase(0, 1); // uklanja prvi karakter '-'
        options.push_back(*it);
        it = tokens.erase(it); // uklanja iz originalnog vektora
    }

    return options;
}

std::string Parser::argumentParse(std::vector<std::string>& tokens) {
    std::vector<std::string> options;
    auto it = tokens.begin();

    if (it != tokens.end() && !it->empty() && ((*it)[0] != '"') && ((*it)[0] != '<') && ((*it)[0] != '>')) {
        std::string opt = *it;
        it = tokens.erase(it);
        return opt;
    }

    return "";
}


std::vector<std::string> Parser::inlineParse(std::vector<std::string>& tokens){
    std::vector<std::string> inlines;
    auto it = tokens.begin();

    while (it != tokens.end() && !it->empty() && (*it)[0] == '"') {
        std::string opt = *it;
        inlines.push_back(it->substr(1, it->size() - 2));
        it = tokens.erase(it); // uklanja iz originalnog vektora
    }
    return inlines;
}

std::string Parser::inputParse(std::vector<std::string>& tokens) {
    std::string input;

    if (tokens.size() == 1 && (tokens[0][0] == '<')) {
        input = tokens[0];
        tokens.erase(tokens.begin());
    }
    else if (tokens.size() >= 2) {
        if (tokens[0][0] == '<') {
            input = tokens[0];
            tokens.erase(tokens.begin());
        }
        else if (tokens[1][0] == '<') {
            input = tokens[0];
            tokens.erase(tokens.begin());
        }
    }
    if (!input.empty()) {
        input = input.substr(1);
    }
    return input;
}

std::string Parser::outputParse(std::vector<std::string>& tokens, bool *append)
{
    std::string output;

    if (tokens.size() == 1 && (tokens[0][0] == '>')) {
        output = tokens[0];
        tokens.erase(tokens.begin());
    }
    else if (tokens.size() >= 2) {
        if (tokens[0][0] == '>') {
            output = tokens[0];
            tokens.erase(tokens.begin());
        }
        else if (tokens[1][0] == '>') {
            output = tokens[0];
            tokens.erase(tokens.begin());
        }
    }
    if (!output.empty()) {
        output = output.substr(1);
        if (output[0] == '>') {
            *append = true;
            output = output.substr(1);
        }
    }
    return output;
}

std::vector<CommandInfo> Parser::parseLine(std::string line)
{
    std::vector<std::string> pipes = pipeParse(line);
    std::vector<CommandInfo> infos = {};
    for (int i = 0; i < pipes.size(); i++) {
        CommandInfo s;
        s.tokens = splitString(pipes[i]);
        s.name = commandParse(s.tokens);
        s.options = optionsParse(s.tokens);
        s.fileName = argumentParse(s.tokens);
        s.inLine = inlineParse(s.tokens);
        s.inputRedirect = inputParse(s.tokens);
        s.outputRedirect = outputParse(s.tokens, &s.append);
        s.isPipedInput = i != 0;
        s.isPipedOutput = i != pipes.size() - 1;
        infos.push_back(s);
    }
    return infos;
}
