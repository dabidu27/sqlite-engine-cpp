#pragma once
#include "CommandType.h"
#include <string>


class CommandParser {

	public:
		CommandType recognizeCommand(std::string command);
		char** tokenizeCommand(std::string command, int& n_tokens);
		bool validateCommand(std::string command);
		bool validateCreateTable(std::string command);

};