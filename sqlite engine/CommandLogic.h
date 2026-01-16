#pragma once
#include <string>
#include "CommandType.h"
#include "CommandParser.h"
#include "Database.h"

class CommandLogic {


	protected:

		std::string* tokens = nullptr;
		int n_tokens = 0;

	public:

		CommandLogic(std::string* tokens, int n_tokens);
		virtual void implementLogic(Database& db) = 0;

};


class CreateTable : public CommandLogic {

	public:

		CreateTable(std::string* tokens, int n_tokens);
		void implementLogic(Database& db);
};

class DropTable : public CommandLogic {

	public:

		DropTable(std::string* tokens, int n_tokens);
		void implementLogic(Database& db);
};

class Insert : public CommandLogic {

public:

	Insert(std::string* tokens, int n_tokens);
	void implementLogic(Database& db);
};


class DisplayTable : public CommandLogic {

private:

	static int NO_DISPLAY_COMMANDS;
public:

	DisplayTable(std::string* tokens, int n_tokens);
	void implementLogic(Database& db);
	std::string getNoDisplays();
};

class Delete : public CommandLogic {

public:

	Delete(std::string* tokens, int n_tokens);
	void implementLogic(Database& db);
};