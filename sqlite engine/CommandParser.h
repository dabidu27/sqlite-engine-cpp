#pragma once
#include "CommandType.h"
#include <string>


class CommandParser {

	private:

		bool validateCreateTable(std::string command);
		bool validateCreateIndex(std::string command);
		bool validateDropTable(std::string command);

	public:
		CommandType recognizeCommand(std::string command);
		char** tokenizeCommand(std::string command, int& n_tokens);
		bool validateCommand(std::string command);

};