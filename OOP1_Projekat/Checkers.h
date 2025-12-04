#pragma once
#include <string>
#include <vector>
#include <memory>
#include <set>

#include "Parsers.h"     
#include "Exceptions.h" 

class Checker {
public:
    virtual void check(const CommandInfo& info) {
        if (info.isPipedInput && (!info.fileName.empty() || !info.inLine.empty() || !info.inputRedirect.empty())) {
            throw RedirectionException("Can't use input redirection or inline args for piped input.");
        }
        if(info.isPipedOutput && !info.outputRedirect.empty()){
            throw RedirectionException("Can't use output redirection for piped input");
        }
    }
    virtual ~Checker() = default;
};


class DateChecker : public Checker { public: void check(const CommandInfo& info) override; };
class TimeChecker : public Checker { public: void check(const CommandInfo& info) override; };
class EchoChecker : public Checker { public: void check(const CommandInfo& info) override; };
class PromptChecker : public Checker { public: void check(const CommandInfo& info) override; };

class TouchChecker : public Checker { public: void check(const CommandInfo& info) override; };
class TruncateChecker : public Checker { public: void check(const CommandInfo& info) override; };
class RmChecker : public Checker { public: void check(const CommandInfo& info) override; };

class WcChecker : public Checker { public: void check(const CommandInfo& info) override; };
class TrChecker : public Checker { public: void check(const CommandInfo& info) override; };
class HeadChecker : public Checker { public: void check(const CommandInfo& info) override; };
class BatchChecker : public Checker { public: void check(const CommandInfo& info) override; };

