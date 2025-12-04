#include "Checkers.h"
#include <cctype>
#include <algorithm>

// DateChecker
void DateChecker::check(const CommandInfo& info) {

    if (!info.options.empty()) throw OptionException("date does not accept options.");
    if (!info.fileName.empty() || !info.inLine.empty() || !info.inputRedirect.empty()) {
        throw ArgumentException("date does not accept arguments or input redirection.");
    }
}

// TimeChecker
void TimeChecker::check(const CommandInfo& info) {
    if (!info.options.empty()) throw OptionException("time does not accept options.");
    if (!info.fileName.empty() || !info.inLine.empty() || !info.inputRedirect.empty()) {
        throw ArgumentException("time does not accept arguments or input redirection.");
    }
}

// EchoChecker
void EchoChecker::check(const CommandInfo& info) {
    if (!info.options.empty()) throw OptionException("echo does not accept options.");
}

// PromptChecker
void PromptChecker::check(const CommandInfo& info) {
    if (!info.options.empty()) throw OptionException("prompt does not accept options.");
    if (info.inLine.size() != 1) throw ArgumentException("prompt requires exactly one inline argument (in quotes).");
    if (!info.fileName.empty() || !info.inputRedirect.empty()) {
        throw SyntaxException("prompt: bad layout of arguments.");
    }
}

// TouchChecker
void TouchChecker::check(const CommandInfo& info) {
    if (!info.options.empty()) throw OptionException("touch does not accept options.");
    if (info.fileName.empty()) throw ArgumentException("touch requires a filename argument.");
    if (!info.inLine.empty() || !info.inputRedirect.empty()) {
        throw SyntaxException("touch: bad layout of arguments (use filename only).");
    }
}

// TruncateChecker
void TruncateChecker::check(const CommandInfo& info) {
    if (!info.options.empty()) throw OptionException("truncate does not accept options.");
    if (info.fileName.empty()) throw ArgumentException("truncate requires a filename argument.");
    if (!info.inLine.empty() || !info.inputRedirect.empty()) {
        throw SyntaxException("truncate: bad layout of arguments (use filename only).");
    }
}

// RmChecker
void RmChecker::check(const CommandInfo& info) {
    if (!info.options.empty()) throw OptionException("rm does not accept options.");
    if (info.fileName.empty()) throw ArgumentException("rm requires a filename argument.");
    if (!info.inLine.empty() || !info.inputRedirect.empty()) {
        throw SyntaxException("rm: bad layout of arguments (use filename only).");
    }
}

// WcChecker
void WcChecker::check(const CommandInfo& info) {
    if (info.options.size() > 1) throw OptionException("wc accepts at most one option (-w or -c).");
    if (info.options.size() == 1) {
        const std::string& opt = info.options[0];
        if (!(opt == "-w" || opt == "-c")) {
            throw OptionException("wc: invalid option '" + opt + "'. Allowed: -w, -c.");
        }
    }
}

// TrChecker
void TrChecker::check(const CommandInfo& info) {
    if (!info.options.empty()) throw OptionException("tr does not accept options.");

    if (info.inLine.empty()) throw ArgumentException("tr requires at least one inline argument (what).");
    if (info.inLine.size() > 3) throw SyntaxException("tr accepts at most three inline arguments.");

    if (info.isPipedInput && !info.fileName.empty()) {
        throw RedirectionException("tr cannot have both piped input and filename.");
    }
}

// HeadChecker
void HeadChecker::check(const CommandInfo& info) {
    if (info.options.empty()) throw ArgumentException("head requires option -n<count>.");
    if (info.options.size() != 1) throw SyntaxException("head accepts exactly one -n option.");
    const std::string& opt = info.options[0];
    std::string num = opt.substr(2);
    if (num.empty() || num.size() > 5) throw SyntaxException("head: invalid count (must be 1..5 digits).");
    for (char c : num) if (!std::isdigit(static_cast<unsigned char>(c))) throw SyntaxException("head: count must be numeric.");
}

// BatchChecker
void BatchChecker::check(const CommandInfo& info) {
    if (!info.options.empty()) throw OptionException("batch does not accept options.");
    if (info.isPipedInput && (!info.fileName.empty() || !info.inLine.empty())) {
        throw RedirectionException("batch cannot have both piped input and filename/inline argument.");
    }
}