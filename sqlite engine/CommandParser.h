#pragma once
#include "CommandType.h"
#include <string>


class CommandParser {

	private:
		std::string command = "";

	public:

		CommandParser(std::string command);
		CommandType recognizeCommand();
		char** tokenizeCommand(int& n_tokens);
		bool validateCommand();

	private:


		bool validateCreateTable();
		bool validateCreateIndex();
		bool validateDropTable();
		bool validateDropIndex();
		bool validateDisplayTable();
};