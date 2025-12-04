#include "Interpreter.h"
#include "Streams.h"
#include "Commands.h"
#include "Exceptions.h"

#include <iostream>
#include <vector>

//class Interpreter

Interpreter::Interpreter() :prompt("$") {
	factories["echo"] = [](CommandInfo info) { return new Echo(); };
	factories["prompt"] = [](CommandInfo info) { return new Prompt(); };
	factories["time"] = [](CommandInfo info) { return new Time(); };
	factories["date"] = [](CommandInfo info) { return new Date(); };
	factories["touch"] = [](CommandInfo info) { return new Touch(); };
	factories["truncate"] = [](CommandInfo info) { return new Truncate(); };
	factories["rm"] = [](CommandInfo info) { return new Rm(); };
	factories["wc"] = [](CommandInfo info) { return new Wc(info.options); };
	factories["tr"] = [](CommandInfo info) { return new Tr(info.inLine); };
	factories["head"] = [](CommandInfo info) { return new Head(info.options); };
	factories["batch"] = [](CommandInfo info) { return new Batch(); };

	inputFactories["echo"] = [](CommandInfo info) { return new InputStream(info); };
	inputFactories["prompt"] = [](CommandInfo info) { return new InputStream(info); };
	inputFactories["time"] = [](CommandInfo info) { return nullptr; };
	inputFactories["date"] = [](CommandInfo info) { return nullptr; };
	inputFactories["touch"] = [](CommandInfo info) { return new InputStreamFile(info); };
	inputFactories["truncate"] = [](CommandInfo info) { return new InputStreamFile(info); };
	inputFactories["rm"] = [](CommandInfo info) { return new InputStreamFile(info); };
	inputFactories["wc"] = [](CommandInfo info) { return new InputStream(info); };
	inputFactories["tr"] = [](CommandInfo info) { return new InputStreamTr(info); };
	inputFactories["head"] = [](CommandInfo info) { return new InputStream(info); };
	inputFactories["batch"] = [](CommandInfo info) { return new InputStream(info); };

	checkerFactories["echo"] = []() { return new EchoChecker(); };
	checkerFactories["prompt"] = []() { return new PromptChecker(); };
	checkerFactories["time"] = []() { return new TimeChecker(); };
	checkerFactories["date"] = []() { return new DateChecker(); };
	checkerFactories["touch"] = []() { return new TouchChecker(); };
	checkerFactories["truncate"] = []() { return new TruncateChecker(); };
	checkerFactories["rm"] = []() {  return new RmChecker();  };
	checkerFactories["wc"] = []() { return new WcChecker(); };
	checkerFactories["tr"] = []() { return new TrChecker(); };
	checkerFactories["head"] = []() { return new HeadChecker(); };
	checkerFactories["batch"] = []() { return new BatchChecker(); };



}

Interpreter* Interpreter::Instance() {
	static Interpreter instance;
	return &instance;
}

void Interpreter::ready() {
	std::cout << prompt << " ";
}

std::vector<Command*> Interpreter::pipeLine(std::vector<CommandInfo> infos) {
	std::vector<Command*> comms;
	for (int i = 0; i < infos.size(); i++) {
		comms.push_back(createCommand(infos[i]));
	}
	return comms;
}

Command* Interpreter::createCommand(CommandInfo info){
	auto it = factories.find(info.name);
	if (it == factories.end()) {
		throw UnknownCommandException(info.name);
	}
	Checker* ch = checkerFactories[info.name]();
	ch->check(info);
	return it->second(info);
}

void Interpreter::run(std::string line) {
	Command* inputCommand = nullptr;
	InputStream* input = nullptr;
	OutputStream* output = nullptr;
	Stream* in = nullptr;
	Stream* out = nullptr;
	std::vector<Command*> comms;

	try {
		std::vector<CommandInfo> infos = Parser::parseLine(line);
		for (auto& info : infos) comms.push_back(createCommand(info));

		input = inputFactories[infos[0].name](infos[0]);
		output = new OutputStream(infos.back());

		if (infos.size() == 1) {
			comms[0]->process(input, output);
		}
		else {
			in = new Stream();
			out = new Stream();
			comms[0]->process(input, out);
			for (size_t i = 1; i < comms.size() - 1; ++i) {
				delete in;
				in = out;
				out = new Stream();
				comms[i]->process(in, out);
			}
			comms.back()->process(out, output);
		}
		output->flush();
		std::cin.clear();
	}
	catch (CommandException& e) {
		std::cerr << e.what() << std::endl;
	}

	delete input;
	delete output;
	delete in;
	delete out;
	for (auto* cmd : comms) delete cmd;
}
