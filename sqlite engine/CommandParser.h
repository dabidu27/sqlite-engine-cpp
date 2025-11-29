#pragma once
#include "CommandType.h"
#include <string>


class CommandParser {

	private:
		std::string command = "";
		std::string* tokens = nullptr;
		int n_tokens = 0;

	public:

		CommandParser(std::string command);
		CommandType recognizeCommand();
		void tokenizeCommand();
		std::string* getTokens();
		int getNoTokens();
		bool validateCommand();
		~CommandParser();


	private:


		bool validateCreateTable();
		//bool validateCreateIndex();
		bool validateDropTable();
		//bool validateDropIndex();
		bool validateDisplayTable();
		bool validateInsert();
		bool validateDeleteTable();
		bool validateSelect();
		bool validateUpdate();
		
};