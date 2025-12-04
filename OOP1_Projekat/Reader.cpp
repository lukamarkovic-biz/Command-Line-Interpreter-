#include "Reader.h"
#include <iostream>
//class Reader

std::string Reader::getLine() {
	std::string input = "";
	int i = 0;
	char c;
	while ((c = getc(stdin)) != '\n') {
		if (i < 512) {
			input.push_back(c);
			i++;
		}
	}
	return input;
}

std::string Reader::getText() {
	std::string input = "";
	int i = 0;
	char c;
	while ((c = getc(stdin)) != EOF) {
		if (i < 512) {
			input.push_back(c);
			i++;
		}
		if (c == '\n') {
			i = 0;
		}
	}
	return input.substr(0, input.length() - 1);
}